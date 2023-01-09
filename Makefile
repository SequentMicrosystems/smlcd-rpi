DESTDIR?=/usr
PREFIX?=/local

ifneq ($V,1)
Q ?= @
endif

CC	= gcc
CFLAGS	= $(DEBUG) -Wall -Wextra $(INCLUDE) -Winline -pipe 

LDFLAGS	= -L$(DESTDIR)$(PREFIX)/lib
LIBS    = -lpthread -lrt -lm -lcrypt

SRC	=	src/smlcd.c src/comm.c src/thread.c

OBJ	=	$(SRC:.c=.o)

all:	smlcd

smlcd:	$(OBJ)
	$Q echo [Link]
	$Q $(CC) -o $@ $(OBJ) $(LDFLAGS) $(LIBS)

.c.o:
	$Q echo [Compile] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

.PHONY:	clean
clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) smlcd *~ core tags *.bak

.PHONY:	install
install: smlcd
	$Q echo "[Install]"
	$Q cp smlcd		$(DESTDIR)$(PREFIX)/bin
ifneq ($(WIRINGPI_SUID),0)
	$Q chown root.root	$(DESTDIR)$(PREFIX)/bin/smlcd
	$Q chmod 4755		$(DESTDIR)$(PREFIX)/bin/smlcd
endif


.PHONY:	uninstall
uninstall:
	$Q echo "[UnInstall]"
	$Q rm -f $(DESTDIR)$(PREFIX)/bin/smlcd
	$Q rm -f $(DESTDIR)$(PREFIX)/man/man1/smlcd.1
