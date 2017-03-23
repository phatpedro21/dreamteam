#pragma once
class pixel
{
public:
	pixel(float depth, char icon);
	~pixel();

	float depth() {return _depth;};
	char icon() {return _icon;};

private:
	float _depth;
	char _icon;
};

