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



# this lib has include files btw
CFLAGS+=-I/usr/include -I$(LOCALBASE)/include -I$(PROJ_DIR) -I$(PROJ_DIR)/include -I$(PROJ_DIR)/lib


XLIBPATH=$(LOCALBASE)/lib

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
COMPILE = cc -c ${INCLUDES} ${LIBS} ${CFLAGS}
DEPENDENCIES=
LINK    = cc

# makes, ie Xm.msg XmMsgI.h, so do before Xm

all::  XmMsgI.h MrmMsgI.h mkmsgcat mkcatdefs

XmMsgI.h:	mkmsgcat ../../lib/Xm/Messages.c
	$(RM) Xm.msg XmMsgI.h || true
	./mkmsgcat -Xm ../../lib/Xm/Messages.c
	cp Xm.msg XmMsgI.h ../../lib/Xm/
	cp Xm.msg XmMsgI.h ../../lib/Xm.so/

MrmMsgI.h:	mkmsgcat ../../lib/Mrm/MrmMessages.c
	$(RM) Mrm.msg MrmMsgI.h || true
	./mkmsgcat -Mrm ../../lib/Mrm/MrmMessages.c
	cp Mrm.msg MrmMsgI.h ../../lib/Mrm/
	cp Mrm.msg MrmMsgI.h ../../lib/Mrm.so/

mkcatdefs:
	$(RM) $@ || true
	$(COMPILE) mkcatdefs.c
	$(LINK) -o mkcatdefs mkcatdefs.o

mkmsgcat:
	$(RM) $@ || true
	$(COMPILE) mkmsgcat.c
	$(LINK) -o mkmsgcat mkmsgcat.o


.PHONY: clean

clean:
	$(RM) mkcatdefs mkmsgcat XmMsgI.h Xm.msg MrmMsgI.h Mrm.msg || true

