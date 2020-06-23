#pragma once

#include "lua.hpp"

#include <string>
#include <vector>

class Script
{
public:
	Script(const std::string&);

	void Start();
	void FixedUpdate();
	void Update();

private:
	lua_State* m_State;
};

class ScriptEngine
{
public:
	inline std::vector<Script*> GetScripts() { return m_Scripts; }
	void AddScript(Script*);
private:
	std::vector<Script*> m_Scripts;
};

