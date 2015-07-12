#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/moduleinfo.h>
#include <psp2/kernel/processmgr.h>

#include <cstdio>
#include <vita2d.h>

#include "../libvitamenu/menu_manager.h"
#include "../libvitamenu/menu.h"
#include "../libvitamenu/menu_item.h"

PSP2_MODULE_INFO(0, 0, "touchvitalibsample");

void log(std::string s)
{
	printf("%s%s", s.c_str(), "\n");
}

int main() {
	log("Starting");
	vita2d_init();

	char menu_name[] = "Test";
	char item_name[] = "Sample test";

	Menu * menu = new Menu(NULL, &menu_name[0]);

	MenuManager * manager = new MenuManager(menu);

	MenuItem * item = new MenuItem(&item_name[0], 100, 100);
	menu->addMenuItem(item);

	//input for both touch and joysticks
	SceCtrlData pad;
	SceTouchData touch;

	while(1) {
		//read input
		sceCtrlPeekBufferPositive(0, &pad, 1);
		sceTouchPeek(0, &touch, 1);

		vita2d_start_drawing();
		vita2d_clear_screen();

		manager->draw();

		vita2d_end_drawing();
		vita2d_swap_buffers();
	}

	log("Stopped.\n");

	vita2d_fini();

	sceKernelExitProcess(0);
	delete manager;

	return 0;
}