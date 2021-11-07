# Makefile

# IMPORTANT: all subdirs depend on PROJ_DIR; insure it is somehow
#            exported if using a MAKE that doesn't know .export

# build directory, anywhere
PROJ_DIR=${PWD}
.export PROJ_DIR

# install directory prefix
PREFIX ?= /usr/local
.export PREFIX

# Xorg assumed prefix
LOCALBASE ?= /usr/local
.export LOCALBASE

# make jobs unsafe:  it is a complex build requiring binary placement
# of certain things, therefore absolutely must be well ordered build

# bash requirement:  an important sh script needs a "for loop" for imake.
# optional use X's config/cf fully assume a shell has Bourne shell "for".
# i can't really remember if Makefiles written by hand use for loop - i
# believe i totally avoided it.  i will check that tomorrow?

# the choice is to be simple and avoid embedding macros
# and provide the fewest bsd options needed (config.h localdef.h aside)

#  remember $() are make and ${} are shell
#  LHS of : built when older than RHS , only dates checked not existence
#           use .PHONY to fake an newer than LHS file
#  $@ means the target name of the rule where found
#  $< means name of file in a list
#  RM are done to insure a stale file doesn't get re-used, old issues
#  and tab /n are required as below but pretty elsewhere ...
#  the following is done if to-build is older than it's prerequisites or DNE

#to-be-built:  pre-required to exist and be fresh so it can be
#<tab>shell commands to create to-build
#<newline>

# this lib has include files btw

CFLAGS+=-I/usr/include -I$(LOCALBASE)/include -I$(PROJ_DIR) -I$(PROJ_DIR)/include -I$(PROJ_DIR)/lib


XLIBPATH?=$(LOCALBASE)/lib

RM ?= rm
MV ?= mv
CC ?= cc
MKDIR ?= mkdir
RMDIR ?= rmdir
GREP ?= grep
RANLIB ?= ranlib
INSTALL ?= install
LN ?= ln -s

INCLUDES ?=
LIBS ?=
LDFLAGS ?=

AR=ar -rc
LEX=lex -L
LEXLIB=-lfl
YACC=yacc -l
COMPILE = cc -c ${INCLUDES} ${LIBS} ${CFLAGS}
DEPENDENCIES=
LINK    = cc

TARGETS =

all::	DONE


# These must be in order, no parallel at all.
# individul makefile do not check all preceeding
# makes to see if they newer

.PHONY: DONE
DONE:
	(cd config/util/ ; $(MAKE))
	(cd localized/util/ ; $(MAKE))
	(cd lib/Xm/ ; $(MAKE))
	(cd lib/Xm.so/ ; $(MAKE))
	(cd lib/Mrm/ ; $(MAKE))
	(cd lib/Mrm.so/ ; $(MAKE))
	(cd tools/wml/ ; $(MAKE))
	(cd clients/uil/ ; $(MAKE))
	(cd clients/xmbind/ ; $(MAKE))
	(cd clients/mwm/ ; $(MAKE))
	@echo "DONE"

.PHONY: demos

