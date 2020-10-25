/*
 * Copyright 2020, Gerasim Troeglazov, 3dEyes@gmail.com
 * Distributed under the terms of the MIT License.
 */

#include <Application.h>
#include <String.h>
#include <Resources.h>
#include <Roster.h>
#include <Mime.h>
#include <Path.h>
#include <AppFileInfo.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "LibreOfficeLauncher.h"

LibreOfficeLauncherApp::LibreOfficeLauncherApp(char *signature, int argc, char **argv)
	: BApplication(signature)
{
	this->argc = argc;
	this->argv = argv;
	
}

LibreOfficeLauncherApp::~LibreOfficeLauncherApp()
{
}


BPath
LibreOfficeLauncherApp::LauncherPath(const char *dir)
{
	app_info inf;
   	be_app->GetAppInfo(&inf);
   	BPath bpath = BPath(&(inf.ref));
   	BPath par;
   	bpath.GetParent(&par);
   	par.Append(dir);
	return(par);
}

BString
LibreOfficeLauncherApp::LauncherName(void)
{
	return "LibreOffice";
}

void
LibreOfficeLauncherApp::RefsReceived(BMessage *pmsg)
{
	if (pmsg->HasMessenger("TrackerViewToken")) {
		pmsg->FindMessenger("TrackerViewToken", &fTrackerMessenger);
	}

	uint32 type;
	int32 count;
	status_t ret = pmsg->GetInfo("refs", &type, &count);
	if (ret != B_OK || type != B_REF_TYPE)
		return;

	entry_ref ref;
	for (int32 i = 0; i < count; i++) {
   		if (pmsg->FindRef("refs", i, &ref) == B_OK)
   		 {
   		    BPath file=BPath(&ref);
   		    char temp[B_PATH_NAME_LENGTH];
   		    sprintf(temp,"\"%s/%s\" --nologo \"%s\" &",
   		    	LauncherPath("program"),
   		    	LauncherName().String(),
   		    	file.Path());
   		    system(temp);
   		    Quit();
   		 }
   	}
}


void
LibreOfficeLauncherApp::ArgvReceived(int32 argc, char **argv)
{
	BMessage *pmsg = NULL;
	for (int32 i = 1; i < argc; i++) {
		entry_ref ref;
		status_t err = get_ref_for_path(argv[i], &ref);
		if (err == B_OK) {
			if (!pmsg) {
				pmsg = new BMessage;
				pmsg->what = B_REFS_RECEIVED;
			}
			pmsg->AddRef("refs", &ref);
		}
	}
	if (pmsg) {
		RefsReceived(pmsg);
		delete pmsg;
	}
}

void
LibreOfficeLauncherApp::ReadyToRun()
{
    char temp[B_PATH_NAME_LENGTH];
    LauncherPath("");
    BString appname;
    if (strstr(argv[0], "Writer") != 0)
    	appname.SetTo("--writer");
    if (strstr(argv[0], "Calc") != 0)
    	appname.SetTo("--calc");
    if (strstr(argv[0], "Draw") != 0)
    	appname.SetTo("--draw");
    if (strstr(argv[0], "Impress") != 0)
    	appname.SetTo("--impress");
    if (strstr(argv[0], "Math") != 0)
    	appname.SetTo("--math");
    if (strstr(argv[0], "Database") != 0)
    	appname.SetTo("--base");
    if (strstr(argv[0], "Web") != 0)
    	appname.SetTo("--web");
    sprintf(temp, "\"%s/%s\" --nologo %s &",
    	LauncherPath("program").Path(),
    	LauncherName().String(),
    	appname.String());
    system(temp);
    Quit();
}


int main(int argc, char **argv)
{
	char signature[B_MIME_TYPE_LENGTH];
	signature[0] = '\0';

	BFile appFile(argv[0], B_READ_ONLY);
	if (appFile.InitCheck() == B_OK) {
		BAppFileInfo info(&appFile);
		if (info.InitCheck() == B_OK) {
			if (info.GetSignature(signature) != B_OK)
				signature[0] = '\0';
		}
	}

	LibreOfficeLauncherApp application(signature, argc, argv);
	application.Run();
	return 0;
}
