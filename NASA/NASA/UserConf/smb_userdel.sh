#!/bin/bash

#인자로 사용자 이름 받기

user=$1

smbpasswd -x $user > /dev/null 2>&1
