#include "main.h"

char *samba_choices[] = {"Add SAMBA", "Edit SAMBA", "Delete SAMBA", "SAMBA User Settings", "Return"};

PANEL *panel5;
PANEL *panel6;


void smbadd();
void smbedit();
void smbdel();

void samba_menu()
{
	clear();
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
		system("./NASA/SambaConf/cleartmp.sh > /dev/null 2>&1");
		char* key = keyname(input);
		if(input == KEY_DOWN)
		{	
			menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(smb_win);
		}
		else if (key[0] == '^' && key[1] == 'E') {
          		endwin();
			exit(0);
		}

		
		else if(input == KEY_UP)
		{
			menu_driver(menu, REQ_UP_ITEM);
			wrefresh(smb_win);
		}
		
		else if(input == KEY_F(5)||input == KEY_LEFT)
		{
			clear();
			refresh();
			break;
		}
		else if(input == KEY_F(7))
		{
			reset_all();
		}
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
	
	clear();
	char config_name[100];
	char config_desc[100];
	char d_path[100];
	
	int drive_num=0;
	
	system("./NASA/SambaConf/listdrive.sh");
	
	FILE *file1 = fopen("./NASA/SambaConf/num_drive.tmp", "r");    //드라이브 개수 가져오기

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
	
	
	FILE *file2 = fopen("./NASA/SambaConf/drive_name.tmp","r");   //드라이브 이름 가져오기
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
	
	
	FILE *file3 = fopen("./NASA/SambaConf/drive_cap.tmp","r");    //드라이브 용량 가져오기
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
	
	
	FILE *file4 = fopen("./NASA/SambaConf/mntpoint.tmp","r");    //드라이브 위치 가져오기
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
		char* key = keyname(input);
		if(input == KEY_F(5)||input == KEY_LEFT)    //F5 누르면 나감
		{
			clear();
			refresh();
			return;
		}
		else if (key[0] == '^' && key[1] == 'E') {
          		endwin();
			exit(0);
		}
	
		else if(input == KEY_F(7))
		{
			reset_all();
		}
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
        
	
	
	
	
	cbreak();
	noecho();
	
	///////////////////////////////////////////////////////////////////
	
	FIELD *test[2];
	FORM *form;

	test[0] = new_field(1,38,0,0,0,0);
	test[1] = NULL;

	//set_field_buffer(test[0], 0, editing[0]);
	//field_opts_on(test[0], O_EDIT);
	//field_opts_on(test[0], O_VISIBLE);
	field_opts_off(test[0], O_STATIC);
	set_field_just(test[0], JUSTIFY_LEFT);

	form = new_form(test);

	WINDOW *win = newwin(5,40,4,0);
	WINDOW *win_name = newwin(2,40,0,1);
	wprintw(win_name, "Please enter your Network Drive's name");
	wrefresh(win_name);
	keypad(win, true);
	set_form_win(form, win);
	set_form_sub(form, derwin(win, 1,38,2,1));
	box(win,0,0);

	post_form(form);

	wrefresh(win);

	form_driver(form, REQ_END_LINE);
	//form_driver(form, REQ_INS_MODE);


	int ch;

	while((ch=wgetch(win)) != '\n')
	{

		char* key = keyname(ch);
		
		if(ch==KEY_LEFT)
			form_driver(form,REQ_LEFT_CHAR);
			
		else if(ch==KEY_RIGHT)
			form_driver(form, REQ_RIGHT_CHAR);
			
		else if(ch==KEY_BACKSPACE)
			form_driver(form, REQ_DEL_PREV);
			
		else if (key[0] == '^' && key[1] == 'E') 
		{
          		endwin();
			exit(0);
		}
		
		else if(ch == KEY_F(5))
		{
			clear();
			refresh();
			return;
		}
			
		else
			form_driver(form, ch);
			
	

		wrefresh(win);


	}

	form_driver(form, REQ_VALIDATION);
	
	strcpy(config_name, field_buffer(test[0],0));

	int config_name_ind = strlen(config_name) -1;
	
	while(config_name_ind>= 0 && isspace(config_name[config_name_ind]))
	{
		config_name[config_name_ind] = '\0';
		config_name_ind--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);
	delwin(win);
	
	

	clear();	/////////////////////////
	
	
	test[0] = new_field(1, 38, 0,0,0,0);
	//set_field_buffer(test[0], 0, editing[1]);
	form = new_form(test);
	wclear(win_name);
	
	
	
	wprintw(win_name, "Please enter your Network Drive's description");
	wrefresh(win_name);
	
	win = newwin(5,40,4,0);
	keypad(win, true);
	set_form_win(form, win);
	set_form_sub(form, derwin(win, 1,38,2,1));
	box(win,0,0);
	
	post_form(form);

	wrefresh(win);

	form_driver(form, REQ_END_LINE);
	//form_driver(form, REQ_INS_MODE);


	

	while((ch=wgetch(win)) != '\n')
	{

		char* key = keyname(ch);
		
		if(ch==KEY_LEFT)
			form_driver(form,REQ_LEFT_CHAR);
			
		else if(ch==KEY_RIGHT)
			form_driver(form, REQ_RIGHT_CHAR);
			
		else if(ch==KEY_BACKSPACE)
			form_driver(form, REQ_DEL_PREV);
			
		else if (key[0] == '^' && key[1] == 'E') 
		{
          		endwin();
			exit(0);
		}
		
		else if(ch == KEY_F(5))
		{
			clear();
			refresh();
			return;
		}
			
		else
			form_driver(form, ch);
			
	

		wrefresh(win);


	}

	form_driver(form, REQ_VALIDATION);
	
	strcpy(config_desc, field_buffer(test[0],0));
	
	int config_desc_ind = strlen(config_desc) -1;
	
	while(config_desc_ind>= 0 && isspace(config_desc[config_desc_ind]))
	{
		config_desc[config_desc_ind] = '\0';
		config_desc_ind--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);
	delwin(win);
	delwin(win_name);
	
	
	
	
	clear();
	refresh();
	
	/*
	
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
	
	
	*/
	
	char command[200];
	
	sprintf(command, "./NASA/SambaConf/smbadd.sh \"%s\" \"%s\" \"%s\"",config_name, config_desc, d_path);
	system(command);
	
	printw("Done! Press any key to continue");
	getch();
	
	
	
	
	
	clear();
	system("./NASA/SambaConf/cleartmp.sh > /dev/null 2>&1");
	
	
	
	return;	

}


