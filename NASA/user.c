#include "main.h"

char *user_choices[] = {"Add User", "Delete User", "Return"};

PANEL *panel7;
PANEL *panel8;


void adduser();
void deluser();

void user_menu()
{

	ITEM **items;
	MENU *menu;
	
	int choices_num = 3;
	items = (ITEM**)calloc(choices_num +1, sizeof(ITEM*));
	
	for(int i = 0; i< choices_num; i++)
		items[i] = new_item(user_choices[i], NULL);
	
	items[choices_num] = NULL;
	
	menu = new_menu((ITEM**)items);
	
	WINDOW *user_win = newwin(10,30,4,0);
	WINDOW *user_name = newwin(3,30,0,1);
	wprintw(user_name, "User Menu");
	wrefresh(user_name);
	
	keypad(user_win, true);
	set_menu_win(menu, user_win);
	set_menu_sub(menu, derwin(user_win, 6, 28, 2, 1));
	box(user_win, 0,0);
	
	post_menu(menu);
	wrefresh(user_win);
	
	panel7 = new_panel(user_name);
	panel8 = new_panel(user_win);

	int input;
	
	while(input = wgetch(user_win))
	{
		system("./NASA/UserConf/cleartmp.sh > /dev/null 2>&1");
		if(input == KEY_DOWN)
		{	
			menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(user_win);
		}
		
		else if(input == KEY_UP)
		{
			menu_driver(menu, REQ_UP_ITEM);
			wrefresh(user_win);
		}
		
		else if(input == KEY_F(5)||input == KEY_LEFT)
		{
			clear();
			refresh();
			break;;
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
				hidemenu(panel7);
				hidemenu(panel8);

				adduser();

				showmenu(panel7);
				showmenu(panel8);

				wrefresh(user_win);

				continue;
					
			}

			else if(selected == items[1])
			{
				
				hidemenu(panel7);
                               hidemenu(panel8);

                               deluser();

                               showmenu(panel7);
                               showmenu(panel8);

                               wrefresh(user_win);

                               continue;

			}

			else if(selected == items[2])
			{
				break;

			}

		}
	
		else
		{
			wrefresh(user_win);
			continue;
		}
	}
	
	for(int i = 0; i<3; i++)
		free_item(items[i]);
		
	free_menu(menu);
	return;

}


void adduser() // 네트워크 설정
{	




	cbreak();
	noecho();



	clear();

	char user_name[100];
	char user_psd[100];
	
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
	wprintw(win_name, "Please enter the SAMBA user's ID");
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
	
	strcpy(user_name, field_buffer(test[0],0));

	int user_name_ind = strlen(user_name) -1;
	
	while(user_name_ind>= 0 && isspace(user_name[user_name_ind]))
	{
		user_name[user_name_ind] = '\0';
		user_name_ind--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);
	delwin(win);
	
	

	clear();	/////////////////////////
	
	
	test[0] = new_field(1, 38, 0,0,0,0);
	//set_field_buffer(test[0], 0, editing[1]);
	field_opts_off(test[0], O_PUBLIC);
	form = new_form(test);
	wclear(win_name);
	
	
	
	wprintw(win_name, "Please enter the SAMBA user's password");
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
	
	strcpy(user_psd, field_buffer(test[0],0));
	
	int user_psd_ind = strlen(user_psd) -1;
	
	while(user_psd_ind>= 0 && isspace(user_psd[user_psd_ind]))
	{
		user_psd[user_psd_ind] = '\0';
		user_psd_ind--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);
	delwin(win);
	delwin(win_name);
	
	/*
	
	printw("Please enter your Network User's name\n>>");
	echo();
	keypad(stdscr, FALSE);
	getstr(user_name);
	refresh();
	
	clear();
	printw("Please enter your Network user's password\n>>");
	noecho();
	getstr(user_psd);
	refresh();
	
	clear();
	refresh();
	
	cbreak();
	noecho();
	
	*/
	
	char command[200];
	
	sprintf(command, "./NASA/UserConf/smb_useradd.sh \"%s\" \"%s\"",user_name, user_psd);
	system(command);
	
	FILE *Usererr = fopen("./NASA/UserConf/error.tmp","r");
	if(Usererr != NULL){
	fseek(Usererr,0,SEEK_END);
	
	int size = ftell(Usererr);
	if(size>0){
			printw("Error,unable to add user.\n");
        		printw("Make sure you entered correctly!\n\n");
        		printw("Press any key to continue");
        		getch();
        		clear();
        		return;
        	}
	}
	fclose(Usererr);
	
	
	printw("Done! Press any key to continue");
	system("./NASA/UserConf/cleartmp.sh > /dev/null 2>&1");
	getch();
	
	clear();
	
	
	
	return;	
	

}


void deluser()  //네트워크 리셋
{	

	clear();

	int user_num = 0;
	
	system("./NASA/UserConf/smb_userlist.sh");
	
	FILE *file1 = fopen("./NASA/UserConf/user_num.tmp", "r");    //드라이브 개수 가져오기

	if (file1 == NULL)
	{
		printw("An error has occured1. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	if(!fscanf(file1, "%d", &user_num))
	{
		printw("An error has occured2. Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	
	if(user_num == 0)
	{
		printw("No user found! Press any key to exit");
		cbreak;
		noecho;
		getch();
		clear();
		refresh();
		return;
	}
	
	fclose(file1);
	
	
	
	FILE *file2 = fopen("./NASA/UserConf/smbuser2.tmp","r");   //설정 이름 가져오기
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
	
	char *user_name[user_num];
	char temp1[100];
	
	for(int i = 0; i<user_num; i++)
	{
		fgets(temp1, sizeof(temp1), file2);
		
		if(strlen(temp1)>0 && temp1[strlen(temp1)-1] == '\n')
			temp1[strlen(temp1)-1] = '\0';
		user_name[i] = (char*)malloc(strlen(temp1)*sizeof(char));
		strcpy(user_name[i], temp1);
	
	}
	
	fclose(file2);
	
	ITEM **items;    //아이템 저장소
	MENU *menu;   //메뉴 생성


	int main_choices_n = ARR_SIZE(user_name); 
	items = (ITEM**)calloc(main_choices_n + 1, sizeof(ITEM*));   //아이템 저장공간 동적할당

	for(int i =0; i<main_choices_n; i++)  //미리 저장한 메뉴 옵션들을 아이템으로 옮김
	{
		items[i] = new_item(user_name[i], NULL);
	}

	items[main_choices_n] = NULL;
	
	menu = new_menu((ITEM**)items);  //메뉴에 아이템 연동
	
	WINDOW *menu_win = newwin(10,30,4,0);   //메뉴가 들어갈 하위 윈도우(박스) 만들기


	WINDOW *main_name = newwin(3,30,0,1);  //메뉴의 이름이 들어갈 박스 만들기
	wprintw(main_name, "Please Select the user name to delete\n");
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
			sel_line_num=selected_loc;
			
			
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
	
	sprintf(command, "./NASA/UserConf/smb_userdel.sh \"%s\"",user_name[sel_line_num]);
	system(command);
	
	
	free_item(items[0]);
	free_item(items[1]);
	free_menu(menu);
	clear();
	refresh();
        
	cbreak();
	noecho();
	
	printw("Done! Press any key to continue");
	system("./NASA/UserConf/cleartmp.sh > /dev/null 2>&1");
	getch();
	
	
	
	
	
	clear();



	
	return;

}
