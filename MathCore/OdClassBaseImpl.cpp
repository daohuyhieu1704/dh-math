#include "pch.h"
#include "OdClassBaseImpl.h"
#include "OdObjectBase.h"
#include "OdBaseAttributeCollection.h"

// Constructor
OdClassBaseImpl::OdClassBaseImpl()
    : m_pseudoConstructor(nullptr), m_parent(nullptr), m_proxyFlags(0), m_customFlags(0) {}

// Destructor
OdClassBaseImpl::~OdClassBaseImpl() {}

OdClassBase* OdClassBaseImpl::isA() const
{
	return nullptr;
}

OdObjectBase* OdClassBaseImpl::queryX(const OdClassBase* pClass) const
{
	return nullptr;
}

// Adds a protocol extension
OdObjectBasePtr OdClassBaseImpl::addX(OdClassBase* pProtocolClass, OdObjectBase* pProtocolObject) {
    if (pProtocolClass && pProtocolObject) {
        m_extensions[pProtocolClass] = pProtocolObject;
        return OdObjectBasePtr(pProtocolObject);
    }
    return nullptr;
}

// Gets the protocol extension for the specified class
OdObjectBasePtr OdClassBaseImpl::getX(const OdClassBase* pProtocolClass) {
    auto it = m_extensions.find(pProtocolClass);
    if (it != m_extensions.end()) {
        return OdObjectBasePtr(it->second);
    }
    return nullptr;
}

// Deletes the protocol extension for the specified class
OdObjectBasePtr OdClassBaseImpl::delX(OdClassBase* pProtocolClass) {
    auto it = m_extensions.find(pProtocolClass);
    if (it != m_extensions.end()) {
        OdObjectBasePtr result = OdObjectBasePtr(it->second);
        m_extensions.erase(it);
        return result;
    }
    return nullptr;
}

// Creates a new instance of the class using the pseudo-constructor
OdObjectBasePtr OdClassBaseImpl::create() const {
    if (m_pseudoConstructor) {
        return m_pseudoConstructor();
    }
    return nullptr;
}

// Returns the application name for the class
const std::string OdClassBaseImpl::appName() const {
    return m_appName;
}

// Returns the DXF class name for the class
const std::string OdClassBaseImpl::dxfName() const {
    return m_dxfName;
}

// Returns the class name for the class
const std::string OdClassBaseImpl::name() const {
    return m_className;
}

// Returns the proxy flags for the class
OdUInt32 OdClassBaseImpl::proxyFlags() const {
    return m_proxyFlags;
}

// Checks if the class is derived from the specified class
bool OdClassBaseImpl::isDerivedFrom(const OdClassBase* pClass) const {
    const OdClassBase* current = m_parent;
    while (current) {
        if (current == pClass) {
            return true;
        }
        current = current->m_pImpl->m_parent;
    }
    return false;
}

// Returns the parent class
OdClassBase* OdClassBaseImpl::myParent() const {
    return m_parent;
}

// Returns the pseudo-constructor function pointer
OdPseudoConstructorType OdClassBaseImpl::constructor() const {
    return m_pseudoConstructor;
}

// Sets the pseudo-constructor function pointer
void OdClassBaseImpl::setConstructor(OdPseudoConstructorType pseudoConstr) {
    m_pseudoConstructor = pseudoConstr;
}

// Returns the custom flags for the class
OdUInt32 OdClassBaseImpl::customFlags() const {
    return m_customFlags;
}

// Returns the attribute collection (const version)
const OdBaseAttributeCollection& OdClassBaseImpl::attributes() const {
    return m_attributes;
}

// Returns the attribute collection (non-const version)
OdBaseAttributeCollection& OdClassBaseImpl::attributes() {
    return m_attributes;
}

AppNameChangeFuncPtr OdClassBaseImpl::appNameCallbackPtr() const
{
	return m_appNameCallback;
}

void exampleAppNameChange(const OdClassBase* classObj, std::string& newAppName, int saveVer)
{
    if (saveVer >= 2024) {
        newAppName = "NewAppName_2024";
    }
    else {
        newAppName = "LegacyAppName";
    }
}
