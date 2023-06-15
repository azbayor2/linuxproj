selected_line=$1
beginline=`expr $selected_line - 1`
endline=`expr $selected_line + 10`
path="./NASA/SambaConf/"

sed -n "$beginline,${endline}p" ${path}smb.conf > ${path}copiedfile.tmp

rm needsedit.tmp > /dev/null 2>&1


sed -n '3 s/\[\([^]]*\)\]/\1/p' ${path}copiedfile.tmp >> ${path}needsedit.tmp
sed -n '4 s/^.\{12\}\(.*\)/\1/p' ${path}copiedfile.tmp >> ${path}needsedit.tmp
#sed -n '5 s/^.\{9\}\(.*\)/\1/p' copiedfile.tmp >> needsedit.tmp
