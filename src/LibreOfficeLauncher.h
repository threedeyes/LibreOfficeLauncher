/*
 * Copyright 2020, Gerasim Troeglazov, 3dEyes@gmail.com
 * Distributed under the terms of the MIT License.
 */

#ifndef LIBREOFFICE_LAUNCHER_H
#define LIBREOFFICE_LAUNCHER_H

#include <Application.h>
#include <String.h>
#include <Resources.h>
#include <Roster.h>
#include <Mime.h>
#include <Path.h>

class LibreOfficeLauncherApp : public BApplication {
	public:
		LibreOfficeLauncherApp(char *signature, int argc, char **argv);
		~LibreOfficeLauncherApp() {};
		void			RefsReceived(BMessage *pmsg);
		void			ArgvReceived(int32 argc, char **argv);
		virtual void 	ReadyToRun();
	private:
		BPath	  		LauncherPath(const char *dir);
		BString 		LauncherName(void);
		BMessenger  	fTrackerMessenger;

		char			**argv;
};

#endif
