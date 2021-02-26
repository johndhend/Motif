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
/*   $XConsortium: ScrollList2.h /main/9 1995/07/13 18:23:39 drk $ */
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
#define NITEMS 62
#define VITEMS 20

/* Global Variables */

char *Istrings[] = {
    "btest1a", "btest1b", "btest2", "btest3",
    "decor00", "decor01", "decor02", "decor03", "decor04", "decor05",
    "decor06", "decor07", "decor08", "decor09",
    "func00", "func01", "func02", "func03", "func04",
    "func05", "func06", "func07", "func08", "func09",
    "func10", "func11", "func12", "func13", "func14",
    "iplac00", "iplac01", "iplac02", "iplac03", "iplac04",
    "iplac05", "iplac06", "iplac07", "iplac08",
    "menu00", "menu01", "menu02", "menu03",
    "menu04", "menu05", "menu06", "menu07",
    "mtest1", "mtest2", "mvrz00", "mvrz01",
    "parse00", "parse01", "parse02", "parse03", "pitest1",
    "prop00", "prop01", "prop02", "prop03", "prop04", "prop05",
    "rstest1"
    };


Widget    List1;

/* Private Functions */


static void  SinSelCB(Widget w, XtPointer client_data, XtPointer call_data);
static void  MulSelCB(Widget w, XtPointer client_data, XtPointer call_data);
static void  ExtSelCB(Widget w, XtPointer client_data, XtPointer call_data);

