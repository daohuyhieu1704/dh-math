#include "pch.h"
#include "OdHostAppService.h"

ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(OdHostAppService, OdHostAppService, OdObjectBase)

OdHostAppService::OdHostAppService()
{
    sessions = std::unordered_map<std::string, MathSessionPtr>();
    createSession("Untitled");
};