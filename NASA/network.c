#include "main.h"

char *network_choices[] = {"Set Static IP", "Default", "Return"};

PANEL *panel3;
PANEL *panel4;


void setnetwork();
void defaultnetwork();

void network_menu()
{

	ITEM **items;
	MENU *menu;
	
	int choices_num = 3;
	items = (ITEM**)calloc(choices_num +1, sizeof(ITEM*));
	
	for(int i = 0; i< choices_num; i++)
		items[i] = new_item(network_choices[i], NULL);
	
	items[choices_num] = NULL;
	
	menu = new_menu((ITEM**)items);
	
	WINDOW *net_win = newwin(10,30,4,0);
	WINDOW *net_name = newwin(3,30,0,1);
	wprintw(net_name, "Network menu");
	wrefresh(net_name);
	
	keypad(net_win, true);
	set_menu_win(menu, net_win);
	set_menu_sub(menu, derwin(net_win, 6, 28, 2, 1));
	box(net_win, 0,0);
	
	post_menu(menu);
	wrefresh(net_win);
	
	panel3 = new_panel(net_name);
	panel4 = new_panel(net_win);

	int input;
	
	while(input = wgetch(net_win))
	{
		system("./NASA/NetworkConf/cleartmp.sh > /dev/null 2>&1");
		char* key = keyname(input);
		if(input == KEY_DOWN)
		{	
			menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(net_win);
		}
		else if (key[0] == '^' && key[1] == 'E') {
          		endwin();
			exit(0);
		}

		else if(input == KEY_UP)
		{
			menu_driver(menu, REQ_UP_ITEM);
			wrefresh(net_win);
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
				hidemenu(panel3);
				hidemenu(panel4);

				setnetwork();

				showmenu(panel3);
				showmenu(panel4);

				wrefresh(net_win);

				continue;
					
			}

			else if(selected == items[1])
			{
				
				hidemenu(panel3);
                                hidemenu(panel4);

                                defaultnetwork();

                                showmenu(panel3);
                                showmenu(panel4);

                                wrefresh(net_win);

                                continue;

			}

			else if(selected == items[2])
			{
				break;

			}

		}
	
		else
		{
			wrefresh(net_win);
			continue;
		}
	}
	
	for(int i = 0; i<3; i++)
		free_item(items[i]);
		
	free_menu(menu);
	return;

}


