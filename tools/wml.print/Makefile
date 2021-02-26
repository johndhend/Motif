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

UILSRC = $(PROJ_DIR)/clients/uil


 
SRCS1 =	wml.c		wmlouth.c	wmloutmm.c \
	wmloutp1.c	wmlresolve.c	wmlsynbld.c	wmlutils.c \
	wmldbcreate.c
 
OBJS1 =	wml.o		wmloutkey.o	wmlouth.o	wmloutmm.o \
	wmloutp1.o	wmlresolve.o	wmlsynbld.o	wmlutils.o
 
SRCS2 = wmluiltok.l
 
OBJS2 = wmlparse.o

SRCS = $(SRCS1) $(SRCS2)
OBJS = $(OBJS1) $(OBJS2)
 
YACCTARGETS = UilLexPars.c	UilLexPars.h

WMLTARGETS = UilConst.h	UilKeyTab.h	 \
	UilSymArTa.h	UilSymArTy.h	UilSymCSet.h	UilSymCtl.h \
	UilSymEnum.h	UilSymGen.h	UilSymNam.h	UilSymRArg.h \
	UilSymReas.h	UilTokName.h	UilUrmClas.h	UilSymChCl.h \
	UilSymChTa.h

TARGETS = $(WMLTARGETS) $(YACCTARGETS) 
 
TABLE = motif.wml
WMDTABLE = motif.wmd
WMLTOOLS = wml wmluiltok
REPORT = wml.report

all::	DONE

%.o: *.c
	$(RM) $@ || true
	$(COMPILE) $<

DONE:	$(WMDTABLE) $(TARGETS) libwml.a
	(cd $(UILSRC); $(RM) $(TARGETS)) || true
	diff -q UilDBDef.h $(UILSRC)/UilDBDef.h
	cp $(TARGETS) $(UILSRC)
	touch DONE

libwml.a:  $(OBJS)
	$(RM) libwml.a || true
	$(AR) libwml.a $(OBJS)

wml:	libwml.a
	$(RM) wml || true
	$(RM) wml.o || true
	$(CC) $(CFLAGS) libwml.a -o wml

wmllex.c:	wmlparse.y wmllex.l
	$(RM) lex.yy.c || true
	$(LEX) wmllex.l
	$(MV) lex.yy.c wmllex.c

wmlsynbld.o:	wmlparse.h

wmlparse.h:	wmlparse.y wmllex.l wmllex.c
	$(RM) wmlparse.c || true
	$(RM) wmlparse.h || true
	$(RM) y.tab.c || true
	$(RM) y.tab.h || true
	$(YACC) -d $(YACCFLAGS) wmlparse.y
	$(MV) y.tab.c wmlparse.c
	$(MV) y.tab.h wmlparse.h
 
wmlparse.c:	wmlparse.y wmllex.l wmllex.c wmlparse.h

wmlsynbld.c:	wmlparse.y wmllex.l wmllex.c wmlparse.h
 
wmluiltok:	wmluiltok.l
	$(RM) wmluiltok || true
	$(RM) lex.yy.c || true
	$(LEX) -d wmluiltok.l
	$(CC) $(CFLAGS) lex.yy.c $(LEXLIB) -o wmluiltok
	$(RM) lex.yy.c

.ifdef VERSION_IS_NOT_DEFINED
$(TARGETS):	$(WMLTOOLS) $(TABLE)
	$(RM) $(TARGETS) $(REPORT) wml-uil.mm || true
	$(YACC) -d $(YACCFLAGS) Uil.y
	$(MV) y.tab.c UilLexPars.c
	$(MV) y.tab.h UilLexPars.h
	$(CLIENTENVSETUP) ./wmluiltok < Uil.y > tokens.dat || true
	$(CLIENTENVSETUP) ./wml $(TABLE)
	$(RM) tokens.dat
	$(RM) wml-uil.mm
.else
$(TARGETS):	$(WMLTOOLS) $(TABLE)
	$(RM) $(TARGETS) $(REPORT) wml-uil.mm || true
	$(YACC) -d $(YACCFLAGS) Uil.y
	$(MV) y.tab.c UilLexPars.c
	rm -f UilLexPars.h
	echo "#undef VERSION" > UilLexPars.h
	cat y.tab.h >> UilLexPars.h
	$(RM) y.tab.h
	$(CLIENTENVSETUP) ./wmluiltok < Uil.y > tokens.dat || true
	$(CLIENTENVSETUP) ./wml $(TABLE)
	$(RM) tokens.dat
	$(RM) wml-uil.mm
.endif


wmldbcreate:	wmldbcreate.c UilLexPars.h
	$(RM) wmldbcreate || true
	$(RM) wmldbcreate.o || true
	$(COMPILE) wmldbcreate.c
	$(LINK) -L$(PROJ_DIR)/lib/Xm -lXm -L$(XLIBPATH) -lXt -lSM -lICE -lXp -lXext -lX11 -L/usr/lib -lc wmldbcreate.o -o wmldbcreate

$(WMDTABLE):	UilLexPars.h UilLexPars.c wmldbcreate 
	$(CLIENTENVSETUP) ./wmldbcreate -o $@


.PHONY: clean

clean:
	(cd $(UILSRC); $(RM) $(TARGETS) Uil.c) || true
	$(RM) $(TARGETS) $(WMDTABLE) $(REPORT) lex.yy.c libwml.a wml \
	*.mm *.sdml *.txt *.o wmlparse.c wmlparse.h wmluiltok wmllex.c \
	wmluiltok.c tokens.dat wmldbcreate y.tab.* Uil.c DONE || true
 
# NOTE:
# wmllex.c UilLexPars.c wmlparse.c
#  will, without -L or -l, have #line ? "y.tab.c" thus need
#  immediate build of .o (before y.tab.c is MV or another .l .y compiles)
#  make cannot insures this - so these would be used after any lex or yacc
#	$(COMPILE) ... created.c
# and if it contains main then need immediate link too
#	$(LINK) ... created

