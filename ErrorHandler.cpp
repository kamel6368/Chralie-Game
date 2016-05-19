#include "ErrorHandler.h"
void ErrorHandler::vShowFileNotFoundMessageBox(string &s_message)
{
	MessageBox(NULL, s_message.c_str(), NULL, MB_OK | MB_ICONERROR);
}

