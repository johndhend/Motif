
#include <localdef.h>

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
static char rcsid[] = "$XConsortium: Mrmerror.c /main/13 1996/11/13 14:00:43 drk $"
#endif
#endif

/* (c) Copyright 1989, 1990, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */

/*
 *++
 *  FACILITY:
 *
 *      UIL Resource Manager (URM):
 *
 *  ABSTRACT:
 *
 *	All error signalling and handling routines are found here.
 *
 *--
 */


/*
 *
 *  INCLUDE FILES
 *
 */

#include <stdio.h>
#include <Mrm/Mrm.h>


/*
 *
 *  GLOBAL VARIABLE DECLARATIONS
 *
 */
externaldef(urm__err_out)		MrmCode	urm__err_out = URMErrOutStdout ;
externaldef(urm__latest_error_code)	MrmCode	urm__latest_error_code = 0 ;
externaldef(urm__latest_error_msg)	String	urm__latest_error_msg = NULL ;


/*
 *
 *  OWN VARIABLE DECLARATIONS
 *
 */

static	String	urm_codes_codstg[] = {
  "MrmFAILURE"
  ,"MrmSUCCESS"
  ,"MrmNOT_FOUND"
  ,"MrmCREATE_NEW"
  ,"MrmEXISTS"
  ,"URMIndex retry"
  ,"MrmNUL_GROUP"
  ,"MrmINDEX_GT"
  ,"MrmNUL_TYPE"
  ,"MrmINDEX_LT"
  ,"MrmWRONG_GROUP"
  ,"MrmPARTIAL_SUCCESS"
  ,"MrmWRONG_TYPE"
  ,"URM unused code 13"
  ,"MrmOUT_OF_RANGE"
  ,"URM unused code 15"
  ,"MrmBAD_RECORD"
  ,"URM unused code 17"
  ,"MrmNULL_DATA"
  ,"URM unused code 19"
  ,"MrmBAD_DATA_INDEX"
  ,"URM unused code 21"
  ,"MrmBAD_ORDER"
  ,"URM unused code 23"
  ,"MrmBAD_CONTEXT"
  ,"URM unused code 25"
  ,"MrmNOT_VALID"
  ,"URM unused code 27"
  ,"MrmBAD_BTREE"
  ,"URM unused code 29"
  ,"MrmBAD_WIDGET_REC"
  ,"URM unused code 31"
  ,"MrmBAD_CLASS_TYPE"
  ,"URM unused code 33"
  ,"MrmNO_CLASS_NAME"
  ,"URM unused code 35"
  ,"MrmTOO_MANY"
  ,"URM unused code 37"
  ,"MrmBAD_IF_MODULE"
  ,"URM unused code 39"
  ,"MrmNULL_DESC"
  ,"URM unused code 41"
  ,"MrmOUT_OF_BOUNDS"
  ,"URM unused code 43"
  ,"MrmBAD_COMPRESS"
  ,"URM unused code 45"
  ,"MrmBAD_ARG_TYPE"
  ,"URM unused code 47"
  ,"MrmNOT_IMP"
  ,"URM unused code 49"
  ,"MrmNULL_INDEX"
  ,"URM unused code 51"
  ,"MrmBAD_KEY_TYPE"
  ,"URM unused code 53"
  ,"MrmBAD_CALLBACK"
  ,"URM unused code 55"
  ,"MrmNULL_ROUTINE"
  ,"URM unused code 57"
  ,"MrmVEC_TOO_BIG"
  ,"URM unused code 59"
  ,"MrmBAD_HIERARCHY"
  ,"URM unused code 61"
  ,"MrmBAD_CLASS_CODE"
} ;

static String urm_codes_invalidcode = "Invalid URM code" ;




/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine is an error signalling routine for use within URM.
 *	It currently just reports the error on the terminal.
 *
 *  FORMAL PARAMETERS:
 *
 *	module		Identifies the module (routine) detecting the error
 *	error		Brief description of the error
 *	file_id		if not NULL, the IDB file implicated in the error
 *	context_id	if not NULL, the URM resource implicated in the error
 *	status		the return code associated with the error.
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

/*ARGSUSED*/
Cardinal 
Urm__UT_Error (char			*module,
	       char			*error,
	       IDBFile			file_id, /* unused */
	       URMResourceContextPtr	context_id, /* unused */
	       Cardinal			status)
{

  /*
   *  Local variables
   */
  char		msg[300] ;	/* error message */


  /*
   * construct error message
   */

  /* Old form
   * sprintf (msg, "%s detected error %s - %s", module, error,
   *	      Urm__UT_UrmCodeString(status)) ;
   */
  sprintf (msg, "%s: %s - %s", module, error, Urm__UT_UrmCodeString(status)) ;

  /*
   * Print or save the message depending on the reporting style
   */
  urm__latest_error_code = status ;

  switch ( urm__err_out )
    {
    case URMErrOutMemory:
      if ( urm__latest_error_msg != NULL )
	XtFree (urm__latest_error_msg) ;
      urm__latest_error_msg = (String) XtMalloc (strlen(msg)+1) ;
      strcpy (urm__latest_error_msg, msg) ;
      return status ;
    case URMErrOutStdout:
    default:
      XtWarning (msg) ;
      return status ;
    }

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine sets the URM error report type to a standard state
 *
 *  FORMAL PARAMETERS:
 *
 *	report_type	URMErrOutMemory	- save message in memory, don't print
 *			URMErrOutStdout	- report to stdout
 *
 *  IMPLICIT INPUTS:
 *
 *	urm__err_out
 *
 *  IMPLICIT OUTPUTS:
 *
 *	urm__err_out
 *
 *  FUNCTION VALUE:
 *
 *      MrmSUCCESS	operation succeeded
 *	MrmFAILURE	illegal state requested
 *
 *  SIDE EFFECTS:
 *
 *--
 */

Cardinal 
Urm__UT_SetErrorReport (MrmCode report_type)
{

  switch ( report_type )
    {
    case URMErrOutMemory:
    case URMErrOutStdout:
      urm__err_out = report_type ;
      return MrmSUCCESS ;

    default:
      return MrmFAILURE ;
    }

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	 Returns the current error code
 *
 *  FORMAL PARAMETERS:
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

MrmCode 
Urm__UT_LatestErrorCode (void)
{

  return urm__latest_error_code ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	 Returns the current error message
 *
 *  FORMAL PARAMETERS:
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

String 
Urm__UT_LatestErrorMessage (void)

{

  return urm__latest_error_msg ;

}



/*
 *++
 *
 *  PROCEDURE DESCRIPTION:
 *
 *	This routine returns a static string naming a URM return code.
 *
 *  FORMAL PARAMETERS:
 *
 *	cod		A URM return code
 *
 *  IMPLICIT INPUTS:
 *
 *  IMPLICIT OUTPUTS:
 *
 *  FUNCTION VALUE:
 *
 *  SIDE EFFECTS:
 *
 *--
 */

String 
Urm__UT_UrmCodeString (MrmCode cod)
{

  if ( cod >= MrmFAILURE && cod <= MrmBAD_CLASS_CODE )
    return urm_codes_codstg[cod] ;
  return urm_codes_invalidcode ;

}

