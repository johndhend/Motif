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
#COMPILE = cc -c ${INCLUDES} ${LIBS} ${CFLAGS}
DEPENDENCIES=
LINK    = cc

SRC = \
 MrmIbuffer.c       MrmIentry.c        MrmIfile.c         MrmIheader.c        \
 MrmIindex.c        MrmIindexw.c       MrmIrid.c          MrmIswap.c          \
 MrmItop.c          MrmItopw.c         MrmMessages.c      Mrmappl.c           \
 Mrmcontext.c       Mrmerror.c         Mrmhier.c          Mrmicon.c           \
 Mrminit.c          Mrmlread.c         Mrmlwrite.c        Mrmmodule.c         \
 Mrmos.c            Mrmptrlist.c       Mrmtable.c         Mrmtime.c           \
 Mrmvm.c            Mrmwci.c           Mrmwcrw.c          Mrmwcrwr.c          \
 Mrmwread.c         Mrmwrefs.c         Mrmwvalues.c       Mrmwwrite.c         \

all::	libMrm.so

libMrm.so:
	$(RM) libMrm.so || true
	$(LINK) -shared -fPIC -Wl,-soname,libMrm.so -o libMrm.so ${INCLUDES} ${LIBS} ${CFLAGS} -L$(PROJ_DIR)/lib/Xm.so -lXm -L$(XLIBPATH) -lXt -lSM -lICE -lXext -lX11 -lXmu -L/usr/lib -lc $(SRC)


.PHONY: clean

clean:
	$(RM) $(TARGETS) *.o libMrm.so DONE || true
 

