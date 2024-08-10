#pragma once
#include <unordered_map>
#include <memory>
#include "MathSession.h"

class OdHostAppService
{
public:
    static OdHostAppService* getInstance() {
		static OdHostAppService instance;
		return &instance;
    }

    std::shared_ptr<MathSession> createSession(const std::string& sessionId) {
		if (sessions.find(sessionId) != sessions.end()) {
			return sessions[sessionId];
		}
        auto session = std::make_shared<MathSession>();
        sessions[sessionId] = session;
		currentSessionId = sessionId;
        return session;
    }

    std::shared_ptr<MathSession> getSession(const std::string& sessionId) {
        if (sessions.find(sessionId) != sessions.end()) {
            return sessions[sessionId];
        }
        return nullptr;
    }

    void ChangeCurrSession(const std::string filePath) {
		if (sessions.find(filePath) != sessions.end()) {
			currentSessionId = filePath;
		}
    }
    void removeSession(const std::string& sessionId) {
        sessions.erase(sessionId);
    }

    std::shared_ptr<MathSession> getCurrentSession() {
		return getSession(currentSessionId);
	}

	void ExecuteAllPrompts() {
		getCurrentSession()->ExecuteAllPrompts();
	}

private:
    OdHostAppService()
    {
		sessions = std::unordered_map<std::string, std::shared_ptr<MathSession>>();
        createSession("Untitled");
    };
    ~OdHostAppService() = default;
    OdHostAppService(const OdHostAppService&) = delete;
    OdHostAppService& operator=(const OdHostAppService&) = delete;

    std::unordered_map<std::string, std::shared_ptr<MathSession>> sessions;
	std::string currentSessionId;
};

