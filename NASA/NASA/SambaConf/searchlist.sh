#!/bin/bash
path='./NASA/SambaConf/'
#삼바 리스트 검색


# "#!@#" 문자열 행 저장
grep -n '#!@#' ${path}smb.conf > ${path}slist.tmp

# 앞에 번호만 저장
cut -d ':' -f 1 ${path}slist.tmp > ${path}slist2.tmp

#줄 개수 저장하기
numlines=`wc -l < ${path}slist2.tmp`




for ((i=1;i<=$numlines;i++));
do
	templine=`sed -n "${i}p" ${path}slist2.tmp`
	templine=`expr $templine + 3`
	#echo $templine
	sed -n "$templine s/^.\{9\}\(.*\)/\1/p" ${path}smb.conf >> ${path}smb_drive_path.tmp
	
done


#이름 추출하기

echo $numlines > ${path}config_num.tmp

for ((i=1 ; i < $numlines+1 ; i++));
do
	nameline=`sed -n ${i}p ${path}slist2.tmp`
	nameline=`expr $nameline + 1`
	sed -n ${nameline}p ${path}smb.conf >> ${path}tempshow.tmp

done


#rm slist.tmp
#rm tempshow.tmp








