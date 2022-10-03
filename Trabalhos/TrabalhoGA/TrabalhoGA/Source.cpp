using namespace std;

#include "SceneManager.h"

int main(int argc, char* argv[])
{
	SceneManager *scene = new SceneManager;
	scene->initialize(800, 600);

	scene->run();

	scene->finish();
	
	return 0;
}