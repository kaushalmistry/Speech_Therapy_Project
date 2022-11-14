// Recognition_Module.cpp : Defines the entry point for the console application.
//

// 224101031_DigitRecognition.cpp : Defines the entry point for the console application.
// Name: Kaushal Mistry
// Roll No: 224101031

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Windows.h"
#include <sys/types.h>
#include <direct.h>
#include <string>
#include <time.h>

#define N 5
#define M 32
#define pi 22 / 7
#define p 12
#define frameSize 320
#define epsilon 0.03
#define delta 0.0001
#define T1 160
#define bThreshold 1e-30

// Change this when the number of utterances considered for the training is changed
#define numOfTrainingUtterances 30

// HMM Input parameters
long double A[N + 1][N + 1] = {0};
long double B[N + 1][M + 1] = {0};
long double PI[N + 1] = {0, 1.0, 0, 0, 0, 0};
int Obs_Seq[T1 + 1] = {0};

// HMM related variables
int T = 160;
// Solution to problem 1
long double Alpha[T1 + 1][N + 1] = {0};
long double Beta[T1 + 1][N + 1] = {0};
long double probOfObsGivenLambda = 0;

// Solution to problem 2
long double Gamma[T1 + 1][N + 1] = {0};
long double Delta[T1 + 1][N + 1] = {0};
int Psi[T1 + 1][N + 1] = {0};
long double Pstar = 1e-250;
long double PstarOld = 1;
int QTstar = 0;
int stateSeq[T1 + 1] = {0};

// solution to problem 3
long double Xi[T1 + 1][N + 1][N + 1] = {0};
long double A_[N + 1][N + 1] = {0};
long double B_[N + 1][M + 1] = {0};
long double PI_[N + 1] = {0, 1.0, 0, 0, 0, 0};
char *outputFile = "output_HMM3.txt";
FILE *file;

// Reading the samples into the array
long double samples[40000];
int noOfSamples = 0;
int start = 0;
int end = 0;

// Durbin's parameters
long double CIs[p + 1] = {0}; // CI's
long double E[p + 1] = {0};   // Energy
long double RIs[p + 1] = {0}; // RI's
long double AIs[p + 1][p + 1] = {0};
long double KIs[p + 1];

