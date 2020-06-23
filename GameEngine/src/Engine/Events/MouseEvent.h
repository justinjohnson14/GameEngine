#include "Event.h"
#include "LayerStack.h"

class MouseEvent : public Event
{
public:
	virtual void Handle() = 0;
};

class MouseButtonEvent : public Event
{
public:
	MouseButtonEvent(int button, int action, int mods)
		: m_Button(button), m_Action(action), m_Mods(mods)
	{

	}
	void Handle()
	{
		int i = (LayerStack::Get()->GetStack().size()) - 1;
		while (!m_Handled && i >= 0)
		{
			Layer* layer = LayerStack::Get()->GetStack().at(i);
			m_Handled = layer->MouseButtonEvent(m_Button, m_Action, m_Mods);
			i--;
		}
	}
private:
	bool m_Handled = false;
	int m_Button, m_Action, m_Mods;
};