#include "Object_Tri.h"
#include "Settings.h"

#define _USE_MATH_DEFINES
#include <math.h>


Object_Tri::Object_Tri(Vector_3D origin, Vector_3D p1, Vector_3D p2, Vector_3D p3)
{
	lr = 0;
	ud = 0;
	_origin = origin;
	_p1 = p1;
	_p2 = p2;
	_p3 = p3;
	world_to_local_m.set(	1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);

	rot_m.set(		1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

	trans_m.set(	1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

	scale_m.set(	1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

	rot_angle_x = 0.0f;
	rot_angle_y = 0.0f;
	rot_angle_z = 0.0f;
}


Object_Tri::~Object_Tri()
{
}

void Object_Tri::left()
{
	lr -= 1.0f;	
	trans_m(2, 3) = lr;
	calc_world_to_local();
	/*trans_m(2, 3) = trans_m(2, 3) - 1.0f;
	//std::<< (float)world_to_local_m(2, 3) << std::endl;
	calc_world_to_local();*/
}

void Object_Tri::right()
{
	lr += 1.0f;
	trans_m(2, 3) = lr;
	calc_world_to_local();
	
	/*trans_m(2, 3) = trans_m(2, 3) + 1.0f;
	//std::cout << (float)world_to_local_m(2, 3) << std::endl;
	calc_world_to_local();*/
}

void Object_Tri::down()
{
	ud += 1.0f;
	trans_m(1, 3) = ud;
	calc_world_to_local();
}

void Object_Tri::up()
{
	ud -= 1.0f;
	trans_m(1, 3) = ud;
	calc_world_to_local();
}

void Object_Tri::scale_down()
{
	//scale_m(0, 0) = scale_m(0, 0) - 1;
	scale_m(1, 1) = scale_m(1, 1) - 1;
	scale_m(2, 2) = scale_m(2, 2) - 1;
	calc_world_to_local();
}

void Object_Tri::scale_up()
{
	//scale_m(0, 0) = scale_m(0, 0) + 1;
	scale_m(1, 1) = scale_m(1, 1) + 1;
	scale_m(2, 2) = scale_m(2, 2) + 1;
	calc_world_to_local();
}

void Object_Tri::rotate_in_x()
{
	rot_angle_x += 0.15f;	
	
	rot_m(1, 1) = cosf(rot_angle_x);
	rot_m(2, 2) = cosf(rot_angle_x);

	rot_m(1, 2) = -sinf(rot_angle_x);
	rot_m(2, 1) = sinf(rot_angle_x);
	calc_world_to_local();
}

void Object_Tri::rotate_in_y()
{
	rot_angle_y += 0.15f;

	rot_m(0, 0) = cosf(rot_angle_z);
	rot_m(2, 2) = cosf(rot_angle_z);

	rot_m(2, 0) = -sinf(rot_angle_z);
	rot_m(0, 2) = sinf(rot_angle_z);
	calc_world_to_local();
}

void Object_Tri::rotate_in_z()
{
	rot_angle_z += 0.15f;

	rot_m(0, 0) = cosf(rot_angle_z);
	rot_m(1, 1) = cosf(rot_angle_z);

	rot_m(0, 1) = -sinf(rot_angle_z);
	rot_m(1, 0) = sinf(rot_angle_z);
	calc_world_to_local();
}


void Object_Tri::local_to_proj(Screen* screen, Camera* camera, char icon, int i)
{

	std::cout << lr << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << world_to_local_m(i, j) << ',';
		}
		std::cout << std::endl;
	}

	//transform to world
	Matrix<float, 4, 4> local_to_world_m;
	//INVERSION SEEMS UNNECESARRY, just to avoid chainging al vairables that may need to be changed back, simply 
	//changing name here (should change for optimisation)
	local_to_world_m = world_to_local_m;
	//invert(local_to_world_m, world_to_local_m);
	Matrix<float, 4, 1> origin_m;
	Matrix<float, 4, 1> t_origin_m;
	Matrix<float, 4, 1> pos_m;
	Matrix<float, 4, 1> t_pos_m;
	origin_m(0, 0) = _origin.x();
	origin_m(1, 0) = _origin.y();
	origin_m(2, 0) = _origin.z();
	origin_m(3, 0) = 1;
	t_pos_m(0, 0) = 0;
	t_pos_m(1, 0) = 0;
	t_pos_m(2, 0) = 0;
	t_pos_m(3, 0) = 1;
	t_origin_m = t_pos_m;

	switch (i)
	{				
	case 1:
		std::cout << 'x';
		pos_m(0, 0) = _p1.x();
		pos_m(1, 0) = _p1.y();
		pos_m(2, 0) = _p1.z();
		pos_m(3, 0) = 1;		
		break;
	case 2:
		std::cout << 'y';
		pos_m(0, 0) = _p2.x();
		pos_m(1, 0) = _p2.y();
		pos_m(2, 0) = _p2.z();
		pos_m(3, 0) = 1;
		break;
	case 3:
		std::cout << 'z';
		pos_m(0, 0) = _p3.x();
		pos_m(1, 0) = _p3.y();
		pos_m(2, 0) = _p3.z();
		pos_m(3, 0) = 1;
		break;
	}	

	
	mult(t_origin_m ,local_to_world_m, origin_m);
	mult(t_pos_m, local_to_world_m, pos_m);

	switch (i)
	{
	case 1:
		display_p1.set(t_origin_m(0, 0) + t_pos_m(0, 0), t_origin_m(1, 0) + t_pos_m(1, 0), t_origin_m(2, 0) + t_pos_m(2, 0));
		break;
	case 2:
		display_p2.set(t_origin_m(0, 0) + t_pos_m(0, 0), t_origin_m(1, 0) + t_pos_m(1, 0), t_origin_m(2, 0) + t_pos_m(2, 0));
		break;
	case 3:
		display_p3.set(t_origin_m(0, 0) + t_pos_m(0, 0), t_origin_m(1, 0) + t_pos_m(1, 0), t_origin_m(2, 0) + t_pos_m(2, 0));
		break;
	}

	//round point to int, and update screen buffer at that point;
	Vector_3D pixel(t_origin_m(0,0) + t_pos_m(0, 0), t_origin_m(1, 0) + t_pos_m(1, 0), t_origin_m(2, 0) + t_pos_m(2, 0));
	//Vector_3D pixel(0, origin_m(0, 1), origin_m(0, 2));
	if (pixel.y() < V_HEIGHT && pixel.y() >= 0 && pixel.z() < V_WIDTH && pixel.z() >= 0)
	{
		screen->viewBuffer[(int)pixel.y()][(int)pixel.z()] = icon;
	}

	std::cout << std::endl << std::endl << std::endl;
}

void Object_Tri::add_lines(Screen* screen, Vector_3D a, Vector_3D b)
{

	int diffY, diffZ, grad, step, x, y;
	bool yPositive = true, zPositive = true;
	//for p1 - p2
	//find diff y
	diffY = (unsigned int)a.y() - (unsigned int)b.y();
	diffY = abs(diffY);
	//find diff z
	diffZ = (int)a.z() - (int)b.z();
	diffZ = abs(diffZ);
	if (a.y() < b.y())
	{
		yPositive = false;
	}
	if (a.z() < b.z())
	{
		zPositive = false;
	}
	step = 0;
	if (diffZ < diffY)
	{
		std::cout << std::endl;
		if (diffZ != 0)
		{
			grad = diffY / diffZ;
			if (grad == 0)	grad = 1;
		}
		for (x = 1; x < diffY; x++)
		{
			if (diffZ != 0)
			{
				if (grad != 0 && x%grad == 0)
				{
					step++;
				}

				if (grad < 0)
				{
					step *= -1;
				}
			}			
			if (yPositive && !zPositive && (int)a.y() - x > 0 && (int)a.y() - x < V_HEIGHT && (int)a.z() + step >= 0 && (int)a.z() + step < V_WIDTH)
			{
				//screen->viewBuffer[(int)a.y() - x][(int)a.z() + step] = '.';
				screen->viewBuffer[(int)a.y() - x][(int)a.z() + step] = '.';
			}
			else if (!yPositive && !zPositive && (int)a.y() - x > 0 && (int)a.y() - x < V_HEIGHT && (int)a.z() + step >= 0 && (int)a.z() + step < V_WIDTH)
			{
				//screen->viewBuffer[(int)a.y() - x][(int)a.z() + step] = '.';
				screen->viewBuffer[(int)a.y() + x][(int)a.z() + step] = '.';
			}
			else if (yPositive && zPositive && (int)a.y() + x > 0 && (int)a.y() + x < V_HEIGHT && (int)a.z() + step >= 0 && (int)a.z() + step < V_WIDTH)
			{
				//screen->viewBuffer[(int)a.y() + x][(int)a.z() + step] = '.';
				screen->viewBuffer[(int)a.y() - x][(int)a.z() - step] = '.';
			}
			else if (!yPositive && zPositive && (int)a.y() + x > 0 && (int)a.y() + x < V_HEIGHT && (int)a.z() + step >= 0 && (int)a.z() + step < V_WIDTH)
			{
				//screen->viewBuffer[(int)a.y() + x][(int)a.z() + step] = '.';
				screen->viewBuffer[(int)a.y() + x][(int)a.z() - step] = '.';
			}			
		}
	}
	else
	{
		if (diffY != 0)
		{
			grad = diffZ / diffY;
		}
		for (x = 1; x < diffZ; x++)
		{
			if (diffY != 0)
			{
				if (x%grad == 0)
				{
					step++;
				}

				if (grad < 0)
				{
					//step *= -1;
				}
			}			
			if (zPositive && !yPositive && (int)a.z() + x > 0 && (int)a.z() + x < V_WIDTH && (int)a.y() + step >= 0 && (int)a.y() + step < V_HEIGHT)
			{
				//screen->viewBuffer[(int)a.y() - x][(int)a.z() + step] = '.';
				screen->viewBuffer[(int)a.y() + step][(int)a.z() - x] = '.';
			}
			else if (!zPositive && !yPositive && (int)a.z() + x > 0 && (int)a.z() + x < V_WIDTH && (int)a.y() + step >= 0 && (int)a.y() + step < V_HEIGHT)
			{
				//screen->viewBuffer[(int)a.y() + x][(int)a.z() + step] = '.';
				screen->viewBuffer[(int)a.y() + step][(int)a.z() + x] = '.';
			}
			else if (zPositive && yPositive && (int)a.z() + x > 0 && (int)a.z() + x < V_WIDTH && (int)a.y() + step >= 0 && (int)a.y() + step < V_HEIGHT)
			{
				//screen->viewBuffer[(int)a.y() + x][(int)a.z() + step] = '.';
				screen->viewBuffer[(int)a.y() - step][(int)a.z() - x] = '.';
			}
			else if (!zPositive && yPositive && (int)a.z() + x > 0 && (int)a.z() + x < V_WIDTH && (int)a.y() + step >= 0 && (int)a.y() + step < V_HEIGHT)
			{
				//screen->viewBuffer[(int)a.y() + x][(int)a.z() + step] = '.';
				screen->viewBuffer[(int)a.y() - step][(int)a.z() + x] = '.';
			}
		}
	}

	//for p2 - p3

	//for p3 - p1
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

	add_lines(screen, display_p1, display_p2);
	add_lines(screen, display_p2, display_p3);
	add_lines(screen, display_p3, display_p1);
}

void Object_Tri::calc_world_to_local()
{
	mult(world_to_local_m, MAT_IDENTITY44F, trans_m);
	mult(world_to_local_m, world_to_local_m, rot_m);
	mult(world_to_local_m, world_to_local_m, scale_m);
}