// Tokhura distance parameters
long double tokhuraWeights[p] = {1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
long double tokhuraDistances[M];

// LBG parameters
long double universe[30000][p] = {0};
long double prevDistortion = 9999;
long double curDistortion = 0;
int universeSize = 1;
long double codeBook[M][p] = {0};
int m = 1; // Current size of the codebook which will be updated in every iteration of the LBG algorithm
FILE *codeBookFp;
FILE *distortionFp;

/**
 * Structer to store the cluster data and its size
 */
struct cluster
{
    int size;
    int items[40000];
};
typedef struct cluster cluster;
// M Clusters to store all the buckets
cluster clusters[M];

// File handling variables
char *universeFile = "files/output/universe.txt";
char inputFile[100] = "digits/0/224101063_0_E_1.txt";
FILE *universeFp;
char *codeBookFile = "files/output/LBG_CodeBooks.txt";
char *distortionFile = "files/output/LBG_Distortion.txt";
char *finalCodeBook = "files/output/codebook.txt";

char *a_file = "files/input/initial_A.txt";
char *b_file = "files/input/initial_B.txt";
char *pi_file = "files/input/initial_PI.txt";
char *obs_seq_file = "HMM_OBSERVATION_SEQUENCE_1.txt";

// intermediate model files
char intermediateModelA[100] = "models/intermediate_models/";
char intermediateModelB[100] = "models/intermediate_models/";
char finalModelA[100] = "models/intermediate_models/";
char finalModelB[100] = "models/intermediate_models/";
FILE *aModelFp;
FILE *bModelFp;

/// ======================================== Words related variables ===========================================
char words[10][10] = {"glasses", "chair", "away"};
long double standardProbabilities[10] = {1};
int noOfWords = 3;
long double maxRecognisedProb = 0;
int recognisedWordIndex = 1;
int curNumberOfWords = 1;
long double tempPercentage = 0;
int percentage = 10;

void readWords() {
    FILE* wordFile = fopen("files/words.txt", "r");

    int count = 0;

    while (!feof(wordFile)) {
        fscanf(wordFile, "%s", words[count]);
        count++;
    }

    noOfWords = count - 1;
    curNumberOfWords = count - 1;

    fclose(wordFile);

    FILE* probFile = fopen("files/standard_word_prob.txt", "r");
    int i = 0;

    while (!feof(probFile) && i < noOfWords) {
        fscanf(probFile, "%Lf", &standardProbabilities[i]);
        i++;
    }

    fclose(probFile);

}

/**
 * Tokhura distance between the code book vector and the vector from universe
 */
long double findTokhuraDistance(int codebookIndex, int universeIndex)
{
    long double distance = 0;
    for (int i = 0; i < p; i++)
    {
        distance += tokhuraWeights[i] * (codeBook[codebookIndex][i] - universe[universeIndex][i]) * (codeBook[codebookIndex][i] - universe[universeIndex][i]);
    }

    return distance;
}

/**
 * Applies the Raised Sine window to the Cepstral coefficients
 */
void applyRaisedSineWindow()
{
    long double wm;
    for (int i = 1; i <= p; i++)
    {
        wm = 1 + (p / 2 * sin((long double)pi * i / p)); // Calculating raised sine window
        CIs[i] = CIs[i] * wm;
    }
}

/**
 * Calculates CI's
 */
void calculateCis()
{
    // utility variables
    int x, k;
    long double sum = 0;

    for (x = 1; x <= p; x++)
    {
        CIs[x] = AIs[x][p];
        for (k = 1; k <= x - 1; k++)
        {
            sum += ((long double)k / x) * CIs[k] * AIs[x - k][p];
        }
        CIs[x] += sum;
        sum = 0;
    }

    // Applies the raised sine window on the calculated CIs
    applyRaisedSineWindow();
}

/**
 * Levension durbins algorithm to calculate AI's
 */
void durbinsAlgo()
{
    // utility variables
    int i, j;
    long double sum = 0;

    // Initialization step
    E[0] = RIs[0];

    for (i = 1; i <= p; i++)
    {
        for (j = 1; j <= i - 1; j++)
        {
            sum += AIs[j][i - 1] * RIs[i - j];
        }
        KIs[i] = (RIs[i] - sum) / E[i - 1];

        AIs[i][i] = KIs[i];

        for (j = 1; j <= i - 1; j++)
        {
            AIs[j][i] = AIs[j][i - 1] - (KIs[i] * AIs[i - j][i - 1]);
        }

        E[i] = (1 - (KIs[i] * KIs[i])) * E[i - 1];
        sum = 0;
    }
}

/**
 * Calculates the RI's for the given frame
 * The frame is specified with the start and end variables
 */
void calculateRis()
{
    int i, j;
    long double sum = 0;

    for (i = 0; i <= p; i++)
    {
        for (j = start; j < end - i; j++)
        {
            sum += samples[j] * samples[j + i];
        }
        RIs[i] = sum;
        sum = 0;
    }
}

/**
 * @brief This is used to store the calculated CIs into universe file
 *
 */
void dumpCIsIntoUniverse()
{
    for (int i = 1; i <= p; i++)
    {
        fprintf(universeFp, "%Lf ", CIs[i]);
    }
    fprintf(universeFp, "\n");
}

/**
 * @brief Applies DC shift to the data
 *
 */
void applyDCShift()
{
    long double mean = 0;

    // Finding the mean from the silence part of first 400 samples
    for (int i = 0; i < 400; i++)
        mean += samples[i];

    mean = mean / 400;

    // Applying the DS Shift by removing the mean from the samples
    for (int i = 0; i < noOfSamples; i++)
        samples[i] = samples[i] - mean;
}

/**
 * @brief Applies normalization to the data
 *
 */
void applyNormalization()
{
    long double maxAmp = 0, wn = 0;
    int i, n;

    for (i = 0; i < noOfSamples; i++)
        maxAmp = fabs(samples[i]) > fabs(maxAmp) ? samples[i] : maxAmp;

    for (i = 0; i < noOfSamples; i++)
    {
        n = 0;

        if (n == frameSize)
            n = 0;

        wn = 0.54 - 0.46 * cos((2 * (long double)pi * n) / (frameSize - 1));

        samples[i] = (samples[i] * 5000.0 / maxAmp) * wn;

        n++;
    }
}

/**
 * Reading the file into the samples array
 */
void readInputFile(char *inputFile)
{
    FILE *fp = fopen(inputFile, "r");
    if (fp == NULL)
    {
        printf("Error while opening the input file: %s\n", inputFile);
        exit(EXIT_FAILURE);
    }
    // Skipping the headers in the file if the header data is not removed from the data
    char ignore[1000];
    for (int i = 0; i < 5; i++)
        fgets(ignore, sizeof(ignore), fp);

    // Reading the inputs
    int i = 0;
    while (!feof(fp) && i < 40000)
    {
        fscanf(fp, "%Lf", &samples[i]);
        i++;
    }
    noOfSamples = i - 1;
    fclose(fp);
}

/**
 * This generates the CIs for every frame of the input file
 */
void generateCIs()
{
    start = 0;
    end = 320;
    while (end <= noOfSamples)
    {
        calculateRis();
        durbinsAlgo();
        calculateCis();
        dumpCIsIntoUniverse();
        start += 80;
        end += 80;
    }
}

/**
 * Creates the universe
 */
void generateUniverse()
{
    remove(universeFile);
    universeFp = fopen(universeFile, "a");
    if (universeFp == NULL)
    {
        printf("Error while opening the input file: %s\n", universeFile);
        exit(EXIT_FAILURE);
    }

    // Looping through 3 words
	for (int word = 1; word <= noOfWords; word++)
	{
		// Looping through 8 utterances
		for (int utterance = 1; utterance <= 30; utterance++)
		{
			// File name format: ST_DataSet/utterance_1_1.txt
			sprintf(inputFile, "ST_DataSet/utterance_%d_%d.txt", word, utterance);

			readInputFile(inputFile);
			// applyDCShift();
			applyNormalization();
			generateCIs();
		}
	}
    
    fclose(universeFp);
}

/**
 * Classify the whole universe into the m buckets based on nearest neighbour rule
 */
void classifyUniverse()
{
    int i, j, clusterIndex = 0;
    long double minDistance = 0;

    // Reinitializing the size of the clusters to 0
    for (i = 0; i < m; i++)
        clusters[i].size = 0;

    // For every vector in the universe find the appropriate cluster
    for (i = 0; i < universeSize; i++)
    {
        // Calculate tokhura distance for every vector with the codebook vectors
        for (j = 0; j < m; j++)
            tokhuraDistances[j] = findTokhuraDistance(j, i);

        // Find the cluster with minimum distance
        clusterIndex = 0;
        minDistance = tokhuraDistances[0];
        for (j = 1; j < m; j++)
        {
            if (tokhuraDistances[j] < minDistance)
            {
                minDistance = tokhuraDistances[j];
                clusterIndex = j;
            }
        }

        // Assign the current vector to the cluster
        clusters[clusterIndex].items[clusters[clusterIndex].size] = i;
        clusters[clusterIndex].size += 1; // Keeping the size of the cluster up-to date
    }
}

/**
 * Computes the centroid of the clusters and updates the codebook vectors
 */
void computeCentroid()
{
    long double sum[p] = {0}; // Finding the sum column wise for every cluster
    for (int i = 0; i < m; i++)
    { // iterating over clusters
        // iterating over all vectors in the specific cluster and summing them up
        for (int j = 0; j < clusters[i].size; j++)
        {
            for (int x = 0; x < p; x++)
            {
                sum[x] += universe[clusters[i].items[j]][x];
            }
        }

        for (int j = 0; j < p; j++)
        {
            codeBook[i][j] = sum[j] / (long double)clusters[i].size;
            sum[j] = 0;
        }
    }
}

/**
 * Dumps codebook vector into the file with the distortion
 */
void dumpCodeBookIntoFile()
{
    int i, j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < p; j++)
        {
            fprintf(codeBookFp, "%Lf ", codeBook[i][j]);
        }
        fprintf(codeBookFp, "\n");
    }

    fprintf(codeBookFp, "The distortion = %Lf \n\n\n", curDistortion);
}

