#include "main.h"

char *samba_choices[] = {"Add SAMBA", "Edit SAMBA", "Delete SAMBA", "SAMBA User Settings", "Return"};

PANEL *panel5;
PANEL *panel6;


void smbadd();
void smbedit();
void smbdel();

void samba_menu()
{

	ITEM **items;
	MENU *menu;
	
	int choices_num = 5;
	items = (ITEM**)calloc(choices_num +1, sizeof(ITEM*));
	
	for(int i = 0; i< choices_num; i++)
		items[i] = new_item(samba_choices[i], NULL);
	
	items[choices_num] = NULL;
	
	menu = new_menu((ITEM**)items);
	
	WINDOW *smb_win = newwin(10,30,4,0);
	WINDOW *smb_name = newwin(3,30,0,1);
	wprintw(smb_name, "Samba Menu");
	wrefresh(smb_name);
	
	keypad(smb_win, true);
	set_menu_win(menu, smb_win);
	set_menu_sub(menu, derwin(smb_win, 6, 28, 2, 1));
	box(smb_win, 0,0);
	
	post_menu(menu);
	wrefresh(smb_win);
	
	panel5 = new_panel(smb_name);
	panel6 = new_panel(smb_win);

	int input;
	
	while(input = wgetch(smb_win))
	{
		if(input == KEY_DOWN)
		{	
			menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(smb_win);
		}
		
		else if(input == KEY_UP)
		{
			menu_driver(menu, REQ_UP_ITEM);
			wrefresh(smb_win);
		}
		
		else if(input == KEY_F(5)||input == KEY_LEFT)
			break;

		else if(input == 10||input == KEY_RIGHT)
		{
			ITEM * selected = current_item(menu);

			if(selected == items[0])
			{
				hidemenu(panel5);
				hidemenu(panel6);

				smbadd();

				showmenu(panel5);
				showmenu(panel6);

				wrefresh(smb_win);

				continue;
					
			}

			else if(selected == items[1])
			{
				
				hidemenu(panel5);
                                hidemenu(panel6);

                                smbedit();

                                showmenu(panel5);
                                showmenu(panel6);

                                wrefresh(smb_win);

                                continue;

			}

			else if(selected == items[2])
                        {

                                hidemenu(panel5);
                                hidemenu(panel6);

                                smbdel();

                                showmenu(panel5);
                                showmenu(panel6);

                                wrefresh(smb_win);

                                continue;

                        }
			
			else if(selected == items[3])
			{

				 hidemenu(panel5);
                                hidemenu(panel6);

                                user_menu();

                                showmenu(panel5);
                                showmenu(panel6);

                                wrefresh(smb_win);

                                continue;

			}

			else if(selected == items[4])
			{
				break;

			}

		}
	
		else
		{
			wrefresh(smb_win);
			continue;
		}
	}
	
	for(int i = 0; i<5; i++)
		free_item(items[i]);
		
	free_menu(menu);
	return;

}


