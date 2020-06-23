#pragma once

#include "Event.h"
#include <sstream>

#include <iostream>

class KeyEvent : public Event
{
public:
	virtual void Handle() = 0;
};

class KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(int key, int scancode, int action, int mods, bool repeat)
		: m_Keycode(key), m_Action(action), m_Mods(mods)
	{

	}

	void Handle()
	{
		//this is the keypress does something
		if (!m_Handled)
		{
			std::cout << "Key pressed: keycode(" << m_Keycode << "), action(" << m_Action << "), mods(" << m_Mods << ")\n";
			m_Handled = true;
		}
	}
private:
	int m_Keycode, m_Action, m_Mods;
	bool m_Handled = false;
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(int key, int scancode, int action, int mods, bool repeat)
		: m_Keycode(key), m_Action(action), m_Mods(mods)
	{

	}

	void Handle()
	{
		if (!m_Handled)
		{
			std::cout << "Key pressed: keycode(" << m_Keycode << "), action(" << m_Action << "), mods(" << m_Mods << ")\n";
			m_Handled = true;
		}
	}
private:
	int m_Keycode, m_Action, m_Mods;
	bool m_Handled = false;
};