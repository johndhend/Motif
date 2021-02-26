/* 
 *  @OPENGROUP_COPYRIGHT@
 *  COPYRIGHT NOTICE
 *  Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 *  Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 *  ALL RIGHTS RESERVED (MOTIF). See the file named COPYRIGHT.MOTIF for
 *  the full copyright text.
 *  
 *  This software is subject to an open license. It may only be
 *  used on, with or for operating systems which are themselves open
 *  source systems. You must contact The Open Group for a license
 *  allowing distribution and sublicensing of this software on, with,
 *  or for operating systems which are not Open Source programs.
 *  
 *  See http://www.opengroup.org/openmotif/license for full
 *  details of the license agreement. Any use, reproduction, or
 *  distribution of the program constitutes recipient's acceptance of
 *  this agreement.
 *  
 *  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 *  PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 *  WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 *  OR FITNESS FOR A PARTICULAR PURPOSE
 *  
 *  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 *  NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 *  EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGES.
*/ 
/* 
 * HISTORY
*/ 
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: ApplicationS.c /main/9 1995/07/14 10:59:28 drk $"
#endif
#endif
/*      @(#)instance	1.2     Date:02/12/91                              */
/******************************************************************************

    TEST: XmApplicationShell
    AUTHOR: Automatic generation.
    DATE: Wed Oct  9 16:38:49 EDT 1991

*******************************************************************************/
/******************************************************************************
       HISTORY:
         12/11/90 PSN Put it under source control. This is version at the
                      time of release.
******************************************************************************/

#include "mvslib.h"
#include <X11/Shell.h>


/*************************************************************************/
/*            This file contains WIDGET SPECIFIC DEFINTIONS              */
/*************************************************************************/

/*************************************************************************/
/*      These are the resources associated with this Widget Class        */
/*************************************************************************/

static MvsResourceInfoRecord Wresource_info[] = {

/* The resource_info structure */
{ XmNaccelerators        , T_XtAccelerators     , True , (MvsArgVal)MVSdynamic           ,
  False, NULL       , 0x0|CREATE|SET|GET,	False },
{ XmNallowResize         , T_Boolean            , False, (MvsArgVal)FALSE                ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNallowShellResize    , T_Boolean            , False, (MvsArgVal)FALSE                ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNancestorSensitive   , T_Boolean            , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL              , 0x0|GET,	False },
{ XmNbackground          , T_Pixel              , True , (MvsArgVal)MVSdynamic           ,
  False, NULL                , 0x0|CREATE|SET|GET,	False },
{ XmNbackgroundPixmap    , T_Pixmap             , False, (MvsArgVal)XmUNSPECIFIED_PIXMAP ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNbaseHeight          , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNbaseWidth           , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNborderColor         , T_Pixel              , True , (MvsArgVal)MVSBlack             ,
  False, NULL                , 0x0|CREATE|SET|GET,	False },
{ XmNborderPixmap        , T_Pixmap             , False, (MvsArgVal)XmUNSPECIFIED_PIXMAP ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNborderWidth         , T_Dimension          , False, (MvsArgVal)1                    ,
  True,  NULL            , 0x0|CREATE|SET|GET,	False },
{ XmNbottomAttachment    , T_unsigned_char      , False, (MvsArgVal)XmATTACH_NONE        ,
  True,  NULL  , 0x0|CREATE|SET,	False },
{ XmNbottomOffset        , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNbottomPosition      , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNbottomWidget        , T_Widget_ref         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET,	False },
{ XmNcolormap            , T_Colormap           , True , (MvsArgVal)MVSdynamic           ,
  False, NULL             , 0x0|CREATE|GET,	False },
{ XmNdefaultFontList     , T_XmFontList         , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL           , 0x0|CREATE,	False },
{ XmNdeleteResponse      , T_unsigned_char      , True , (MvsArgVal)MVSdynamic           ,
  False, NULL        , 0x0|CREATE|SET|GET,	False },
{ XmNdepth               , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|GET,	False },
{ XmNgeometry            , T_String             , False, (MvsArgVal)NULL	,
  True,  NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNheight              , T_Dimension          , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL            , 0x0|CREATE|SET|GET,	True },
{ XmNheightInc           , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNiconMask            , T_Pixmap             , False, (MvsArgVal)NULL                 ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNiconName            , T_String             , False, (MvsArgVal)NULL	,
  True,  NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNiconPixmap          , T_Pixmap             , False, (MvsArgVal)NULL                 ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNiconWindow          , T_Widget_ref         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET|GET,	False },
{ XmNiconX               , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNiconY               , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNiconic              , T_Boolean            , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNinitialResourcesPersistent, T_Boolean            , False, (MvsArgVal)TRUE                 ,
  False, NULL              , 0x0|CREATE,	False },
{ XmNinitialState        , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNinput               , T_Boolean            , False, (MvsArgVal)FALSE                ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNinsertPosition      , T_XmFunction         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET|GET,	False },
{ XmNkeyboardFocusPolicy , T_unsigned_char      , True , (MvsArgVal)MVSdynamic           ,
  False, NULL        , 0x0|CREATE|SET|GET,	False },
{ XmNleftAttachment      , T_unsigned_char      , False, (MvsArgVal)XmATTACH_NONE        ,
  True,  NULL    , 0x0|CREATE|SET,	False },
{ XmNleftOffset          , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNleftPosition        , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNleftWidget          , T_Widget_ref         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET,	False },
{ XmNmappedWhenManaged   , T_Boolean            , False, (MvsArgVal)TRUE                 ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNmaxAspectX          , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNmaxAspectY          , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNmaxHeight           , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNmaxWidth            , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNminAspectX          , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNminAspectY          , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNminHeight           , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNminWidth            , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNmwmDecorations      , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNmwmFunctions        , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNmwmInputMode        , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNmwmMenu             , T_String             , False, (MvsArgVal)NULL	,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNoverrideRedirect    , T_Boolean            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNpaneMaximum         , T_Integer            , False, (MvsArgVal)1000                 ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNpaneMinimum         , T_Integer            , False, (MvsArgVal)1                    ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNpopdownCallback     , T_XtCallbackList     , False, (MvsArgVal)NULL                 ,
  False, NULL       , 0x0|CREATE,	False },
{ XmNpopupCallback       , T_XtCallbackList     , False, (MvsArgVal)NULL                 ,
  False, NULL       , 0x0|CREATE,	False },
{ XmNresizable           , T_Boolean            , False, (MvsArgVal)TRUE                 ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNrightAttachment     , T_unsigned_char      , False, (MvsArgVal)XmATTACH_NONE        ,
  True,  NULL   , 0x0|CREATE|SET,	False },
{ XmNrightOffset         , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNrightPosition       , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNrightWidget         , T_Widget_ref         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET,	False },
{ XmNsaveUnder           , T_Boolean            , False, (MvsArgVal)FALSE                ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNscreen              , T_Pointer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|GET,	False },
{ XmNsensitive           , T_Boolean            , False, (MvsArgVal)TRUE                 ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNskipAdjust          , T_Boolean            , False, (MvsArgVal)FALSE                ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNtitle               , T_String             , True , (MvsArgVal)MVSdynamic,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNtopAttachment       , T_unsigned_char      , False, (MvsArgVal)XmATTACH_NONE        ,
  True,  NULL     , 0x0|CREATE|SET,	False },
{ XmNtopOffset           , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNtopPosition         , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNtopWidget           , T_Widget_ref         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET,	False },
{ XmNtransient           , T_Boolean            , False, (MvsArgVal)FALSE                ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNtranslations        , T_XtTranslations     , True , (MvsArgVal)MVSdynamic           ,
  False, NULL       , 0x0|CREATE|SET|GET,	False },
{ XmNwaitForWm           , T_Boolean            , False, (MvsArgVal)TRUE                 ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNwidth               , T_Dimension          , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL            , 0x0|CREATE|SET|GET,	True },
{ XmNwidthInc            , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNwinGravity          , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNwindowGroup         , T_Widget_ref         , True , (MvsArgVal)MVSdynamic           ,
  False, NULL           , 0x0|CREATE|SET|GET,	False },
{ XmNwmTimeout           , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNx                   , T_Position           , False, (MvsArgVal)0                    ,
  True,  NULL             , 0x0|CREATE|SET|GET,	False },
{ XmNy                   , T_Position           , False, (MvsArgVal)0                    ,
  True,  NULL             , 0x0|CREATE|SET|GET,	False },
{ XmNdestroyCallback     , T_XtCallbackList     , False, (MvsArgVal)NULL                 ,
  False, NULL       , 0x0|CREATE,	False },

};