demos:
	(cd demos/lib/Xmd/ ; $(MAKE))
	(cd demos/lib/Exm/wml/ ; $(MAKE))
	(cd demos/lib/Exm/ ; $(MAKE))
	(cd demos/lib/Wsm/ ; $(MAKE))
	(cd demos/programs/ButtonBox ; $(MAKE))
	(cd demos/programs/ColorSel ; $(MAKE))
	(cd demos/programs/Column ; $(MAKE))
	(cd demos/programs/DropDown ; $(MAKE))
	(cd demos/programs/Exm/app_in_c ; $(MAKE))
	(cd demos/programs/Exm/app_in_uil ; $(MAKE))
	(cd demos/programs/Exm/simple_app ; $(MAKE))
	(cd demos/programs/FontSel ; $(MAKE))
	(cd demos/programs/IconB ; $(MAKE))
	(cd demos/programs/MultiList ; $(MAKE))
	(cd demos/programs/Outline ; $(MAKE))
	(cd demos/programs/Paned ; $(MAKE))
	(cd demos/programs/TabStack ; $(MAKE))
	(cd demos/programs/Tree ; $(MAKE))
	(cd demos/programs/airport ; $(MAKE))
	(cd demos/programs/animate ; $(MAKE))
	(cd demos/programs/drag_and_drop ; $(MAKE))
	(cd demos/programs/draw ; $(MAKE))
	(cd demos/programs/earth ; $(MAKE))
	(cd demos/programs/filemanager ; $(MAKE))
	(cd demos/programs/fileview ; $(MAKE))
	(cd demos/programs/getsubres ; $(MAKE))
	(cd demos/programs/hellomotif ; $(MAKE))
	(cd demos/programs/hellomotifi18n ; $(MAKE))
	(cd demos/programs/i18ninput ; $(MAKE))
	(cd demos/programs/panner ; $(MAKE))
	(cd demos/programs/periodic ; $(MAKE))
	(cd demos/programs/piano ; $(MAKE))
	(cd demos/programs/popups ; $(MAKE))
	(cd demos/programs/sampler2_0 ; $(MAKE))
	(cd demos/programs/setdate ; $(MAKE))
	(cd demos/programs/todo ; $(MAKE))
	(cd demos/programs/tooltips ; $(MAKE))
	(cd demos/programs/workspace ; $(MAKE))
	(cd demos/unsupported/Exm ; $(MAKE))
	(cd demos/unsupported/aicon ; $(MAKE))
	(cd demos/unsupported/dainput ; $(MAKE))
	(cd demos/unsupported/dogs ; $(MAKE))
	(cd demos/unsupported/hellomotif ; $(MAKE))
	(cd demos/unsupported/motifshell ; $(MAKE))
	(cd demos/unsupported/uilsymdump ; $(MAKE))
	(cd demos/unsupported/xmapdef ; $(MAKE))
	(cd demos/unsupported/xmfonts ; $(MAKE))
	(cd demos/unsupported/xmforc ; $(MAKE))
	(cd demos/unsupported/xmform ; $(MAKE))
	(cd demos/doc/programGuide/ch05/Scale ; $(MAKE))
	(cd demos/doc/programGuide/ch06/combo_box ; $(MAKE))
	(cd demos/doc/programGuide/ch06/spin_box ; $(MAKE))
	(cd demos/doc/programGuide/ch08/Container ; $(MAKE))
	(cd demos/doc/programGuide/ch08/Notebook ; $(MAKE))
	(cd demos/doc/programGuide/ch16 ; $(MAKE))
	(cd demos/doc/programGuide/ch17/simple_drag ; $(MAKE))
	(cd demos/doc/programGuide/ch17/simple_drop ; $(MAKE))
	@echo "DONE"


.PHONY: install

install:
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/bin 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/include/Mrm 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/include/X11/bitmaps
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/include/Xm 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/include/uil 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/lib/X11 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/lib/X11/bindings 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/share/man/man1 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/share/man/man2 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/share/man/man3 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/share/man/man4 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/share/man/man5 
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/share/man/manm 
	$(INSTALL) -g wheel -o root -s \
`find . -type f -perm -0555 | $(GREP) -v "demos\|tests/\|config\|[.]sh\|[.]so\|[.]git"` \
$(PREFIX)/Motif/bin/
	$(INSTALL) -g wheel -o root -s demos/programs/panner/panner \
$(PREFIX)/Motif/bin/
	$(INSTALL) -g wheel -o root \
`find . -type f -name "*.so" -o -name "*.a" | $(GREP) -v "demos\|tests\|config\|[.]sh\|imports"`  $(PREFIX)/Motif/lib/
	$(INSTALL) -g wheel -o root  localdef.h config.h  \
$(PREFIX)/Motif/include/
	(cd lib/Mrm ; $(INSTALL) -g wheel -o root  IDB.h Mrm.h \
MrmAppl.h MrmDecls.h MrmPublic.h MrmosI.h  $(PREFIX)/Motif/include/Mrm/)
	$(INSTALL) -g wheel -o root bitmaps/xm_*  \
$(PREFIX)/Motif/include/X11/bitmaps/
	$(INSTALL) -g wheel -o root  clients/mwm/system.mwmrc  \
$(PREFIX)/Motif/lib/X11/
	(cd lib/Xm ; $(INSTALL) -g wheel -o root  *.h  \
$(PREFIX)/Motif/include/Xm/)
	(cd clients/uil ; $(INSTALL) -g wheel -o root  Uil.h UilDBDef.h \
UilDef.h UilSymDef.h UilSymGl.h XmAppl.uil  $(PREFIX)/Motif/include/uil/)
	$(MKDIR) -p /tmp/fo2121/
	$(MV) bindings/Imakefile bindings/README  \
