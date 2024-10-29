#pragma once
#include "OdObjectBase.h"
#include "OdBaseAttributeCollection.h"
#include <string>
#include <unordered_map>

/// <summary>
/// This is example App name change function
/// </summary>
/// <param name="classObj"></param>
/// <param name="newAppName"></param>
/// <param name="saveVer"></param>
void exampleAppNameChange(const OdClassBase* classObj, std::string& newAppName, int saveVer);

class OdClassBaseImpl {
public:
    OdClassBaseImpl();
    ~OdClassBaseImpl();
	OdClassBase* isA() const;
	OdObjectBase* queryX(const OdClassBase* pClass) const;
    OdObjectBasePtr addX(OdClassBase* pProtocolClass, OdObjectBase* pProtocolObject);
    OdObjectBasePtr getX(const OdClassBase* pProtocolClass);
    OdObjectBasePtr delX(OdClassBase* pProtocolClass);
    OdObjectBasePtr create() const;

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
    AppNameChangeFuncPtr m_appNameCallback;
    OdPseudoConstructorType m_pseudoConstructor;
    OdBaseAttributeCollection m_attributes;
};