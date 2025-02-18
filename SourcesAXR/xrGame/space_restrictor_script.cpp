#include "pch_script.h"

#include "SamZone.h"
#include "space_restrictor.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CSpaceRestrictor::script_register(lua_State *L)
{
	module(L)
	[
		class_<CSpaceRestrictor,CGameObject>("CSpaceRestrictor")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CSpaceRestrictor, CObjectScript);
