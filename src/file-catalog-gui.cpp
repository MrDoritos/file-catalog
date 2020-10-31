#include "file-catalog-gui.h"

filecatalog *filecatalog::instance;

#ifndef DEBUG_TESTS
int main(int argc, char **argv) {
	filecatalog instance;	
	filecatalog::instance = &instance;
		
	screen wscreen;
	s_screen = &wscreen;
	filecatalog::instance->wscreen = &wscreen;
	
	filecatalog::instance->indexPath = "index.dev.tdb";
	
	//Set the master child
	guiHandler masterGuiChild;
	filecatalog::instance->guiChild = &masterGuiChild;
	filecatalog::instance->wscreen->child = filecatalog::instance->guiChild;
	
	std::thread screen_thread = std::thread(screen::start, filecatalog::instance->wscreen);
	//filecatalog::instance->wscreen->start();
	
	optionListElement test;
	masterGuiChild.add(test);
	test.addOption(0, "This option has to scroll. This is more text. Just filler text.");
	
	screen_thread.join();
	return 0;
}
#endif