WINAMP CONTROL CENTRE
Version 1.4.3

Copyright © Owen Rudge 2001-2015
================================

Thank you for downloading my Winamp Control Centre. This consists
of a collection of very small programs that you can use to control
Winamp with in a variety of scenarios. Please note that Winamp
Control Centre will only work with Winamp 2.x and 5.x (and possibly 1.x)
- it will not work with Winamp3.

The following files are included:

readme.txt           You're reading it now.
winampcc.exe         Main executable, which can control Winamp in almost
                     any desirable way, by specifying settings in 
                     and is extendable.
winampcc.ini         INI file for winampcc.exe

"winampcc.exe" is the preferred executable to use, and is described in the
"Using winampcc.exe" section below.

The following legacy applications are also included. These are all 16-bit
applications and are only useful for Windows 95/98/Me, where they arguably
execute faster than winampcc.exe:

wa_hide.exe          Run this program to hide Winamp.
wa_next.exe          Run this program to play the next track.
wa_pause.exe         Run this program to pause/unpause Winamp.
wa_play.exe          Run this program to start/restart playing.
wa_prev.exe          Run this program to play the previous track.
wa_show.exe          Run this program to show Winamp.
wa_stop.exe          Run this program to stop playing.

These applications will be slower on Windows 2000 or later, and will not run
at all on 64-bit versions of Windows.

USING WINAMPCC.EXE
==================

If you just run "winampcc" on its own, nothing will happen (assuming
you have Winamp running - if it's not running, you'll receive an
error message). To make it do something, you need to use command-line
arguments.

The following command-line arguments are available by default:

/SHOW          Shows Winamp
/HIDE          Hides Winamp
/PLAY          Starts/restarts playing
/PAUSE         Pauses/unpauses Winamp
/STOP          Stops playing
/NEXT          Plays the next track
/PREV          Plays the previous track
/FLIPSHOW      Show Winamp if it's hidden, hide it if it's visible
/TOFRONT       Brings Winamp to the front of the screen
/PLAYPAUSE     Pauses/unpauses Winamp if currently playing; starts playing if stopped

However, WinampCC is customisable, in that you can add new actions.
This is what winampcc.ini is for. If you look at it, you'll see the
following (by default):

   ; Winamp Control Centre 1.4.3
   ; Configuration File
   ;
   ; See README.TXT for more information
   ;
   ; Overview of this file
   ; ---------------------
   ;
   ; [...]
   ;
   ; Please see README.TXT for information on the [Commands] section of this file.
   
   [Configuration]
   Class=Winamp v1.x
   Path=C:\Program Files\Winamp\Winamp.exe
   Autoload=1
   WaitLength=150
   HideOnLoad=1
   PathOnCmdLine=1

   [Commands]
   PLAY=40045
   PAUSE=40046
   STOP=40047
   NEXT=40048
   PREV=40044
   ...etc...

If you run "winampcc pause" (without the quotation marks), you will
find that the music is paused/unpaused. Try commenting out the
PAUSE=40046 line (place a ';' before it) and save the file. Then
type "winampcc pause". It won't do anything. This is a custom
action. As an aside, WinampCC is case-insensitive, so "PAUSE", "pause"
and "PaUsE" would all be valid.

Note also that the /PLAY, /PAUSE, etc, commands listed above are
built in, and will work even if no winampcc.ini is present or if all
commands are deleted from the INI file.

With Winamp Control Centre 1.4, you can specify multiple commands at once,
with a limit of 63 arguments. For instance:

   winampcc /next /next /next /play /forward_5secs

will forward 3 places in the playlist, and start playing 5 seconds into
the song.

How does 40046 refer to Pause? Well, each button Winamp has has an
internal ID which Windows sends to Winamp when you click it. 40046
is the ID for Pause. Try adding the following line to the file:

/MAKE-SOME-MUSIC=40045

Then run "winampcc /make-some-music". Winamp will (re-)start playing.
A list of extra IDs is included in winampcc.ini at the bottom. For
the full list of IDs, see the Nullsoft Developer Network at
http://dev.winamp.com/.

Adding a Default Action
-----------------------

If you want something to happen when you run "winampcc" without any
command-line parameters, add a line like:

=40046

to winampcc.ini. If you enter nothing on the command line, the music
will pause.

THE CONFIGURATION SECTION OF WINAMPCC.INI
=========================================

The [Configuration] section of winampcc.ini was new in Winamp Control
Centre 1.2. It is optional, and lets you control several enhanced
features that are new in this release.

Class
-----

This is the window class of the Winamp window. Usually "Winamp v1.x",
but this can be set via Winamp command line parameters - if you run
multiple instances of Winamp with different window classes, you can use
this to alter which instance to control.

