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
 ArrowB.c           ArrowBG.c          AtomMgr.c          BBUtil.c            \
 BaseClass.c        BulletinB.c        ButtonBox.c        Cache.c             \
 CallbackI.c        CareVisualT.c      CascadeB.c         CascadeBG.c         \
 ChColor.c          ClipWindow.c       ColObjFunc.c       Color.c             \
 ColorObj.c         ColorS.c           Column.c           ComboBox.c          \
 ComboBox2.c        Command.c          Container.c        CutPaste.c          \
 CvtUnit.c          DataF.c            DataFSel.c         Desktop.c           \
 Dest.c             DialogS.c          DialogSE.c         Direction.c         \
 Display.c          DrArrow.c          DrHiDash.c         DrPoly.c            \
 DrTog.c            DragBS.c           DragC.c            DragICC.c           \
 DragIcon.c         DragOverS.c        DragUnder.c        Draw.c              \
 DrawUtils.c        DrawingA.c         DrawnB.c           DropSMgr.c          \
 DropSMgrI.c        DropTrans.c        EditresCom.c       Ext18List.c         \
 ExtObject.c        FileSB.c           FocusAct.c         FontS.c             \
 Form.c             Frame.c            GMUtils.c          Gadget.c            \
 GadgetUtil.c       GeoUtils.c         GetPixData.c       GetRes.c            \
 GrabShell.c        Hash.c             Hierarchy.c        I18List.c           \
 IconBox.c          IconButton.c       IconFile.c         IconG.c             \
 IconH.c            ImageCache.c       IsMwmRun.c         Label.c             \
 LabelG.c           List.c             MainW.c            Manager.c           \
 MapEvents.c        MenuProc.c         MenuShell.c        MenuState.c         \
 MenuUtil.c         MessageB.c         Messages.c         Notebook.c          \
 Obso1_2.c          Obso2_0.c          ObsoStr.c          ObsoXme.c           \
 Outline.c          Paned.c            PanedW.c           Picture.c           \
 PixConv.c          Primitive.c        Protocols.c        PushB.c             \
 PushBG.c           RCHook.c           RCLayout.c         RCMenu.c            \
 RCPopup.c          ReadImage.c        Region.c           RepType.c           \
 ResConvert.c       ResEncod.c         ResInd.c           Resolve.c           \
 RowColumn.c        SSpinB.c           Sash.c             ScalTics.c          \
 Scale.c            Screen.c           ScroVis.c          ScrollBar.c         \
 ScrollFrameT.c     ScrolledW.c        SelectioB.c        SeparatoG.c         \
 Separator.c        ShellE.c           Simple.c           SlideC.c            \
 SpinB.c            Synthetic.c        TabBox.c           TabList.c           \
 TabStack.c         TearOff.c          TearOffB.c         Text.c              \
 TextF.c            TextFSel.c         TextFind.c         TextFunc.c          \
 TextIn.c           TextOut.c          TextSel.c          TextStrSo.c         \
 ToggleB.c          ToggleBG.c         ToolTip.c          TrackLoc.c          \
 Trait.c            Transfer.c         TranslNew.c        Transltns.c         \
 TravAct.c          Traversal.c        TraversalI.c       Tree.c              \
 TxtPropCv.c        UniqueEvnt.c       VaSimple.c         ValTime.c           \
 VendorS.c          VendorSE.c         VirtKeys.c         WidGet.c            \
 Xm.c               XmExtUtil.c        XmFontList.c       XmIm.c              \
 XmRenderT.c        XmStrDefs.c        XmString.c         XmStringFunc.c      \
 XmStringGet.c      XmStringObso.c     XmStringSeg.c      XmTabList.c         \
 Xmos.c             XpmAttrib.c        XpmCrBufFrI.c      XpmCrBufFrP.c       \
 XpmCrDatFrI.c      XpmCrDatFrP.c      XpmCrIFrBuf.c      XpmCrIFrDat.c       \
 XpmCrIFrP.c        XpmCrPFrBuf.c      XpmCrPFrDat.c      XpmCrPFrI.c         \
 XpmImage.c         XpmInfo.c          XpmRdFToBuf.c      XpmRdFToDat.c       \
 XpmRdFToI.c        XpmRdFToP.c        XpmWrFFrBuf.c      XpmWrFFrDat.c       \
 XpmWrFFrI.c        XpmWrFFrP.c        Xpmcreate.c        Xpmdata.c           \
 Xpmhashtab.c       Xpmmisc.c          Xpmparse.c         Xpmrgb.c            \
 Xpmscan.c          xmlist.c           


STRINGS_FILES = XmStrDefs.c XmStrDefs.h XmStrDefs22.h XmStrDefsI.h

STRINGS_TMPLS = XmStrDefs.ct XmStrDefs.ht XmStrDefsI.ht

MAKESTRS = $(PROJ_DIR)/config/util/makestrs

all::  $(STRINGS_FILES) libXm.so

# this creates STRINGS_FILES (if you have them, bypass if you must)

$(STRINGS_FILES): xmstring.list $(STRINGS_TMPLS)
	$(RM) $(STRINGS_FILES) || true
	$(MAKESTRS) $(STRINGSABIOPTIONS) < xmstring.list > XmStrDefs.c

libXm.so: $(STRINGS_FILES)
	echo "HIT3"
	$(RM) libXm.so || true
	$(LINK) -shared -fPIC -Wl,-soname,libXm.so -o libXm.so ${INCLUDES} ${LIBS} ${CFLAGS} -L$(XLIBPATH) -lXt -lSM -lICE -lXext -lX11 -lXmu -L/usr/lib -lc $(SRC)

##	$(LINK) -Wl,-shared -Wl,-f,PIC -znorelro -znotext -soname libXm.so.1 -lregex -o libXm.so.1.0 $(OBJS)


.PHONY: clean

clean:
	$(RM) $(TARGETS) *.o libXm.so $(STRINGS_FILES) DONE || true
 

# note: on some systems you'd also need -lregex
# with llvm clang ld.lld it can't make .o and look at llvm's poor
# documentation and you'll see why:  a lone .o could be from any lang any arch
# with any intented lang arch as output.  here is "what it wants" if you want
# to "stay sain" - one step only is what it wants.  note -shared and -fPIC are
# linker options but don't use -Wl - brain damaged.

