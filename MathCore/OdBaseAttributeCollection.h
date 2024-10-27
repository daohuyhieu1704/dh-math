#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "OdBaseAttribute.h"

class OdBaseAttribute;

class OdBaseAttributeCollection {
public:
    OdBaseAttributeCollection() = default;

    ~OdBaseAttributeCollection() = default;

    void addAttribute(OdBaseAttributePtr attribute);

    OdBaseAttributePtr getAttribute(const std::string& name) const;

    bool removeAttribute(const std::string& name);

    bool hasAttribute(const std::string& name) const;

    void clear();

    size_t size() const;

    auto begin() { return m_attributes.begin(); }
    auto end() { return m_attributes.end(); }
    auto begin() const { return m_attributes.begin(); }
    auto end() const { return m_attributes.end(); }

private:
    // Internal storage for attributes
    std::vector<OdBaseAttributePtr> m_attributes;
};
