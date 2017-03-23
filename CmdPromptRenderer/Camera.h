#pragma once
#include "Settings.h"
#include "Screen.h"
#include "Vector_3D.h"
#include "pixel.h" 
#include "gmtl\Matrix.h"

#include "Object_Quad.h"

class Camera
{
public:
	Camera();
	~Camera();
	void buildView(Screen* screen);

	gmtl::Matrix44f getCam_to_Proj() { return camera_to_proj_m_ortho; }
	gmtl::Matrix44f getCam_to_World() { return camera_to_world_m; }

private:
	Vector_3D position, direction;
	//the 10 and 0.2 values at [2][2] and [2][3] are far and near clipping plains, should probably be moved to constant
	gmtl::Matrix44f camera_to_proj_m_ortho;
	gmtl::Matrix44f camera_to_world_m;
	Object_Quad rect;
	

};

