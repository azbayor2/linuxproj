#pragma once
#include <curses.h>
#include <menu.h>
#include <panel.h>
#include <stdlib.h>
#include <unistd.h>
#include <form.h>
#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])

void network_menu();  //network.c
void samba_menu();    //samba.c
void user_menu();     //user.c
void reset_all();    //reset.c

//clear()을 하게 되면 메뉴를 포함한 모든 것들이 영구적으로 사라짐. 일시적으로만 사라지게 하고 다시 띄우는 함수
void hidemenu(PANEL *panel1);    //panel.c 
void showmenu(PANEL *panel1);