/**
 * Computes the distortion for the current codebook
 */
void computeCurDistortion()
{
    long double distortion = 0;
    long double clusterWiseDistortion;
    int i, j;

    for (i = 0; i < m; i++)
    {
        clusterWiseDistortion = 0;
        for (j = 0; j < clusters[i].size; j++)
        {
            clusterWiseDistortion += findTokhuraDistance(i, clusters[i].items[j]);
        }
        distortion += clusterWiseDistortion;
    }

    prevDistortion = curDistortion;
    curDistortion = distortion / (long double)universeSize;
    fprintf(distortionFp, "%Lf\n", curDistortion);
}

/**
 * The K means algorithm to cluster the data and get the better codebook
 */
void kMeansAlgorithm()
{
    // Getting the initial code book with an adequate method
    int count = 0;

    while (fabsl(curDistortion - prevDistortion) > delta)
    {
        count++;
        classifyUniverse();
        computeCentroid();
        computeCurDistortion();
        dumpCodeBookIntoFile();
    }

    printf("\nFor m = %d, number of iteration for K-means = %d\n", m, count);
}

/**
 * Computes the initial codebook required for LBG by finding the centroid of the whole universe
 */
void computeInitialCodeBookForLBG()
{
    int i, j;
    for (i = 0; i < universeSize; i++)
    {
        for (j = 0; j < p; j++)
        {
            codeBook[0][j] += universe[i][j];
        }
    }

    for (j = 0; j < p; j++)
    {
        codeBook[0][j] /= (long double)universeSize;
    }
}

/**
 * Splits the codebook into twice the size of current codebook
 */
void splitCodeBook()
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < p; j++)
        {
            codeBook[i + m][j] = codeBook[i][j] * (1 - epsilon);
            codeBook[i][j] = codeBook[i][j] * (1 + epsilon);
        }
    }
}

/**
 * Creates the file that would store the final codebook
 */
