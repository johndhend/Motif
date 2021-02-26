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
CFLAGS+=-I/usr/include -I$(LOCALBASE)/include -I$(PROJ_DIR) -I$(PROJ_DIR)/include -I$(PROJ_DIR)/lib -I$(PROJ_DIR)/demos/lib -I$(PROJ_DIR)/demos/lib/Exm -I$(PROJ_DIR)/demos/lib/Xmd -I$(PROJ_DIR)/demos/lib/Wsm -I..


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

OBJS = Container.o

all:: $(OBJS)

%.o: *.c
	$(RM) $@ || true
	$(COMPILE) $<

.PHONY: clean

clean:
	$(RM) *.o bboxdemo DONE || true
 
