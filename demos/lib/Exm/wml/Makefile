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
CPP = cpp

WMLSRC = $(PROJ_DIR)/tools/wml

# this wmldbcreate.c is moslty same as in wlmsrc - has Exm.h included
 
SRCS1 =	wmldbcreate.c
OBJS1 =	wml.o
 
SRCS = $(SRCS1) $(SRCS2)
OBJS = $(OBJS1) $(OBJS2)
 
YACCTARGETS = UilLexPars.c	UilLexPars.h

WMLTARGETS = UilConst.h	UilKeyTab.h	 \
	UilSymArTa.h	UilSymArTy.h	UilSymCSet.h	UilSymCtl.h \
	UilSymEnum.h	UilSymGen.h	UilSymNam.h	UilSymRArg.h \
	UilSymReas.h	UilTokName.h	UilUrmClas.h	UilSymChCl.h \
	UilSymChTa.h

TARGETS = $(WMLTARGETS) $(YACCTARGETS) 
 
TABLE = Exm.wml
WMDTABLE = Exm.wmd
REPORT = wml.report

all:: $(TARGETS) $(WMDTABLE)

.ifdef VERSION_IS_NOT_DEFINED
$(TARGETS):	$(WMLTOOLS) $(TABLE)
	$(RM) UilDBDef.h || true
	cp $(WMLSRC)/UilDBDef.h .
	$(RM) $(TARGETS) $(REPORT) wml-uil.mm || true
	$(YACC) -d $(YACCFLAGS) $(WMLSRC)/Uil.y
	$(MV) y.tab.c UilLexPars.c
	$(MV) y.tab.h UilLexPars.h
	$(CLIENTENVSETUP) $(WMLSRC)/wmluiltok < $(WMLSRC)/Uil.y > tokens.dat || true
	$(CPP) -I$(WMLSRC) $(TABLE) | $(WMLSRC)/wml
	$(RM) tokens.dat
	$(RM) wml-uil.mm
.else
$(TARGETS):	$(WMLTOOLS) $(TABLE)
	$(RM) UilDBDef.h || true
	cp $(WMLSRC)/UilDBDef.h .
	$(RM) $(TARGETS) $(REPORT) wml-uil.mm || true
	$(YACC) -d $(YACCFLAGS) $(WMLSRC)/Uil.y
	$(MV) y.tab.c UilLexPars.c
	rm -f UilLexPars.h
	echo "#undef VERSION" > UilLexPars.h
	cat y.tab.h >> UilLexPars.h
	$(RM) y.tab.h
	$(CLIENTENVSETUP) $(WMLSRC)/wmluiltok < $(WMLSRC)/Uil.y > tokens.dat || true
	$(CPP) -I$(WMLSRC) $(TABLE) | $(WMLSRC)/wml
	$(RM) tokens.dat
	$(RM) wml-uil.mm
.endif

wmldbcreate:	wmldbcreate.c UilLexPars.h
	$(RM) wmldbcreate || true
	$(RM) wmldbcreate.o || true
	$(COMPILE) -I../.. wmldbcreate.c
	$(LINK) -L$(PROJ_DIR)/lib/Xm -lXm -L$(PROJ_DIR)/lib/Mrm -lMrm -L$(XLIBPATH) -lXt wmldbcreate.o -o wmldbcreate

$(WMDTABLE):	UilLexPars.h UilLexPars.c wmldbcreate 
	$(CLIENTENVSETUP) ./wmldbcreate -o $@


.PHONY: clean

clean:
	$(RM) $(TARGETS) $(WMDTABLE) $(REPORT) \
	*.mm *.o \
	tokens.dat wmldbcreate y.tab.* || true
 
# see also tools/wml/Makefile
# cpp above is used as a pre-processor (the compiler is not invoked)

