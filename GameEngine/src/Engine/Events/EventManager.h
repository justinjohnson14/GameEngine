#pragma once

#include "Event.h"

#include <queue>

class EventManager
{
public:
	std::queue<Event*> GetQueue() { return queue; }
	void Push(Event* e)
	{
		queue.push(e);
	}
	static EventManager* Get() { return s_Instance; }
	void Pop() { queue.pop(); }
public:
	static EventManager* s_Instance;
	std::queue<Event*> queue;
};