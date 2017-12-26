#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace AsherProject;

[STAThreadAttribute]
void Main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	AsherProject::MyForm form;
	Application::Run(%form);
}