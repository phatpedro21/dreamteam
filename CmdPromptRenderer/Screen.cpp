#include "Screen.h"



Screen::Screen()
{
	clearBuffer();
}


Screen::~Screen()
{
}

void Screen::clearBuffer()
{
	for (int i = 0; i < V_HEIGHT; i++)
	{
		for (int j = 0; j < V_WIDTH; j++)
		{
			viewBuffer[i][j] = ' ';
		}
	}
}