void dumpFinalCodeBook()
{
    int i, j;
    FILE *fp = fopen(finalCodeBook, "w");
    if (fp == NULL)
    {
        printf("Error while opening the input file: %s\n", finalCodeBook);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < p; j++)
        {
            fprintf(fp, "%Lf ", codeBook[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

/**
 * Reads the final code book for generating the observation sequences
 */
void readCodeBook()
{
    int i, j;
    FILE *fp = fopen(finalCodeBook, "r");
    if (fp == NULL)
    {
        printf("Error while opening the file: %s\n", finalCodeBook);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < p; j++)
        {
            fscanf(fp, "%Lf", &codeBook[i][j]);
        }
    }

    fclose(fp);
}

/**
 * LBG algorithm
 */
void LBGAlgorithm()
{
    computeInitialCodeBookForLBG();
    dumpCodeBookIntoFile();

    while (m < M)
    {
        prevDistortion = 9999;
        splitCodeBook();
        m *= 2;
        kMeansAlgorithm();
        dumpCodeBookIntoFile();
    }
    dumpFinalCodeBook();
}

/**
 * Reading the universe from the input file.
 */
void readUniverse(char *fileName)
{
    // File pointer to read the file
    FILE *filePtr = fopen(fileName, "r");
    if (filePtr == NULL)
    {
        printf("Error while opening the file having universe data: %s", fileName);
        exit(EXIT_FAILURE);
    }

    long double curData;
    char c;
    int i = 0;
    int j = 0;

    while (!feof(filePtr))
    {
        for (j = 0; j < 12; j++)
        {
            fscanf(filePtr, "%Lf", &universe[i][j]);
            if (j < 11)
                fscanf(filePtr, "%c", &c);
        }
        i++;
    }

    // Updating the universe size
    universeSize = i - 1;
    fclose(filePtr); // closing file
}

/**
 * Generates the codebook of size 32
 */
void generateCodeBook()
{
    remove(codeBookFile);
    remove(distortionFile);
    codeBookFp = fopen(codeBookFile, "a");
    if (codeBookFp == NULL)
    {
        printf("Error while opening the file: %s\n", codeBookFile);
        exit(EXIT_FAILURE);
    }

    distortionFp = fopen(distortionFile, "a");
    if (distortionFp == NULL)
    {
        printf("Error while opening the input file: %s\n", distortionFile);
        exit(EXIT_FAILURE);
    }

    readUniverse(universeFile);

    LBGAlgorithm();
    fclose(codeBookFp);
    fclose(distortionFp);
}

/**
 * Prints the A matrix from the model lamda
 */
void printA()
{
    int i, j;
    printf("\n\nA Matrix: \n");
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
            printf("%e ", A[i][j]);
        printf("\n");
    }
}

/**
 * Prints the B matrix from the model lamda
 */
void printB()
{
    int i, j;
    printf("\n\nB Matrix: \n");
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
            printf("%e ", B[i][j]);
        printf("\n");
    }
}

/**
 * Forward procedure for calculating the Alpha matrix and the probability of Observation seq given model lamda
 */
void forwardProcedure()
{
    int t, i, j;

    for (i = 1; i <= N; i++)
    {
        Alpha[1][i] = PI[i] * B[i][Obs_Seq[1]];
    }

    long double sum = 0;
    for (t = 1; t <= T - 1; t++)
    {
        for (j = 1; j <= N; j++)
        {
            for (int i = 1; i <= N; i++)
            {
                sum += Alpha[t][i] * A[i][j];
            }
            Alpha[t + 1][j] = B[j][Obs_Seq[t + 1]] * sum;
            sum = 0;
        }
    }
    probOfObsGivenLambda = 0;
    for (i = 1; i <= N; i++)
        probOfObsGivenLambda += Alpha[T][i];
}

/**
 * Backward procedure for calculating the values of bete
 */
void backwardProcedure()
{
    int i, j, t;
    for (i = 1; i <= N; i++)
    {
        Beta[T][i] = 1;
    }

    for (t = T - 1; t > 0; t--)
    {
        for (i = 1; i <= N; i++)
        {
            Beta[t][i] = 0;
            for (j = 1; j <= N; j++)
                Beta[t][i] += A[i][j] * B[j][Obs_Seq[t + 1]] * Beta[t + 1][j];
        }
    }
}

/**
 * Calculate Gamma
 */
void calculateGamma()
{
    int t, i, j;
    long double sum = 0;
    for (t = 1; t <= T; t++)
    {
        for (j = 1; j <= N; j++)
            sum += Alpha[t][j] * Beta[t][j];

        for (i = 1; i <= N; i++)
            Gamma[t][i] = (Alpha[t][i] * Beta[t][i]) / sum;

        sum = 0;
    }
}

/**
 * Viterbi algorithm to calculate Pstar and State sequence
 */
void viterbiAlgo()
{
    int i, j, t;
    // Induction step
    for (i = 1; i <= N; i++)
    {
        Delta[1][i] = PI[i] * B[i][Obs_Seq[1]];
        Psi[1][i] = 0;
    }

    // Recursion step
    long double maxPrevDelta, temp;
    int maxState = 0;
    for (t = 2; t <= T; t++)
    {
        for (j = 1; j <= N; j++)
        {
            maxPrevDelta = Delta[t - 1][1] * A[1][j];
            maxState = 1;
            for (i = 1; i <= N; i++)
            {
                temp = Delta[t - 1][i] * A[i][j];
                if (temp > maxPrevDelta)
                {
                    maxPrevDelta = temp;
                    maxState = i;
                }
            }

            Delta[t][j] = maxPrevDelta * B[j][Obs_Seq[t]];

            Psi[t][j] = maxState;
        }
    }

    // Termination step
    Pstar = Delta[T][1];
    QTstar = 1;

    for (i = 1; i <= N; i++)
    {
        if (Delta[T][i] > Pstar)
        {
            Pstar = Delta[T][i];
            QTstar = i;
        }
    }

    // Path backtracking
    stateSeq[T] = QTstar;
    for (t = T - 1; t >= 1; t--)
    {
        stateSeq[t] = Psi[t + 1][stateSeq[t + 1]];
    }

    // // Print state sequence
    printf("\n\n\nState sequence: \n\n");
    for (i = 1; i <= T; i++)
    {
        printf("%d (%d)  ", stateSeq[i], Obs_Seq[i]);
    }
}

/**
 * Calculates the XI
 */
void calculateXI()
{
    int i, j, t;
    long double den = 0;

    for (t = 1; t <= T - 1; t++)
    {

        for (i = 1; i <= N; i++)
        {
            for (j = 1; j <= N; j++)
                den += Alpha[t][i] * A[i][j] * B[j][Obs_Seq[t + 1]] * Beta[t + 1][j];
        }

        for (i = 1; i <= N; i++)
        {
            for (j = 1; j <= N; j++)
            {
                Xi[t][i][j] = (Alpha[t][i] * A[i][j] * B[j][Obs_Seq[t + 1]] * Beta[t + 1][j]) / den;
            }
        }
        den = 0;
    }
}

/**
 * Re estimation of the PI
 */
void reEstimatePI()
{
    for (int i = 1; i <= N; i++)
        PI_[i] = Gamma[1][i];
}

/**
 * Re estimating the A matrix
 */
void reEstimateA()
{
    int i, j, t;
    long double num = 0, den = 0;

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {

            for (t = 1; t <= T - 1; t++)
            {
                num += Xi[t][i][j];
                den += Gamma[t][i];
            }

            A_[i][j] = num / den;
            num = den = 0;
        }
    }
}

