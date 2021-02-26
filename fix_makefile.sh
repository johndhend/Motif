#!/usr/local/bin/bash
# motif250.sh imake use this - do not run it by hand

# fix Concat() space bug macro from config/cf files*

for x in Makefile ; do
cat << EOF | ed
r $x
%s/ ____ //g
wq $x
EOF
done

mv Makefile Makefile.tmp

# fix tab space bug for imake*

cat Makefile.tmp | awk '
BEGIN{RS="";FS="\n"}
{
  x=1 ; last=0
  while( $x ~ "^#" )
  { print $x ; ++x ; if( x > NF ) next }
  if( $x ~ "^ifdef[[:space:]]" || $x ~ "^if[[:space:]]" || $x ~ "^else$" || $x ~ "^endif$" ) { print $x ; ++x }
  if( $x ~ "^[^[:space:]][^=]+:" )
  {
    sub("[[:space:]]+$","",$x);
    print $x
    z=length($x)
    y=substr($x,z,1)
    if( y == "\\" )
    { last=1 }
    while( ++x <= NF )
    {
      if( last == 0 )
      {
        if( $x ~ "^ifdef[[:space:]]" || $x ~ "^if[[:space:]]" || $x ~ "^else$" || $x ~ "^endif$" ) { print $x ; ++x ; continue }
        printf "\t"
        sub("^[[:space:]]*","",$x);
      }
      else { printf "  " }
      print $x
    z=length($x)
    y=substr($x,z,1)
    if( y == "\\" )
      { last=1 } else { last=0 }
    }
    print ""
    print ""
  } else { print ; print "" ; print ""}
}
' > Makefile

rm Makefile.tmp || true
exit

# _________________
#
# * these relied on cpp macros to be exact and as it turned out
# all (available) cpp became changlings
#
# Concat() bug macro from config/cf files which relied on cpp sanity
# ... easy, but determining what was exaclty was the only bug was not
#
# It would seem impossible to fix the tab bug, but as it
# turns out the make syntax involved is easy for awk.
#   or so i'd think - one nasty detail: if "\\" is really
#   last on line (if not, absolutely dangerous to touch)
# . print any header comments in record
# . is it a make target?
# . is the last line continued \
# that's all make does as far as "tabs" is concerned
# BEGIN{ RS="\n\n" ; FS="\n" }
#  does not work on bsd and apparently OFS ORS do not follow RS FS
#
# Did break a few rules concerning \ perfection but rules were broken
# broken before release of cf, they never split a word.  It relies on
# no \ was followed by a quoted tab, But the writers of the cf knew
# not to (split a sed script on a tab, or were superstitious).
#
# If "ifdef" has erroneous whitespace preceeding the awk script ignores it
# (optionally it could absorb ^whitespace, but there should be need to)
#
#  while( $x ~ "^#" ) { ++x ; if( x > NF ) next }
#  ignore comment in make record:  could, but i refuse.  stop make, fix it.
#
# The script has to be called from inside imake to work.  Imake has a
# hack to fix but "never worked" and for different issue.
#
