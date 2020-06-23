#include "ScriptEngine.h"

#include <iostream>

Script::Script(const std::string& filename)
{
	m_State = luaL_newstate();
	if (luaL_dofile(m_State, filename.c_str()) != 0)
	{
		std::cerr << "Error opening file: " << filename << "\n";
	}

	Start();
}

void Script::Start()
{
	lua_getglobal(m_State, "Start");

	if (lua_isfunction(m_State, -1))
	{
		lua_pcall(m_State, 0, 0, 0);
	}
}

void Script::FixedUpdate()
{
	lua_getglobal(m_State, "FixedUpdate");

	if (lua_isfunction(m_State, -1))
	{
		lua_pcall(m_State, 0, 0, 0);
	}
}

void Script::Update()
{
	lua_getglobal(m_State, "Update");

	if (lua_isfunction(m_State, -1))
	{
		lua_pcall(m_State, 0, 0, 0);
	}
}

void ScriptEngine::AddScript(Script* script)
{
	m_Scripts.push_back(script);
}
