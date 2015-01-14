// MyCustomAction.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "MSI_Logging.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
    return TRUE;
}


UINT __stdcall SampleFunction ( MSIHANDLE hModule )
{
	LogString(hModule, "About to show the MessageBox.");

	// I don't recommend using a MessageBox to get user input, because
	// we don't know the parent window handle... but for testing
	// purposes, I will use a MessageBox.
	MessageBox(NULL, "Hello world.  This is a normal windows MessageBox(), and it can easily become hidden behind other setup dialogs.", "CodeProject.com", MB_OK);

	// now get some property from the MSI, and write it to the log
	TCHAR szBuffer1[MAX_PATH] = {'0'};
	TCHAR szBuffer2[MAX_PATH] = {'0'};
	DWORD dwLen = MAX_PATH;
	MsiGetProperty(hModule, "ProductName", szBuffer1, &dwLen);

	// Now write a friendly string out to the logfile.
	sprintf(szBuffer2, "Your product name is: %s", szBuffer1);
	LogString(hModule, szBuffer2);

	return ERROR_SUCCESS;
}



UINT __stdcall SampleFunction2 ( MSIHANDLE hModule )
{
    MessageBox(NULL, "Hello world", "CodeProject.com", MB_OK);
    return ERROR_SUCCESS;
}



UINT __stdcall SampleFunction3 ( MSIHANDLE hModule)
{
	// this function will correctly use a modal messagebox (which is authored in the MSI as the 
	// Error Dialog (see msidbDialogAttributesError in msi.chm))
	LogString(hModule, "SampleFunction3:  About to show the true Modal MessageBox.");
	// now show a message box... and use the MB_ICONINFORMATION icon
	MsiMessageBox(hModule, "Hello world. This modal dialog box is authored inside of the .MSI file. It is not like a normal MessageBox() where Windows will automatically expand the dialog to accomidate all your text.", MB_OK | MB_ICONINFORMATION);
	
	// now ask the user for input, and use the MB_ICONQUESTION.
	if (MsiMessageBox(hModule, "Are you having a good day?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		LogString(hModule, "You clicked YES.  Returning to the setup.");
	else
	{
		// The user is having a rough day.  
		// Ask them if they want to exit the installation.  Using the MB_ICONSTOP
		LogString(hModule, "You clicked NO.  Asking the user if they wish to exit...");
		if (MsiMessageBox(hModule, "I'm sorry to hear that.  Would you like to exit this installation?", MB_YESNO | MB_ICONSTOP) == IDYES)
		{
			// alright.  Send back the error message stating that the user wants to exit.
			LogString(hModule, "User chose to exit the installation.  Returning ERROR_INSTALL_USEREXIT.");
			return ERROR_INSTALL_USEREXIT;
		}
	}

	// if we got this far, the user is having a good day, or a bad day and wishes to continue with the setup.  :)
	return ERROR_SUCCESS;
}