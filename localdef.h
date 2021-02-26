#ifndef _LOCAL_DEF_H
#define _LOCAL_DEF_H

/* see also: config/imake/imakemdep.h */

/*
#define PAN_DEBUG 1
*/
#define ADD_PAN 1
	/* tells a demo which header to choose */
#define USE_IMAKE_BUILD

/*
important heads up compiling note tools/wml :

. if tools/wml fails the most likely thing is Xm lib or something else
  failed before.  you will not get a "lib didn't build" warning.  it is
  because a binary needs to build link and run for it to Make

. the .y .h .c .lex is not simple nor easy to read from Makefile, if they
  fail it may be do to directory not being properly clean or missing file
  do to past failed build (build from clean .tar extrac is always safer)
*/


/* -DHAVE_CONFIG works for .c but not .h - this cannot go in configure */
/* motif: missing src skip it.  openlook compat ? */

/* -DHAVE_CONFIG works for .c but not .h - this cannot go in configure */

#ifndef _CONFIG_H
#define _CONFIG_H
#include <config.h>
#endif

/* 
 * (old linux only)
 * an old define by old linux.cf that today stops imake build
 * undef X_LOCALE if you have a recent linux (if you have good locale.h)
 */
#if (LinuxCLibMajorVersion >= 6 || LinuxDistribution == LinuxSuSE)
#undef X_LOCALE
#endif

/* 2.2.3 uses Select() as libc name which is likely wrong for everyone */
/*
 * also, the includes do not work for gnulibc
 *   gnulibc select() documents
 *     "POSIX.1-2001" gnulibc current wishes <sys/select.h>
 *     gnulibc_old wishes <sys/time.h> <sys/types.h> <unistd.h>
 * if not defined here, Select is used if GLIBC is not present
 */

#define SELECT_LIBC_NAME	select
/* #define GNULIBC_POSIX_NEW */

/* 
 * Ignore
 *   turns out ICCC works fine if HAVE_CONF_REQ_EV is on (is 1/2 of ICCC)
 *   WM_NORMAL_HINTS applies to x,y an w,h hinto on open.
 *   probably all versions ok as 1st ver starts at 0, all true.
 *   if not vfalse: you get inconventient window size and have to resize unless
 *   keep in mind is in .Xdefaults or ~/app-defaults, ie App*width : 200
 */
#define PAN250
#define ICCC_R2_ONLY
#ifdef ICCC_R2_ONLY
#define OK_ICCC_R (pNormalHints->icccVersion == ICCC_R2)
#else
#define OK_ICCC_R (pNormalHints->icccVersion >= ICCC_R2)
#endif

/* IGNORE
 *   these just put things back to origional state
 *   attempted to get part of WSM to compile to
 *   re-enable panning, but later found un-necessary
 *   (WSM is for cde and shouldn't be effected)
 */
#if defined(WSM) || defined(MWM_WSM) || defined(PANELIST)
              /* || defined(PANACOMM) */
#define USE_DT
#define HAVE_CONF_REQ_EV
#define REG_EMB_CLI
#endif
/* oops - always set this - it may have bee used oppositely for the test */
#ifndef HAVE_CONF_REQ_EV
#define HAVE_CONF_REQ_EV
#endif

#define ADD_PAN 1
/* #define PAN_DEBUG */

#define NO_XP

#define FIX_1127
/* purports fun(**p) XtFree *(p+1) damages p so that XtFree *p will break
   looks like total magic to me, since orig code passes *p not p it should
   if *(p+n) are addresses Xtfree knows but not *p, then called should be
   fixed - caller is f'ed up, and making *tmp=*p and to free *tmp should
   not help except possibly to leave a memory climb?  WmXSMP.c
       could be diff C lib rules means XtFree works differently? */
#define FIX_1193


#endif /* _LOCAL_DEF_H */


/* ---------------- END ------------------ */


#ifdef NEVER


/* the following are in configure, some are conditional, orig to Motif */


