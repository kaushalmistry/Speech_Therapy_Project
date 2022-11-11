#pragma once
#include "Live training.h"

namespace Speech_Therapy_App {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main_Form
	/// </summary>
	public ref class Main_Form : public System::Windows::Forms::Form
	{
	public:
		Main_Form(void)
		{
			readWords();
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main_Form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  text_box_title;
	private: System::Windows::Forms::Button^  speak_button;
	private: System::Windows::Forms::Button^  listen_button;
	private: System::Windows::Forms::Label^  question_label;
	private: System::Windows::Forms::Button^  yes_button;
	private: System::Windows::Forms::Button^  no_button;
	private: System::Windows::Forms::Label^  feedback_label;
	public: System::Windows::Forms::Label^  word_label;
	private: 

	private: System::Windows::Forms::Label^  speak_label;
	private: System::Windows::Forms::Label^  listen_label;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  listen_warning;

	private: System::Windows::Forms::Button^  progress_button;
	private: System::Windows::Forms::Button^  train_button;

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
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->text_box_title = (gcnew System::Windows::Forms::Label());
			this->speak_button = (gcnew System::Windows::Forms::Button());
			this->listen_button = (gcnew System::Windows::Forms::Button());
			this->question_label = (gcnew System::Windows::Forms::Label());
			this->yes_button = (gcnew System::Windows::Forms::Button());
			this->no_button = (gcnew System::Windows::Forms::Button());
			this->feedback_label = (gcnew System::Windows::Forms::Label());
			this->word_label = (gcnew System::Windows::Forms::Label());
			this->speak_label = (gcnew System::Windows::Forms::Label());
			this->listen_label = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->listen_warning = (gcnew System::Windows::Forms::Label());
			this->progress_button = (gcnew System::Windows::Forms::Button());
			this->train_button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"glasses", L"chair", L"away"});
			this->listBox1->Location = System::Drawing::Point(22, 67);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(159, 225);
			this->listBox1->TabIndex = 0;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Main_Form::listBox1_SelectedIndexChanged_1);
			// 
			// text_box_title
			// 
			this->text_box_title->AutoSize = true;
			this->text_box_title->Location = System::Drawing::Point(22, 33);
			this->text_box_title->Name = L"text_box_title";
			this->text_box_title->Size = System::Drawing::Size(151, 13);
			this->text_box_title->TabIndex = 1;
			this->text_box_title->Text = L"Lets play with the words below";
			this->text_box_title->Click += gcnew System::EventHandler(this, &Main_Form::label1_Click);
			// 
			// speak_button
			// 
			this->speak_button->Location = System::Drawing::Point(351, 137);
			this->speak_button->Name = L"speak_button";
			this->speak_button->Size = System::Drawing::Size(75, 23);
			this->speak_button->TabIndex = 2;
			this->speak_button->Text = L"Speak";
			this->speak_button->UseVisualStyleBackColor = true;
			this->speak_button->Click += gcnew System::EventHandler(this, &Main_Form::speak_button_Click);
			// 
			// listen_button
			// 
			this->listen_button->Location = System::Drawing::Point(352, 74);
			this->listen_button->Name = L"listen_button";
			this->listen_button->Size = System::Drawing::Size(75, 23);
			this->listen_button->TabIndex = 3;
			this->listen_button->Text = L"Listen";
			this->listen_button->UseVisualStyleBackColor = true;
			this->listen_button->Click += gcnew System::EventHandler(this, &Main_Form::listen_button_Click);
			// 
			// question_label
			// 
			this->question_label->AutoSize = true;
			this->question_label->Location = System::Drawing::Point(287, 186);
			this->question_label->Name = L"question_label";
			this->question_label->Size = System::Drawing::Size(124, 13);
			this->question_label->TabIndex = 4;
			this->question_label->Text = L"Are you trying to speak _";
			// 
			// yes_button
			// 
			this->yes_button->Location = System::Drawing::Point(255, 215);
			this->yes_button->Name = L"yes_button";
			this->yes_button->Size = System::Drawing::Size(75, 23);
			this->yes_button->TabIndex = 5;
			this->yes_button->Text = L"Yes";
			this->yes_button->UseVisualStyleBackColor = true;
			this->yes_button->Click += gcnew System::EventHandler(this, &Main_Form::yes_button_Click);
			// 
			// no_button
			// 
			this->no_button->Location = System::Drawing::Point(351, 215);
			this->no_button->Name = L"no_button";
			this->no_button->Size = System::Drawing::Size(75, 23);
			this->no_button->TabIndex = 6;
			this->no_button->Text = L"No";
			this->no_button->UseVisualStyleBackColor = true;
			this->no_button->Click += gcnew System::EventHandler(this, &Main_Form::no_button_Click);
			// 
			// feedback_label
			// 
			this->feedback_label->AutoSize = true;
			this->feedback_label->Location = System::Drawing::Point(300, 250);
			this->feedback_label->Name = L"feedback_label";
			this->feedback_label->Size = System::Drawing::Size(0, 13);
			this->feedback_label->TabIndex = 7;
			this->feedback_label->Click += gcnew System::EventHandler(this, &Main_Form::label1_Click_1);
			// 
			// word_label
			// 
			this->word_label->AutoSize = true;
			this->word_label->Location = System::Drawing::Point(275, 33);
			this->word_label->Name = L"word_label";
			this->word_label->Size = System::Drawing::Size(107, 13);
			this->word_label->TabIndex = 8;
			this->word_label->Text = L"Selected word: None";
			// 
			// speak_label
			// 
			this->speak_label->AutoSize = true;
			this->speak_label->Location = System::Drawing::Point(238, 143);
			this->speak_label->Name = L"speak_label";
			this->speak_label->Size = System::Drawing::Size(38, 13);
			this->speak_label->TabIndex = 9;
			this->speak_label->Text = L"Speak";
			// 
			// listen_label
			// 
			this->listen_label->AutoSize = true;
			this->listen_label->Location = System::Drawing::Point(238, 77);
			this->listen_label->Name = L"listen_label";
			this->listen_label->Size = System::Drawing::Size(35, 13);
			this->listen_label->TabIndex = 10;
			this->listen_label->Text = L"Listen";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(672, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 11;
			// 
			// listen_warning
			// 
			this->listen_warning->AutoSize = true;
			this->listen_warning->Location = System::Drawing::Point(309, 104);
			this->listen_warning->Name = L"listen_warning";
			this->listen_warning->Size = System::Drawing::Size(0, 13);
			this->listen_warning->TabIndex = 12;
			// 
			// progress_button
			// 
			this->progress_button->Location = System::Drawing::Point(290, 289);
			this->progress_button->Name = L"progress_button";
			this->progress_button->Size = System::Drawing::Size(104, 23);
			this->progress_button->TabIndex = 14;
			this->progress_button->Text = L"See your progress";
			this->progress_button->UseVisualStyleBackColor = true;
			// 
			// train_button
			// 
			this->train_button->Location = System::Drawing::Point(70, 298);
			this->train_button->Name = L"train_button";
			this->train_button->Size = System::Drawing::Size(103, 23);
			this->train_button->TabIndex = 15;
			this->train_button->Text = L"Add new word";
			this->train_button->UseVisualStyleBackColor = true;
			this->train_button->Click += gcnew System::EventHandler(this, &Main_Form::train_button_Click);
			// 
			// Main_Form
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::MenuBar;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(858, 325);
			this->Controls->Add(this->train_button);
			this->Controls->Add(this->progress_button);
			this->Controls->Add(this->listen_warning);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listen_label);
			this->Controls->Add(this->speak_label);
			this->Controls->Add(this->word_label);
			this->Controls->Add(this->feedback_label);
			this->Controls->Add(this->no_button);
			this->Controls->Add(this->yes_button);
			this->Controls->Add(this->question_label);
			this->Controls->Add(this->listen_button);
			this->Controls->Add(this->speak_button);
			this->Controls->Add(this->text_box_title);
			this->Controls->Add(this->listBox1);
			this->Name = L"Main_Form";
			this->Text = L"Main_Form";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void listBox1_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e) {
			 		// testPrint();
				this->word_label->Text = "Selected word: " + this->listBox1->SelectedItem->ToString();
				this->feedback_label->Text = "";

		 }

