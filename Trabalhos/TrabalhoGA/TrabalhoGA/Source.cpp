using namespace std;

#include "SceneManager.h"


// The MAIN function, from here we start the application and run the game loop
int main(int argc, char* argv[])
{
	SceneManager *scene = new SceneManager;
	scene->initialize(800, 600);

	scene->run();

	scene->finish();
	
	return 0;
}