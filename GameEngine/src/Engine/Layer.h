#pragma once

#include <string>

class Layer
{
public:
	Layer(const std::string&);

	virtual void Update(double) = 0;
	virtual void Input() = 0;
	virtual void Render(double) = 0;
	virtual bool MouseButtonEvent(int,int,int) = 0;
private:
	std::string m_Name;
};

