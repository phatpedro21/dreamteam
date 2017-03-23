#pragma once
#include <iostream>
#include "Camera.h"
#include "Screen.h"
#include "Settings.h"
#include <Query.h>
#include "Object_Tri.h"

//For Testing
#include <conio.h>


class Renderer
{
public:
	Renderer();
	~Renderer();

	void mainLoop();
	void draw();
	void update();


private:

	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;
	Camera* _camera;
	Screen* _screen;
	Object_Tri* _tri1;

};

