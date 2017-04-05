#pragma once
#include "Vector_3D.h"


class Object
{
public:
	Object();
	~Object();

protected:
	Vector_3D _position, _direction;
	char texture;
};