Path
----

Path to Winamp. Required if Autoload is set to 1, unless PathOnCmdLine is
set to 1.

Autoload 
--------

If set to 1, Winamp automatically loads when you call Winamp Control
Centre.

WaitLength
----------

The length of time to wait, in milliseconds, between starting Winamp and
sending a command. Slower computers will require a longer wait. If you
set this value too low, Winamp may load but the command you asked for may
not be picked up by Winamp.

HideOnLoad
----------

If set to 1, Winamp will be hidden after it loads.

PathOnCmdLine
-------------

If set to 1, Winamp Control Centre will look for the path to Winamp as the
first command line argument, and will ignore the Path configuration option
completely. The path must be enclosed in quotation marks if it contains
spaces. For example:

   winampcc "C:\Program Files\Winamp\Winamp.exe" /play

is valid, but:

   winampcc C:\Program Files\Winamp\Winamp.exe /play

will not work at all.

CREATING A WINAMP TOOLBAR
=========================

On all versions of Windows since Windows 98 (or 95/NT 4.0 with IE4),
you can create a toolbar in the task bar which controls Winamp. To do
this:

1. Create a folder somewhere and name it "Winamp".

2. Create a shortcut to "winampcc.exe /play" in here and name it "Play".
   You can use the "Change Icon" option to select a Play icon from the
   winampcc.exe program.

3. Repeat step 2 for "/stop", "/pause", "/prev" and "/next" command
   line arguments. (If you're still running Windows 95/98/Me, you may
   prefer to use the wa_play.exe, etc, executables).

4. Right-click on the taskbar, point to Toolbars and choose New
   Toolbar...

5. Browse to the folder you created and click OK.

6. You should now have a Winamp toolbar in your taskbar. By default,
   you have a "Winamp" title and a caption for each button. To save
   space, you can turn these off by right-clicking an empty space on
   the Winamp toolbar or right-clicking the little "movable band" (if
   "Lock Taskbar" isn't enabled) and unchecking "Show Text" and
   "Show Title".

7. Launch Winamp (if you have not enabled Autoload in winampcc.ini) and
   click the Play button in the taskbar. Your music should start playing.
   Test the other buttons, and enjoy!

LICENCE
=======

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

VERSION HISTORY
===============

New in version 1.4.3 is the /PLAYPAUSE switch, enabling you to start playing
music if Winamp is currently stopped, or pause/unpause if Winamp is currently
playing. Handy if, like me, you have a combined Play/Pause button on your keyboard
that you want to map.

Version 1.4.2 did not contain any new functionality, but marked the open
source release of Winamp Control Centre under the GNU General Public License.
The source code for Winamp Control Centre can be downloaded from
www.owenrudge.net/utils/winampcc, and if you wish to offer modifications,
suggestions or new features for the application, you can do so on the
GitHub site linked from the above page.

Additionally, the "previous" and "next" icons have been increased to 4-bit
colour depth (previously 1-bit) because the 1-bit icons seemed to cause issues
on Windows XP or later (randomly being replaced with other icons in Explorer or
the taskbar).

New in version 1.4.1 is a switch, /TOFRONT, which brings the Winamp window to the
front of the screen - useful if you want to open a Winamp window, but Winamp
is hidden behind another program.

New in version 1.4 was support for specifying the path to Winamp on the
command line. Winamp Control Centre can now also process multiple commands at
once. See below for details.

New in version 1.3 was an option, /FLIPSHOW, to show Winamp if it's hidden,
or hide it if it's currently shown. I have also included more switches by
default in the WINAMPCC.INI, as well as the NSDN API reference (see
below).

New in version 1.2 were several enhancements to WINAMPCC.EXE. You can
now have Winamp automatically load when you run WINAMPCC.EXE, and it
can be automatically hidden at load too.

New in version 1.1 was WINAMPCC.EXE. This is a 32-bit program that
lets you do everything the 16-bit programs could do, and more. It
will also be faster on Windows NT/2000/XP.

If you have any problems, comments or queries about this software, e-mail
me - contact details are available at www.owenrudge.net/contact.

Owen Rudge, 6th August 2015
http://www.owenrudge.net/

----------------------------------------------------------------------------------
This software was built listening to Winamp. It was compiled using Open Watcom
C/C++, which generates very small code. For information on the Winamp API,
please visit http://dev.winamp.com/.

These programs will run under Windows 3.1 or higher, although it's unlikely you'll
have Winamp itself running on any version of Windows before Windows 95 or NT
3.51. :)
----------------------------------------------------------------------------------
