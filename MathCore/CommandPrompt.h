#pragma once
#include <string>
#include <map>
#include "IActionCmd.h"

namespace EditorInput
{

    class CommandPrompt {
    public:
        CommandPrompt();
        void processInput(std::string& input);
        void registerCommand(const std::string& command, IActionCmd* func);
    private:
        std::string currentCommand;
        struct PromptComparer {
            bool operator()(const std::string& lhs, const std::string& rhs) const {
                IActionCmd* cmdLhs = commandMap.at(lhs);
                IActionCmd* cmdRhs = commandMap.at(rhs);
                return cmdLhs->getId() < cmdRhs->getId();
            }

            static std::map<std::string, IActionCmd*> commandMap;
        };

        std::map<std::string, IActionCmd*, PromptComparer> commandMap;
        bool executeAllCommand();
    };
}