/*************************************************************************/
/*      This is the name of the class (for debugging purposes)           */
/*************************************************************************/

static char Widget_class_name[] =
			"XmApplicationShell";


/*************************************************************************/
/*    This function is used to create a widget of a particular Widget    */
/* Class. The class is apparent from the name of the convenience         */
/* used for widget creation.                                             */
/*************************************************************************/

static Widget CreateWidget(parent, name, args, nargs, xtclass)
Widget parent;
char *name;
Arg args[];
int nargs;
WidgetClass xtclass;
{
    Widget widget;
    char   *tmp_name;

    if (name == NULL)
       tmp_name = "XmApplicationShell";
    else
       tmp_name = name;

    widget = XmCreateApplicationShell (parent, tmp_name, args, nargs, xtclass);

    return(widget);

} /* End CreateWidget() */


/*********************************************************************/
/*    This function sets up the widget info structure that contains  */
/* all information that applies to a particular widget class. This   */
/* information is of a static nature and is declared statically in   */
/* this module. However, the class info structure is globally visible*/
/*********************************************************************/


static MvsWidgetClassInfo mvXmApplicationShellWidgetClass = {

  /* Widget                (*proc_SetExpectedActions)(); */ NULL,
  /* void                  (*proc_CreateWidget)();       */ CreateWidget,
  /* void                  (*proc_TestBehavior)();       */ NULL,
  /* char                  class_name[];                 */ Widget_class_name,
  /* MvsResourceInfoRecord *resource_info;               */ Wresource_info,
  /* short                 num_resources;                */
                          sizeof(Wresource_info)/sizeof(MvsResourceInfoRecord),
  /* MvsIntResInfoRecord   *intres_info;  */                NULL,
  /* short                 num_intres;                   */ 
                           0,
  /* Arg                   common_args[20];              */
      { {"",0},{"",0},{"",0},{"",0},{"",0},{"",0},{"",0},{"",0},{"",0},
        {"",0},{"",0},{"",0},{"",0},{"",0},{"",0},{"",0},{"",0},{"",0},
        {"",0},{"",0} },
  /* short                 num_common_args;              */ 0,
  /* short    res_color_ref[10];     */
	{  4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* short    res_pixmap_ref[10];     */
	{  5, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
  /* short    num_res_colors;         */
	2,

};

MvsWidgetClassInfo *iXmApplicationShellWidgetClass = &mvXmApplicationShellWidgetClass;