/* use local cpu mutex locking for Xm.  configure test to see if Xt used */
#define XTHREADS

/* libc select() default but poll() can be used (listen file/sock changes) */
#define USE_POLL

/* enable Editres to work with motif widgets */
#define X_XMU -lXmu
/* disuse X shape extention - note define in localdef.h not in configure */
#define NO_SHAPE
/* a libtool option for linux, because it has a known bug with rpath */
#define USE_LD_PRELOAD

/* no openlook compat curtail */
#define NO_OL_COMPAT

/* 
 * motif: has define to skip and src is missing so skip it
 * BulletinB.c , lib/Xm/XmMsgI.h, XmMsgCatI.h (missing)
 * note: MessageCatalog needs to be defined for Makefiles either way
 */
#define NO_MESSAGE_CATALOG


/*
 * other defaults in configure are Makefile variable defaults
 *   (there are many more in code not seen here)
 */

/* number of times to poll before blocking on a config event */
#define CONFIG_POLL_COUNT       300

/* if kernel can handles zombies, signal.h, use is less portable for unix */
#define SA_NOCLDWAIT

/*
 * see Motif documentation for, ie WSM, of course
 * not a comprehensive list of all: just some i saw not in configure
 */

/* for panner - but now a commandline option so dont use */
#define X_ONLY
/* Can't build WSM without CDE, some files needed come with CDE.
 * WSM "app workgroups" supports the desktop buttons in CDE
 */
#define WSM
/* local: in WmResParse.c if WSM and GNU, #include <signal.h>
 * local: in WmFunction.h if WSM , add missing extern F_Action
 * i dont use full WSM so cannot say if other things are also missing
 */
#define USE_LOC_DEF
/* unsure - likely adds internal Dt support to mwm */
#define MWM_WSM
/* Widget wPanelist; panel object i assume CDE relies on mwm do draw parts */
#define PANELIST
/* unsure - work w/ session manager ? or something else ? */
#define PANACOMM
/* local: allow inclusion of Dt/ headers (a MUST with WSM) */
#define USE_DT
/* local: define this if XConfigureRequestEvent is not missing */
#define HAVE_CONF_REQ_EV
/* local: a MUST panelist lines were commented out in hope of getting WM_PAN
   w/o Dt but failed.  regEmbclient is part of panelist and or wsm */
#define REG_EMB_CLI
/* include some headers even if Dt is off - a failed try to add WSM w/o Dt
   as while many things were found by adding .h, still several were not
   NOT RELATED to _LOCAL_DEF_H*/

/* some appear to be "major version hacks" because they fix something small one
   but break others who already worked around the issue */

/* use <Xm.h> not <Xm/Xm.h> in Xm/Screen.c to make Sun happy ! */
#define FIX_5943
/* input focus hack , if window doesnt want input then */
#define FIX_1350
/* see WmInitWs.c , use DefaultVisual */
#define DEFAULT_VISUAL
/* see WmMenu.c.c , also CircUpDown */
#define ADD_CIRC_CHK
/* for now is just LIBDIR v. MWMRCDIR - extraneous WmResParse.c */
#define USE_234
/* add a hack for intl concerns WmResParse.c */

/*
 * makefile variable if Editres can be used (define is HAVE_LIBXMU)
 *   OM_XMU , and LDADD ${X_XMU} == -lXmu if available
 */

#define HAVE_LIBXMU

/*
 * old X linked with apps in a way where app could not use certain std C lib
 * things because X was using them (code had to provide their own non-clashing
 * versions of)
 */
#define X_NOT_STDC_ENV

/* note to me had DrawSliderPixmap.c:1197 ret if sbw==NULL but unnecessary */

/* these only apply to building tests/ using imake, det. if SUBDIR is made:
 *   tests/uil/Manual/DtWidgets
 */
#define HAVE_LIB_DtMrm
#define HAVE_LIB_DtTerm

#endif /* NEVER */

