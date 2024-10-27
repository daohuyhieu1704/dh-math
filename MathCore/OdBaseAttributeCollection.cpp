#include "pch.h"
#include "OdBaseAttributeCollection.h"

void OdBaseAttributeCollection::addAttribute(OdBaseAttributePtr attribute) {
    if (attribute) {
        m_attributes.push_back(attribute);
    }
}

OdBaseAttributePtr OdBaseAttributeCollection::getAttribute(const std::string& name) const {
    auto it = std::find_if(m_attributes.begin(), m_attributes.end(),
        [&name](const OdBaseAttributePtr& attr) {
            return attr->name() == name;
        });
    return (it != m_attributes.end()) ? *it : nullptr;
}

bool OdBaseAttributeCollection::removeAttribute(const std::string& name) {
    auto it = std::remove_if(m_attributes.begin(), m_attributes.end(),
        [&name](const OdBaseAttributePtr& attr) {
            return attr->name() == name;
        });
    if (it != m_attributes.end()) {
        m_attributes.erase(it, m_attributes.end());
        return true;
    }
    return false;
}

bool OdBaseAttributeCollection::hasAttribute(const std::string& name) const {
    return std::any_of(m_attributes.begin(), m_attributes.end(),
        [&name](const OdBaseAttributePtr& attr) {
            return attr->name() == name;
        });
}

void OdBaseAttributeCollection::clear() {
    m_attributes.clear();
}

size_t OdBaseAttributeCollection::size() const {
    return m_attributes.size();
}