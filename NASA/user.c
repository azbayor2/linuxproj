#include "main.h"

char *user_choices[] = {"Add User", "Delete User", "Return"};

PANEL *panel3;
PANEL *panel4;


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
	
	panel3 = new_panel(user_name);
	panel4 = new_panel(user_win);

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
		
		else if(input == KEY_F(5))
			break;

		else if(input == 10)
		{
			ITEM * selected = current_item(menu);

			if(selected == items[0])
			{
				hidemenu(panel3);
				hidemenu(panel4);

				adduser();

				showmenu(panel3);
				showmenu(panel4);

				wrefresh(user_win);

				continue;
					
			}

			else if(selected == items[1])
			{
				
				hidemenu(panel3);
                               hidemenu(panel4);

                               deluser();

                               showmenu(panel3);
                               showmenu(panel4);

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
	
	return;	

}


void deluser()  //네트워크 리셋
{
	
	return;

}
