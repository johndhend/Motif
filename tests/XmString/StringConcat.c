/* $XConsortium: StringConcat.c /main/5 1995/07/15 21:12:34 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
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
 * 
 */
/*
 * HISTORY
 */

#include <stdio.h>
#include <testlib.h>

#define NUM_COMPONENT_TYPES 13

static char *render_tag = "render";
static XmDirection direction = XmLEFT_TO_RIGHT;
static XmStringDirection string_direction = XmSTRING_DIRECTION_L_TO_R;

typedef struct _Components {
  XmStringComponentType	type;
  int                   length;
  XtPointer             value;
} Components;

Components components[NUM_COMPONENT_TYPES] = {
  { XmSTRING_COMPONENT_LAYOUT_PUSH, sizeof(XmDirection), (XtPointer)&direction },
  { XmSTRING_COMPONENT_RENDITION_BEGIN, 0, (XtPointer)0 },
  { XmSTRING_COMPONENT_TAG, 0, (XtPointer)0 },
  { XmSTRING_COMPONENT_LOCALE, 0, (XtPointer)0 },
  { XmSTRING_COMPONENT_TAB, 0, (XtPointer)NULL },
  { XmSTRING_COMPONENT_DIRECTION, sizeof(XmStringDirection), (XtPointer)&string_direction },
  { XmSTRING_COMPONENT_TEXT, 0, (XtPointer)0 },
  { XmSTRING_COMPONENT_LOCALE_TEXT, 0, (XtPointer)0 },
  { XmSTRING_COMPONENT_WIDECHAR_TEXT, 0, (XtPointer)0 },
  { XmSTRING_COMPONENT_RENDITION_END, 0, (XtPointer)0 },
  { XmSTRING_COMPONENT_LAYOUT_POP, 0, NULL },
  { XmSTRING_COMPONENT_SEPARATOR, 0, NULL },
  { XmSTRING_COMPONENT_END, 0, NULL }};

typedef struct _CompStrings {
  XmStringComponentType	type;
  String                string;
} CompStrings;

CompStrings comp_strings[NUM_COMPONENT_TYPES] = {
  { XmSTRING_COMPONENT_LAYOUT_PUSH, "XmSTRING_COMPONENT_LAYOUT_PUSH" },
  { XmSTRING_COMPONENT_RENDITION_BEGIN, "XmSTRING_COMPONENT_RENDITION_BEGIN" },
  { XmSTRING_COMPONENT_TAG, "XmSTRING_COMPONENT_TAG" },
  { XmSTRING_COMPONENT_LOCALE, "XmSTRING_COMPONENT_LOCALE" },
  { XmSTRING_COMPONENT_TAB, "XmSTRING_COMPONENT_TAB" },
  { XmSTRING_COMPONENT_DIRECTION, "XmSTRING_COMPONENT_DIRECTION" },
  { XmSTRING_COMPONENT_TEXT, "XmSTRING_COMPONENT_TEXT" },
  { XmSTRING_COMPONENT_LOCALE_TEXT, "XmSTRING_COMPONENT_LOCALE_TEXT" },
  { XmSTRING_COMPONENT_WIDECHAR_TEXT, "XmSTRING_COMPONENT_WIDECHAR_TEXT" },
  { XmSTRING_COMPONENT_RENDITION_END, "XmSTRING_COMPONENT_RENDITION_END" },
  { XmSTRING_COMPONENT_LAYOUT_POP, "XmSTRING_COMPONENT_LAYOUT_POP" },
  { XmSTRING_COMPONENT_SEPARATOR, "XmSTRING_COMPONENT_SEPARATOR" },
  { XmSTRING_COMPONENT_END, "XmSTRING_COMPONENT_END" }};

String get_component_string( XmStringComponentType type )
{
   	int 	i;
	String  string;
	

   for ( i = 0; i < NUM_COMPONENT_TYPES; i++ )
       if ( type == comp_strings[i].type )
       {
            string = comp_strings[i].string;
            break;
       }

   return( string );
}

void set_args( Components *comp, unsigned int *length, char **value )
{
           switch ( comp->type )
           {
               case XmSTRING_COMPONENT_TAG:
               case XmSTRING_COMPONENT_LOCALE_TEXT:
               case XmSTRING_COMPONENT_RENDITION_BEGIN:
               case XmSTRING_COMPONENT_RENDITION_END:
               case XmSTRING_COMPONENT_WIDECHAR_TEXT:
                 *length = strlen(render_tag);
                 *value = render_tag;
                 break;
               case XmSTRING_COMPONENT_LOCALE:
                 *length = strlen(_MOTIF_DEFAULT_LOCALE); 
                 *value = _MOTIF_DEFAULT_LOCALE;
                 break;
               default:
                 *length = comp->length;
                 *value = comp->value;
                 break;
            }

      return;
}

       
main ( int argc, char *argv[] )
{

     XmString 	comp1, comp2, string;
     int        i, j;
     unsigned int  length;
     char       *value;


     CommonTestInit( argc, argv );

   /*
    *  Call XmStringConcatAndFree() using every combination of
    *  XmStringComponentTypes.
    */
     for ( i = 0; i < NUM_COMPONENT_TYPES; i++ )
     {
        for ( j = 0; j < NUM_COMPONENT_TYPES; j++ ) 
        {
           set_args( &components[i], &length, &value );
           comp1 = XmStringComponentCreate( components[i].type,
                                            length, value );

           set_args( &components[j], &length, &value );
           comp2 = XmStringComponentCreate( components[j].type,
                                            length, value );
           
           printf("XmStringConcatAndFree(%s, \n",
                  get_component_string( components[i].type ));
           printf("                      %s):",
                  get_component_string( components[j].type ));
                 
           string = XmStringConcatAndFree( comp1, comp2 );

           if ( string )
              printf("         ** PASSED **\n");
           else
              printf("         ** FAILED **\n");

	   XmStringFree( string );
        }

        printf("\n");
     }

     CommonPause();
     CommonPause();

     XtAppMainLoop( app_context );
}
