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
			break;

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
{	char user_name[100];
	char user_psd[100];
	
	
	printw("Please enter your Network User's name\n>>");
	echo();
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
	
	char command[200];
	
	sprintf(command, "./NASA/UserConf/smb_useradd.sh \"%s\" \"%s\"",user_name,user_psd);
	system(command);
	
	
	printw("Done! Press any key to continue");
	getch();
	
	clear();
	
	
	
	return;	
	

}


void deluser()  //네트워크 리셋
{
	
	return;

}
