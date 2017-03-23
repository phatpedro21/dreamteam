#pragma once
#include "Object_2D.h"
#include "Camera.h"
#include "Screen.h"
#include <iostream>
#include <conio.h>

#include <gmtl-0.6.1/gmtl/Matrix.h>
#include <gmtl-0.6.1/gmtl/MatrixOps.h>

using namespace gmtl;

class Object_Tri : public Object_2D
{
public:
	Object_Tri(Vector_3D origin, Vector_3D p1, Vector_3D p2, Vector_3D p3);
	~Object_Tri();
	void rasterise(Screen* screen, Camera* camera);
	void local_to_proj(Screen* screen, Camera* camera, char icon, int i /*for testing*/);

	void left();
	void right();
	void up();
	void down();
	void scale_up();
	void scale_down();
private:
	Vector_3D _p1, _p2, _p3, _v1, _v2, _v3, _origin;

	/*DESCRIBED AS
	
	
	[ Transform_XAxis.x , Transform_YAxis.x, Transform_ZAxis.x, Translation.x]
	[ Transform_XAxis.y , Transform_YAxis.y, Transform_ZAxis.y, Translation.y]
	[ Transform_XAxis.z , Transform_YAxis.z, Transform_ZAxis.z, Translation.z]
	[         0         ,          0       ,          0       ,        1     ]
	
	Where Transform_XAxis is the XAxis orientation in the new space, Transform_YAxis is 
	the YAxis orientation in the new space, Transform_ZAxis is the ZAxis orientation in 
	the new space and Translation describes the position where the new space is going to be 
	relatively to the active space. */ 

	Matrix44f world_to_local_m;
};

