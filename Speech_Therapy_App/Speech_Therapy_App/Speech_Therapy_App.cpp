// Speech_Therapy_App.cpp : main project file.

#include "stdafx.h"
#include "Main_Form.h"

using namespace Speech_Therapy_App;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Main_Form());
	return 0;
}
