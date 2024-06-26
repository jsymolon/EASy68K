/*
 * EASy68K.cpp
 *
 *  Created on: Aug 5, 2023
 *      Author: jsymolon
 */
#include "../include/EASy68K.h"
#include "../include/MainFrame.h"
#include "../include/extern.h"

//#ifndef TESTINGON
IMPLEMENT_APP(EASy68K)
// A macro that tells wxWidgets to create an instance of our application
//#endif

bool EASy68K::OnInit() {
	mainframe = new MainFrame(_("EASy68K"), wxDefaultPosition,
			wxSize(1000, 600), this);
	mainframe->Show(true); // show the window
	SetTopWindow(mainframe); // and finally, set it as the main window
	return (true);
}
