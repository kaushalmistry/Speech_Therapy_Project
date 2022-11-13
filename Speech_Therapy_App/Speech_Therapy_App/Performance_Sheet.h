
#pragma once

// #include "HMM_Utilities.h"



namespace Speech_Therapy_App {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Performance_Sheet
	/// </summary>
	public ref class Performance_Sheet : public System::Windows::Forms::Form
	{

	public:
		Performance_Sheet(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		Performance_Sheet(String^ param)
		{
			InitializeComponent();
			this->data_passing_label->Text = param;

		}




	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Performance_Sheet()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  performance_label;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Label^  data_passing_label;
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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->performance_label = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->data_passing_label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// performance_label
			// 
			this->performance_label->AutoSize = true;
			this->performance_label->BackColor = System::Drawing::Color::Transparent;
			this->performance_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->performance_label->Location = System::Drawing::Point(152, 6);
			this->performance_label->Name = L"performance_label";
			this->performance_label->Size = System::Drawing::Size(159, 23);
			this->performance_label->TabIndex = 0;
			this->performance_label->Text = L"Performance Sheet";
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(-3, 35);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(445, 333);
			this->chart1->TabIndex = 1;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &Performance_Sheet::chart1_Click);
			// 
			// data_passing_label
			// 
			this->data_passing_label->AutoSize = true;
			this->data_passing_label->Enabled = false;
			this->data_passing_label->Location = System::Drawing::Point(387, 326);
			this->data_passing_label->Name = L"data_passing_label";
			this->data_passing_label->Size = System::Drawing::Size(0, 13);
			this->data_passing_label->TabIndex = 2;
			// 
			// Performance_Sheet
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(441, 370);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->performance_label);
			this->Controls->Add(this->data_passing_label);
			this->Name = L"Performance_Sheet";
			this->Text = L"Performance_Sheet";
			this->Load += gcnew System::EventHandler(this, &Performance_Sheet::Performance_Sheet_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}


#pragma endregion

	private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void Performance_Sheet_Load(System::Object^  sender, System::EventArgs^  e) {
			char pSheet[100];
			char buf[100];

			sprintf(pSheet, "files/PastRecords/%s/performanceSheet.txt", gcnew String(this->data_passing_label->Text));

			this->performance_label->Text = gcnew String(pSheet);


			// // FILE* fp = fopen("files/PastRecords/away/performanceSheet.txt", "r");
			FILE* fp = fopen(pSheet, "r");
			int x = 1;
			float pb;
			while (fgets(buf, 100, fp)) {
				sscanf(buf, "%f", &pb);
				chart1->Series[0]->Points->AddXY(x, pb);
				x++;
			}

			fclose(fp);
		 }
};
}
