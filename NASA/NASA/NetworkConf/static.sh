#!/bin/bash
#경로를 상위 폴더인 NASA 기준으로 수정


cp ./NASA/NetworkConf/network.txt ./NASA/NetworkConf/01-network.tmp #edit

#변수 대입하기
input_name_of_interface=`echo $1 | cut -d ':' -f 1`
input_intf_type=`echo $1 | cut -d ':' -f 2`
input_ip_addresses=$2
input_DNS1=$3
input_DNS2=$4


 

sed -i "s/intf_type/${input_intf_type}/g" ./NASA/NetworkConf/01-network.tmp

sed -i "s/name_of_interface/${input_name_of_interface}/g" ./NASA/NetworkConf/01-network.tmp

sed -i "s|ip_addresses|${input_ip_addresses}|g" ./NASA/NetworkConf/01-network.tmp

sed -i "s/DNS1/${input_DNS1}/g" ./NASA/NetworkConf/01-network.tmp

sed -i "s/DNS2/$input_DNS2/g" ./NASA/NetworkConf/01-network.tmp

mkdir /etc/netplan/pro_backup/ > /dev/null 2>&1

mv /etc/netplan/*.yaml /etc/netplan/pro_backup/* > /dev/null 2>&1 #backup
mv ./NASA/NetworkConf/01-network.tmp /etc/netplan/01-network.yaml > /dev/null 2>&1 #substitute

sudo netplan apply > /dev/null 2>&1 > ./NASA/NetworkConf/error.tmp
