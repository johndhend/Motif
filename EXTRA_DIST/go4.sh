#!/usr/local/bin/bash

pwd="$PWD"

for x in `find . -type f -name "*.c"`
do
cat << EOF | ed
r $x
%s/unsigned int	argc/int argc/g
w $x
q
EOF
done

