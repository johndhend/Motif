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

OBJS = \
 UilCmd.o           UilDB.o            UilData.o          UilDiags.o          \
 UilKeyTab.o        UilLexAna.o        UilLexPars.o       UilLstLst.o         \
 UilLstMac.o        UilP2Out.o         UilP2Reslv.o        \
 UilSarComp.o       UilSarExp.o        UilSarInc.o         \
 UilSarMod.o        UilSarObj.o        UilSarProc.o       UilSarVal.o         \
 UilSemCSet.o       UilSemVal.o        UilSrcSrc.o        UilSymNam.o         \
 UilSymStor.o       

SRC = \
 UilCmd.c           UilDB.c            UilData.c          UilDiags.c          \
 UilKeyTab.c        UilLexAna.c        UilLexPars.c       UilLstLst.c         \
 UilLstMac.c        UilP2Out.c         UilP2Reslv.c        \
 UilSarComp.c       UilSarExp.c        UilSarInc.c         \
 UilSarMod.c        UilSarObj.c        UilSarProc.c       UilSarVal.c         \
 UilSemCSet.c       UilSemVal.c        UilSrcSrc.c        UilSymNam.c         \
 UilSymStor.c       

# note: tools/wml must be freshly built it puts files in this directory
# note: there is no Uil.c and it is not supposed to be made

all:: uil libUil.a libUil.so

%.o: *.c UilMain.c
	$(RM) $@ || true
	$(COMPILE) $<

uil:	$(SRC) Uil.o Uil.h $(OBJS) UilMain.o
	([ -e UilParser.c ] && [ -e UilMain.c ] && diff -q UilParser.c UilMain.c && $(RM) UilParser.c) || true
	([ -e UilParser.c ] && [ ! -e UilMain.c ] && mv UilParser.c UilMain.c) || true
	$(RM) Uil || true
	$(LINK) -L$(PROJ_DIR)/lib/Xm -lXm -L$(PROJ_DIR)/lib/Mrm -lMrm -L$(XLIBPATH) -lXt -lSM -lICE -lXext -lX11 -lXmu -o uil $(OBJS) UilMain.o


libUil.a:  $(OBJS) uil
	$(RM) libUil.a || true
	$(RM) UilParse.c UilParse.o || true
	cp UilMain.c UilParse.c
	$(COMPILE) -DCALLABLE UilParse.c
	$(AR) libUil.a $(OBJS) UilParse.o

libUil.so: $(SRC) libUil.a uil UilParse.o
	$(RM) libUil.so || true
	$(LINK) -DCALLABLE -shared -fPIC -Wl,-soname,libUil.so.1 -o libUil.so ${INCLUDES} ${LIBS} ${CFLAGS} -L$(PROJ_DIR)/lib/Xm.so -lXm -L$(PROJ_DIR)/lib/Mrm.so -lMrm -L$(XLIBPATH) -lXt -lSM -lICE -lXext -lX11 -lXmu -L/usr/lib -lc $(SRC) UilParse.c


.PHONY: clean

clean:
	$(RM) $(TARGETS) *.o uil libUil.a DONE || true
 
# see tools/wml Makefile for notes about lex yacc
# to note: in the orig distro there is a fiasco of UilParser.c
# UilMain.c being the same file and of "sharing", which has to do
# with using one directory for two different builds; ignore it

# i'd rather have .so in own directory but make isn't helpful with "lex"
# (would be forced to build libUil.a to get lex rebuild which isn't
#  simpler or better).  but we can't re-use the .o and .so will fail
# if it uses them.  it's a run around each and every way.

