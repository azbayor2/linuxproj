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
		if(input == KEY_DOWN)
		{	
			menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(net_win);
		}
		
		else if(input == KEY_UP)
		{
			menu_driver(menu, REQ_UP_ITEM);
			wrefresh(net_win);
		}
		
		else if(input == KEY_F(5))
			break;

		else if(input == 10)
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
	
	FILE *file1 = fopen("./NASA/NetworkConf/temp1_num.txt", "r");
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
	
	FILE *file2 = fopen("./NASA/NetworkConf/temp1.txt","r");
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
		if(input == KEY_F(5))    //F5 누르면 나감
			return;

		else if(input == KEY_DOWN)     //아랫방향
		{	menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(menu_win);
		}
		else if(input == KEY_UP)    //윗방향          
		{	menu_driver(menu, REQ_UP_ITEM);
			wrefresh(menu_win);
		}

		else if(input == 10) //엔터
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
        
	
	
	
	
	nocbreak();
	echo();
	
	printw("Please enter your ipaddress/length\n>>");
	getstr(ipaddress);
	refresh();
	
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
	
	char command[200];
	
	sprintf(command, "./NASA/NetworkConf/static.sh %s %s %s %s",int_name, ipaddress, DNS1, DNS2);
	system(command);
	
	printw("Done! Press any key to continue");
	getch();
	
	
	
	
	
	clear();
	
	
	
	
	return;	

}


void defaultnetwork()  //네트워크 리셋
{
	
	
	char int_name[100];	
	int interface_num=0;
	
	system("./NASA/NetworkConf/new_interface.sh");
	
	FILE *file1 = fopen("./NASA/NetworkConf/temp1_num.txt", "r");
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
	
	FILE *file2 = fopen("./NASA/NetworkConf/temp1.txt","r");
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
		if(input == KEY_F(5))    //F5 누르면 나감
		{	
			clear();
			refresh();
			return;
			
		}

		else if(input == KEY_DOWN)     //아랫방향
		{	menu_driver(menu, REQ_DOWN_ITEM);
			wrefresh(menu_win);
		}
		else if(input == KEY_UP)    //윗방향          
		{	menu_driver(menu, REQ_UP_ITEM);
			wrefresh(menu_win);
		}

		else if(input == 10) //엔터
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
	
	sprintf(command, "./NASA/NetworkConf/static.sh %s",int_name);
	system(command);
	
	printw("Done! Press any key to continue");
	refresh();
	getch();
	
	
	
	
	
	clear();
	refresh();
	
	
	
	
	return;	


}
