
#include <localdef.h>

/* $XConsortium: mkmsgcat.c /main/1 1996/06/05 18:21:57 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#if defined(__GLIBC__)
#include <stdlib.h>
#endif

char buf[1024];

char *OSF_COPYRIGHT = "$\n\
$  @OPENGROUP_COPYRIGHT@\n\
$  COPYRIGHT NOTICE\n\
$  Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.\n\
$  Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group\n\
$  ALL RIGHTS RESERVED (MOTIF). See the file named COPYRIGHT.MOTIF for\n\
$  the full copyright text.\n\
$ \n\
$  This software is subject to an open license. It may only be\n\
$  used on, with or for operating systems which are themselves open\n\
$  source systems. You must contact The Open Group for a license\n\
$  allowing distribution and sublicensing of this software on, with,\n\
$  or for operating systems which are not Open Source programs.\n\
$  \n\
$  See http://www.opengroup.org/openmotif/license for full\n\
$  details of the license agreement. Any use, reproduction, or\n\
$  distribution of the program constitutes recipient's acceptance of\n\
$  this agreement.\n\
$  \n\
$  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS\n\
$  PROVIDED ON AN \"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY\n\
$  KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY\n\
$  WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY\n\
$  OR FITNESS FOR A PARTICULAR PURPOSE\n\
$  \n\
$  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT\n\
$  NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,\n\
$  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n\
$  DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED\n\
$  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n\
$  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN\n\
$  ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE\n\
$  EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE\n\
$  POSSIBILITY OF SUCH DAMAGES.\n\
$ \n\
$ (c) Copyright 1996 Digital Equipment Corporation.\n\
$ (c) Copyright 1996 Hewlett-Packard Company.\n\
$ (c) Copyright 1996 International Business Machines Corp.\n\
$ (c) Copyright 1996 Sun Microsystems, Inc.\n\
$ (c) Copyright 1996 Novell, Inc. \n\
$ (c) Copyright 1996 FUJITSU LIMITED.\n\
$ (c) Copyright 1996 Hitachi.\n\
$";

char *OSF_COPYRIGHT_C = "/*\n\
 *\n\
 *  @OPENGROUP_COPYRIGHT@\n\
 *  COPYRIGHT NOTICE\n\
 *  Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.\n\
 *  Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group\n\
 *  ALL RIGHTS RESERVED (MOTIF). See the file named COPYRIGHT.MOTIF for\n\
 *  the full copyright text.\n\
 *\n\
 *  This software is subject to an open license. It may only be\n\
 *  used on, with or for operating systems which are themselves open\n\
 *  source systems. You must contact The Open Group for a license\n\
 *  allowing distribution and sublicensing of this software on, with,\n\
 *  or for operating systems which are not Open Source programs.\n\
 *\n\
 *  See http://www.opengroup.org/openmotif/license for full\n\
 *  details of the license agreement. Any use, reproduction, or\n\
 *  distribution of the program constitutes recipient's acceptance of\n\
 *  this agreement.\n\
 *\n\
 *  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS\n\
 *  PROVIDED ON AN \"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY\n\
 *  KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY\n\
 *  WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY\n\
 *  OR FITNESS FOR A PARTICULAR PURPOSE\n\
 *\n\
 *  EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT\n\
 *  NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,\n\
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n\
 *  DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED\n\
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n\
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN\n\
 *  ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE\n\
 *  EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE\n\
 *  POSSIBILITY OF SUCH DAMAGES.\n\
 */\n\
/*\n\
 * (c) Copyright 1996 Digital Equipment Corporation.\n\
 * (c) Copyright 1996 Hewlett-Packard Company.\n\
 * (c) Copyright 1996 International Business Machines Corp.\n\
 * (c) Copyright 1996 Sun Microsystems, Inc.\n\
 * (c) Copyright 1996 Novell, Inc. \n\
 * (c) Copyright 1996 FUJITSU LIMITED.\n\
 * (c) Copyright 1996 Hitachi.\n\
 */\n";

static void parse_args(
           int argc, char **argv, char **prefix, char **source_file_name);

/****************************************************************************
 * 
 * This utility should be run with 2 arguments. The first one is used as a 
 * prefix to generate the names of the output files, as well as the contents.
 * The second name is the full path of the source file to use.
 *
 * Running like this:
 *       mkmsgcat -Xm /proj/motif/lib/Xm/Messages.c
 *
 * it will open the /proj/motif/lib/Xm/Messages.c file and generate 2 output 
 * files:
 *     - Xm.msg
 *     - XmMsgI.h 
 *
 * The externaldef message names are expected to be of the following form 
 * in the source file, and not be longer than 10 characters:
 *     _<prefix>Msg<name>     for example (_XmMsgBulletinB_0001, _MrmMsg_0000)
 *
 ***************************************************************************/

