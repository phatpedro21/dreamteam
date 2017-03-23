#include "Renderer.h"



Renderer::Renderer()
{
	QueryPerformanceFrequency(&frequency);
	_screen = new Screen;
	_camera = new Camera;

	Vector_3D v(0.0f, 0.0f, 0.0f);
	Vector_3D p1(0.0f, 0.0f, 0.0f);
	Vector_3D p2(0.0f, 1.0f, 0.0f);
	Vector_3D p3(0.0f, 0.0f, 1.0f);
	_tri1 = new Object_Tri(v, p1, p2, p3);
}


Renderer::~Renderer()
{
	delete _screen;
	delete _camera;
	delete _tri1;
}

void Renderer::mainLoop()
{
	_screen->clearBuffer();
	_tri1->rasterise(_screen, _camera);
	// start timer
	QueryPerformanceCounter(&t1);
	draw();
	char in = _getch();
	switch (in)
	{
	case 'a':
		_tri1->left();
		break;
	case 'd':
		_tri1->right();
		break;
	case 'w':
		_tri1->up();
		break;
	case 's':
		_tri1->down();
		break;
	case 'q':
		_tri1->scale_down();
		break;
	case 'e':
		_tri1->scale_up();
		break;
	default:
		break;
	}
	update();
	// stop timer
	QueryPerformanceCounter(&t2);

	// compute frame time so far, and then 'wait' until we are ready for next frame
	while ((t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart < 200)
	{
		QueryPerformanceCounter(&t2);
	}
	std::system("cls");
	
}

void Renderer::update()
{
	_camera->buildView(_screen);
}

void Renderer::draw()
{
	for (int i = 0; i < V_HEIGHT; i++)
	{
		for (int j = 0; j < V_WIDTH; j++)
		{
			std::cout << _screen->viewBuffer[i][j];
		}
		std::cout << std::endl;
	}
}
