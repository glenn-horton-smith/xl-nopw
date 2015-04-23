xl-nopw: A simple transparent X11 lock with no password handling
==

This is a simple, transparent screen locker for X11, based on
Danny Dulai's [xl](https://github.com/dannydulai/xl/).

The goal here is to have very simple, very small, very robust program
to prevent passers-by from interacting with the screen.  All this
program does is lock your keyboard and mouse.  The screen is not
blanked, which is useful if you want to leave a display running for
public viewing.  The only way to unlock the screen is by killing the
program somehow, which cannot be done through the locked screen.

The main differences with respect to the original xl are:

* It avoids the need for any password management by simply
  not having any way to unlock, by password or otherwise.
  You must arrange some other way to kill the program.
  
* A countdown has been added so that user has time to hide the
  terminal window if this is invoked from the terminal.
  
* Added some checks for failure to obtain the pointer
  and keyboard grabs.

Display manager hot buttons and keys
--

Some display managers intercept key presses and mouse movements in
ways that bypass pointer and keyboard grabs.  In particular, a hidden
Unity launcher bar will still appear when the mouse pointer is moved
to the edge of the window, and the "Meta" and "Left-Alt" keys might
still cause HUD's to appear.  This is probably harmless as the user
still can't type or click on anything.  But to achieve complete
non-interactivity, you'd have to disable these features or simply use
a different windows manager.  (twm, anyone?)

Alternative approaches
--

* xinput can be used to completely disable input devices, as described
[here](http://unix.stackexchange.com/questions/17170/disable-keyboard-mouse-input-on-unix-under-x).
An advantage of that approach is that the devices are totally
disabled, such that not even the display managers can receive them.  A
disadvantage is that a visitor could plug in another device and it
might start working by default, unless you take special actions to
configure X differently; or simply unplugging and reconnecting a
device could do this; or a mouse might even keep re-enabling itself,
as described
[here](https://www.centos.org/forums/viewtopic.php?f=13&t=46795).  The
basic xinput approach also needs a little manual attention to
find the correct device number(s).

* If you have physical control of the computer and a way of stopping
people from plugging their own keyboards or pointers into it, you
could simply lock away or remove the keyboard and mouse.

* [xtrlock](http://manpages.ubuntu.com/manpages/karmic/man1/xtrlock.1x.html)
was an old favorite, but last time I checked it only supported
passwords in /etc/passwd or /etc/shadow.  Using /etc/shadow required
xtrlock to run with elevated privileges.  A version supporting PAM
that can be run unprivileged is available on github as
[xtrlock-pam](https://github.com/aanatoly/xtrlock-pam).  These both
suffer from the feature noted above under "Display manager hot buttons
and keys", but they have the ability to unlock the screen with a
password, which might be nice depending on your application.
