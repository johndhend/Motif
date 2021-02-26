#!/usr/local/bin/bash

for x in `find . -type f -name "Makefile"`
do

cat << EOF | ed
r $x
%s/^\^//
w $x
q
EOF
done

