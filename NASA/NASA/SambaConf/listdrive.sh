#!/bin/bash

#드라이브 목록 보이기
#나중에 경로 바꾸기

lsblk -o size,mountpoint | grep /media > ./NASA/SambaConf/dlist1.txt


#cat -b ./NASA/SambaConf/dlist1.tmp > ./NASA/SambaConf/dlist2.txt   #드라이브 목록에 행 번호를 더함. 출력 용도.

cut -d ' ' -f 4 ./NASA/SambaConf/dlist1.txt > ./NASA/SambaConf/mntpoint.txt  #드라이브의 경로가 저장됨
cut -d ' ' -f 3 ./NASA/SambaConf/dlist1.txt > ./NASA/SambaConf/drive_cap.txt
cut -d '/' -f 4 ./NASA/SambaConf/dlist1.txt > ./NASA/SambaConf/drive_name.txt


wc -l ./NASA/SambaConf/dlist1.txt | cut -d ' ' -f 1 > ./NASA/SambaConf/num_drive.txt

#smbadd 과정이 끝나면 tmp 파일 지우기


