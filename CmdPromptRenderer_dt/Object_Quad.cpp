#include "Object_Quad.h"



Object_Quad::Object_Quad()
{
	_width = 20;
	_height = 5;
	Object_2D::Object::texture = 'K';
	Object_2D::Object::_position.set(10.0f, 4.0f, -8.0f);
}


Object_Quad::~Object_Quad()
{
}

pixel Object_Quad::hit(Vector_3D ray)
{
	//NO CHECK FOR IF QUAD IS BEHIND THE CAMERA

	if (((Object_2D::Object::_position.y() + (_width / 2)) > ray.y()) && (Object_2D::Object::_position.y() - (_width / 2)) < ray.y())
	{
		if(((Object_2D::Object::_position.z() + (_height / 2)) > ray.z()) && (Object_2D::Object::_position.z() - (_height/ 2)) < ray.z())
		{
			return pixel(Object_2D::Object::_position.x(), Object_2D::Object::texture);
		}
	}
	return pixel(-1.0f, '¬');
	
}
