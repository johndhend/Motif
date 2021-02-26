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

/*
 * This file contains time routines used by the performance monitor
 */

#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: AutoTime.c /main/7 1996/10/07 15:03:58 drk $"
#endif
#endif


#include <sys/time.h>

#include "testlib.h"
#include "AutoMessages.h"

struct timeval StartTime, EndTime;



void
AutoGetTime(enum WHICH_TIME time_to_get)
{
  struct timezone zone_time;

  if (time_to_get == START_TIME)  {
    if (gettimeofday(&StartTime, &zone_time) != 0)
      AutoMessage(_AutoMessages[WARNMSG126]);
  }
  else 
    if (time_to_get == END_TIME)  {
      if (gettimeofday(&EndTime, &zone_time) != 0)
	  printf("AUTOWARNING** : Could not gettimeofday\n");
      /* COMMENTED OUT UNTIL REPORT GEN BUG IS FIXED
	  AutoMessage(_AutoMessages[WARNMSG126]);
       */
    }
    else
	printf("AUTOWARNING** : AutoGetTime not start or end time\n");
        /*  COMMENTED OUT UNTIL REPORT GEN BUG IS FIXED
        AutoMessage(_AutoMessages[WARNMSG127]);
	 */
}



void
AutoPrintDurationTime(struct timeval *start_time, 
		      struct timeval *end_time)
{

  struct timeval lapsed;
  char msg_string[75];

  if (start_time->tv_usec > end_time->tv_usec)  {
    end_time->tv_usec += 1000000;
    end_time->tv_sec--;
  }

  lapsed.tv_usec = end_time->tv_usec - start_time->tv_usec;
  lapsed.tv_sec = end_time->tv_sec - start_time->tv_sec;


  printf("PERFORMANCE_MESSAGE** : Automation command duration is %ld.%03d seconds\n",
	 (long)lapsed.tv_sec, lapsed.tv_usec%1000);
  /*  COMMENTED OUT UNTIL REPORT GEN BUG IS FIXED
  sprintf(msg_string, _AutoMessages[PERFORMANCE1],
	  lapsed.tv_sec, lapsed.tv_usec%1000000);
  AutoMessage(msg_string); 
   */
}

