#include "Camera.h"

Camera::Camera()
{
	position.set(0.0f, 0.0f, 0.0f);
	direction.set(1.0f, 0.0f, 0.0f);

	camera_to_proj_m_ortho.set(	(float)1 / V_WIDTH, 0.0f, 0.0f, 0.0f,
								0, 1 / V_HEIGHT, 0, 0,
								0, 0, (float)-(2 / (10 - 0.2)), (float)-((10 + 0.2) / (10 - 0.2)),
								0, 0, 0, 1	);

	camera_to_world_m.set(1.0f, 0.0f, 0.0f, 0.0f,
						  0.0f, 1.0f, 0.0f, 0.0f,
						  0.0f, 0.0f, 1.0f, 0.0f,
						  0.0f, 0.0f, 0.0f, 1.0f);
}


Camera::~Camera()
{
}

void Camera::buildView(Screen* screen){


}
