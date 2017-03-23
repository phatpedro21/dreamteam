#pragma once
#include "Settings.h"

class Screen
{
public:
	Screen();
	~Screen(); 

	void clearBuffer();
	

	char viewBuffer[V_HEIGHT][V_WIDTH];

};

