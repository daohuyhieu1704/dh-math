#include "pch.h"
#include "ObjectBase.h"
#include "OdError_NotThatKindOfClass.h"
#include "OdClassBaseImpl.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <ctime>
#include <string>

// Initialize the static member
OdClassBase* OdObjectBase::g_pDesc = nullptr;

std::string OdObjectBase::GetObjectId() const
{
    return m_objectId;
}

std::string OdObjectBase::GenerateShortId()
{
    std::time_t t = std::time(nullptr);
    std::mt19937 rng(static_cast<unsigned int>(t));
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 15);

    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << (t & 0xFFFFFFF);

    for (int i = 0; i < 2; ++i) {
        ss << std::hex << dist(rng);
    }

    return ss.str().substr(0, 8);
}

// Destructor
OdObjectBase::~OdObjectBase() {}

// Implementation of queryX
OdObjectBase* OdObjectBase::queryX(const OdClassBase* pClass) const {
    if (pClass && isKindOf(pClass)) {
        // If the class matches, return this object
        return const_cast<OdObjectBase*>(this);
    }
    // If not, return nullptr
    return nullptr;
}

// Implementation of x
OdObjectBase* OdObjectBase::x(const OdClassBase* pClass) const {
    if (!pClass) {
        throw std::invalid_argument("Invalid input: pClass is null.");
    }

    OdObjectBase* result = queryX(pClass);
    if (!result) {
        throw OdError_NotThatKindOfClass(desc(), pClass);
    }

    return result;
}

// Implementation of desc
OdClassBase* OdObjectBase::desc() {
    return g_pDesc;
}

// Implementation of isA
OdClassBase* OdObjectBase::isA() const {
    return g_pDesc;
}

// Implementation of numRefs
long OdObjectBase::numRefs() const {
    return 1; // Default implementation. Derived classes should override.
}

// Implementation of clone (default implementation)
OdPrObjectPtr OdObjectBase::clone() const {
    throw OdError(eNotApplicable);
}

// Implementation of copyFrom (default implementation)
void OdObjectBase::copyFrom(const OdObjectBase* pSource) {
    if (!pSource) {
        throw OdError(eInvalidInput);
    }
    throw OdError(eNotApplicable);
}

// Implementation of comparedTo (default implementation)
OdPr::Ordering OdObjectBase::comparedTo(const OdObjectBase* pOther) const {
    return OdPr::kNotOrderable;
}

// Implementation of isEqualTo (default implementation)
bool OdObjectBase::isEqualTo(const OdObjectBase* pOther) const {
    return this == pOther;
}

// Constructor that initializes m_pImpl with the provided implementation
OdClassBase::OdClassBase(OdClassBaseImpl* impl) : m_pImpl(impl) {}

OdClassBase::OdClassBase() : m_pImpl(new OdClassBaseImpl()) {}

OdClassBase::~OdClassBase() {
    delete m_pImpl;
}

// Implementation of addX: Adds a protocol extension to the class
OdPrObjectPtr OdClassBase::addX(OdClassBase* pProtocolClass, OdObjectBase* pProtocolObject) {
    if (m_pImpl) {
        return m_pImpl->addX(pProtocolClass, pProtocolObject);
    }
    return nullptr;
}

// Implementation of getX: Gets the protocol extension for the specified protocol class
OdPrObjectPtr OdClassBase::getX(const OdClassBase* pProtocolClass) {
    if (m_pImpl) {
        return m_pImpl->getX(pProtocolClass);
    }
    return nullptr;
}

// Implementation of delX: Deletes the protocol extension for the specified protocol class
OdPrObjectPtr OdClassBase::delX(OdClassBase* pProtocolClass) {
    if (m_pImpl) {
        return m_pImpl->delX(pProtocolClass);
    }
    return nullptr;
}

// Implementation of create: Creates a new instance of the class using the pseudo-constructor
OdPrObjectPtr OdClassBase::create() const {
    if (m_pImpl) {
        return m_pImpl->create();
    }
    return nullptr;
}

// Implementation of appName: Returns the application name for the class
const std::string OdClassBase::appName() const {
    if (m_pImpl) {
        return m_pImpl->appName();
    }
    return std::string();
}

// Implementation of appNameCallbackPtr: Returns the application name callback function pointer
AppNameChangeFuncPtr OdClassBase::appNameCallbackPtr() const {
    if (m_pImpl) {
        return m_pImpl->appNameCallbackPtr();
    }
    return nullptr;
}

// Implementation of dxfName: Returns the DXF class name for the class
const std::string OdClassBase::dxfName() const {
    if (m_pImpl) {
        return m_pImpl->dxfName();
    }
    return std::string();
}

// Implementation of name: Returns the class name for the class
const std::string OdClassBase::name() const {
    if (m_pImpl) {
        return m_pImpl->name();
    }
    return std::string();
}

// Implementation of proxyFlags: Returns the proxy flags for the class
OdUInt32 OdClassBase::proxyFlags() const {
    if (m_pImpl) {
        return m_pImpl->proxyFlags();
    }
    return 0;
}

// Implementation of isDerivedFrom: Checks if the class is derived from the specified class
bool OdClassBase::isDerivedFrom(const OdClassBase* pClass) const {
    if (m_pImpl) {
        return m_pImpl->isDerivedFrom(pClass);
    }
    return false;
}

// Implementation of myParent: Returns the parent class of this class
OdClassBase* OdClassBase::myParent() const {
    if (m_pImpl) {
        return m_pImpl->myParent();
    }
    return nullptr;
}

// Implementation of constructor: Returns the pseudo-constructor function pointer
OdPseudoConstructorType OdClassBase::constructor() {
    if (m_pImpl) {
        return m_pImpl->constructor();
    }
    return nullptr;
}

// Implementation of setConstructor: Sets the pseudo-constructor function pointer
void OdClassBase::setConstructor(OdPseudoConstructorType pseudoConstr) {
    if (m_pImpl) {
        m_pImpl->setConstructor(pseudoConstr);
    }
}

// Implementation of customFlags: Returns the custom flags for the class
OdUInt32 OdClassBase::customFlags() const {
    if (m_pImpl) {
        return m_pImpl->customFlags();
    }
    return 0;
}

// Implementation of attributes (const): Returns the attribute collection for the class (const version)
const OdBaseAttributeCollection& OdClassBase::attributes() const {
    if (m_pImpl) {
        return m_pImpl->attributes();
    }
    // Return an empty instance if m_pImpl is null
    static OdBaseAttributeCollection emptyAttributes;
    return emptyAttributes;
}

// Implementation of attributes (non-const): Returns the attribute collection for the class (non-const version)
OdBaseAttributeCollection& OdClassBase::attributes() {
    if (m_pImpl) {
        return m_pImpl->attributes();
    }
    // Return a static empty instance if m_pImpl is null
    static OdBaseAttributeCollection emptyAttributes;
    return emptyAttributes;
}