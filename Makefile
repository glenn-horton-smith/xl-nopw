
X11HOME = /usr/X11R6

CC	= gcc
CFLAGS	= -O2 -Wall -I${X11HOME}/include
LIBS	= -L${X11HOME}/lib -lX11

# uncomment if you are running under solaris
#LIBS   += -lnsl -lsocket

OBJS = xl-nopw.o
EXE = xl-nopw

all:	$(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)

realclean: clean
	rm -f $(EXE)