void smbedit()  //삼바 수정
{
	clear();
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
		printw("No config found! Press any key to exit");
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
	
	
	FILE *file4 = fopen("./NASA/SambaConf/smb_drive_path.tmp","r");   //드라이브 경로 가져오기
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
	
	char *drive_path[config_num];
	char temp2[100];
	
	for(int i = 0; i<config_num; i++)
	{
		fgets(temp2, sizeof(temp2), file4);
		
		if(strlen(temp2)>0 && temp2[strlen(temp2)-1] == '\n')
			temp2[strlen(temp2)-1] = '\0';
		drive_path[i] = (char*)malloc(strlen(temp2)*sizeof(char));
		strcpy(drive_path[i], temp2);
	
	}
	
	fclose(file4);
	
	
	
	
	
	
	ITEM **items;    //아이템 저장소
	MENU *menu;   //메뉴 생성


	int main_choices_n = ARR_SIZE(config_line); 
	items = (ITEM**)calloc(main_choices_n + 1, sizeof(ITEM*));   //아이템 저장공간 동적할당

	for(int i =0; i<main_choices_n; i++)  //미리 저장한 메뉴 옵션들을 아이템으로 옮김
	{
		items[i] = new_item(config_name[i], drive_path[i]);
	}

	items[main_choices_n] = NULL;
	
	menu = new_menu((ITEM**)items);  //메뉴에 아이템 연동
	
	WINDOW *menu_win = newwin(10,40,4,0);   //메뉴가 들어갈 하위 윈도우(박스) 만들기


	WINDOW *main_name = newwin(3,40,0,1);  //메뉴의 이름이 들어갈 박스 만들기
	wprintw(main_name, "Please Select the config name to edit\n");
	wprintw(main_name, "Press F5 to exit");
	wrefresh(main_name);
	
	keypad(menu_win, true);
	set_menu_win(menu, menu_win);
	set_menu_sub(menu, derwin(menu_win, 6, 38, 2,1));  //메뉴 설정(윗줄이 왜 필요한지 모르겠음)
	box(menu_win, 0,0);
	
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	post_menu(menu);
	wrefresh(menu_win);


	
	int input;
	int sel_line_num;
	char previous_drive_path[200];
	

	while(input = wgetch(menu_win))
	{	char* key = keyname(input);
		if(input == KEY_F(5)||input == KEY_LEFT)    //F5 누르면 나감
		{
			clear();
			refresh();
			return;
		}
		
		else if (key[0] == '^' && key[1] == 'E') {
          		endwin();
			exit(0);
		}

		else if(input == KEY_F(7))
		{
			reset_all();
		}
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
			strcpy(previous_drive_path, drive_path[selected_loc]);
			
			
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
	
	
	char command1[200];
	
	sprintf(command1, "./NASA/SambaConf/getedit.sh \"%d\"", sel_line_num);
	system(command1);
	
	FILE *file5 = fopen("./NASA/SambaConf/needsedit.tmp","r");   //드라이브 경로 가져오기
	if (file5 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	char *editing[2];
	char temp3[100];
	
	for(int i = 0; i<2; i++)
	{
		fgets(temp3, sizeof(temp3), file5);
		
		if(strlen(temp3)>0 && temp3[strlen(temp3)-1] == '\n')
			temp3[strlen(temp3)-1] = '\0';
		editing[i] = (char*)malloc(strlen(temp3)*sizeof(char));
		strcpy(editing[i], temp3);
	
	}
	
	fclose(file5);
	
	/////////////////////////////////////////
	
	
	
	refresh();
	clear();
	
	cbreak();
	noecho();
	
	char new_name[200];
	char new_comment[200];
	
	
	
	FIELD *test[2];
	FORM *form;

	test[0] = new_field(1,38,0,0,0,0);
	test[1] = NULL;

	set_field_buffer(test[0], 0, editing[0]);
	//field_opts_on(test[0], O_EDIT);
	//field_opts_on(test[0], O_VISIBLE);
	field_opts_off(test[0], O_STATIC);
	set_field_just(test[0], JUSTIFY_LEFT);

	form = new_form(test);

	WINDOW *win = newwin(5,40,4,0);
	WINDOW *win_name = newwin(2,40,0,1);
	wprintw(win_name, "Please enter the new name");
	wrefresh(win_name);
	keypad(win, true);
	set_form_win(form, win);
	set_form_sub(form, derwin(win, 1,38,2,1));
	box(win,0,0);

	post_form(form);

	wrefresh(win);

	form_driver(form, REQ_END_LINE);
	//form_driver(form, REQ_INS_MODE);


	int ch;

	while((ch=wgetch(win)) != '\n')
	{

		char* key = keyname(ch);
		
		if(ch==KEY_LEFT)
			form_driver(form,REQ_LEFT_CHAR);
			
		else if(ch==KEY_RIGHT)
			form_driver(form, REQ_RIGHT_CHAR);
			
		else if(ch==KEY_BACKSPACE)
			form_driver(form, REQ_DEL_PREV);
			
		else if (key[0] == '^' && key[1] == 'E') 
		{
          		endwin();
			exit(0);
		}
		
		else if(ch == KEY_F(5))
		{
			clear();
			refresh();
			return;
		}
			
		else
			form_driver(form, ch);
			
	

		wrefresh(win);


	}

	form_driver(form, REQ_VALIDATION);
	
	strcpy(new_name, field_buffer(test[0],0));

	int new_name_ind = strlen(new_name) -1;
	
	while(new_name_ind>= 0 && isspace(new_name[new_name_ind]))
	{
		new_name[new_name_ind] = '\0';
		new_name_ind--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);
	delwin(win);
	
	

	clear();	/////////////////////////
	
	
	test[0] = new_field(1, 38, 0,0,0,0);
	set_field_buffer(test[0], 0, editing[1]);
	form = new_form(test);
	wclear(win_name);
	
	
	
	wprintw(win_name, "Please enter the new comment");
	wrefresh(win_name);
	
	win = newwin(5,40,4,0);
	keypad(win, true);
	set_form_win(form, win);
	set_form_sub(form, derwin(win, 1,38,2,1));
	box(win,0,0);
	
	post_form(form);

	wrefresh(win);

	form_driver(form, REQ_END_LINE);
	//form_driver(form, REQ_INS_MODE);


	

	while((ch=wgetch(win)) != '\n')
	{

		char* key = keyname(ch);
		
		if(ch==KEY_LEFT)
			form_driver(form,REQ_LEFT_CHAR);
			
		else if(ch==KEY_RIGHT)
			form_driver(form, REQ_RIGHT_CHAR);
			
		else if(ch==KEY_BACKSPACE)
			form_driver(form, REQ_DEL_PREV);
			
		else if (key[0] == '^' && key[1] == 'E') 
		{
          		endwin();
			exit(0);
		}
		
		else if(ch == KEY_F(5))
		{
			clear();
			refresh();
			return;
		}
			
		else
			form_driver(form, ch);
			
	

		wrefresh(win);


	}

	form_driver(form, REQ_VALIDATION);
	
	strcpy(new_comment, field_buffer(test[0],0));
	
	int new_comment_ind = strlen(new_comment) -1;
	
	while(new_comment_ind>= 0 && isspace(new_comment[new_comment_ind]))
	{
		new_comment[new_comment_ind] = '\0';
		new_comment_ind--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);
	delwin(win);
	delwin(win_name);
	
	
	
	
	clear();
	refresh();
	
	
	char command2[200];
	
	sprintf(command2, "./NASA/SambaConf/smbdel.sh \"%d\"", sel_line_num);
	system(command2);
	
	char command3[200];
	
	sprintf(command3, "./NASA/SambaConf/smbadd.sh \"%s\" \"%s\" \"%s\"", new_name, new_comment, 		previous_drive_path);
	system(command3);
	
	system("./NASA/SambaConf/cleartmp.sh > /dev/null 2>&1");
	clear();
	
	printw("Done! Press any key to continue");
	getch();
	
	clear();
	cbreak();
	noecho();
	
	
	return;

}

void smbdel() //삼바 삭제
{
	clear();
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
		printw("No configs found! Press any key to exit");
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
	if (file3 == NULL)
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
		char* key = keyname(input);
		if(input == KEY_F(5)||input == KEY_LEFT)    //F5 누르면 나감
		{
			clear();
			refresh();
			return;
		}
		else if (key[0] == '^' && key[1] == 'E') {
          		endwin();
			exit(0);
		}
	
		else if(input == KEY_F(7))
		{
			reset_all();
		}
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
	system("./NASA/SambaConf/cleartmp.sh > /dev/null 2>&1");
	getch();
	
	
	
	
	
	clear();
	

	return;
}
