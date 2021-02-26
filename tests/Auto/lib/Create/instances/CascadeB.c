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
static char rcsid[] = "$XConsortium: CascadeB.c /main/8 1995/07/14 11:01:12 drk $"
#endif
#endif
/*      @(#)instance	1.2     Date:02/12/91                              */
/**************************************************************************
    
    TEST: XmCascadeButton
    AUTHOR: Automatic generation.
    DATE: Wed Oct  9 16:39:26 EDT 1991

       HISTORY:
         12/11/90 PSN Put it under source control. This is version at the
                      time of release.
*************************************************************************/
#include "mvslib.h"
#include <Xm/CascadeB.h>


/*************************************************************************/
/*            This file contains WIDGET SPECIFIC DEFINTIONS              */
/*************************************************************************/

/*************************************************************************/
/*      These are the resources associated with this Widget Class        */
/*************************************************************************/

static MvsResourceInfoRecord Wresource_info[] = {

/* The resource_info structure */
{ XmNaccelerator         , T_String             , False, (MvsArgVal)NULL	,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNacceleratorText     , T_XmString           , False, (MvsArgVal)NULL	,
  False, NULL             , 0x0|CREATE|SET|GET,	False },
{ XmNaccelerators        , T_XtAccelerators     , True , (MvsArgVal)MVSdynamic           ,
  False, NULL       , 0x0|CREATE|SET|GET,	False },
{ XmNalignment           , T_unsigned_char      , False, (MvsArgVal)XmALIGNMENT_CENTER   ,
  True,  NULL         , 0x0|CREATE|SET|GET,	False },
{ XmNallowResize         , T_Boolean            , False, (MvsArgVal)FALSE                ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNancestorSensitive   , T_Boolean            , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL              , 0x0|GET,	False },
{ XmNbackground          , T_Pixel              , True , (MvsArgVal)MVSdynamic           ,
  False, NULL                , 0x0|CREATE|SET|GET,	False },
{ XmNbackgroundPixmap    , T_Pixmap             , False, (MvsArgVal)XmUNSPECIFIED_PIXMAP ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNborderColor         , T_Pixel              , True , (MvsArgVal)MVSBlack             ,
  False, NULL                , 0x0|CREATE|SET|GET,	False },
{ XmNborderPixmap        , T_Pixmap             , False, (MvsArgVal)XmUNSPECIFIED_PIXMAP ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNborderWidth         , T_Dimension          , False, (MvsArgVal)0                    ,
  True,  NULL            , 0x0|CREATE|SET|GET,	False },
{ XmNbottomAttachment    , T_unsigned_char      , False, (MvsArgVal)XmATTACH_NONE        ,
  True,  NULL  , 0x0|CREATE|SET,	False },
{ XmNbottomOffset        , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNbottomPosition      , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNbottomShadowColor   , T_Pixel              , True , (MvsArgVal)MVSdynamic           ,
  False, NULL                , 0x0|CREATE|SET|GET,	False },
{ XmNbottomShadowPixmap  , T_Pixmap             , True , (MvsArgVal)MVSdynamic           ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNbottomWidget        , T_Widget_ref         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET,	False },
{ XmNcascadePixmap       , T_Pixmap             , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNcolormap            , T_Colormap           , True , (MvsArgVal)MVSdynamic           ,
  False, NULL             , 0x0|CREATE|GET,	False },
{ XmNdepth               , T_Integer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|GET,	False },
{ XmNfontList            , T_XmFontList         , True , (MvsArgVal)MVSdynamic           ,
  False, NULL           , 0x0|CREATE|SET|GET,	False },
{ XmNforeground          , T_Pixel              , True , (MvsArgVal)MVSdynamic           ,
  False, NULL                , 0x0|CREATE|SET|GET,	False },
{ XmNheight              , T_Dimension          , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL            , 0x0|CREATE|SET|GET,	True },
{ XmNhighlightColor      , T_Pixel              , True , (MvsArgVal)MVSdynamic           ,
  False, NULL                , 0x0|CREATE|SET|GET,	False },
{ XmNhighlightOnEnter    , T_Boolean            , False, (MvsArgVal)FALSE                ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNhighlightPixmap     , T_Pixmap             , True , (MvsArgVal)MVSdynamic           ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNhighlightThickness  , T_Dimension          , False, (MvsArgVal)0                    ,
  True,  NULL            , 0x0|CREATE|SET|GET,	False },
{ XmNinitialResourcesPersistent, T_Boolean            , False, (MvsArgVal)TRUE                 ,
  False, NULL              , 0x0|CREATE,	False },
{ XmNlabelInsensitivePixmap, T_Pixmap             , False, (MvsArgVal)XmUNSPECIFIED_PIXMAP ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNlabelPixmap         , T_Pixmap             , False, (MvsArgVal)XmUNSPECIFIED_PIXMAP ,
  True,  NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNlabelString         , T_XmString           , True , (MvsArgVal)MVSdynamic,
  True,  NULL             , 0x0|CREATE|SET|GET,	False },
{ XmNlabelType           , T_unsigned_char      , False, (MvsArgVal)XmSTRING             ,
  True,  NULL         , 0x0|CREATE|SET|GET,	False },
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
{ XmNmappingDelay        , T_Integer            , False, (MvsArgVal)180                  ,
  False, NULL      , 0x0|CREATE|SET|GET,	False },
{ XmNmarginBottom        , T_Dimension          , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL            , 0x0|CREATE|SET|GET,	True },
{ XmNmarginHeight        , T_Dimension          , False, (MvsArgVal)2                    ,
  True,  NULL            , 0x0|CREATE|SET|GET,	False },
{ XmNmarginLeft          , T_Dimension          , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL            , 0x0|CREATE|SET|GET,	True },
{ XmNmarginRight         , T_Dimension          , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL            , 0x0|CREATE|SET|GET,	True },
{ XmNmarginTop           , T_Dimension          , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL            , 0x0|CREATE|SET|GET,	True },
{ XmNmarginWidth         , T_Dimension          , False , (MvsArgVal)0,
  True,  NULL            , 0x0|CREATE|SET|GET,	False },
{ XmNmnemonic            , T_KeySym             , False, (MvsArgVal)NULL                 ,
  False, NULL          , 0x0|CREATE|SET|GET,	False },
{ XmNmnemonicCharSet     , T_String             , True , (MvsArgVal)MVSdynamic,
  False, NULL   , 0x0|CREATE|SET|GET,	False },
{ XmNnavigationType      , T_XmNavigationType   , False, (MvsArgVal)XmNONE               ,
  False, NULL                 , 0x0|GET,	False },
{ XmNpaneMaximum         , T_Integer            , False, (MvsArgVal)1000                 ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNpaneMinimum         , T_Integer            , False, (MvsArgVal)1                    ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNrecomputeSize       , T_Boolean            , False, (MvsArgVal)TRUE                 ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
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
{ XmNscreen              , T_Pointer            , True , (MvsArgVal)MVSdynamic           ,
  False, NULL              , 0x0|CREATE|GET,	False },
{ XmNsensitive           , T_Boolean            , False, (MvsArgVal)TRUE                 ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNshadowThickness     , T_Dimension          , False, (MvsArgVal)2                    ,
  True,  NULL            , 0x0|CREATE|SET|GET,	False },
{ XmNskipAdjust          , T_Boolean            , False, (MvsArgVal)FALSE                ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNstringDirection     , T_XmStringDirection  , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL    , 0x0|CREATE|SET|GET,	False },
{ XmNsubMenuId           , T_Widget_ref         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET|GET,	False },
{ XmNtopAttachment       , T_unsigned_char      , False, (MvsArgVal)XmATTACH_NONE        ,
  True,  NULL     , 0x0|CREATE|SET,	False },
{ XmNtopOffset           , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNtopPosition         , T_Integer            , False, (MvsArgVal)0                    ,
  True,  NULL              , 0x0|CREATE|SET,	False },
{ XmNtopShadowColor      , T_Pixel              , True , (MvsArgVal)MVSdynamic           ,
  False, NULL                , 0x0|CREATE|SET|GET,	False },
{ XmNtopShadowPixmap     , T_Pixmap             , True , (MvsArgVal)MVSdynamic           ,
  False, NULL               , 0x0|CREATE|SET|GET,	False },
{ XmNtopWidget           , T_Widget_ref         , False, (MvsArgVal)NULL                 ,
  False, NULL           , 0x0|CREATE|SET,	False },
{ XmNtranslations        , T_XtTranslations     , True , (MvsArgVal)MVSdynamic           ,
  False, NULL       , 0x0|CREATE|SET|GET,	False },
{ XmNtraversalOn         , T_Boolean            , False, (MvsArgVal)TRUE                 ,
  True,  NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNunitType            , T_unsigned_char      , True , (MvsArgVal)MVSdynamic           ,
  False, NULL        , 0x0|CREATE|SET|GET,	False },
{ XmNuserData            , T_caddr_t            , False, (MvsArgVal)NULL                 ,
  False, NULL              , 0x0|CREATE|SET|GET,	False },
{ XmNwidth               , T_Dimension          , True , (MvsArgVal)MVSdynamic           ,
  True,  NULL            , 0x0|CREATE|SET|GET,	True },
{ XmNx                   , T_Position           , False, (MvsArgVal)0                    ,
  True,  NULL             , 0x0|CREATE|SET|GET,	False },
{ XmNy                   , T_Position           , False, (MvsArgVal)0                    ,
  True,  NULL             , 0x0|CREATE|SET|GET,	False },
{ XmNactivateCallback    , T_XtCallbackList     , False, (MvsArgVal)NULL                 ,
  False, NULL       , 0x0|CREATE,	False },
{ XmNcascadingCallback   , T_XtCallbackList     , False, (MvsArgVal)NULL                 ,
  False, NULL       , 0x0|CREATE,	False },
{ XmNdestroyCallback     , T_XtCallbackList     , False, (MvsArgVal)NULL                 ,
  False, NULL       , 0x0|CREATE,	False },
{ XmNhelpCallback        , T_XtCallbackList     , False, (MvsArgVal)NULL                 ,
  False, NULL       , 0x0|CREATE,	False },
{ XmNenableDragIcon      , T_Boolean            , False, (MvsArgVal)FALSE		 ,
  False, NULL , 0x0|CREATE|SET|GET,     False },

};


/*************************************************************************/
/*      This is the name of the class (for debugging purposes)           */
/*************************************************************************/

static char Widget_class_name[] =
			"XmCascadeButton";


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
       tmp_name = "XmCascadeButton";
    else
       tmp_name = name;

    widget = XmCreateCascadeButton (parent, tmp_name, args, nargs);
    return(widget);

} /* End CreateWidget() */


/*********************************************************************/
/*    This function sets up the widget info structure that contains  */
/* all information that applies to a particular widget class. This   */
/* information is of a static nature and is declared statically in   */
/* this module. However, the class info structure is globally visible*/
/*********************************************************************/


static MvsWidgetClassInfo mvXmCascadeButtonWidgetClass = {

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
	{  6, 8, 14, 21, 23, 64, -1, -1, -1, 0 },
  /* short    res_pixmap_ref[10];     */
	{  7, 9, 15, -1, 25, 65, 17, 28, 29, 0 },
  /* short    num_res_colors;         */
	9,

};

MvsWidgetClassInfo *iXmCascadeButtonWidgetClass = &mvXmCascadeButtonWidgetClass;

