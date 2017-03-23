#pragma once
#include "Object_2D.h"
#include "Vector_3D.h"
#include "pixel.h"
class Object_Quad : public Object_2D
{
public:
	Object_Quad();

	~Object_Quad();

	pixel hit(Vector_3D ray);

private:
	float _width, _height;
};

