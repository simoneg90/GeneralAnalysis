#!/bin/bash -l
source ~/.bashrc
. /Users/Anacleto/root/bin/thisroot.sh
root -l $1 <<EOF
_file0->ls();
EOF
  