/**
 * Re estimation of the B matrix
 */
void reEstimateB()
{

    int i, j, k, t;
    long double num = 0, den = 0;

    for (j = 1; j <= N; j++)
    {
        for (k = 1; k <= M; k++)
        {
            for (t = 1; t <= T; t++)
            {
                den += Gamma[t][j];

                // if (Obs_Seq[t] == k && stateSeq[t] == j)
                if (Obs_Seq[t] == k)
                {
                    num += Gamma[t][j];
                }
            }

            B_[j][k] = num / den;
            num = den = 0;
        }
    }
}

/**
 * Utility to make the A matrix stochastic by adjustments
 */
void adjustA()
{
    long double rowSum = 0, max, diff = 0;
    int i, j, index;

    for (i = 1; i <= N; i++)
    {
        max = A_[i][1];
        index = 1;
        for (j = 1; j <= N; j++)
        {
            rowSum += A_[i][j];
            if (A_[i][j] > max)
            {
                max = A_[i][j];
                index = j;
            }
        }

        A_[i][index] += (1 - rowSum);
        rowSum = 0;
    }
}

/**
 * Utility to make the B matrix stochastic by adjustments
 */
void adjustB()
{
    int i, j, index;
    long double max, rowSum = 0, diff = 0;

    for (i = 1; i <= N; i++)
    {
        max = B_[i][1];
        index = 1;

        for (j = 1; j <= M; j++)
        {
            if (B_[i][j] < bThreshold)
            {
                B_[i][j] = bThreshold;
            }
            rowSum += B_[i][j];
            if (B_[i][j] > max)
            {
                max = B_[i][j];
                index = j;
            }
        }

        B_[i][index] += (1 - rowSum);
        rowSum = 0;
    }
}

/**
 * Reads the input from the input files and adds them into the global arrays
 */
void readInputForHMM()
{
    int i, j;
    FILE *fp = fopen(a_file, "r"); // reading Aij
    if (fp == NULL)
    {
        printf("Error while opening the input file: %s\n", a_file);
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            fscanf(fp, "%Lf", &A[i][j]);
        }
    }
    fclose(fp);

    fp = fopen(b_file, "r"); // Reading Bjk
    if (fp == NULL)
    {
        printf("Error while opening the input file: %s\n", b_file);
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
        {
            fscanf(fp, "%Lf", &B[i][j]);
        }
    }

    fclose(fp);

    fp = fopen(pi_file, "r"); // Reading PI matrix
    if (fp == NULL)
    {
        printf("Error while opening the input file: %s\n", pi_file);
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= N; i++)
    {
        fscanf(fp, "%Lf", &PI[i]);
    }

    fclose(fp);

    // Update the initial Pstar
    Pstar = 1e-250;
}

