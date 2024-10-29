#pragma once
#include "OdObjectBase.h"
#include <unordered_map>
#include <memory>
#include "MathSession.h"

class OdHostAppService : public OdObjectBase
{
public:
    static OdHostAppServicePtr getInstance()
    {
        static OdHostAppServicePtr instance = OdHostAppService::createObject();
        return instance;
    }
    ODBASE_DECLARE_MEMBERS(OdHostAppService)

    MathSessionPtr createSession(const std::string& sessionId) {
		if (sessions.find(sessionId) != sessions.end()) {
			return sessions[sessionId];
		}
        auto session = MathSessionPtr();
        sessions[sessionId] = session;
		currentSessionId = sessionId;
        return session;
    }

    MathSessionPtr getSession(const std::string& sessionId) {
        if (sessions.find(sessionId) != sessions.end()) {
            return sessions[sessionId];
        }
        return MathSessionPtr();
    }

    void ChangeCurrSession(const std::string filePath) {
		if (sessions.find(filePath) != sessions.end()) {
			currentSessionId = filePath;
		}
    }
    void removeSession(const std::string& sessionId) {
        sessions.erase(sessionId);
    }

    MathSessionPtr getCurrentSession() {
		return getSession(currentSessionId);
	}

	void ExecuteAllPrompts() {
		getCurrentSession()->ExecuteAllPrompts();
	}
    void addRef() override;
    void release() override;
private:
    OdHostAppService();
    ~OdHostAppService() = default;
    OdHostAppService(const OdHostAppService&) = delete;
    OdHostAppService& operator=(const OdHostAppService&) = delete;

    std::unordered_map<std::string, MathSessionPtr> sessions;
	std::string currentSessionId;
};

typedef OdSmartPtr<OdHostAppService> OdHostAppServicePtr;