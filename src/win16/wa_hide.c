/*************************************************/
/* WinAmp Control Centre                         */
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

int PASCAL WinMain(HINSTANCE hCurInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndWinamp;

	hwndWinamp = FindWindow("Winamp v1.x", NULL);

	if (hwndWinamp == NULL)
	{
		MessageBox(NULL, "Winamp is not running.", "Winamp Control Centre", MB_OK);
		return(0);
	}
	else
	{
		ShowWindow(hwndWinamp, SW_MINIMIZE);
		ShowWindow(hwndWinamp, SW_HIDE);
	}

	return(0);
}
