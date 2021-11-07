
#include <localdef.h>

/* $XConsortium: Print.h /main/13 1996/10/31 02:09:08 cde-hp $ */
/*
 * DtPrint/Print.h
 */
/* (c) Copyright 1990, 1991, 1992, 1993, 1994 OPEN SOFTWARE FOUNDATION, INC.
 *     ALL RIGHTS RESERVED
 * (c) Copyright 1989, 1996 DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.
 * (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992, 1995, 1996,
 *     HEWLETT-PACKARD COMPANY
 * (c) Copyright 1996 International Business Machines Corp.
 * (c) Copyright 1996 Sun Microsystems, Inc.
 * (c) Copyright 1996 Novell, Inc. 
 * (c) Copyright 1996 FUJITSU LIMITED.
 * (c) Copyright 1996 Hitachi.
 */
#ifndef _DtPrint_h
#define _DtPrint_h

#include <Xm/Xm.h>

#ifndef NO_XP
#include <X11/extensions/Print.h> 
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class record constants 
 */
externalref WidgetClass dtPrintSetupBoxWidgetClass;

#ifndef NO_XP
typedef struct _DtPrintSetupBoxClassRec * DtPrintSetupBoxWidgetClass;
typedef struct _DtPrintSetupBoxRec      * DtPrintSetupBoxWidget;

#ifndef DtIsPrintSetupBox
#define DtIsPrintSetupBox(w)  (XtIsSubclass (w, dtPrintSetupBoxWidgetClass))
#endif
#endif

/*
 * Resource Names
 */
#define DtNcancelCallback "cancelCallback"
#define DtNclosePrintDisplayCallback "closePrintDisplayCallback"
#define DtNcopies "copies"
#define DtNdescription "description"
#define DtNdestroyContextCallback "destroyContextCallback"
#define DtNfileName "fileName"
#ifndef DtNminimizeButtons
# define DtNminimizeButtons "minimizeButtons"
#endif
#define DtNoptionCount "optionCount"
#define DtNoptions "options"

#ifndef NO_XP
#define DtNprintCallback "printCallback"
#define DtNprintDestination "printDestination"
#define DtNprinterInfoProc "printerInfoProc"
#define DtNprinterName "printerName"
#define DtNprintSetupMode "printSetupMode"
#define DtNselectFileProc "selectFileProc"
#define DtNselectPrinterProc "selectPrinterProc"
#define DtNverifyPrinterProc "verifyPrinterProc"
#endif

#define DtNsetupCallback "setupCallback"
#define DtNworkAreaLocation "workAreaLocation"
#define DtCCancelCallback "CancelCallback"

#ifndef NO_XP
#define DtCClosePrintDisplayCallback "ClosePrintDisplayCallback"
#define DtCCopies "Copies"
#endif

#define DtCDescription "Description"
#define DtCDestroyContextCallback "DestroyContextCallback"
#define DtCFileName "FileName"
#ifndef DtCMinimizeButtons
# define DtCMinimizeButtons "MinimizeButtons"
#endif
#define DtCOptionCount "OptionCount"
#define DtCOptions "Options"

#ifndef NO_XP
#define DtCPrintCallback "PrintCallback"
#define DtCPrintDestination "PrintDestination"
#define DtCPrinterInfoProc "PrinterInfoProc"
#define DtCPrinterName "PrinterName"
#define DtCPrintSetupMode "PrintSetupMode"
#define DtCSelectFileProc "SelectFileProc"
#define DtCSelectPrinterProc "SelectPrinterProc"
#define DtCVerifyPrinterProc "VerifyPrinterProc"
#define DtRPrintSetupProc "PrintSetupProc"
#endif

#define DtCWorkAreaLocation "WorkAreaLocation"
#define DtCSetupCallback "SetupCallback"

/*
 * DtNsetupMode Resource Values
 */
#ifndef NO_XP
enum {
    DtPRINT_SETUP_PLAIN,
    DtPRINT_SETUP_XP
};
#endif

/*
 * DtNworkAreaLocation Resource Values
 */
enum {
    DtWORK_AREA_NONE,
    DtWORK_AREA_TOP,
    DtWORK_AREA_TOP_AND_BOTTOM,
    DtWORK_AREA_BOTTOM
};

#ifndef NO_XP
/*
 * DtNprintDestination Resource Values
 */
enum { DtPRINT_NO_DESTINATION, DtPRINT_TO_PRINTER, DtPRINT_TO_FILE };

/*
 * DtNprinterNameMode Resource Values
 */
enum { DtSHORT_NAME, DtMEDIUM_NAME, DtLONG_NAME };

/*
 * Mode values for DtPrintSetupBoxResetConnection()
 */
typedef enum {
    DtPRINT_CLOSE_CONNECTION,
    DtPRINT_RELEASE_CONNECTION
} DtPrintResetConnectionMode;

/*
 * Callback Reasons
 */
enum {
    DtPRINT_CR_NONE,
    DtPRINT_CR_CANCEL,
    DtPRINT_CR_CLOSE_PRINT_DISPLAY,
    DtPRINT_CR_PRINT,
    DtPRINT_CR_SETUP
};

/*
 * DtPrint proecdure return values
 */
enum {
    DtPRINT_SUCCESS,
    DtPRINT_BAD_PARM,
    DtPRINT_FAILURE,
    DtPRINT_INVALID_DISPLAY,
    DtPRINT_NOT_XP_DISPLAY,
    DtPRINT_NO_CONNECTION,
    DtPRINT_NO_DEFAULT,
    DtPRINT_NO_DEFAULT_DISPLAY,
    DtPRINT_NO_PRINTER,
    DtPRINT_PRINTER_MISSING
};

enum {
    DtPRINT_HINT_MESSAGES_OK,
    DtPRINT_HINT_NO_MESSAGES
};

/*
 * PrintSetupBox Callback Structure Definition
 */
typedef struct _DtPrintSetupData
{
    String printer_name;
    Display *print_display;
    XPContext print_context;
    XtEnum destination;
    String dest_info;
    XtEnum messages_hint;
} DtPrintSetupData;

typedef struct _DtPrintSetupCallbackStruct
{
    int reason;
    XEvent *event;
    DtPrintSetupData *print_data;
} DtPrintSetupCallbackStruct;

/*
 * PrintSetupBox Procedure Resource Type Definition
 */
typedef XtEnum (*DtPrintSetupProc)(Widget, DtPrintSetupData*);
#endif

/*
 * Public Function Declarations
 */

#ifndef NO_XP
extern Widget DtCreatePrintSetupBox(
				    Widget p,
				    String name,
				    ArgList args,
				    Cardinal n) ;
extern Widget DtCreatePrintSetupDialog(
				       Widget ds_p,
				       String name,
				       ArgList sb_args,
				       Cardinal sb_n) ;
extern DtPrintSetupData* DtPrintCopySetupData(
					      DtPrintSetupData* target,
					      const DtPrintSetupData* source);
extern XtEnum DtPrintFillSetupData(
				   Widget psub,
				   DtPrintSetupData* print_data);
extern void DtPrintFreeSetupData(
				 DtPrintSetupData* target);
extern XtEnum DtPrintResetConnection(
				     Widget psub,
				     DtPrintResetConnectionMode m);
#endif

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#endif /* _DtPrint_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
