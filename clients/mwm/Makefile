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

#ROJ_DIR=/usr/local/src/motif-2.5.0-build

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
 WmCDInfo.o         WmCDecor.o         WmCEvent.o         WmCPlace.o          \
 WmCmd.o            WmColormap.o       WmError.o          WmEvent.o           \
 WmFeedback.o       WmFunction.o       WmGraphics.o       WmIDecor.o          \
 WmIPlace.o         WmIconBox.o        WmImage.o          WmInitWs.o          \
 WmKeyFocus.o       WmMain.o           WmManage.o         WmMenu.o            \
 WmProperty.o       WmProtocol.o       WmResCvt.o         WmResParse.o        \
 WmResource.o       WmSignal.o         WmWinConf.o        WmWinInfo.o         \
 WmWinList.o        WmWinState.o       WmWsm.o            WmXSMP.o            \
 debug.o            disp.o             free.o             pack.o              \
 recv.o             send.o             util.o             utm_send.o          \
 version.o          


all:: first mwm


.PHONY: first
first:
	cp WmWsmLib/*.c .
	cp WmWsmLib/*.h .

%.o: *.c first
	$(RM) $@ || true
	$(COMPILE) $<

mwm:	WmMain.o WmMain.c first $(OBJS)
	$(RM) mwm || true
	$(LINK) -L$(PROJ_DIR)/lib/Xm.so -lXm -L$(XLIBPATH) -lXt -lSM -lICE -lXext -lX11 -L/usr/lib -lc -lm -o mwm $(OBJS)


.PHONY: clean

clean:
	$(RM) $(TARGETS) *.o mwm || true
 
# didn't make a redistributable WmWsmLib.a because Motif does not install it

