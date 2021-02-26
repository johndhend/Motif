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
 MrmIbuffer.o       MrmIentry.o        MrmIfile.o         MrmIheader.o        \
 MrmIindex.o        MrmIindexw.o       MrmIrid.o          MrmIswap.o          \
 MrmItop.o          MrmItopw.o         MrmMessages.o      Mrmappl.o           \
 Mrmcontext.o       Mrmerror.o         Mrmhier.o          Mrmicon.o           \
 Mrminit.o          Mrmlread.o         Mrmlwrite.o        Mrmmodule.o         \
 Mrmos.o            Mrmptrlist.o       Mrmtable.o         Mrmtime.o           \
 Mrmvm.o            Mrmwci.o           Mrmwcrw.o          Mrmwcrwr.o          \
 Mrmwread.o         Mrmwrefs.o         Mrmwvalues.o       Mrmwwrite.o         \


all::	libMrm.a

%.o: *.c
	$(RM) $@ || true
	$(COMPILE) $<
	$(LINK) -o $@

libMrm.a: $(OBJS)
	$(RM) libMrm.a || true
	$(AR) libMrm.a $(OBJS)


.PHONY: clean

clean:
	$(RM) $(TARGETS) *.o libMrm.a DONE || true
 
