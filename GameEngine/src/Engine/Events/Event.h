#pragma once

#include <fstream>
#include <functional>

class Event
{
public:
	virtual void Handle() = 0;
private:
};