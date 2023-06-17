#include "main.h"




char *main_choices[] = {"Network Settings", "Samba Settings", "Exit"};   //메인 메뉴 옵션들 미리 저장


PANEL *panel1;   //패널화 한 이유는 다음 메뉴 띄울때 숨길려고
PANEL *panel2;

int main()     //메인 메뉴 출력 부분
{
	
	
	initscr();
	printw("NASA\n");
	
	if(geteuid()!=0)
	{
		printw("\n\nThis Program requires Root Priviledge!\n\n");
		printw("Please run as ROOT!\n\n\n\n");
		printw("Press any key to Exit");
		getch();
		
		
		endwin();
		
		return 0;
	}
	printw("Press any key to enter");
	refresh();

	noecho();
	keypad(stdscr, TRUE);
	cbreak();

	getch();
	clear();
	refresh();

	
	
	
	ITEM **main_items;    //아이템 저장소
	MENU *main_menu;   //메뉴 생성


	int main_choices_n = ARR_SIZE(main_choices); 
	main_items = (ITEM**)calloc(main_choices_n + 1, sizeof(ITEM*));   //아이템 저장공간 동적할당

	for(int i =0; i<main_choices_n; i++)  //미리 저장한 메뉴 옵션들을 아이템으로 옮김
	{
		main_items[i] = new_item(main_choices[i], NULL);
	}

	main_items[main_choices_n] = NULL;
	
	main_menu = new_menu((ITEM**)main_items);  //메뉴에 아이템 연동
	

	WINDOW *main_menu_win = newwin(10,30,4,0);   //메뉴가 들어갈 하위 윈도우(박스) 만들기


	WINDOW *main_name = newwin(3,30,0,1);  //메뉴의 이름이 들어갈 박스 만들기
	wprintw(main_name, "Main Menu\n");
	wprintw(main_name, "Press F5 to exit");
	wrefresh(main_name);
	
	keypad(main_menu_win, true);
	set_menu_win(main_menu, main_menu_win);
	set_menu_sub(main_menu, derwin(main_menu_win, 6, 28, 2,1));  //메뉴 설정(윗줄이 왜 필요한지 모르겠음)
	box(main_menu_win, 0,0);

	post_menu(main_menu);
	wrefresh(main_menu_win);

	panel1 = new_panel(main_menu_win);   //윈도우 두개를 패널화함.
	panel2 = new_panel(main_name);
	
	int input;
	
	while(input = wgetch(main_menu_win))
	{
	char* key = keyname(input);
		if(input == KEY_F(5))    //F5 누르면 나감
			break;
		else if(input == KEY_F(7))
		{
			reset_all();
		}
		
        	else if (key[0] == '^' && key[1] == 'E') {
          		endwin();
			exit(0);
		}
		else if(input == KEY_DOWN)     //아랫방향
		{	menu_driver(main_menu, REQ_DOWN_ITEM);
			wrefresh(main_menu_win);
		}
		else if(input == KEY_UP)    //윗방향          
		{	menu_driver(main_menu, REQ_UP_ITEM);
			wrefresh(main_menu_win);
		}

		else if(input == 10||input == KEY_RIGHT) //엔터
		{
			ITEM * selected = current_item(main_menu);
		        
			if(selected == main_items[0])  //네트워크 드라이브 메뉴 호출
			{
				
				hidemenu(panel1);
				hidemenu(panel2);
				
				network_menu();
				
				showmenu(panel1);
				showmenu(panel2);
				wrefresh(main_menu_win);			
				
				continue;
			}	

			else if(selected == main_items[1]) //삼바 드라이브 메뉴 호출
			{
				hidemenu(panel1);
				hidemenu(panel2);
				
				samba_menu();
				
				showmenu(panel1);
				showmenu(panel2);
				wrefresh(main_menu_win);
				
				continue;
			}

			else if(selected == main_items[2])
				break;
		}
		
		else
		{
			wrefresh(main_menu_win);
			continue;
		}
	}

	free_item(main_items[0]);
	free_item(main_items[1]);
	free_menu(main_menu);
	endwin();

}



