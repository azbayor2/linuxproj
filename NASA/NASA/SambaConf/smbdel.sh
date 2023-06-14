#!/bin/bash


#samba 파일 지우기

#인자로 줄 넘겨받기


delline=`expr $1 + 1` # 첫 줄
endline=`expr $delline + 11` #마지막 줄


sed -i "$delline,${endline}d" smb.conf  #지우기