void smbadd() // 삼바 추가
{
	
	char config_name[100];
	char config_desc[100];
	char d_path[100];
	
	int drive_num=0;
	
	system("./NASA/SambaConf/listdrive.sh");
	
	FILE *file1 = fopen("./NASA/SambaConf/num_drive.txt", "r");    //드라이브 개수 가져오기

	if (file1 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	if(!fscanf(file1, "%d", &drive_num))
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	
	if(drive_num == 0)
	{
		printw("No drives found! Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	fclose(file1);
	
	
	FILE *file2 = fopen("./NASA/SambaConf/drive_name.txt","r");   //드라이브 이름 가져오기
	if (file2 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	char *drive_name[drive_num];
	char temp1[100];
	
	for(int i = 0; i<drive_num; i++)
	{
		fgets(temp1, sizeof(temp1), file2);
		
		if(strlen(temp1)>0 && temp1[strlen(temp1)-1] == '\n')
			temp1[strlen(temp1)-1] = '\0';
		drive_name[i] = (char*)malloc(strlen(temp1)*sizeof(char));
		strcpy(drive_name[i], temp1);
	
	}
	
	fclose(file2);
	
	
	FILE *file3 = fopen("./NASA/SambaConf/drive_cap.txt","r");    //드라이브 용량 가져오기
	if (file3 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	char *drive_cap[drive_num];
	char temp2[100];
	
	for(int i = 0; i<drive_num; i++)
	{
		fgets(temp2, sizeof(temp2), file3);
		
		if(strlen(temp2)>0 && temp2[strlen(temp2)-1] == '\n')
			temp2[strlen(temp2)-1] = '\0';
		drive_cap[i] = (char*)malloc(strlen(temp2)*sizeof(char));
		strcpy(drive_cap[i], temp2);
	
	}
	

	fclose(file3);
	
	
	FILE *file4 = fopen("./NASA/SambaConf/mntpoint.txt","r");    //드라이브 위치 가져오기
	if (file4 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	char *drive_loc[drive_num];
	char temp3[1000];
	
	for(int i = 0; i<drive_num; i++)
	{
		fgets(temp3, sizeof(temp3), file4);
		
		if(strlen(temp3)>0 && temp3[strlen(temp3)-1] == '\n')
			temp3[strlen(temp3)-1] = '\0';
		drive_loc[i] = (char*)malloc(strlen(temp3)*sizeof(char));
		strcpy(drive_loc[i], temp3);
	
	}
	
	fclose(file4);
	
	
	
	ITEM **items;    //아이템 저장소
	MENU *menu;   //메뉴 생성


	int main_choices_n = ARR_SIZE(drive_name); 
	items = (ITEM**)calloc(main_choices_n + 1, sizeof(ITEM*));   //아이템 저장공간 동적할당

	for(int i =0; i<main_choices_n; i++)  //미리 저장한 메뉴 옵션들을 아이템으로 옮김
	{
		items[i] = new_item(drive_name[i], drive_cap[i]);
	}

	items[main_choices_n] = NULL;
	
	menu = new_menu((ITEM**)items);  //메뉴에 아이템 연동
	

	WINDOW *menu_win = newwin(10,30,4,0);   //메뉴가 들어갈 하위 윈도우(박스) 만들기


	WINDOW *main_name = newwin(3,30,0,1);  //메뉴의 이름이 들어갈 박스 만들기
	wprintw(main_name, "Please Select your drive\n");
	wprintw(main_name, "Press F5 to exit");
	wrefresh(main_name);
	
	keypad(menu_win, true);
	set_menu_win(menu, menu_win);
	set_menu_sub(menu, derwin(menu_win, 6, 28, 2,1));  //메뉴 설정(윗줄이 왜 필요한지 모르겠음)
	box(menu_win, 0,0);
	
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	post_menu(menu);
	wrefresh(menu_win);


	
	int input;
	
	

	while(input = wgetch(menu_win))
	{
		if(input == KEY_F(5)||input == KEY_LEFT)    //F5 누르면 나감
			return;

		else if(input == KEY_DOWN)     //아랫방향
		{	menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(menu_win);
		}
		else if(input == KEY_UP)    //윗방향          
		{	menu_driver(menu, REQ_UP_ITEM);
			wrefresh(menu_win);
		}

		else if(input == 10||input == KEY_RIGHT) //엔터
		{
			int selected_loc = item_index(current_item(menu));
			strcpy(d_path, drive_loc[selected_loc]);
			
			
			break;
		        
			
		}
		
		else
		{
			wrefresh(menu_win);
			continue;
		}
	}

	free_item(items[0]);
	free_item(items[1]);
	free_menu(menu);
	clear();
	refresh();
        
	
	
	
	
	nocbreak();
	echo();
	
	printw("Please enter your Network Drive's name\n>>");
	getstr(config_name);
	refresh();
	
	clear();
	printw("Please enter your Network Drive's description\n>>");
	getstr(config_desc);
	refresh();
	
	clear();
	refresh();
	
	cbreak();
	noecho();
	
	char command[200];
	
	sprintf(command, "./NASA/SambaConf/smbadd.sh \"%s\" \"%s\" \"%s\"",config_name, config_desc, d_path);
	system(command);
	
	printw("Done! Press any key to continue");
	getch();
	
	
	
	
	
	clear();
	
	
	
	return;	

}


void smbedit()  //삼바 수정
{
	
	int config_num = 0;
	
	system("./NASA/SambaConf/searchlist.sh");
	
	FILE *file1 = fopen("./NASA/SambaConf/config_num.tmp", "r");    //드라이브 개수 가져오기

	if (file1 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	if(!fscanf(file1, "%d", &config_num))
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	
	if(config_num == 0)
	{
		printw("No drives found! Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	fclose(file1);
	
	
	
	FILE *file2 = fopen("./NASA/SambaConf/tempshow.tmp","r");   //설정 이름 가져오기
	if (file2 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	char *config_name[config_num];
	char temp1[100];
	
	for(int i = 0; i<config_num; i++)
	{
		fgets(temp1, sizeof(temp1), file2);
		
		if(strlen(temp1)>0 && temp1[strlen(temp1)-1] == '\n')
			temp1[strlen(temp1)-1] = '\0';
		config_name[i] = (char*)malloc(strlen(temp1)*sizeof(char));
		strcpy(config_name[i], temp1);
	
	}
	
	fclose(file2);
	
	
	
	
	FILE *file3 = fopen("./NASA/SambaConf/slist2.tmp","r");   //설정 위치 가져오기
	if (file2 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	int config_line[config_num];
	int temp_conf_line = 0;
	
	for(int i = 0; i<config_num; i++)
	{
		fscanf(file3, "%d", &config_line[i]);
	
	}
	
	fclose(file3);
	
	
	
	
	
	
	ITEM **items;    //아이템 저장소
	MENU *menu;   //메뉴 생성


	int main_choices_n = ARR_SIZE(config_line); 
	items = (ITEM**)calloc(main_choices_n + 1, sizeof(ITEM*));   //아이템 저장공간 동적할당

	for(int i =0; i<main_choices_n; i++)  //미리 저장한 메뉴 옵션들을 아이템으로 옮김
	{
		items[i] = new_item(config_name[i], NULL);
	}

	items[main_choices_n] = NULL;
	
	menu = new_menu((ITEM**)items);  //메뉴에 아이템 연동
	
	WINDOW *menu_win = newwin(10,30,4,0);   //메뉴가 들어갈 하위 윈도우(박스) 만들기


	WINDOW *main_name = newwin(3,30,0,1);  //메뉴의 이름이 들어갈 박스 만들기
	wprintw(main_name, "Please Select the config name to edit\n");
	wprintw(main_name, "Press F5 to exit");
	wrefresh(main_name);
	
	keypad(menu_win, true);
	set_menu_win(menu, menu_win);
	set_menu_sub(menu, derwin(menu_win, 6, 28, 2,1));  //메뉴 설정(윗줄이 왜 필요한지 모르겠음)
	box(menu_win, 0,0);
	
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	post_menu(menu);
	wrefresh(menu_win);


	
	int input;
	int sel_line_num;
	
	

	while(input = wgetch(menu_win))
	{
		if(input == KEY_F(5)||input == KEY_LEFT)    //F5 누르면 나감
			return;

		else if(input == KEY_DOWN)     //아랫방향
		{	menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(menu_win);
		}
		else if(input == KEY_UP)    //윗방향          
		{	menu_driver(menu, REQ_UP_ITEM);
			wrefresh(menu_win);
		}

		else if(input == 10||input == KEY_RIGHT) //엔터
		{
			int selected_loc = item_index(current_item(menu));
			sel_line_num=config_line[selected_loc];
			
			
			break;
		        
			
		}
		
		else
		{
			wrefresh(menu_win);
			continue;
		}
	}
	
	

	free_item(items[0]);
	free_item(items[1]);
	free_menu(menu);
	clear();
	refresh();
	
	
	refresh();
	getch();
	clear();
	
	
	
	
	return;

}

void smbdel() //삼바 삭제
{
	int config_num = 0;
	
	system("./NASA/SambaConf/searchlist.sh");
	
	FILE *file1 = fopen("./NASA/SambaConf/config_num.tmp", "r");    //드라이브 개수 가져오기

	if (file1 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	if(!fscanf(file1, "%d", &config_num))
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	
	if(config_num == 0)
	{
		printw("No drives found! Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	fclose(file1);
	
	
	
	FILE *file2 = fopen("./NASA/SambaConf/tempshow.tmp","r");   //설정 이름 가져오기
	if (file2 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	char *config_name[config_num];
	char temp1[100];
	
	for(int i = 0; i<config_num; i++)
	{
		fgets(temp1, sizeof(temp1), file2);
		
		if(strlen(temp1)>0 && temp1[strlen(temp1)-1] == '\n')
			temp1[strlen(temp1)-1] = '\0';
		config_name[i] = (char*)malloc(strlen(temp1)*sizeof(char));
		strcpy(config_name[i], temp1);
	
	}
	
	fclose(file2);
	
	FILE *file3 = fopen("./NASA/SambaConf/slist2.tmp","r");   //설정 위치 가져오기
	if (file2 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	int config_line[config_num];
	int temp_conf_line = 0;
	
	for(int i = 0; i<config_num; i++)
	{
		fscanf(file3, "%d", &config_line[i]);
	
	}
	
	fclose(file3);
//개수에 따른 메뉴 제공
	ITEM **items;    //아이템 저장소
	MENU *menu;   //메뉴 생성


	int main_choices_n = ARR_SIZE(config_name); 
	items = (ITEM**)calloc(main_choices_n + 1, sizeof(ITEM*));   //아이템 저장공간 동적할당

	for(int i =0; i<main_choices_n; i++)  //미리 저장한 메뉴 옵션들을 아이템으로 옮김
	{
		items[i] = new_item(config_name[i], NULL);
	}

	items[main_choices_n] = NULL;
	
	menu = new_menu((ITEM**)items);  //메뉴에 아이템 연동
	
	WINDOW *menu_win = newwin(10,30,4,0);   //메뉴가 들어갈 하위 윈도우(박스) 만들기


	WINDOW *main_name = newwin(3,30,0,1);  //메뉴의 이름이 들어갈 박스 만들기
	wprintw(main_name, "Please Select the config name to delete\n");
	wprintw(main_name, "Press F5 to exit");
	wrefresh(main_name);
	
	keypad(menu_win, true);
	set_menu_win(menu, menu_win);
	set_menu_sub(menu, derwin(menu_win, 6, 28, 2,1));  //메뉴 설정(윗줄이 왜 필요한지 모르겠음)
	box(menu_win, 0,0);
	
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	post_menu(menu);
	wrefresh(menu_win);


	
	int input;
	int sel_line_num;
	
	

	while(input = wgetch(menu_win))
	{
		if(input == KEY_F(5)||input == KEY_LEFT)    //F5 누르면 나감
			return;

		else if(input == KEY_DOWN)     //아랫방향
		{	menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(menu_win);
		}
		else if(input == KEY_UP)    //윗방향          
		{	menu_driver(menu, REQ_UP_ITEM);
			wrefresh(menu_win);
		}

		else if(input == 10||input == KEY_RIGHT) //엔터
		{
			int selected_loc = item_index(current_item(menu));
			sel_line_num=config_line[selected_loc];
			
			
			break;
		        
			
		}
		
		else
		{
			wrefresh(menu_win);
			continue;
		}
	}
	
	
	free_item(items[0]);
	free_item(items[1]);
	free_menu(menu);
	clear();
	refresh();
//선택받은 인자 반환
	char command[200];
	
	sprintf(command, "./NASA/SambaConf/smbdel.sh \"%d\"",sel_line_num);
	system(command);
	
	
	free_item(items[0]);
	free_item(items[1]);
	free_menu(menu);
	clear();
	refresh();
        
	cbreak();
	noecho();
	
	printw("Done! Press any key to continue");
	getch();
	
	
	
	
	
	clear();
	

	return;
}
