#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>

class OdObjectBase {
private:
    std::string m_objectId = "";
public:
    OdObjectBase() : m_objectId(GenerateShortId()) {}
    virtual ~OdObjectBase() {}

#pragma region Properties
    std::string GetObjectId() const;
#pragma endregion
    static std::string GenerateShortId();
    virtual OdObjectBase* Clone() const = 0;
};

typedef std::shared_ptr<OdObjectBase> FmObjectBasePtr;

class ObjectBaseFactory {
public:
    using CreatorFunc = std::function<std::shared_ptr<OdObjectBase>()>;

    static ObjectBaseFactory& Instance();

    template<typename T>
    void RegisterType(const std::string& type);

    std::shared_ptr<OdObjectBase> CreateObject(const std::string& type) const;

private:
    std::unordered_map<std::string, CreatorFunc> creators;
    ObjectBaseFactory() = default;
    ObjectBaseFactory(const ObjectBaseFactory&) = delete;
    ObjectBaseFactory& operator=(const ObjectBaseFactory&) = delete;
};

template<typename T>
inline void ObjectBaseFactory::RegisterType(const std::string& type) {
    creators[type] = []() -> std::shared_ptr<OdObjectBase> {
        return std::make_shared<T>();
        };
}
