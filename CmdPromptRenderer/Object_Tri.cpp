#include "Object_Tri.h"
#include "Settings.h"


Object_Tri::Object_Tri(Vector_3D origin, Vector_3D p1, Vector_3D p2, Vector_3D p3)
{
	_origin = origin;
	_p1 = p1;
	_p2 = p2;
	_p3 = p3;
	world_to_local_m.set(1.0f, 0.0f, 0.0f, 0.0f, 
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f, 
						0.0f, 0.0f, 0.0f, 1.0f);
}


Object_Tri::~Object_Tri()
{
}

void Object_Tri::left()
{
	world_to_local_m(2, 3) = world_to_local_m(2, 3) + 1.0f;
	std::cout << (float)world_to_local_m(2, 3) << std::endl;
}

void Object_Tri::right()
{
	world_to_local_m(2, 3) = world_to_local_m(2, 3) - 1.0f;
	std::cout << (float)world_to_local_m(2, 3) << std::endl;
}

void Object_Tri::down()
{
	world_to_local_m(1, 3) = world_to_local_m(1, 3) - 1.0f;
	std::cout << (float)world_to_local_m(3, 3) << std::endl;
}

void Object_Tri::up()
{
	world_to_local_m(1, 3) = world_to_local_m(1, 3) + 1.0f;
	std::cout << (float)world_to_local_m(3, 3) << std::endl;
}

void Object_Tri::scale_down()
{
	world_to_local_m(0, 0) = world_to_local_m(0, 0) + 1.0f;
	world_to_local_m(1, 1) = world_to_local_m(1, 1) + 1.0f;
	world_to_local_m(2, 2) = world_to_local_m(2, 2) + 1.0f;

}

void Object_Tri::scale_up()
{
	world_to_local_m(0, 0) = world_to_local_m(0, 0) - 1.0f;
	world_to_local_m(1, 1) = world_to_local_m(1, 1) - 1.0f;
	world_to_local_m(2, 2) = world_to_local_m(2, 2) - 1.0f;
}



void Object_Tri::local_to_proj(Screen* screen, Camera* camera, char icon, int i)
{
	//transform to world
	Matrix<float, 4, 4> local_to_world_m;
	invert(local_to_world_m, world_to_local_m);

	Matrix<float, 1, 4> pos_m;
	switch (i)
	{
	case 1:
		pos_m(0, 0) = _p1.x();
		pos_m(0, 1) = _p1.y();
		pos_m(0, 2) = _p1.z();
		break;
	case 2:
		pos_m(0, 0) = _p2.x();
		pos_m(0, 1) = _p2.y();
		pos_m(0, 2) = _p2.z();
		break;
	case 3:
		pos_m(0, 0) = _p3.x();
		pos_m(0, 1) = _p3.y();
		pos_m(0, 2) = _p3.z();
		break;
	default:
		break;
	}
	

	std::cout << '(' << pos_m(0, 0) << ',' << pos_m(0, 1) << ',' << pos_m(0, 2) << ") local \n";
	//pos_m//(local_to_world_m, pos_m);	
	float hold_s, hold_p;
	for (int i = 0; i < 4; i++)
	{		
		for (int j = 0; j < 4; j++)
		{			
			if (j == i)
			{
				hold_s = local_to_world_m(i, j);
			}
			if (j == 3)
			{
				hold_p = local_to_world_m(i, j);
			}			
		}
		pos_m(0, i) = (hold_s*pos_m(0, i)) + hold_p;
	}

	std::cout << '(' << pos_m(0, 0) << ',' << pos_m(0, 1) << ',' << pos_m(0, 2) << ") world\n";
	/*std::cout << '(' << pos_m(0,0) << ',' << pos_m(0, 1) << ',' << pos_m(0, 2) << ") world to camera\n";
	//transform to camera (from world)
	Matrix<float, 4, 4> world_to_Cam_m;
	invert(world_to_Cam_m, camera->getCam_to_World());
	pos_m = pos_m * world_to_Cam_m;

	std::cout << '(' << pos_m(0, 0) << ',' << pos_m(0, 1) << ',' << pos_m(0, 2) << ")camera to proj\n";
	//Transform to proj (from camera)
	Matrix<float, 4, 4> cam_to_Proj_m;
	invert(cam_to_Proj_m, camera->getCam_to_Proj());
	pos_m = pos_m * cam_to_Proj_m;	*/


	//round point to int, and update screen buffer at that point;
	Vector_3D pixel(0, pos_m(0, 1), pos_m(0, 2));
	if (pixel.y() < V_HEIGHT && pixel.y() >= 0 && pixel.z() < V_WIDTH && pixel.z() >= 0)
	{
		screen->viewBuffer[(int)pixel.y()][(int)pixel.z()] = icon;
	}
}

void Object_Tri::rasterise(Screen* screen, Camera* camera)
{
	//for first point (for now)	
	float point[4] = { _p1.x(), _p1.y(), _p1.z(), 1 };
	local_to_proj(screen, camera, 'x', 1);

	/*point[0] = _p2.x();
	point[1] = _p2.y();
	point[2] = _p2.z();
	point[3] = 1 ;*/
	local_to_proj(screen, camera, 'y', 2);

	/*point[0] = _p3.x();
	point[1] = _p3.y();
	point[2] = _p3.z();
	point[3] = 1;*/
	local_to_proj(screen, camera, 'z', 3);	


}

