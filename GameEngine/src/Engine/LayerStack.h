#pragma once

#include <Layer.h>
#include <vector>

class LayerStack
{
public:
	static LayerStack* Get()
	{
		return s_Instance;
	}

	std::vector<Layer*> GetStack()
	{
		return m_Layers;
	}

	void PushStack(Layer* layer)
	{
		m_Layers.push_back(layer);
	}

	void PopStack()
	{
		m_Layers.pop_back();
	}
private:
	std::vector<Layer*> m_Layers;

	static LayerStack* s_Instance;
};

