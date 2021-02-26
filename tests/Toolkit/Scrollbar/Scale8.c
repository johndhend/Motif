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
static char rcsid[] = "$XConsortium: Scale8.c /main/6 1995/07/13 19:12:51 drk $"
#endif
#endif
/*
*  (c) Copyright 1989, HEWLETT-PACKARD COMPANY */
#include <testlib.h>

#define INITIAL_SHADOWTHICKNESS 8
#define TB_COUNT 2

Widget Scale1;
Widget BBoard1;
Widget shadowScale, widthScale, heightScale;
Widget orientRB, orientTB[2];
Widget defaultPB;
Widget label1;
XmString string, string2;
Arg args[MAX_ARGS];
int	n;


static void shadowScaleCB(w, client_data, data)
Widget w;
XtPointer client_data;
XtPointer data ;
{
XmScaleCallbackStruct *call_data = (XmScaleCallbackStruct *) data ;
	n = 0;
	XtSetArg(args[n], XmNshadowThickness, call_data->value); n++;
	XtSetValues(Scale1, args, n);
}

static void widthScaleCB(w, client_data, data)
Widget w;
XtPointer client_data;
XtPointer data;
{
XmScaleCallbackStruct *call_data = (XmScaleCallbackStruct *) data;
	n = 0;
	XtSetArg(args[n], XmNscaleWidth, call_data->value); n++;
	XtSetValues(Scale1, args, n);
}

static void heightScaleCB(w, client_data, data)
Widget w;
XtPointer client_data;
XtPointer data ;
{
XmScaleCallbackStruct *call_data = (XmScaleCallbackStruct *) data;
	n = 0;
	XtSetArg(args[n], XmNscaleHeight, call_data->value); n++;
	XtSetValues(Scale1, args, n);
}

static void orientCB(w, client_data, data)
Widget w;
XtPointer client_data;
XtPointer data ;
{
    XmToggleButtonCallbackStruct *call_data = 
                                  (XmToggleButtonCallbackStruct *) data;

    if (call_data->set == XmSET) {  
	n = 0;
	XtSetArg(args[n], XmNorientation, client_data); n++;
	XtSetValues(Scale1, args, n);
    }
}

static void defaultCB(w, client_data, data)
Widget w;
XtPointer client_data;
XtPointer data ;
{
        XmPushButtonCallbackStruct *call_data = 
					(XmPushButtonCallbackStruct *) data ;
	Dimension	scale1_width = 0;
	Dimension	scale1_height = 0;

	XtDestroyWidget(Scale1);
	n = 0;
	XtSetArg(args[n], XmNx, 20); n++;
	XtSetArg(args[n], XmNy, 10);  n++;
	XtSetArg(args[n], XmNtitleString, string);  n++; 
	XtSetArg(args[n], XmNfontList, CommonGetFontList("variable"));  n++; 
	XtSetArg(args[n], XmNshowValue, True);  n++; 
	XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_BOTTOM);  n++;
	XtSetArg(args[n], XmNshadowThickness, INITIAL_SHADOWTHICKNESS);  n++;
	Scale1 = XmCreateScale(BBoard1, "Scale1", args, n); 
	XtRealizeWidget(Scale1);
	XtManageChild(Scale1);

	n = 0;
	XtSetArg(args[n], XmNvalue, INITIAL_SHADOWTHICKNESS); n++;
	XtSetValues(shadowScale, args, n);

	n = 0;
	XtSetArg(args[n], XmNvalue, 0); n++;
	XtSetValues(widthScale, args, n);

	n = 0;
	XtSetArg(args[n], XmNvalue, 0); n++;
	XtSetValues(heightScale, args, n);

	n = 0;
	XtSetArg(args[n], XmNset, True); n++;
	XtSetValues(orientTB[0], args, n);

	n = 0;
	XtSetArg(args[n], XmNset, False); n++;
	XtSetValues(orientTB[1], args, n);
}


