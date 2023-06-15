#!/bin/bash

./NASA/SambaConf/searchlist.sh

filename="./NASA/SambaConf/slist2.tmp"
declare -i check=$(wc -l < $filename)
if [ $check -lt 1 ]; then
	echo
elif [ $check == 1 ]; then
	firstline=$(head -n 1 "$filename")
	delline=`expr $firstline - 1`
	endline=`expr $delline + 11`
       	sed -i "$delline,${endline}d" ./NASA/SambaConf/smb.conf
else
	firstline=$(head -n 1 "$filename")
	lastline=$(tail -n 1 "$filename")
	delline=`expr $firstline - 1`
	endline=`expr $lastline + 10`
	sed -i "$delline,${endline}d" ./NASA/SambaConf/smb.conf
fi