private: System::Void speak_button_Click(System::Object^  sender, System::EventArgs^  e) {
			int detectedWordIndex = liveTesting();
			char question[100];
			sprintf(question, "Are you trying to speak %s?", words[detectedWordIndex]);
			this->question_label->Text = gcnew String(question);
		 }

private: System::Void listen_button_Click(System::Object^  sender, System::EventArgs^  e) {
				System::Media:: SoundPlayer^ player=gcnew System::Media::SoundPlayer();

				char testString[100];
				char pathString[100];

                if (this->word_label->Text == "Selected word: None") {
					this->listen_warning->Text = "Please select a word";
                } else {
					this->listen_warning->Text= "";
					for (int i = 0; i < noOfWords; i++) {
						sprintf(testString, "Selected word: %s", words[i]);
						if(this->word_label->Text == gcnew String(testString)) {
							sprintf(pathString, "files/listen/%s.wav", words[i]);
							player->SoundLocation = gcnew String(pathString);
							break;
						}
					}
					player->Load();
					player->PlaySync();
                }
		}
private: System::Void no_button_Click(System::Object^  sender, System::EventArgs^  e) {
				this->feedback_label->Text = "Unable to detect. Please try again!";
		 }
private: System::Void yes_button_Click(System::Object^  sender, System::EventArgs^  e) {
				char resultString[100];

				sprintf(resultString, "Hurray! You spoke it well.\nYou are %Lf near to the perfection.", maxRecognisedProb);

				this->feedback_label->Text = gcnew String(resultString);

				dumpLiveDataForRecords();
		 }
private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void train_button_Click(System::Object^  sender, System::EventArgs^  e) {
			Livetraining^ addingNewWord = gcnew Livetraining();
			addingNewWord->Show();
		 }
};
}
