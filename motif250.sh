#!/usr/local/bin/bash

  echo "Will clobber Makefiles via imake rebuild, continue?  (yes/no)"
  read X
  [ ! c"$X" = c"yes" ] && exit

  # bourne shell with "for" needed for fix-makefiles.sh and X's imake
  # build both

  # to build use make, use this if your wishing to use imake + config/cf
  # the Makefiles for default build are in mkfiles.tar.gz if you clobber
  # (the Imakefile are not, do not clobber)

  # bsd DESTDIR jail note:  imake cf does not obey BSD, it obeys
  # X11 install locationS, which are set in config/cf by X/org
  # they can be called out but not faked in: config/cf/host.def
  #   there are a plethera of macro options, try BINDIR LIBDIR
  # (cp: i'm not making cf scripts for each jail scenario thanks)

  set -e
  pwd="$PWD"

  # --------------
  # Sun Feb 21 21:54:19 EST 2021
  # a couple run-arounds for imake build
  # populate imports/, old xc/ rule, if building outside of X tree
  mkdir -p imports/x11/lib/
  cd imports/x11/lib/
  ln -s /usr/X11/lib/libX11.* . || true
  ln -s /usr/X11/lib/libXt.* . || true
  ln -s /usr/X11/lib/libXext.* . || true
  ln -s /usr/X11/lib/libXmu.* . || true
  ln -s /usr/X11/lib/libICE.* . || true
  ln -s /usr/X11/lib/libSM.* . || true
  ln -s /usr/X11/lib/libXp.* . || true
  cd "$pwd"
  # if you try re-building a demo in a subdir you'll need this
  mkdir -p imports/x11/include/X11/
  cd imports/x11/include/X11/
  ln -s /usr/local/include/X11/* . || true
  cd "$pwd"
  # the (tests) keep creating softlink "dir/" directories
  # but clean or rebuild does not delete them, and build stops
  if [ -e tests ] ; then
    cd tests/ || exit
    rm -r `find . -type d -name "dir"` || true
    cd "$pwd"
  fi
  # important: cf issues with cpp eating white space, which clang does
  cp fix_makefile.sh /tmp/
  # --------------

  EXTRA_INCLUDES="-I/usr/X11/include -I/usr/X11/include/X11 -I/usr/include -I${pwd} -I${pwd}/include"
  BOOTSTRAPCFLAGS=" -P $EXTRA_INCLUDES -DXCOMM=# -U__FreeBSD__ "
  CDEBUGFLAGS=" -O0 "
  export EXTRA_INCLUDES BOOTSTRAPCFLAGS CDEBUGFLAGS

  # this imake is required none other, build it
  echo "# making imake"
  cd config/imake/
  make -f Makefile.ini BOOTSTRAPCFLAGS="$BOOTSTRAPCFLAGS"
  cd "$pwd"
  export PATH="/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin:/root/bin:${pwd}/config/imake"

  # this delets hand made Makefiles, see makefiles.tar.gz
  echo "# making Makefiles"
  config/imake/imake -I${pwd}/config/cf

  echo "# making Motif"
  make Everything EXTRA_INCLUDES="$EXTRA_INCLUDES" CDEBUGFLAGS="$CDEBUGFLAGS"

  rm /tmp/fix_makefile.sh
