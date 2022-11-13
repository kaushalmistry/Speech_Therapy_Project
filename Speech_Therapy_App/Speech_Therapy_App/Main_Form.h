#pragma once
#include "Live training.h"
#include "Performance_Sheet.h"

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
	private: System::Windows::Forms::Label^  placeholder_label;
	private: System::Windows::Forms::Label^  label2;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Form::typeid));
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
			this->placeholder_label = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->BackColor = System::Drawing::Color::LightCyan;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 26;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"glasses", L"chair", L"away"});
			this->listBox1->Location = System::Drawing::Point(81, 119);
			this->listBox1->Margin = System::Windows::Forms::Padding(13, 3, 3, 3);
			this->listBox1->Name = L"listBox1";
			this->listBox1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->listBox1->Size = System::Drawing::Size(111, 134);
			this->listBox1->TabIndex = 0;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Main_Form::listBox1_SelectedIndexChanged_1);
			// 
			// text_box_title
			// 
			this->text_box_title->AutoSize = true;
			this->text_box_title->BackColor = System::Drawing::Color::Transparent;
			this->text_box_title->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->text_box_title->ForeColor = System::Drawing::Color::Bisque;
			this->text_box_title->Location = System::Drawing::Point(60, 64);
			this->text_box_title->Name = L"text_box_title";
			this->text_box_title->Size = System::Drawing::Size(152, 46);
			this->text_box_title->TabIndex = 1;
			this->text_box_title->Text = L"Let\'s play with the \r\n    words below";
			this->text_box_title->Click += gcnew System::EventHandler(this, &Main_Form::label1_Click);
			// 
			// speak_button
			// 
			this->speak_button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"speak_button.Image")));
			this->speak_button->Location = System::Drawing::Point(379, 161);
			this->speak_button->Name = L"speak_button";
			this->speak_button->Size = System::Drawing::Size(38, 39);
			this->speak_button->TabIndex = 2;
			this->speak_button->UseVisualStyleBackColor = true;
			this->speak_button->Click += gcnew System::EventHandler(this, &Main_Form::speak_button_Click);
			// 
			// listen_button
			// 
			this->listen_button->BackColor = System::Drawing::Color::Transparent;
			this->listen_button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"listen_button.Image")));
			this->listen_button->Location = System::Drawing::Point(386, 98);
			this->listen_button->Name = L"listen_button";
			this->listen_button->Size = System::Drawing::Size(28, 27);
			this->listen_button->TabIndex = 3;
			this->listen_button->UseVisualStyleBackColor = false;
			this->listen_button->Click += gcnew System::EventHandler(this, &Main_Form::listen_button_Click);
			// 
			// question_label
			// 
			this->question_label->AutoSize = true;
			this->question_label->BackColor = System::Drawing::Color::Transparent;
			this->question_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->question_label->Location = System::Drawing::Point(253, 213);
			this->question_label->Name = L"question_label";
			this->question_label->Size = System::Drawing::Size(185, 20);
			this->question_label->TabIndex = 4;
			this->question_label->Text = L"Are you trying to speak _";
			// 
			// yes_button
			// 
			this->yes_button->BackColor = System::Drawing::Color::SeaShell;
			this->yes_button->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"yes_button.BackgroundImage")));
			this->yes_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->yes_button->Location = System::Drawing::Point(280, 249);
			this->yes_button->Name = L"yes_button";
			this->yes_button->Size = System::Drawing::Size(73, 25);
			this->yes_button->TabIndex = 5;
			this->yes_button->Text = L"Yes";
			this->yes_button->UseVisualStyleBackColor = false;
			this->yes_button->Click += gcnew System::EventHandler(this, &Main_Form::yes_button_Click);
			// 
			// no_button
			// 
			this->no_button->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"no_button.BackgroundImage")));
			this->no_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->no_button->Location = System::Drawing::Point(375, 250);
			this->no_button->Name = L"no_button";
			this->no_button->Size = System::Drawing::Size(75, 24);
			this->no_button->TabIndex = 6;
			this->no_button->Text = L"No";
			this->no_button->UseVisualStyleBackColor = true;
			this->no_button->Click += gcnew System::EventHandler(this, &Main_Form::no_button_Click);
			// 
			// feedback_label
			// 
			this->feedback_label->AutoSize = true;
			this->feedback_label->BackColor = System::Drawing::Color::Transparent;
			this->feedback_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->feedback_label->Location = System::Drawing::Point(232, 289);
			this->feedback_label->Name = L"feedback_label";
			this->feedback_label->Size = System::Drawing::Size(0, 20);
			this->feedback_label->TabIndex = 7;
			this->feedback_label->Click += gcnew System::EventHandler(this, &Main_Form::label1_Click_1);
			// 
			// word_label
			// 
			this->word_label->AutoSize = true;
			this->word_label->BackColor = System::Drawing::Color::Transparent;
			this->word_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->word_label->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->word_label->Location = System::Drawing::Point(276, 59);
			this->word_label->Name = L"word_label";
			this->word_label->Size = System::Drawing::Size(163, 21);
			this->word_label->TabIndex = 8;
			this->word_label->Text = L"Selected word: None";
			// 
			// speak_label
			// 
			this->speak_label->AutoSize = true;
			this->speak_label->BackColor = System::Drawing::Color::Transparent;
			this->speak_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->speak_label->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->speak_label->Location = System::Drawing::Point(282, 167);
			this->speak_label->Name = L"speak_label";
			this->speak_label->Size = System::Drawing::Size(55, 23);
			this->speak_label->TabIndex = 9;
			this->speak_label->Text = L"Speak";
			// 
			// listen_label
			// 
			this->listen_label->AutoSize = true;
			this->listen_label->BackColor = System::Drawing::Color::Transparent;
			this->listen_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->listen_label->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->listen_label->Location = System::Drawing::Point(281, 98);
			this->listen_label->Name = L"listen_label";
			this->listen_label->Size = System::Drawing::Size(54, 23);
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
			this->listen_warning->BackColor = System::Drawing::Color::Transparent;
			this->listen_warning->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->listen_warning->ForeColor = System::Drawing::Color::Red;
			this->listen_warning->Location = System::Drawing::Point(307, 132);
			this->listen_warning->Name = L"listen_warning";
			this->listen_warning->Size = System::Drawing::Size(0, 18);
			this->listen_warning->TabIndex = 12;
			// 
			// progress_button
			// 
			this->progress_button->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"progress_button.BackgroundImage")));
			this->progress_button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->progress_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->progress_button->Location = System::Drawing::Point(306, 319);
			this->progress_button->Name = L"progress_button";
			this->progress_button->Size = System::Drawing::Size(125, 34);
			this->progress_button->TabIndex = 14;
			this->progress_button->Text = L"See your progress";
			this->progress_button->UseVisualStyleBackColor = true;
			this->progress_button->Click += gcnew System::EventHandler(this, &Main_Form::progress_button_Click);
			// 
			// train_button
			// 
			this->train_button->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"train_button.BackgroundImage")));
			this->train_button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->train_button->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->train_button->Location = System::Drawing::Point(81, 319);
			this->train_button->Name = L"train_button";
			this->train_button->Padding = System::Windows::Forms::Padding(0, 0, 0, 2);
			this->train_button->Size = System::Drawing::Size(116, 34);
			this->train_button->TabIndex = 15;
			this->train_button->Text = L"Add New Word";
			this->train_button->UseVisualStyleBackColor = true;
			this->train_button->Click += gcnew System::EventHandler(this, &Main_Form::train_button_Click);
			// 
			// placeholder_label
			// 
			this->placeholder_label->AutoSize = true;
			this->placeholder_label->Location = System::Drawing::Point(112, 213);
			this->placeholder_label->Name = L"placeholder_label";
			this->placeholder_label->Size = System::Drawing::Size(42, 13);
			this->placeholder_label->TabIndex = 16;
			this->placeholder_label->Text = L"glasses";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Bisque;
			this->label2->Location = System::Drawing::Point(119, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(319, 27);
			this->label2->TabIndex = 17;
			this->label2->Text = L"Welcome To Your Training Home!";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Main_Form
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::MenuBar;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(547, 365);
			this->Controls->Add(this->label2);
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
			this->Controls->Add(this->placeholder_label);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Main_Form";
			this->Text = L"Home Page";
			this->Load += gcnew System::EventHandler(this, &Main_Form::Main_Form_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void listBox1_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e) {
				this->word_label->Text = "Selected word: " + this->listBox1->SelectedItem->ToString();
				this->placeholder_label->Text = this->listBox1->SelectedItem->ToString();
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
private: System::Void progress_button_Click(System::Object^  sender, System::EventArgs^  e) {
			// SetValueForWord = this->word_label->Text;
			Performance_Sheet^ pSheet = gcnew Performance_Sheet(this->placeholder_label->Text);
			// Performance_Sheet^ pSheet = gcnew Performance_Sheet();
			// pSheet->wordForPerformanceSheet = this->listBox1->SelectedItem->ToString();
			pSheet->Show();
		 }
private: System::Void Main_Form_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
