#include "pch.h"
#include "DbObject.h"

OdDbObject* MathCore::DbObject::GetImpObj()
{
	return static_cast<OdDbObject*>(Drawable::GetImpObj());
}

String^ MathCore::DbObject::Json::get()
{
    nlohmann::json json = GetImpObj()->ToJson();
    std::string jsonString = json.dump();
    return gcnew System::String(jsonString.c_str());
}
