#!/bin/bash
#나중에 파일 경로 수정할 것(상위 폴더인 NASA 기준으로)

netstat -i | cut -d ' ' -f 1 > ./NASA/NetworkConf/temp1.tmp  #인터페이스 목록 추출

sed -i '1,2d' ./NASA/NetworkConf/temp1.tmp   #필요없는 1,2줄 지움


lo_loc=`grep -n 'lo' ./NASA/NetworkConf/temp1.tmp | cut -d ':' -f 1`  #lo 위치 찾기

sed -i "${lo_loc}d" ./NASA/NetworkConf/temp1.tmp   # lo가 있는 행 지우기

sed -i '/^$/d' ./NASA/NetworkConf/temp1.tmp   # 빈 행 지우기

numlines=`wc -l ./NASA/NetworkConf/temp1.tmp | cut -d ' ' -f 1`   #파일 안에 있는 행 수(인터페이스 개수) 찾기

#echo $numlines #잘 되는지 확인용


for ((i=1 ; i<=numlines; i++))
do

#ens의 경우
if [ `sed -n "$i{p;q;}" ./NASA/NetworkConf/temp1.tmp | grep -q 'ens' && echo 'true' || echo 'false'` ]; then
	sed -i "${i}s|$|:ethernets|" ./NASA/NetworkConf/temp1.tmp
	
	
#enp의 경우	
elif [ `sed -n "$i{p;q;}" ./NASA/NetworkConf/temp1.tmp | grep -q 'eth' && echo 'true' || echo 'false'` ]; then
	sed -i "${i}s|$|:ethernets|" ./NASA/NetworkConf/temp1.tmp

#wlp의 경우
elif [ `sed -n "$i{p;q;}" ./NASA/NetworkConf/temp1.tmp | grep -q 'wlp' && echo 'true' || echo 'false'` ]; then
	sed -i "${i}s|$|:wifis|" ./NASA/NetworkConf/temp1.tmp


fi

done

wc -l ./NASA/NetworkConf/temp1.tmp | cut -d ' ' -f 1 >> ./NASA/NetworkConf/temp1_num.tmp


#i번째 행에서 특정 키워드 (ens, enp, wlp)를 검색함. 존재하면 :장치종류 를 추가함.
