#pragma once
#include "HMM_Utilities.h"
int recordCount = 1;
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
			this->new_word_label2->BackColor = System::Drawing::Color::Transparent;
			this->new_word_label2->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->new_word_label2->ForeColor = System::Drawing::SystemColors::InfoText;
			this->new_word_label2->Location = System::Drawing::Point(118, 20);
			this->new_word_label2->Name = L"new_word_label2";
			this->new_word_label2->Size = System::Drawing::Size(161, 23);
			this->new_word_label2->TabIndex = 0;
			this->new_word_label2->Text = L"Adding New Word! ";
			this->new_word_label2->Click += gcnew System::EventHandler(this, &Livetraining::new_word_label2_Click);
			// 
			// new_input_label2
			// 
			this->new_input_label2->AutoSize = true;
			this->new_input_label2->BackColor = System::Drawing::Color::Transparent;
			this->new_input_label2->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->new_input_label2->ForeColor = System::Drawing::SystemColors::WindowText;
			this->new_input_label2->Location = System::Drawing::Point(16, 71);
			this->new_input_label2->Name = L"new_input_label2";
			this->new_input_label2->Size = System::Drawing::Size(205, 19);
			this->new_input_label2->TabIndex = 1;
			this->new_input_label2->Text = L"Enter name of the new word";
			// 
			// new_word_textBox
			// 
			this->new_word_textBox->BackColor = System::Drawing::Color::MistyRose;
			this->new_word_textBox->Location = System::Drawing::Point(227, 72);
			this->new_word_textBox->Name = L"new_word_textBox";
			this->new_word_textBox->Size = System::Drawing::Size(122, 20);
			this->new_word_textBox->TabIndex = 2;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::SeaShell;
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(103, 125);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(166, 31);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Record 30 utterances";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Livetraining::button1_Click);
			// 
			// utterance_count_label
			// 
			this->utterance_count_label->AutoSize = true;
			this->utterance_count_label->BackColor = System::Drawing::Color::Transparent;
			this->utterance_count_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->utterance_count_label->Location = System::Drawing::Point(82, 172);
			this->utterance_count_label->Name = L"utterance_count_label";
			this->utterance_count_label->Size = System::Drawing::Size(193, 19);
			this->utterance_count_label->TabIndex = 4;
			this->utterance_count_label->Text = L"No of recorded utterences: ";
			// 
			// count_label
			// 
			this->count_label->AutoSize = true;
			this->count_label->BackColor = System::Drawing::Color::Transparent;
			this->count_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->count_label->Location = System::Drawing::Point(264, 172);
			this->count_label->Name = L"count_label";
			this->count_label->Size = System::Drawing::Size(17, 19);
			this->count_label->TabIndex = 5;
			this->count_label->Text = L"0";
			// 
			// train_hmm
			// 
			this->train_hmm->BackColor = System::Drawing::Color::SeaShell;
			this->train_hmm->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->train_hmm->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->train_hmm->Location = System::Drawing::Point(66, 208);
			this->train_hmm->Name = L"train_hmm";
			this->train_hmm->Size = System::Drawing::Size(251, 32);
			this->train_hmm->TabIndex = 6;
			this->train_hmm->Text = L"Train model with newly added word";
			this->train_hmm->UseVisualStyleBackColor = false;
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
			this->progressBar1->BackColor = System::Drawing::Color::SeaShell;
			this->progressBar1->Location = System::Drawing::Point(20, 298);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(329, 23);
			this->progressBar1->TabIndex = 8;
			this->progressBar1->Click += gcnew System::EventHandler(this, &Livetraining::progressBar1_Click);
			// 
			// training_warning_label
			// 
			this->training_warning_label->AutoSize = true;
			this->training_warning_label->BackColor = System::Drawing::Color::Transparent;
			this->training_warning_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->training_warning_label->ForeColor = System::Drawing::Color::Firebrick;
			this->training_warning_label->Location = System::Drawing::Point(40, 262);
			this->training_warning_label->Name = L"training_warning_label";
			this->training_warning_label->Size = System::Drawing::Size(0, 17);
			this->training_warning_label->TabIndex = 9;
			// 
			// Livetraining
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::RosyBrown;
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
			this->Load += gcnew System::EventHandler(this, &Livetraining::Livetraining_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void new_word_label2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void progressBar1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			
			char listenPath[100];
			sprintf(listenPath, "files/listen/%s.wav", gcnew String(this->new_word_textBox->Text));

			liveRecording(recordCount, listenPath);
			this->count_label->Text = Convert::ToString(recordCount);
			recordCount++;

		 }
private: System::Void train_hmm_Click(System::Object^  sender, System::EventArgs^  e) {

			if (recordCount > 30) {
				
				this->training_warning_label->Text = "";
				
				this->progressBar1->Increment(1);
				sprintf(newWord, "%s", gcnew String(this->new_word_textBox->Text));
				appendNewWord(newWord);

				this->progressBar1->Increment(5);

				readWords();

				generateUniverse();

				this->progressBar1->Increment(10);

				generateCodeBook();

				this->progressBar1->Increment(25);

				readWords();

				this->progressBar1->Increment(10);


				trainHMM();

				this->progressBar1->Increment(54);
			} else {
				this->training_warning_label->Text = "You must record 30 utterence before training the model";

			}

		 }
private: System::Void Livetraining_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
