#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string&);

	unsigned int GetID() { return m_ID; }
	void Bind();
private:
	unsigned int m_ID;
};

