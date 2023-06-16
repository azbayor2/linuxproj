#!/bin/bash

#인자로 네트워크 인터페이스 받기
network_int=$1

cp ./NASA/NetworkConf/reset_dhcp.txt ./NASA/NetworkConf/reset_dhcp.tmp

sed -i "s/network_interface/$network_int/g" ./NASA/NetworkConf/reset_dhcp.tmp


#netplan폴더에서 config 파일 지우기
rm /etc/netplan/*.yaml

mv ./NASA/NetworkConf/reset_dhcp.tmp /etc/netplan/01-netplan.yaml

netplan apply