void setnetwork() // 네트워크 설정 
{
	
	char ipaddress[100];
	char DNS1[100];
	char DNS2[100];
	char int_name[100];
	
	int interface_num=0;
	
	system("./NASA/NetworkConf/new_interface.sh");
	
	FILE *file1 = fopen("./NASA/NetworkConf/temp1_num.tmp", "r");
	if (file1 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	if(!fscanf(file1, "%d", &interface_num))
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	
	if(interface_num == 0)
	{
		printw("No interface found! Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	fclose(file1);
	
	FILE *file2 = fopen("./NASA/NetworkConf/temp1.tmp","r");
	if (file2 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	char *interface[interface_num];
	char temp[100];
	
	for(int i = 0; i<interface_num; i++)
	{
		fgets(temp, sizeof(temp), file1);
		
		if(strlen(temp)>0 && temp[strlen(temp)-1] == '\n')
			temp[strlen(temp)-1] = '\0';
		interface[i] = (char*)malloc(strlen(temp)*sizeof(char));
		strcpy(interface[i], temp);
	
	}
	

	
	
	fclose(file2);
	
	ITEM **items;    //아이템 저장소
	MENU *menu;   //메뉴 생성


	int main_choices_n = ARR_SIZE(interface); 
	items = (ITEM**)calloc(main_choices_n + 1, sizeof(ITEM*));   //아이템 저장공간 동적할당

	for(int i =0; i<main_choices_n; i++)  //미리 저장한 메뉴 옵션들을 아이템으로 옮김
	{
		items[i] = new_item(interface[i], NULL);
	}

	items[main_choices_n] = NULL;
	
	menu = new_menu((ITEM**)items);  //메뉴에 아이템 연동
	

	WINDOW *menu_win = newwin(10,30,4,0);   //메뉴가 들어갈 하위 윈도우(박스) 만들기


	WINDOW *main_name = newwin(3,30,0,1);  //메뉴의 이름이 들어갈 박스 만들기
	wprintw(main_name, "Please Select your interface\n");
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
			ITEM * selected = current_item(menu);
			strncpy(int_name, item_name(selected), 100);
			
			
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
	///////////////////////////
	FIELD *test[2];
	FORM *form;

	test[0] = new_field(1,38,0,0,0,0);
	test[1] = NULL;

	
	//field_opts_on(test[0], O_EDIT);
	//field_opts_on(test[0], O_VISIBLE);
	//field_opts_off(test[0], O_STATIC);
	set_field_just(test[0], JUSTIFY_LEFT);

	form = new_form(test);

	WINDOW *win = newwin(5,40,4,0);
	WINDOW *win_name = newwin(2,40,0,1);
	wprintw(win_name, "Please enter the IP address");
	wrefresh(win_name);
	keypad(win, true);
	set_form_win(form, win);
	set_form_sub(form, derwin(win, 1,38,2,1));
	box(win,0,0);

	post_form(form);

	wrefresh(win);

	//form_driver(form, REQ_END_LINE);
	//form_driver(form, REQ_INS_MODE);


	int ch;

	while((ch=wgetch(win)) != '\n')
	{

		
		
		
		switch(ch)
		{
			case KEY_LEFT: form_driver(form, REQ_LEFT_CHAR); break;
			case KEY_RIGHT: form_driver(form, REQ_RIGHT_CHAR); break;
			case KEY_BACKSPACE: form_driver(form, REQ_DEL_PREV); break;
		
			default: if(isdigit(ch) || ch=='.' || ch=='/') form_driver(form,ch); break;
		}	

		wrefresh(win);


	}

	form_driver(form, REQ_VALIDATION);



	strcpy(ipaddress, field_buffer(test[0],0));
	
	int ipaddress_length = strlen(ipaddress)-1;
	
	while(ipaddress_length>= 0 && isspace(ipaddress[ipaddress_length]))
	{
		ipaddress[ipaddress_length] = '\0';
		ipaddress_length--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);

	clear();

	
	
	///////////////////////////////////
	
	
	test[0] = new_field(1,38,0,0,0,0);
	test[1] = NULL;

	
	//field_opts_on(test[0], O_EDIT);
	//field_opts_on(test[0], O_VISIBLE);
	//field_opts_off(test[0], O_STATIC);
	set_field_just(test[0], JUSTIFY_LEFT);

	form = new_form(test);

	win = newwin(5,40,4,0);
	wclear(win_name);
	wprintw(win_name, "Please enter the Primary DNS");
	
	wrefresh(win_name);
	keypad(win, true);
	set_form_win(form, win);
	set_form_sub(form, derwin(win, 1,38,2,1));
	box(win,0,0);

	post_form(form);

	wrefresh(win);

	//form_driver(form, REQ_END_LINE);
	//form_driver(form, REQ_INS_MODE);




	while((ch=wgetch(win)) != '\n')
	{

		
		
		
		switch(ch)
		{
			case KEY_LEFT: form_driver(form, REQ_LEFT_CHAR); break;
			case KEY_RIGHT: form_driver(form, REQ_RIGHT_CHAR); break;
			case KEY_BACKSPACE: form_driver(form, REQ_DEL_PREV); break;
		
			default: if(isdigit(ch) || ch=='.') form_driver(form,ch); break;
		}	

		wrefresh(win);


	}

	form_driver(form, REQ_VALIDATION);



	strcpy(DNS1, field_buffer(test[0],0));
	
	int DNS1_length = strlen(DNS1)-1;
	
	while(DNS1_length>= 0 && isspace(DNS1[DNS1_length]))
	{
		DNS1[DNS1_length] = '\0';
		DNS1_length--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);

	clear();

	

	
	/////////////////////////////
	
	test[0] = new_field(1,38,0,0,0,0);
	test[1] = NULL;

	
	//field_opts_on(test[0], O_EDIT);
	//field_opts_on(test[0], O_VISIBLE);
	//field_opts_off(test[0], O_STATIC);
	set_field_just(test[0], JUSTIFY_LEFT);

	form = new_form(test);

	win = newwin(5,40,4,0);
	wclear(win_name);
	wprintw(win_name, "Please enter the Secondary DNS");
	
	wrefresh(win_name);
	keypad(win, true);
	set_form_win(form, win);
	set_form_sub(form, derwin(win, 1,38,2,1));
	box(win,0,0);

	post_form(form);

	wrefresh(win);

	//form_driver(form, REQ_END_LINE);
	//form_driver(form, REQ_INS_MODE);


	

	while((ch=wgetch(win)) != '\n')
	{

		
		
		
		switch(ch)
		{
			case KEY_LEFT: form_driver(form, REQ_LEFT_CHAR); break;
			case KEY_RIGHT: form_driver(form, REQ_RIGHT_CHAR); break;
			case KEY_BACKSPACE: form_driver(form, REQ_DEL_PREV); break;
		
			default: if(isdigit(ch) || ch=='.') form_driver(form,ch); break;
		}	

		wrefresh(win);


	}

	form_driver(form, REQ_VALIDATION);



	strcpy(DNS2, field_buffer(test[0],0));
	
	int DNS2_length = strlen(DNS2)-1;
	
	while(DNS2_length>= 0 && isspace(DNS2[DNS2_length]))
	{
		DNS2[DNS2_length] = '\0';
		DNS2_length--;
	}
	
	unpost_form(form);
	free_form(form);
	free_field(test[0]);

	clear();
	
	///////////////////////
	/*
	clear();
	printw("Please enter your primary DNS\n>>");
	getstr(DNS1);
	refresh();
	
	clear();
	printw("Please enter your secondary DNS\n>>");
	getstr(DNS2);
	refresh();
	
	cbreak();
	noecho();
	*/
	
	char command[200];
	
	sprintf(command, "./NASA/NetworkConf/static.sh %s %s %s %s",int_name, ipaddress, DNS1, DNS2);
	system(command);
	
	FILE *neterr = fopen("./NASA/NetworkConf/error.tmp", "r");
	
	if (neterr != NULL) {
        	fseek(neterr, 0, SEEK_END); 
        	
        	int size = ftell(neterr);
        	if(size >0){
        		printw("Error, Netplan was unable to apply setting.\n");
        		printw("Make sure you entered correctly!\n\n");
        		printw("Press any key to continue");
        		getch();
        		clear();
        		return;
        	}
        }
        		
       fclose(neterr);
        
	
	printw("Done! Press any key to continue");
	system("./NASA/NetworkConf/cleartmp.sh");
	
	
	
	getch();
	
	
	clear();
	
	
	return;	

}


void defaultnetwork()  //네트워크 리셋
{
	
	
	char int_name[100];	
	int interface_num=0;
	
	system("./NASA/NetworkConf/new_interface.sh");
	
	FILE *file1 = fopen("./NASA/NetworkConf/temp1_num.tmp", "r");
	if (file1 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	if(!fscanf(file1, "%d", &interface_num))
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	
	if(interface_num == 0)
	{
		printw("No interface found! Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	fclose(file1);
	
	FILE *file2 = fopen("./NASA/NetworkConf/temp1.tmp","r");
	if (file2 == NULL)
	{
		printw("An error has occured. Press any key to exit");
		cbreak;
		noecho;
		getch();
		return;
	}
	
	char *interface[interface_num];
	char temp[100];
	
	for(int i = 0; i<interface_num; i++)
	{
		fgets(temp, sizeof(temp), file1);
		
		if(strlen(temp)>0 && temp[strlen(temp)-1] == '\n')
			temp[strlen(temp)-1] = '\0';
		interface[i] = (char*)malloc(strlen(temp)*sizeof(char));
		strcpy(interface[i], temp);
	
	}
	

	
	
	fclose(file2);
	
	ITEM **items;    //아이템 저장소
	MENU *menu;   //메뉴 생성


	int main_choices_n = ARR_SIZE(interface); 
	items = (ITEM**)calloc(main_choices_n + 1, sizeof(ITEM*));   //아이템 저장공간 동적할당

	for(int i =0; i<main_choices_n; i++)  //미리 저장한 메뉴 옵션들을 아이템으로 옮김
	{
		items[i] = new_item(interface[i], NULL);
	}

	items[main_choices_n] = NULL;
	
	menu = new_menu((ITEM**)items);  //메뉴에 아이템 연동
	

	WINDOW *menu_win = newwin(10,30,4,0);   //메뉴가 들어갈 하위 윈도우(박스) 만들기


	WINDOW *main_name = newwin(3,30,0,1);  //메뉴의 이름이 들어갈 박스 만들기
	wprintw(main_name, "Please Select your interface\n");
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
			ITEM * selected = current_item(menu);
			strncpy(int_name, item_name(selected), 100);
			
			
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
	
	
	
	char command[200];
	
	sprintf(command, "./NASA/NetworkConf/reset.sh %s",int_name);
	system(command);
	
	printw("Done! Press any key to continue");
	system("./NASA/NetworkConf/cleartmp.sh > /dev/null 2>&1");
	refresh();
	getch();
	
	
	
	
	
	clear();
	refresh();
	
	
	
	
	return;	


}
