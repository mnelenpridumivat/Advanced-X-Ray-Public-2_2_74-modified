#include "pch_script.h"
#include "console_registrator.h"
#include "../xrEngine/xr_ioconsole.h"
#include "../xrEngine/xr_ioc_cmd.h"

using namespace luabind;

CConsole*	console()
{
	return Console;
}

int get_console_integer( CConsole* c, LPCSTR cmd )
{
	int min = 0, max = 0;
	int val = c->GetInteger ( cmd, min, max );
	return val;
}

float get_console_float( CConsole* c, LPCSTR cmd )
{
	float min = 0.0f, max = 0.0f;
	float val = c->GetFloat ( cmd, min, max );
	return val;
}

bool get_console_bool( CConsole* c, LPCSTR cmd )
{
	return c->GetBool( cmd );
}

void execute_console_command_deferred	(CConsole* c, LPCSTR string_to_execute)
{
	Engine.Event.Defer	("KERNEL:console", size_t(xr_strdup(string_to_execute)) );
}

IConsole_Command* find_cmd(CConsole* c, LPCSTR cmd)
{
	CConsole::vecCMD_IT I = c->Commands.find(cmd);
	IConsole_Command* icmd = nullptr;

	if (I != c->Commands.end())
		icmd = I->second;

	return icmd;
}

void disable_cmd(CConsole* c, LPCSTR cmd)
{
	IConsole_Command* icmd = find_cmd(c, cmd);
	if (icmd)
		icmd->SetEnabled(false);
}

void enable_cmd(CConsole* c, LPCSTR cmd)
{
	IConsole_Command* icmd = find_cmd(c, cmd);
	if (icmd)
		icmd->SetEnabled(true);
}

#pragma optimize("s",on)
void console_registrator::script_register(lua_State *L)
{
	module(L)
	[
		def("get_console",					&console),

		class_<CConsole>("CConsole")
			.def("disable_command",			&disable_cmd)
			.def("enable_command",			&enable_cmd)
			.def("execute",					&CConsole::Execute)
			.def("execute_script",			&CConsole::ExecuteScript)
			.def("show",					&CConsole::Show)
			.def("hide",					&CConsole::Hide)

			.def("get_string",				&CConsole::GetString)
			.def("get_integer",				&get_console_integer)
			.def("get_bool",				&get_console_bool)
			.def("get_float",				&get_console_float)
			.def("get_token",				&CConsole::GetToken)
			.def("execute_deferred",		&execute_console_command_deferred)
	];
}

SCRIPT_EXPORT1(console_registrator);