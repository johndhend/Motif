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
CFLAGS+=-I/usr/include -I$(LOCALBASE)/include -I$(PROJ_DIR) -I$(PROJ_DIR)/include -I$(PROJ_DIR)/lib -I$(PROJ_DIR)/demos/lib -I$(PROJ_DIR)/demos/lib/Exm -I$(PROJ_DIR)/demos/lib/Xmd -I$(PROJ_DIR)/demos/lib/Wsm


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

PROG = xmanimate

OBJS = xmanimate.o

UILOBJ = \
  dog.uid dog2.uid \
  plane.uid superman.uid xmanimate.uid

all:: $(PROG) $(UILOBJ)

%.o: *.c
	$(RM) $@ || true
	$(COMPILE) $<

dog.uid:  dog.uil
	$(RM) $@ || true
	../../../clients/uil/uil dog.uil -o dog.uid

dog2.uid:  dog2.uil
	$(RM) $@ || true
	../../../clients/uil/uil dog2.uil -o dog2.uid

plane.uid:  plane.uil
	$(RM) $@ || true
	../../../clients/uil/uil plane.uil -o plane.uid

superman.uid:  superman.uil
	$(RM) $@ || true
	../../../clients/uil/uil superman.uil -o superman.uid

xmanimate.uid:  xmanimate.uil
	$(RM) $@ || true
	../../../clients/uil/uil xmanimate.uil -o xmanimate.uid

$(PROG):  $(OBJS) $(UILOBJ)
	$(RM) $(PROG) || true
	$(LINK) ${INCLUDES} ${LIBS} ${CFLAGS} -L$(PROJ_DIR)/lib/Xm.so -lXm -L$(PROJ_DIR)/lib/Mrm.so -lMrm -L$(PROJ_DIR)/demos/lib/Exm -lExm -lExmMrm -L$(PROJ_DIR)/demos/lib/Xmd -lXmd -L$(PROJ_DIR)/demos/lib/Wsm -lWsm -L$(XLIBPATH) -lXt -lSM -lICE -lXext -lXmu -lX11 -L/usr/lib -lc -lm -o $(PROG) $(OBJS)


.PHONY: clean

clean:
	$(RM) *.o *.uid xmanimate DONE || true
 
