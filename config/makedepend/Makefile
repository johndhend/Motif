# Makefile

#  remember $() are make and ${} are shell
#  depends are not used:  specified per case in preprequisites
#  $@ means the target name of the rule where found
#  $< means name of file in a list
#  RM are done to insure a stale file doesn't get re-used
#  and tab /n are required as below but pretty elsewhere ...
#  the following is done if to-build is older than it's prerequisites or DNE

#to-be-built:  pre-required to exist and be fresh so it can be
#<tab>shell commands to create to-build
#<newline>



CFLAGS+=-I/usr/include -I$(LOCALBASE)/include -I$(LOCALBASE)/include/X11 -I$(PROJ_DIR)


XLIBPATH=$(LOCALBASE)/lib

#STDINCDIR = /usr/include
#STDINC_DEFINES = -DINCLUDEDIR=\"$(STDINCDIR)\"
#OSUF = .o
#OSUF_DEFINES = -DOBJSUFFIX=\"$(OSUF)\"

LEX=lex -L
RM=rm
MV=mv
CC=cc
AR=ar -rc
RANLIB=ranlib
LEXLIB=-lfl
YACC=yacc -l
INCLUDES ?=
LIBS ?=
LDFLAGS ?=
DEPENDENCIES=
COMPILE = cc -c ${INCLUDES} ${LIBS} ${CFLAGS} $(STDINC_DEFINES) $(OSUF_DEFINES)
LINK    = cc

OBJS = \
 cppsetup.o         ifparser.o         include.o          \
 parse.o            pr.o               

all:: first makedepend

.PHONY: first
first:
	[ ! -e def.h.old ] && cp def.h def.h.old
	echo '#define INCLUDEDIR "/usr/include"' >> def.h
	echo '#define OBJSUFFIX ".o"' >> def.h

%.o: *.c
	$(RM) $@ || true
	$(COMPILE) $<

makedepend:	$(OBJS) main.o first
	$(RM) makedepend || true
	$(LINK) -L/usr/lib -lc -o makedepend $(OBJS) main.o

.PHONY: clean

clean:
	$(RM) *.o DONE || true
	$(MV) def.h.old def.h || true
 
# didn't make a redistributable WmWsmLib.a because it isn't an install item