/**
 * Generates the observation sequence for the input file using the final code book
 */
void generateObservationSequence(char *fileName)
{
    int i, j;
    start = 0;
    end = 320;

    int index = 1, minIndex = 0;
    long double distance, minDistance;
    readInputFile(fileName);
    // applyDCShift();
    applyNormalization();

    while (end <= noOfSamples)
    {
        if (index > 160)
        {
            break;
        }
        calculateRis();
        durbinsAlgo();
        calculateCis();

        minDistance = 9999999;
        for (j = 0; j < M; j++)
        {
            distance = 0;
            for (i = 0; i < p; i++)
            {
                distance += tokhuraWeights[i] * (codeBook[j][i] - CIs[i + 1]) * (codeBook[j][i] - CIs[i + 1]);
            }

            if (distance < minDistance)
            {
                minDistance = distance;
                minIndex = j;
            }
        }

        Obs_Seq[index++] = minIndex + 1;
        start += 80;
        end += 80;
    }

    T = index - 1;
}

/**
 * Overwrites the updated model with the initial model
 */
void replaceEstimatedModel()
{
    int j, k;
    for (j = 1; j <= N; j++)
    {
        for (k = 1; k <= N; k++)
            A[j][k] = A_[j][k];
    }

    for (j = 1; j <= N; j++)
    {
        for (k = 1; k <= M; k++)
            B[j][k] = B_[j][k];
    }
}

/**
 * Models the HMM for the word file
 */
void hmmModelingForOneWord()
{
    int i = 0, j, k;
    generateObservationSequence(inputFile);

    do
    {
        PstarOld = Pstar;
        forwardProcedure();
        backwardProcedure();
        calculateGamma();
        viterbiAlgo();
        calculateXI();
        reEstimateA();
        reEstimateB();
        adjustA();
        adjustB();

        replaceEstimatedModel();

        printf("\n\n------ Iteration %d -------\n", i);
        printf("\nOld Pstar = %.32e", PstarOld);
        printf("\n Pstar = %.32e", Pstar);
        i++;
    } while (i <= 100 && (Pstar > PstarOld));
}

/**
 * Reads the averages value for the second iteration of the HMM modeling
 */
void readAveragedModel(int word, int iteration)
{
    int i, j;
    long double data;
    char aModel[100], bModel[100];
    sprintf(aModel, "files/models/intermediate_models/%d_A_%d.txt", word, iteration);
    sprintf(bModel, "files/models/intermediate_models/%d_B_%d.txt", word, iteration);

    // Opening the files to read the intermediate models and do average of it and use it as initial model
    FILE *fptr1 = fopen(aModel, "r");
    FILE *fptr2 = fopen(bModel, "r");

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
            A[i][j] = 0;
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
            B[i][j] = 0;
    }

    for (int k = 0; k < numOfTrainingUtterances; k++)
    {
        for (i = 1; i <= N; i++)
        {
            for (j = 1; j <= N; j++)
            {
                fscanf(fptr1, "%Lf", &data);
                A[i][j] += data;
            }
        }

        for (i = 1; i <= N; i++)
        {
            for (j = 1; j <= M; j++)
            {
                fscanf(fptr2, "%Lf", &data);
                B[i][j] += data;
            }
        }
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
            A[i][j] /= (long double)numOfTrainingUtterances;
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
            B[i][j] /= (long double)numOfTrainingUtterances;
    }
    fclose(fptr1);
    fclose(fptr2);

    // Update Initial Pstar
    Pstar = 1e-250;
}

/**
 * The intermediate models are dumped into the file
 */
void dumpModelsIntoIntermediateFiles(FILE *aModelFp, FILE *bModelFp)
{
    int i, j;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
            fprintf(aModelFp, "%.32e ", A[i][j]);
        fprintf(aModelFp, "\n");
    }
    fprintf(aModelFp, "\n");

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
            fprintf(bModelFp, "%.32e ", B[i][j]);
        fprintf(bModelFp, "\n");
    }
    fprintf(bModelFp, "\n");
}

/**
 * The final models are dumped into the file
 */
void dumpFinalModel(int word)
{
    // The final model is the average model of the first iteration
    // Change the second parameter to 2 to change it to second iteration
    readAveragedModel(word, 1);

    sprintf(inputFile, "files/models/final_models/%d_model.txt", word);
    remove(inputFile);
    FILE *fptr = fopen(inputFile, "a");

    int i, j;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
            fprintf(fptr, "%.32e ", A[i][j]);
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
            fprintf(fptr, "%.32e ", B[i][j]);
        fprintf(fptr, "\n");
    }
    fclose(fptr);
}

/**
 * Training the HMM model with all the digits
 */
