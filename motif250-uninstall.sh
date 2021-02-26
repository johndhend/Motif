#!/usr/local/bin/bash

  set -e

  # note this works only if you didn't change config/cf to
  # alter install locations

  echo "Will un-install Motif files from OS, continue?  (yes/no)"
  read X
  [ ! c"$X" = c"yes" ] && exit

  [ -f install-destinations ] || exit

  [ -f install-destinations.man ] || exit

  rm `cat install-destinations`

  rm `cat install-destinations.man`

