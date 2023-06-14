#!/bin/bash

#인자로 프로파일 이름, 드라이브 이름, 드라이브 경로를 받아서 
#수정함.
#수정할 부분을 지우고 다시 추가하는 방식
#smbdel.sh 참고


delline=$1
profilename=$2
drivename=$3
drivepath=$4 #드라이브 경로에는 '/'가 있으므로 대입할 때 주의!


bash smbdel.sh $delline  #지우기

bash smbadd.sh $profilename $drivename $drivepath # 추가하기


#끝


