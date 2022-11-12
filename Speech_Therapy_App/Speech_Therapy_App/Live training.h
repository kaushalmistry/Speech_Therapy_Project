#pragma once
#include "HMM_Utilities.h"
int recordCount = 0;
char newWord[20] = "";

namespace Speech_Therapy_App {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Livetraining
	/// </summary>
	public ref class Livetraining : public System::Windows::Forms::Form
	{
	public:
		Livetraining(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Livetraining()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  new_word_label2;
	private: System::Windows::Forms::Label^  new_input_label2;
	private: System::Windows::Forms::TextBox^  new_word_textBox;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  utterance_count_label;
	private: System::Windows::Forms::Label^  count_label;
	private: System::Windows::Forms::Button^  train_hmm;
	private: System::Windows::Forms::Label^  warning_on_utt_count;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  training_warning_label;

	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->new_word_label2 = (gcnew System::Windows::Forms::Label());
			this->new_input_label2 = (gcnew System::Windows::Forms::Label());
			this->new_word_textBox = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->utterance_count_label = (gcnew System::Windows::Forms::Label());
			this->count_label = (gcnew System::Windows::Forms::Label());
			this->train_hmm = (gcnew System::Windows::Forms::Button());
			this->warning_on_utt_count = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->training_warning_label = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// new_word_label2
			// 
			this->new_word_label2->AutoSize = true;
			this->new_word_label2->Location = System::Drawing::Point(127, 20);
			this->new_word_label2->Name = L"new_word_label2";
			this->new_word_label2->Size = System::Drawing::Size(104, 13);
			this->new_word_label2->TabIndex = 0;
			this->new_word_label2->Text = L"Adding a new word! ";
			this->new_word_label2->Click += gcnew System::EventHandler(this, &Livetraining::new_word_label2_Click);
			// 
			// new_input_label2
			// 
			this->new_input_label2->AutoSize = true;
			this->new_input_label2->Location = System::Drawing::Point(24, 69);
			this->new_input_label2->Name = L"new_input_label2";
			this->new_input_label2->Size = System::Drawing::Size(140, 13);
			this->new_input_label2->TabIndex = 1;
			this->new_input_label2->Text = L"Enter name of the new word";
			// 
			// new_word_textBox
			// 
			this->new_word_textBox->Location = System::Drawing::Point(201, 69);
			this->new_word_textBox->Name = L"new_word_textBox";
			this->new_word_textBox->Size = System::Drawing::Size(100, 20);
			this->new_word_textBox->TabIndex = 2;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(109, 125);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(154, 31);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Record 20 utterances";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Livetraining::button1_Click);
			// 
			// utterance_count_label
			// 
			this->utterance_count_label->AutoSize = true;
			this->utterance_count_label->Location = System::Drawing::Point(106, 175);
			this->utterance_count_label->Name = L"utterance_count_label";
			this->utterance_count_label->Size = System::Drawing::Size(137, 13);
			this->utterance_count_label->TabIndex = 4;
			this->utterance_count_label->Text = L"No of recorded utterences: ";
			// 
			// count_label
			// 
			this->count_label->AutoSize = true;
			this->count_label->Location = System::Drawing::Point(243, 175);
			this->count_label->Name = L"count_label";
			this->count_label->Size = System::Drawing::Size(13, 13);
			this->count_label->TabIndex = 5;
			this->count_label->Text = L"0";
			// 
			// train_hmm
			// 
			this->train_hmm->Location = System::Drawing::Point(79, 207);
			this->train_hmm->Name = L"train_hmm";
			this->train_hmm->Size = System::Drawing::Size(205, 23);
			this->train_hmm->TabIndex = 6;
			this->train_hmm->Text = L"Train model with newly added word";
			this->train_hmm->UseVisualStyleBackColor = true;
			this->train_hmm->Click += gcnew System::EventHandler(this, &Livetraining::train_hmm_Click);
			// 
			// warning_on_utt_count
			// 
			this->warning_on_utt_count->AutoSize = true;
			this->warning_on_utt_count->Location = System::Drawing::Point(172, 243);
			this->warning_on_utt_count->Name = L"warning_on_utt_count";
			this->warning_on_utt_count->Size = System::Drawing::Size(0, 13);
			this->warning_on_utt_count->TabIndex = 7;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(91, 295);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(183, 23);
			this->progressBar1->TabIndex = 8;
			this->progressBar1->Click += gcnew System::EventHandler(this, &Livetraining::progressBar1_Click);
			// 
			// training_warning_label
			// 
			this->training_warning_label->AutoSize = true;
			this->training_warning_label->Location = System::Drawing::Point(44, 254);
			this->training_warning_label->Name = L"training_warning_label";
			this->training_warning_label->Size = System::Drawing::Size(42, 13);
			this->training_warning_label->TabIndex = 9;
			this->training_warning_label->Text = L"Dummy";
			// 
			// Livetraining
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(375, 353);
			this->Controls->Add(this->training_warning_label);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->warning_on_utt_count);
			this->Controls->Add(this->train_hmm);
			this->Controls->Add(this->count_label);
			this->Controls->Add(this->utterance_count_label);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->new_word_textBox);
			this->Controls->Add(this->new_input_label2);
			this->Controls->Add(this->new_word_label2);
			this->Name = L"Livetraining";
			this->Text = L"Livetraining";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void new_word_label2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void progressBar1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

			liveRecording(recordCount);

			recordCount++;
			this->count_label->Text = Convert::ToString(recordCount);

		 }
private: System::Void train_hmm_Click(System::Object^  sender, System::EventArgs^  e) {

			if (this->new_word_textBox->Text != "30") {
				this->training_warning_label->Text = "You must record 30 utterence before training the model";
			} else {
				
				sprintf(newWord, "%s", gcnew String(this->new_word_textBox->Text));
				appendNewWord(newWord);

				this->progressBar1->Increment(1);

				generateCodeBook();

				this->progressBar1->Increment(10);

				generateCodeBook();

				this->progressBar1->Increment(25);

				readWords();

				this->progressBar1->Increment(10);


				trainHMM();

				this->progressBar1->Increment(54);
			}

		 }
};
}