/tmp/fo2121/
	$(INSTALL) -g wheel -o root  bindings/*  \
$(PREFIX)/Motif/lib/X11/bindings/
	$(MV) /tmp/fo2121/Imakefile /tmp/fo2121/README  bindings/
	$(RMDIR) /tmp/fo2121/
	$(INSTALL) -g wheel -o root  tools/wml/motif.wmd  $(PREFIX)/Motif/bin/
	$(INSTALL) -g wheel -o root  \
`find config/ -type f -name "*.man"` \
$(PREFIX)/Motif/share/man/man1/
	$(INSTALL) -g wheel -o root  \
`find doc/ -type f -name "*.1"`  \
$(PREFIX)/Motif/share/man/man1/
	$(INSTALL) -g wheel -o root  \
`find doc/ -type f -name "*.3"`  \
$(PREFIX)/Motif/share/man/man3/
	$(INSTALL) -g wheel -o root  \
`find doc/ -type f -name "*.4"`  \
$(PREFIX)/Motif/share/man/man4/
	$(INSTALL) -g wheel -o root  \
`find doc/ -type f -name "*.5"`  \
$(PREFIX)/Motif/share/man/man5/
	(cd $(PREFIX)/Motif/lib ; $(RM) -f libXm.so.2 ; \
$(LN) libXm.so.2.1 libXm.so.2)
	(cd $(PREFIX)/Motif/lib ; $(RM) -f libXm.so ; \
$(LN) libXm.so.2.1 libXm.so)
	(cd $(PREFIX)/Motif/lib ; $(RM) -f libMrm.so.2 ; \
$(LN) libMrm.so.2.1 libMrm.so.2)
	(cd $(PREFIX)/Motif/lib ; $(RM) -f libMrm.so ; \
$(LN) libMrm.so.2.1 libMrm.so)
	(cd $(PREFIX)/Motif/lib ; $(RM) -f libUil.so.2 ; \
$(LN) libUil.so.2.1 libUil.so.2)
	(cd $(PREFIX)/Motif/lib ; $(RM) -f libUil.so ; \
$(LN) libUil.so.2.1 libUil.so)
	(cd $(PREFIX)/Motif/lib ; $(RANLIB) *.a)
	$(CP) COPYRIGHT.MOTIF $(PREFIX)/Motif/
	$(CP) EXTRA_DIST/Xdefaults $(PREFIX)/Motif/lib/X11/
	$(CP) EXTRA_DIST/mwmrc $(PREFIX)/Motif/lib/X11/
	@echo "DONE.  don't forget ldconfig"

# the shlib version is same as for imake cf build for consisency


.PHONY: install-demos

install-demos:
	$(INSTALL) -d -g wheel -o root $(PREFIX)/Motif/bin/pixmaps 
	$(INSTALL) -g wheel -o root  demos/programs/pixmaps/*.x*m  \
$(PREFIX)/Motif/bin/pixmaps/ 
	$(INSTALL) -g wheel -o root  demos/programs/fileview/xmfile \
$(PREFIX)/Motif/bin/
	$(INSTALL) -g wheel -o root -s \
`find demos/ -type f -perm -0555 | $(GREP) -v "[.]sh\|[.]so\|xmfile"` \
$(PREFIX)/Motif/bin/
	$(INSTALL) -g wheel -o root  \
`find demos/lib/ -type f -name "*.so" -o -name "*.a"` \
$(PREFIX)/Motif/lib/
	$(INSTALL) -g wheel -o root  \
`find demos/ -type f -name "*.uid" -o -name "*.wmd" -o -name "*.help" -o -name "*.xpm" -o -name "*.xbm" -o -name "*.df" -o -name "*.piano" -o -name "*.images" -o -name "*.todo" -o -name "*.bm"` \
$(PREFIX)/Motif/bin/
	$(INSTALL) -g wheel -o root  \
`find demos/lib -type f -name "*.2"` \
$(PREFIX)/Motif/share/man/man2/
	$(INSTALL) -g wheel -o root  \
`find demos/programs -type f -name "*.man"` \
$(PREFIX)/Motif/share/man/man1/
	@echo "DONE.  don't forget ldconfig"


.PHONY: clean

clean:
	(cd localized/util/ ; $(MAKE) clean)
	(cd lib/Xm/ ; $(MAKE) clean)
	(cd lib/Xm.so/ ; $(MAKE) clean)
	(cd lib/Mrm/ ; $(MAKE) clean)
	(cd lib/Mrm.so/ ; $(MAKE) clean)
	(cd tools/wml/ ; $(MAKE) clean)
	(cd clients/uil/ ; $(MAKE) clean)
	(cd clients/xmbind/ ; $(MAKE) clean)
	(cd clients/mwm/ ; $(MAKE) clean)
	(cd demos/lib/Xmd/ ; $(MAKE) clean)
	(cd demos/lib/Exm/wml/ ; $(MAKE) clean)
	(cd demos/lib/Exm/ ; $(MAKE) clean)
	(cd demos/lib/Wsm/ ; $(MAKE) clean)
	(cd demos/programs/ButtonBox ; $(MAKE) clean)
	(cd demos/programs/ColorSel ; $(MAKE) clean)
	(cd demos/programs/Column ; $(MAKE) clean)
	(cd demos/programs/DropDown ; $(MAKE) clean)
	(cd demos/programs/Exm/app_in_c ; $(MAKE) clean)
	(cd demos/programs/Exm/app_in_uil ; $(MAKE) clean)
	(cd demos/programs/Exm/simple_app ; $(MAKE) clean)
	(cd demos/programs/FontSel ; $(MAKE) clean)
	(cd demos/programs/IconB ; $(MAKE) clean)
	(cd demos/programs/MultiList ; $(MAKE) clean)
	(cd demos/programs/Outline ; $(MAKE) clean)
	(cd demos/programs/Paned ; $(MAKE) clean)
	(cd demos/programs/TabStack ; $(MAKE) clean)
	(cd demos/programs/Tree ; $(MAKE) clean)
	(cd demos/programs/airport ; $(MAKE) clean)
	(cd demos/programs/animate ; $(MAKE) clean)
	(cd demos/programs/drag_and_drop ; $(MAKE) clean)
	(cd demos/programs/draw ; $(MAKE) clean)
	(cd demos/programs/earth ; $(MAKE) clean)
	(cd demos/programs/filemanager ; $(MAKE) clean)
	(cd demos/programs/fileview ; $(MAKE) clean)
	(cd demos/programs/getsubres ; $(MAKE) clean)
	(cd demos/programs/hellomotif ; $(MAKE) clean)
	(cd demos/programs/hellomotifi18n ; $(MAKE) clean)
	(cd demos/programs/i18ninput ; $(MAKE) clean)
	(cd demos/programs/panner ; $(MAKE) clean)
	(cd demos/programs/periodic ; $(MAKE) clean)
	(cd demos/programs/piano ; $(MAKE) clean)
	(cd demos/programs/popups ; $(MAKE) clean)
	(cd demos/programs/sampler2_0 ; $(MAKE) clean)
	(cd demos/programs/setdate ; $(MAKE) clean)
	(cd demos/programs/todo ; $(MAKE) clean)
	(cd demos/programs/tooltips ; $(MAKE) clean)
	(cd demos/programs/workspace ; $(MAKE) clean)
	(cd demos/unsupported/Exm ; $(MAKE) clean)
	(cd demos/unsupported/aicon ; $(MAKE) clean)
	(cd demos/unsupported/dainput ; $(MAKE) clean)
	(cd demos/unsupported/dogs ; $(MAKE) clean)
	(cd demos/unsupported/hellomotif ; $(MAKE) clean)
	(cd demos/unsupported/motifshell ; $(MAKE) clean)
	(cd demos/unsupported/uilsymdump ; $(MAKE) clean)
	(cd demos/unsupported/xmapdef ; $(MAKE) clean)
	(cd demos/unsupported/xmfonts ; $(MAKE) clean)
	(cd demos/unsupported/xmforc ; $(MAKE) clean)
	(cd demos/unsupported/xmform ; $(MAKE) clean)
	(cd demos/doc/programGuide/ch05/Scale ; $(MAKE) clean)
	(cd demos/doc/programGuide/ch06/combo_box ; $(MAKE) clean)
	(cd demos/doc/programGuide/ch06/spin_box ; $(MAKE) clean)
	(cd demos/doc/programGuide/ch08/Container ; $(MAKE) clean)
	(cd demos/doc/programGuide/ch08/Notebook ; $(MAKE) clean)
	(cd demos/doc/programGuide/ch16 ; $(MAKE) clean)
	(cd demos/doc/programGuide/ch17/simple_drag ; $(MAKE) clean)
	(cd demos/doc/programGuide/ch17/simple_drop ; $(MAKE) clean)

deinstall:
	[ -d $(PREFIX)/Motif/ ] && $(RM) -r $(PREFIX)/Motif/


# ERRATA
# for DtPrint you need to #undefine NO_XP in localdef.h and try
#     (cd tools/wml.print/Makefile ; $(MAKE))
#   or pivot the two directories is needed for demos
#   the two differs only by motif.wml version before the build
# demos foo.uil in demos won't work until demos/lib/Exm/wml is done,
# install:
#   omitted: todo: the install placement is differnt and xorg uses .pc


#.include <bsd.port.mk>
