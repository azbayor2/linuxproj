#!/bin/bash


#인자로 사용자 이름과 비밀번호 받기
user=$1
password1=$2

 
#사용자 추가
smbpasswd -a $user < <(echo -e "$password1\n$password1") > /dev/null 2>&1
