#!/bin/bash
path='./NASA/UserConf/'

pdbedit -L > ${path}smbuser.tmp

cut -d ':' -f 1 ${path}smbuser.tmp>${path}smbuser2.tmp 

numlines=`wc -l < ${path}smbuser2.tmp`

echo $numlines > ${path}user_num.tmp
