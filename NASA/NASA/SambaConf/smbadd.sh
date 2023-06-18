#!/bin/bash

#'삼바추가' 설정 스크립트

#나중에 경로 바꾸기

#tui 구현시 smbname, drivename, drivepath 인자로 받음.



smbname=$1
drivename=$2
drivepath=$3

cp ./NASA/SambaConf/conf.dll ./NASA/SambaConf/temp_conf.tmp   #경로바꾸기

sed -i "s/input1/$smbname/g" ./NASA/SambaConf/temp_conf.tmp  #파일 안의 input1을 $smbname으로 바꿈, 나중에 경로바꾸기

sed -i "s/input2/$drivename/g" ./NASA/SambaConf/temp_conf.tmp #경로바꾸기

sed -i "s@input3@$drivepath@g" ./NASA/SambaConf/temp_conf.tmp  #경로바꾸기

cat ./NASA/SambaConf/temp_conf.tmp >> /etc/samba/smb.conf  #경로바꾸기

# temp_conf.dll