void trainHMM()
{
	// Reads the final codebook into the codebook array
    readCodeBook();

    int utterance, iteration;
    int type, word;
    remove("files/standard_word_prob.txt");
    FILE* standardProbFile = fopen("files/standard_word_prob.txt", "w");

    for (word = 1; word <= noOfWords; word++)
    {
        long double highestProb = 0;
        for (iteration = 1; iteration <= 2; iteration++)
        {
            sprintf(intermediateModelA, "files/models/intermediate_models/%d_A_%d.txt", word, iteration);
            sprintf(intermediateModelB, "files/models/intermediate_models/%d_B_%d.txt", word, iteration);

            // Removing the files before remodeling
            remove(intermediateModelA);
            remove(intermediateModelB);

            // Opening the files to append the intermediate models
            aModelFp = fopen(intermediateModelA, "a");
            if (aModelFp == NULL)
            {
                printf("Error while opening the file for dumping intermediate model: %s", intermediateModelA);
                exit(EXIT_FAILURE);
            }
            bModelFp = fopen(intermediateModelB, "a");
            if (bModelFp == NULL)
            {
                printf("Error while opening the file for dumping intermediate model: %s", intermediateModelB);
                exit(EXIT_FAILURE);
            }
			for (utterance = 1; utterance <= 30; utterance++)
			{
				if (iteration == 1)
					readInputForHMM();
				else
					readAveragedModel(word, iteration - 1);
				// inputFile = "digits/0/224101063_0_E_1.txt";
				sprintf(inputFile, "ST_DataSet/utterance_%d_%d.txt", word, utterance);
				printf("\n\nFile Name: %s \n", inputFile);

				hmmModelingForOneWord();

                if (Pstar > highestProb) {
                    highestProb = Pstar;
                }

				dumpModelsIntoIntermediateFiles(aModelFp, bModelFp);
			}
			fclose(aModelFp);
			fclose(bModelFp);


        }
        fprintf(standardProbFile, "%e\n", highestProb);

        standardProbabilities[word - 1] = highestProb;
        dumpFinalModel(word);

    }
    
    fclose(standardProbFile);
}

/**
 * Reading the final model for testing
 */
void readFinalModel(int word)
{
    sprintf(inputFile, "files/models/final_models/%d_model.txt", word);
    FILE *fptr = fopen(inputFile, "r");
    if (fptr == NULL) {
        printf("\nError while opening the file %s", inputFile);
        exit(EXIT_FAILURE);
    }

    int i, j;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
            fscanf(fptr, "%Lf", &A[i][j]);
    }

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= M; j++)
            fscanf(fptr, "%Lf", &B[i][j]);
    }
    fclose(fptr);
}


void calculateRangePerc() {
    if (tempPercentage < 1e-300) {
        percentage = rand() % 10 + 20;
    } else if (tempPercentage < 1e-260 && tempPercentage > 1e-300) {
        percentage = rand() % 10 + 30;
    } else if (tempPercentage < 1e-220 && tempPercentage > 1e-260) {
        percentage = rand() % 10 + 40;
    } else if (tempPercentage < 1e-180 && tempPercentage > 1e-220) {
        percentage = rand() % 10 + 50;
    } else if (tempPercentage < 1e-160 && tempPercentage > 1e-180) {
        percentage = rand() % 10 + 60;
    } else if (tempPercentage < 1e-140 && tempPercentage > 1e-160) {
        percentage = rand() % 10 + 70;
    } else if (tempPercentage < 1e-130 && tempPercentage > 1e-140) {
        percentage = rand() % 10 + 80;
    } else if (tempPercentage > 1e-130) {
        percentage = rand() % 10 + 90;
    } else {
        percentage = 10;
    }
}


/**
 * Testing the input file with the final models
 */
int testingFile()
{
    int iteration;
    maxRecognisedProb = 0;

	printf("\n\nfile %s", inputFile);


    recognisedWordIndex = 1;
    generateObservationSequence(inputFile);


    for (iteration = 1; iteration <= noOfWords; iteration++)
    {
        readFinalModel(iteration);
        forwardProcedure();
        printf("\nProbability (O|lamda) for word %d = %.32e", iteration, probOfObsGivenLambda);
        if (iteration == 1)
        {
            maxRecognisedProb = probOfObsGivenLambda;
        }
        else
        {
            if (probOfObsGivenLambda > maxRecognisedProb)
            {
                maxRecognisedProb = probOfObsGivenLambda;
                recognisedWordIndex = iteration;
            }
        }
    }
    printf("\nThe recongnised word = %d\n", recognisedWordIndex);

    tempPercentage = maxRecognisedProb / standardProbabilities[recognisedWordIndex - 1];

    calculateRangePerc();

    return recognisedWordIndex;
}

/**
 * Testing the HMM for the every test file
 */
void testHMM()
{
	// Reads the final codebook into the codebook array
    readCodeBook();

    int word, utterance;

    int probcount = 0;
    for (word = 1; word <= noOfWords; word++)
    {
        for (utterance = 31; utterance <= 40; utterance++)
        {
			sprintf(inputFile, "ST_DataSet/utterance_%d_%d.txt", word, utterance);

			if (testingFile() == word)
				probcount++;
        }
    }

    printf("\n\ncount = %d and Accuracy: %f\n", probcount, probcount / 0.3);
}


