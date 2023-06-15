#include "main.h"

void hidemenu(PANEL *panel1)
{

	hide_panel(panel1);
	update_panels();
	doupdate();
	return;
}


void showmenu(PANEL *panel1)
{
	show_panel(panel1);
	update_panels();
	doupdate();
	return;
}
