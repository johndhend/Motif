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
 ArrowB.o           ArrowBG.o          AtomMgr.o          BBUtil.o            \
 BaseClass.o        BulletinB.o        ButtonBox.o        Cache.o             \
 CallbackI.o        CareVisualT.o      CascadeB.o         CascadeBG.o         \
 ChColor.o          ClipWindow.o       ColObjFunc.o       Color.o             \
 ColorObj.o         ColorS.o           Column.o           ComboBox.o          \
 ComboBox2.o        Command.o          Container.o        CutPaste.o          \
 CvtUnit.o          DataF.o            DataFSel.o         Desktop.o           \
 Dest.o             DialogS.o          DialogSE.o         Direction.o         \
 Display.o          DrArrow.o          DrHiDash.o         DrPoly.o            \
 DrTog.o            DragBS.o           DragC.o            DragICC.o           \
 DragIcon.o         DragOverS.o        DragUnder.o        Draw.o              \
 DrawUtils.o        DrawingA.o         DrawnB.o           DropSMgr.o          \
 DropSMgrI.o        DropTrans.o        EditresCom.o       Ext18List.o         \
 ExtObject.o        FileSB.o           FocusAct.o         FontS.o             \
 Form.o             Frame.o            GMUtils.o          Gadget.o            \
 GadgetUtil.o       GeoUtils.o         GetPixData.o       GetRes.o            \
 GrabShell.o        Hash.o             Hierarchy.o        I18List.o           \
 IconBox.o          IconButton.o       IconFile.o         IconG.o             \
 IconH.o            ImageCache.o       IsMwmRun.o         Label.o             \
 LabelG.o           List.o             MainW.o            Manager.o           \
 MapEvents.o        MenuProc.o         MenuShell.o        MenuState.o         \
 MenuUtil.o         MessageB.o         Messages.o         Notebook.o          \
 Obso1_2.o          Obso2_0.o          ObsoStr.o          ObsoXme.o           \
 Outline.o          Paned.o            PanedW.o           Picture.o           \
 PixConv.o          Primitive.o        Protocols.o        PushB.o             \
 PushBG.o           RCHook.o           RCLayout.o         RCMenu.o            \
 RCPopup.o          ReadImage.o        Region.o           RepType.o           \
 ResConvert.o       ResEncod.o         ResInd.o           Resolve.o           \
 RowColumn.o        SSpinB.o           Sash.o             ScalTics.o          \
 Scale.o            Screen.o           ScroVis.o          ScrollBar.o         \
 ScrollFrameT.o     ScrolledW.o        SelectioB.o        SeparatoG.o         \
 Separator.o        ShellE.o           Simple.o           SlideC.o            \
 SpinB.o            Synthetic.o        TabBox.o           TabList.o           \
 TabStack.o         TearOff.o          TearOffB.o         Text.o              \
 TextF.o            TextFSel.o         TextFind.o         TextFunc.o          \
 TextIn.o           TextOut.o          TextSel.o          TextStrSo.o         \
 ToggleB.o          ToggleBG.o         ToolTip.o          TrackLoc.o          \
 Trait.o            Transfer.o         TranslNew.o        Transltns.o         \
 TravAct.o          Traversal.o        TraversalI.o       Tree.o              \
 TxtPropCv.o        UniqueEvnt.o       VaSimple.o         ValTime.o           \
 VendorS.o          VendorSE.o         VirtKeys.o         WidGet.o            \
 Xm.o               XmExtUtil.o        XmFontList.o       XmIm.o              \
 XmRenderT.o        XmStrDefs.o        XmString.o         XmStringFunc.o      \
 XmStringGet.o      XmStringObso.o     XmStringSeg.o      XmTabList.o         \
 Xmos.o             XpmAttrib.o        XpmCrBufFrI.o      XpmCrBufFrP.o       \
 XpmCrDatFrI.o      XpmCrDatFrP.o      XpmCrIFrBuf.o      XpmCrIFrDat.o       \
 XpmCrIFrP.o        XpmCrPFrBuf.o      XpmCrPFrDat.o      XpmCrPFrI.o         \
 XpmImage.o         XpmInfo.o          XpmRdFToBuf.o      XpmRdFToDat.o       \
 XpmRdFToI.o        XpmRdFToP.o        XpmWrFFrBuf.o      XpmWrFFrDat.o       \
 XpmWrFFrI.o        XpmWrFFrP.o        Xpmcreate.o        Xpmdata.o           \
 Xpmhashtab.o       Xpmmisc.o          Xpmparse.o         Xpmrgb.o            \
 Xpmscan.o          xmlist.o           

STRINGS_FILES = XmStrDefs.c XmStrDefs.h XmStrDefs22.h XmStrDefsI.h

STRINGS_TMPLS = XmStrDefs.ct XmStrDefs.ht XmStrDefsI.ht

MAKESTRS = $(PROJ_DIR)/config/util/makestrs

all:: $(STRINGS_FILES) libXm.a

# this creates STRINGS_FILES (if you have them, bypass if you must)

$(STRINGS_FILES): xmstring.list $(STRINGS_TMPLS)
	$(RM) $(STRINGS_FILES) || true
	$(MAKESTRS) $(STRINGSABIOPTIONS) < xmstring.list > XmStrDefs.c

%.o: *.c
	$(RM) $@ || true
	$(COMPILE) $<

libXm.a: $(OBJS) $(STRINGS_FILES)
	$(RM) libXm.a || true
	$(AR) libXm.a $(OBJS)


.PHONY: clean

clean:
	$(RM) $(TARGETS) *.o libXm.a $(STRINGS_FILES) DONE || true
 
