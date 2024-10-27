#pragma once
#include "ObjectBase.h"
#include "OdBaseAttributeCollection.h"
#include <string>
#include <unordered_map>

/// <summary>
/// This is example App name change function
/// </summary>
/// <param name="classObj"></param>
/// <param name="newAppName"></param>
/// <param name="saveVer"></param>
void exampleAppNameChange(const OdClassBase* classObj, std::string& newAppName, int saveVer) {
    if (saveVer >= 2024) {
        newAppName = "NewAppName_2024";
    }
    else {
        newAppName = "LegacyAppName";
    }
}

class OdClassBaseImpl {
public:
    OdClassBaseImpl();
    ~OdClassBaseImpl();

    OdPrObjectPtr addX(OdClassBase* pProtocolClass, OdObjectBase* pProtocolObject);
    OdPrObjectPtr getX(const OdClassBase* pProtocolClass);
    OdPrObjectPtr delX(OdClassBase* pProtocolClass);
    OdPrObjectPtr create() const;

    const std::string appName() const;
    const std::string dxfName() const;
    const std::string name() const;
    OdUInt32 proxyFlags() const;
    bool isDerivedFrom(const OdClassBase* pClass) const;
    OdClassBase* myParent() const;
    OdPseudoConstructorType constructor() const;
    void setConstructor(OdPseudoConstructorType pseudoConstr);
    OdUInt32 customFlags() const;
    const OdBaseAttributeCollection& attributes() const;
    OdBaseAttributeCollection& attributes();
    AppNameChangeFuncPtr appNameCallbackPtr() const;

private:
    std::unordered_map<const OdClassBase*, OdObjectBase*> m_extensions;
    std::string m_appName;
    std::string m_dxfName;
    std::string m_className;
    OdUInt32 m_proxyFlags;
    OdUInt32 m_customFlags;
    OdClassBase* m_parent;
    AppNameChangeFuncPtr m_appNameCallback = exampleAppNameChange;
    OdPseudoConstructorType m_pseudoConstructor;
    OdBaseAttributeCollection m_attributes;
};