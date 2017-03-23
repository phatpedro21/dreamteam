#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Renderer.h"
#include "Object_Tri.h"



Renderer renderer;
int main()
{	

	//need to convert each object to world space, then to view space.
	//


	while (true)
	{	
		renderer.mainLoop();
	}
	return 0;
}