int
main(  
       int argc,
       char **argv )
{
    FILE *header = NULL, *catalog = NULL, *source = NULL;
    int stars, i;
    char *p, *q, setname[32], messagename[64];
    char *prefix = NULL;
    char *source_file_name = NULL;
    char header_name[32], catalog_name[32];

    /* parse command line and get the prefix and source file name to use. */
    parse_args(argc, argv, &prefix, &source_file_name);

    if (prefix == NULL || source_file_name == NULL) {
	fprintf(stderr, "Usage: mkmsgcat -<prefix> <source_file_name>\n");
	exit(1);
    }

    strcpy(header_name, prefix);
    strcat(header_name, "MsgI.h");
    
    header = fopen(header_name, "w");

    strcpy(catalog_name, prefix);
    strcat(catalog_name, ".msg");

    catalog = fopen(catalog_name, "w");

    source = fopen(source_file_name, "r");

    if (!catalog) {
      fprintf(stderr, "Cannot write message catalog, exiting!\n");
      exit(1);
    }
    if (!header) {
      fprintf(stderr, "Cannot write header file, exiting!\n");
      exit(1);
    }
    if (!source) {
      fprintf(stderr, "Cannot read source file, exiting!\n");
      exit(1);
    }
    fprintf(catalog, "$ $%s$\n", "XConsortium");
    fprintf(catalog, "%s\n", OSF_COPYRIGHT);
    fprintf(catalog, "$ This file is automatically generated. \n");
    fprintf(catalog, "$ Do not edit. \n");
    fprintf(catalog, "\n");
    if (header) {
      fprintf(header, "/* $%s$ */\n", "XConsortium");
      fprintf(header, OSF_COPYRIGHT_C);
      fprintf(header, "/* This file is automatically generated. */\n");
      fprintf(header, "/* Do not edit. */\n\n");
      fprintf(header, "#ifndef NO_MESSAGE_CATALOG\n\n");
      fprintf(header, "#include <nl_types.h>\n#include \"%sMsgCatI.h\"\n\n", 
	      prefix);
      fprintf(header, "externalref nl_catd %s_catd;\n\n", prefix);
      fprintf(header, "\
#define _%sCatgets(catd, set_num, msg_num, def_str) \\\n\
        catgets(catd, set_num, msg_num, def_str)\n\n", prefix);
      fprintf(header, "#else\n\n");
      fprintf(header, 
	      "#define _%sCatgets(catd, set_num, msg_num, def_str)   def_str\n\n", 
	      prefix);
      fprintf(header, "#endif /* NO_MESSAGE_CATALOG */\n\n");
    }
    while (fgets(buf, 1024, source)) {
      if (!buf[0])
	continue;
      p = buf;
      while (isspace(*p)) p++;
      if (*p == '/') {
	/*
	 * Start of a comment. If there is at least 3 '*' following the '/',
         * this is information for the message catalog.
	 */
	for (stars = 0, p++; 
	     *p && *p == '*'; 
	     stars++, p++);
	if (stars < 3)
	  continue;
	while (isspace(*p)) p++;
	if (*p == '+') {
	  /* 
	   * Extra message catalog text.
	   * (ex. messages obsoleted in the code, but needed 
	   * for binary BC, comments) 
	   */
	  p++;
	  for (q = p; *q && *q != '\n' && *q != '*'; q++);
	  *q = '\0';
	  fprintf(catalog, "%s\n", p);
	  continue;
	} else {
	  /*
	   * This is the set name
	   */
	  for (i = 0; 
	       isalpha(*p) && i < 31; 
	       i++, p++)
	    setname[i] = *p;
	  setname[i] = '\0';
	  fprintf(catalog, "\n$set MS_%s\n\n", setname);
	  continue;
	}
      }
      if (*p == 'e') {
	char subs[11];
	int len_subs;
	/* 
	 * This is a message.
	 */
	if (strncmp(p, "externaldef", 11) != 0)
	  continue;

	/* Find the substring to look for, based on the prefix. */
	strcpy(subs, "_");
	strcat(subs, prefix);
	strcat(subs, "Msg");
	len_subs = strlen(subs);

	p = strstr(p, subs);
	if (!p) continue;
	p += len_subs;
	for (i = 0; 
	     !isspace(*p) && i < 63; 
	     i++, p++)
	  messagename[i] = *p;
	messagename[i] = '\0';
	p = strchr(p, '"');
	if (!p) {
	  do 
	    fgets(buf, 1024, source);
	  while (!buf[0]);
	  p = strchr(buf, '"');
	}
	if (!p) 
	  continue;
	fprintf(catalog, "MSG_%s ", messagename);
	p++;
	do {
	  q = strchr(p, '"');
	  while (q && *(--q) == '\\') {
	    q += 2; 
	    q = strchr(q, '"');
	  }
	  if (q) {
	    q++;
	    *q = '\0';
	    fprintf(catalog, "%s\n", p);
	  } else {
	    fprintf(catalog, "%s", p);
	    fgets(buf, 1024, source);
	    p = buf;
	  }
	} while (!q);
	if (header)
	  fprintf(header, 
		  "#define _%sMMsg%s%*s _%sCatgets(%s_catd, MS_%s, MSG_%s, _%sMsg%s)\n",
		  prefix, messagename, 20-i, " ", prefix, prefix, setname, 
		  messagename, prefix, messagename);
      }
    }

    return 0;
}


static void parse_args(
       int argc, 
       char **argv, 
       char **prefix, 
       char **source_file_name)
{

    if (argc < 3) {
	fprintf(stderr, "Usage: mkmsgcat -<prefix> <source_file_name>\n");
	exit(1);
    }

    /* Skip the first argument since it is the program name. */
    argv++;
    argc--;
    
    /* This argument should be the prefix, preceded with a '-'. */
    if (strncmp(*argv, "-", 1)) {
	fprintf(stderr, "Usage: mkmsgcat -<prefix> <source_file_name>\n");
	exit(1);
    }
    else {
	/* Skip the '-' */
	(*argv)++;
	*prefix = *argv;

	/* Now get the source file name. */
	argv++;
	argc--;
	*source_file_name = *argv;
    }

}

