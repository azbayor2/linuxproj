#!/bin/bash

#삼바 리스트 검색


# "#!@#" 문자열 행 저장
grep -n '#!@#' smb.conf > slist.tmp

# 앞에 번호만 저장
cut -d ':' -f 1 slist.tmp > slist2.tmp

#줄 개수 저장하기
numlines=`wc -l < slist2.tmp`


#이름 추출하기
for ((i=1 ; i < $numlines+1 ; i++));
do
	nameline=`sed -n ${i}p slist2.tmp`
	nameline=`expr $nameline + 1`
	sed -n ${nameline}p smb.conf >> tempshow.tmp

done


#rm slist.tmp
#rm tempshow.tmp