int calculateEnergy(char* liveFileName) {
    long double energyThreshold = 1000000.0;
	int fixedBack = 1200;
	int skip = 0;

    FILE* fptr = fopen(liveFileName, "r");

    long double data, energy = 0;
    int datapoints = 0;
    
    while (!feof(fptr)) {
        if (datapoints % 100 == 0) {
            if (energy > energyThreshold) {
                skip = datapoints - fixedBack;
                break;
            }
            energy = 0;
        }
        fscanf(fptr, "%Lf", &data);
        energy += data*data;
        datapoints++;
    }

    fclose(fptr);

	return skip;
}



/**
 * To support live testing the initial silence needs to be trimmed
 */
void skipSilence()
{

	int skip = calculateEnergy("files/liveTesting/livetesting.txt");

    FILE *fptr1 = fopen("files/liveTesting/livetesting.txt", "r");
    FILE *fptr2 = fopen("files/liveTesting/livetesting1.txt", "w");

    int count = 0;
    int data;
    while (!feof(fptr1) && count < skip)
    {
        fscanf(fptr1, "%d", &data);
        count++;
    }

    count = 0;
    while (!feof(fptr1) && count < 13000)
    {
        fscanf(fptr1, "%d", &data);
        fprintf(fptr2, "%d\n", data);
        count++;
    }
    fclose(fptr1);
    fclose(fptr2);
}

/**
 * Live testing
 */
int liveTesting()
{
	// Reads the final codebook into the codebook array
    readCodeBook();
    Sleep(2000);
    system("Recording_Module.exe 2 files/liveTesting/livetesting.wav files/liveTesting/livetesting.txt");
    skipSilence();
    sprintf(inputFile, "files/liveTesting/livetesting1.txt");

    recognisedWordIndex = testingFile() - 1;

    return recognisedWordIndex;
}


void dumpLiveDataForRecords() {
    char dirPath[100];
    char recordFilePath[100];

    sprintf(dirPath, "files/PastRecords/%s", words[recognisedWordIndex]);

    if (!_mkdir(dirPath)) {
        _mkdir(dirPath);
    }

    char timeStamp[100];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(timeStamp, "%d-%02d-%02d %02d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    sprintf(recordFilePath, "%s/%s.txt", dirPath, timeStamp);

    FILE* recordFilePtr = fopen(recordFilePath, "w");
    FILE* liveFilePtr = fopen("files/liveTesting/livetesting1.txt", "r");

    int transferData;
    while (!feof(liveFilePtr)) {
        fscanf(liveFilePtr, "%d", &transferData);
        fprintf(recordFilePtr, "%d\n", transferData);
    }

    fclose(liveFilePtr);
    fclose(recordFilePtr);


    sprintf(recordFilePath, "%s/performanceSheet.txt", dirPath);
    FILE* performanceSheetFptr = fopen(recordFilePath, "a");
    
    fprintf(performanceSheetFptr, "%d, %s\n", percentage, timeStamp);

    fclose(performanceSheetFptr);
}


// ---------------------------------------- Live training modules ----------------------------------------

void appendNewWord(char* newWord) {
    FILE* wordFilePtr = fopen("files/words.txt", "a");
    fprintf(wordFilePtr, "%s\n", newWord);
    fclose(wordFilePtr);
}

void liveRecording(int utt, char* newWordPath) {

    if (utt == 1) {
        curNumberOfWords++;
    }
    Sleep(1000);
    system("Recording_Module.exe 2 files/liveTesting/livetesting.wav files/liveTesting/livetesting.txt");
    skipSilence();

    char newFileName[100];
    int transferData;
    sprintf(newFileName, "ST_DataSet/utterance_%d_%d.txt", curNumberOfWords, utt);

    FILE* newRecordedFile = fopen("files/liveTesting/livetesting1.txt", "r");
    FILE* appendFileToDB = fopen(newFileName, "w");

    while (!feof(newRecordedFile)) {
        fscanf(newRecordedFile, "%d", &transferData);
        fprintf(appendFileToDB, "%d\n", transferData);
    }

    fclose(newRecordedFile);
    fclose(appendFileToDB);

    if (utt == 1) {
        rename("files/liveTesting/livetesting.wav", newWordPath);
    }

}


// ---------------------------------------- End of section ----------------------------------------

int console_main()
{
    readWords();
    // The below function is to generate the universe with the data
    generateUniverse();
    // The below function generates the code book with the data in the universe file
    generateCodeBook();

    // Trains the HMM model with the data
    trainHMM();

    // Tests the HMM model against all the test files
    // testHMM();
	// 	// Reads the final codebook into the codebook array
    // readCodeBook();

    // Live testing for the data
    // liveTesting();

    // printf("File name: %s", inputFile);

    getchar();
    return 0;
}
