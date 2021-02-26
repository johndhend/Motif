#!/usr/local/bin/sh

# PROJ_DIR [start|stop]

# Let  PROJ_DIR=  be physically in and out of all Makefiles, start/stop
# with invoking PWD as the right value.

# DESCRIPTION
#   PROJ_DIR is a two edged sword, if it's inherited then porting is easier
# but that makes developing individual packages a pain.  Try to solve that
# with cmdline options it's ' un-reliable' and try to force ENVIRONMENT to
# contain DIR - it's unreliable and installers will "miss it".  Whew!
# (note depend builds are never to be trusted anyway - are dangerous)

# do this in TOP

pwd="$PWD"

case "$1" in

start)

for x in `find . -type d -name "Makefile"`
do
  cd "$x"
cat << EOF | ed
r Makefile
/^#/
.a
PROJ_DIR="$pwd"
PREFIX=/usr/local
LOCALBASE=/usr/local
.
w Makefile
q
EOF
  cd "$pwd"
done
;;
# avoid .a before specifying a line number. used /^#/ to get a line no.
# (using line 0 takes more practice, requires insert, using .a easier)

stop)
for x in `find . -type d -name "Makefile"`
do
  cd "$x"
cat << EOF | ed
r Makefile
/^PROJ_DIR=/
.,.+2d
w Makefile
q
EOF
  cd "$pwd"
done
;;

*)
  echo "PROJ_DIR [start|stop] - please read DESCRIPTION in script"
;;

esac