void main (argc,argv)
int argc;
char **argv;
{
	Dimension	scale1_width = 0;
	Dimension	scale1_height = 0;

	/*  initialize toolkit  */
	 CommonTestInit(argc, argv);
    
	n = 0;
	XtSetArg(args[n], XmNmarginHeight, 20);  n++;
	XtSetArg(args[n], XmNmarginWidth, 20);  n++;
	/* test case for PIR 3154 */
#ifndef	BESTCASE
	XtSetArg(args[n], XmNallowOverlap, False);  n++;
#endif	/* BESTCASE */
	/* end of test case for PIR 3154 */
	XtSetArg(args[n], XmNresizePolicy, XmRESIZE_GROW);  n++;
	BBoard1 = XmCreateBulletinBoard(Shell1, "BBoard1", args, n);
	XtManageChild(BBoard1);

	string = XmStringCreate ("Affected", XmSTRING_DEFAULT_CHARSET);
	n = 0;
	XtSetArg(args[n], XmNx, 10); n++;
	XtSetArg(args[n], XmNy, 10);  n++;
	XtSetArg(args[n], XmNtitleString, string);  n++; 
	XtSetArg(args[n], XmNfontList, CommonGetFontList("variable"));  n++; 
	XtSetArg(args[n], XmNshowValue, True);  n++; 
	XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_BOTTOM);  n++;
	XtSetArg(args[n], XmNshadowThickness, INITIAL_SHADOWTHICKNESS);  n++;
	Scale1 = XmCreateScale(BBoard1, "Scale1", args, n); 

	XtManageChild(Scale1);

	n = 0;
	XtSetArg(args[n], XmNx, 20); n++;
	XtSetArg(args[n], XmNy, 260); n++;
	XtSetArg(args[n], XmNhighlightOnEnter, True); n++;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	XtSetArg(args[n], XmNscaleHeight, 20); n++;
	XtSetArg(args[n], XmNscaleWidth, 180); n++;
	XtSetArg(args[n], XmNmaximum, 50); n++;
	XtSetArg(args[n], XmNvalue, INITIAL_SHADOWTHICKNESS); n++;
	XtSetArg(args[n], XmNshowValue, True); n++;
	XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_RIGHT); n++;
	XtSetArg(args[n], XmNtitleString,
		 XmStringCreate("shadowThickness", 
				XmSTRING_DEFAULT_CHARSET)); n++;
	shadowScale = XmCreateScale(BBoard1, "shadowScale", args, n);
	XtAddCallback(shadowScale, XmNvalueChangedCallback,
		shadowScaleCB, NULL);
	XtManageChild(shadowScale);

	n = 0;
	XtSetArg(args[n], XmNscaleWidth, &scale1_width); n++;
	XtGetValues(Scale1, args, n);

	n = 0;
	XtSetArg(args[n], XmNx, 20); n++;
	XtSetArg(args[n], XmNy, 315); n++;
	XtSetArg(args[n], XmNhighlightOnEnter, True); n++;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	XtSetArg(args[n], XmNscaleHeight, 20); n++;
	XtSetArg(args[n], XmNscaleWidth, 180); n++;
	XtSetArg(args[n], XmNmaximum, 200); n++;
	XtSetArg(args[n], XmNvalue, scale1_width); n++;
	XtSetArg(args[n], XmNshowValue, True); n++;
	XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_RIGHT); n++;
	XtSetArg(args[n], XmNtitleString,
		 XmStringCreate("scaleWidth", 
				XmSTRING_DEFAULT_CHARSET)); n++;
	widthScale = XmCreateScale(BBoard1, "widthScale", args, n);
	XtAddCallback(widthScale, XmNvalueChangedCallback,
		widthScaleCB, NULL);
	XtManageChild(widthScale);

	n = 0;
	XtSetArg(args[n], XmNscaleHeight, &scale1_height); n++;
	XtGetValues(Scale1, args, n);

	n = 0;
	XtSetArg(args[n], XmNx, 20); n++;
	XtSetArg(args[n], XmNy, 370); n++;
	XtSetArg(args[n], XmNhighlightOnEnter, True); n++;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	XtSetArg(args[n], XmNscaleHeight, 20); n++;
	XtSetArg(args[n], XmNscaleWidth, 180); n++;
	XtSetArg(args[n], XmNmaximum, 200); n++;
	XtSetArg(args[n], XmNvalue, scale1_height); n++;
	XtSetArg(args[n], XmNshowValue, True); n++;
	XtSetArg(args[n], XmNprocessingDirection, XmMAX_ON_RIGHT); n++;
	XtSetArg(args[n], XmNtitleString,
		 XmStringCreate("scaleHeight", 
				XmSTRING_DEFAULT_CHARSET)); n++;
	heightScale = XmCreateScale(BBoard1, "heightScale", args, n);
	XtAddCallback(heightScale, XmNvalueChangedCallback,
		heightScaleCB, NULL);
	XtManageChild(heightScale);

	string2 = XmStringCreate("orientation", XmSTRING_DEFAULT_CHARSET);
	n = 0;
	XtSetArg(args[n], XmNx, 120); n++;
	XtSetArg(args[n], XmNy, 455); n++;
	XtSetArg(args[n], XmNlabelString, string2);  n++;
	label1 = XmCreateLabel(BBoard1, "label1", args, n);
	XtManageChild(label1);

	n = 0;
	XtSetArg(args[n], XmNx, 20); n++;
	XtSetArg(args[n], XmNy, 435); n++;
	XtSetArg(args[n], XmNborderWidth, 2); n++;
	XtSetArg(args[n], XmNisHomogeneous, False); n++;
	orientRB = XmCreateRadioBox(BBoard1, "orientRB", args, n);

	n = 0;
	XtSetArg(args[n], XmNset, True); n++;
	orientTB[0] = XmCreateToggleButtonGadget(orientRB,
		"vertical", args, n);
	orientTB[1] = XmCreateToggleButtonGadget(orientRB,
		"horizontal", NULL, 0);

	XtAddCallback(orientTB[0], XmNvalueChangedCallback,
		orientCB, (XtPointer) XmVERTICAL);
	XtAddCallback(orientTB[1], XmNvalueChangedCallback,
		orientCB, (XtPointer) XmHORIZONTAL);

	XtManageChild(orientRB);
	XtManageChildren(orientTB, TB_COUNT);

	n = 0;
	XtSetArg(args[n], XmNx, 20); n++;
	XtSetArg(args[n], XmNy, 505); n++;
	XtSetArg(args[n], XmNshadowThickness, 2); n++;
	XtSetArg(args[n], XmNlabelString,
		 XmStringCreate("set defaults", 
				XmSTRING_DEFAULT_CHARSET)); n++;
	defaultPB = XmCreatePushButton(BBoard1, "defaultPB", args, n);
	XtAddCallback(defaultPB, XmNactivateCallback, defaultCB, NULL);
	XtManageChild(defaultPB);


	XtRealizeWidget (Shell1);

#ifndef MOTIF1_1
	/* test case for PIR 3158, see .dat */
	CommonPause();
#endif

	/* test case for PIR 3157, see .dat */
	CommonPause();

	/* test case for PIR 3154, see .dat */
	CommonPause();

	XtAppMainLoop(app_context);
}
