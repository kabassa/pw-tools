#pragma once

#include "MainWindow.h"

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Select international culture Profile (NumberFormat, Localization,...)
	Application::CurrentCulture = System::Globalization::CultureInfo::InvariantCulture;

	// Create the main window and run it
	Application::Run(gcnew MainWindow());
	return 0;
}