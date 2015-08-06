/*************************************************/
/* WinAmp Control Centre                         */
/* Version 1.4.3                                 */
/*                                               */
/* Copyright (c) Owen Rudge 2001-2015            */
/*************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
	
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define IS_COMMAND_LINE(cmd)                    CheckCommandLine(argc, argv, cmd)
#define IS_COMMAND_LINE_ARG(cmd, i)             lstrcmpi(argv[i], cmd)

int CheckCommandLine(int argc, char **argv, char *cmd);
int ParseCommandLine(char *line, char **argv, int max_argc);
void RunThroughCmdLineOptions(int argc, char **argv, HWND hwndWinamp, char *szINIFileName);
void PlayPause(HWND hwndWinamp);

char copyright_str[] = "Winamp Control Centre 1.4.2. Copyright \xA9 Owen Rudge 2001-2015. All Rights Reserved. www.owenrudge.net";
char build_date[] = "Built on " __DATE__ " at " __TIME__ ".";

BOOLEAN PathOnCmdLine = FALSE;

int WINAPI WinMain(HINSTANCE hCurInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndWinamp;
	char szINIFileName[250];
	char szFileName[250];
	char szPathStr[250];
	char szAppPath[MAX_PATH];
	char szWinClass[250];
	char *pathloc;
	BOOLEAN DisplayError;
	UINT ret;
	int argc;
	char *argv[64]; // max 64 command line arguments

	argc = ParseCommandLine(GetCommandLine(), argv, 64);

	GetModuleFileName(hCurInstance, szFileName, 250);

	pathloc = strrchr(szFileName, '\\');

	if (pathloc == NULL)
		strcpy(szINIFileName, "WINAMPCC.INI"); // don't want any errors, so let's play it safe
	else
	{
		memset(szPathStr, 0, sizeof(szPathStr));
		memcpy(szPathStr, szFileName, pathloc-szFileName);

		strcpy(szINIFileName, szPathStr);
		strcat(szINIFileName, "\\WINAMPCC.INI"); // dirty cludge, but it seems to be required :-(
	}

	GetPrivateProfileString("Configuration", "Class", "Winamp v1.x", szWinClass, sizeof(szWinClass), szINIFileName);

	if (strlen(szWinClass) == 0)
		strcpy(szWinClass, "Winamp v1.x");

	hwndWinamp = FindWindow(szWinClass, NULL);

	if (hwndWinamp == NULL)
	{
		if (GetPrivateProfileInt("Configuration", "Autoload", 0, szINIFileName) == 1)
		{
			if (GetPrivateProfileInt("Configuration", "PathOnCmdLine", 0, szINIFileName) == 1)
			{
				PathOnCmdLine = TRUE;
				strcpy(szAppPath, argv[1]);
			}
			else
			{
				PathOnCmdLine = FALSE;
				GetPrivateProfileString("Configuration", "Path", "", szAppPath, sizeof(szAppPath), szINIFileName);
			}

			if (strlen(szAppPath) == 0)
				DisplayError = TRUE;
			else
			{
				ret = WinExec(szAppPath, SW_NORMAL);

				if (ret < 32)
					MessageBox(NULL, "Unable to start Winamp.", "Winamp Control Centre", MB_OK | MB_ICONEXCLAMATION);
				else
				{
					Sleep(GetPrivateProfileInt("Configuration", "WaitLength", 1000, szINIFileName));

					hwndWinamp = FindWindow(szWinClass, NULL);

					if ((IS_COMMAND_LINE("/HIDE") == 0) || (GetPrivateProfileInt("Configuration", "HideOnLoad", 0, szINIFileName) == 1))
					{
						ShowWindow(hwndWinamp, SW_MINIMIZE);
						ShowWindow(hwndWinamp, SW_HIDE);
					}
				}
			}
		}

		if (DisplayError == TRUE)
		{
			MessageBox(NULL, "Winamp is not running.", "Winamp Control Centre", MB_OK | MB_ICONEXCLAMATION);
			return(0);
		}
	}

	if (DisplayError != TRUE)
		RunThroughCmdLineOptions(argc, argv, hwndWinamp, szINIFileName);

	return(TRUE);
}

int ParseCommandLine(char *line, char **argv, int max_argc)
{
	int n = 0;

	do
	{
		// skip whitespace
		while (*line == ' ' || *line == '\t')
		{
			line++;
		}

		// end?
		if (*line == 0)
			break;

		// special handling when quoted
		if (*line == '"')
		{
			argv[n++] = ++line;

			while (*line != '"')
			{
				if (*line == 0)
					return n;

				line++;
			}
		}
		else
		{
			argv[n++] = line;

			while (*line != ' ' && *line != '\t')
			{
				if (*line == 0)
					return n;

				line++;
			}
		}

		*line++ = 0;
	}
	while (n != max_argc);

	return n;
}

int CheckCommandLine(int argc, char **argv, char *cmd)
{
	int i;

	for (i = 1; i < argc; i++)
	{
		if (lstrcmpi(argv[i], cmd) == 0)
			return(0);
	}

	return(1);
}

void RunThroughCmdLineOptions(int argc, char **argv, HWND hwndWinamp, char *szINIFileName)
{
	UINT uMsg;
	int i, start;

	if (PathOnCmdLine == TRUE)
		start = 2;
	else
		start = 1;

	for (i = start; i < argc; i++)
	{
		if (IS_COMMAND_LINE_ARG("/HIDE", i) == 0)
		{
			ShowWindow(hwndWinamp, SW_MINIMIZE);
			ShowWindow(hwndWinamp, SW_HIDE);
		}
		else if (IS_COMMAND_LINE_ARG("/SHOW", i) == 0)
		{
			ShowWindow(hwndWinamp, SW_SHOWNORMAL);
		}
		else if (IS_COMMAND_LINE_ARG("/FLIPSHOW", i) == 0)
		{
			if (IsWindowVisible(hwndWinamp) == TRUE)
			{
				ShowWindow(hwndWinamp, SW_MINIMIZE);
				ShowWindow(hwndWinamp, SW_HIDE);
			}
			else
				ShowWindow(hwndWinamp, SW_SHOWNORMAL);
		}
		else if (IS_COMMAND_LINE_ARG("/TOFRONT", i) == 0)
		{
			SetForegroundWindow(hwndWinamp);
		}
		else if (IS_COMMAND_LINE_ARG("/PLAYPAUSE", i) == 0)
		{
			PlayPause(hwndWinamp);
		}
		else
		{
			if (IS_COMMAND_LINE_ARG("/PLAY", i) == 0)
				uMsg = 40045;
			else if (IS_COMMAND_LINE_ARG("/STOP", i) == 0)
				uMsg = 40047;
			else if (IS_COMMAND_LINE_ARG("/NEXT", i) == 0)
				uMsg = 40048;
			else if (IS_COMMAND_LINE_ARG("/PREV", i) == 0)
				uMsg = 40044;
			else if (IS_COMMAND_LINE_ARG("/PAUSE", i) == 0)
				uMsg = 40046;
			else
				uMsg = GetPrivateProfileInt("Commands", argv[i], 0, szINIFileName);

			if (uMsg != 0)
			{
				SendMessage(hwndWinamp, WM_COMMAND, uMsg, (DWORD)NULL);
				Sleep(0);
			}
		}
	}
}

void PlayPause(HWND hwndWinamp)
{
	UINT uMsg;
	int ret;

	// Get current playback status
	ret = SendMessage(hwndWinamp, WM_USER, 0, 104);

	if (ret == 1) // Currently playing
		uMsg = 40046; // Pause
	else // Currently paused or stopped
		uMsg = 40045;

	SendMessage(hwndWinamp, WM_COMMAND, uMsg, (DWORD)NULL);
}
