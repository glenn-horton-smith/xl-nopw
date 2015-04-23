/*
 *  Simple, transparent screen locker in X11
 *
 *  Based on Danny Dulai's "xl", https://github.com/dannydulai/xl/
 *
 *  Modified by Glenn Horton-Smith as follows:
 *
 *   - Avoids the need for any password management by simply
 *     not having any way to unlock, by password or otherwise.
 *     You must arrange some other way to kill the program.
 *   - Added a countdown so that user has time to hide the terminal
 *     window if this is invoked from the terminal.
 *   - Also added some checks for failure to obtain the pointer
 *     and keyboard grabs.
 *
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int
main(int argc, char *argv[])
{
    Display *display;
    Window root;
    XEvent ev;
    int status;
    int countdown = 5;

    if ((display = XOpenDisplay(NULL)) == NULL) {
	fprintf(stderr, "could not connect to display\n");
	exit(1);
    }

    printf("This display will be transparently locked.\n"
	   "There will be no way to unlock except by killing this program,\n"
	   "which will be impossible to do from this display.\n"
	   "Locking in ");
    for (; countdown > 0; --countdown) {
      printf("%d... ", countdown);
      fflush(stdout);
      sleep(1);
    }
    printf("0.\n");

    root = DefaultRootWindow(display);
    status = XGrabPointer(display, root, 0,
			  ButtonPressMask|ButtonReleaseMask|PointerMotionMask,
			  GrabModeAsync, GrabModeAsync,
			  None, None, CurrentTime);
    if (status != GrabSuccess) {
      fprintf(stderr, "Could not grab pointer.\n");
      exit(1);
    }
    status = XGrabKeyboard(display, root, 0,
			   GrabModeAsync, GrabModeAsync, CurrentTime);
    if (status != GrabSuccess) {
      fprintf(stderr, "Could not grab keyboard.\n");
      exit(1);
    }

    printf("Locked.\n");
    while (1) {
      XNextEvent(display, &ev);
    }
}
