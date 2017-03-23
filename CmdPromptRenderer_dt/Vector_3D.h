#pragma once

class Vector_3D
{
public:	
	Vector_3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	~Vector_3D();


	void set(float x, float y, float z) {_x = x; _y = y;  _z = z;}
	float x() { return _x; }
	void x(float x) { _x = x; }
	float y() { return _y; }
	void y(float y) { _y = y; }
	float z() { return _z; }
	void z(float z) { _z = z; }

private:
	float _x, _y, _z;
};

