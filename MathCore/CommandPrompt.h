#pragma once
#include <string>
#include <map>
#include "IActionCmd.h"
#include <sstream>

namespace EditorInput
{

    class CommandPrompt {
    public:
        static std::vector<std::string> split(const std::string& str) {
            std::istringstream iss(str);
            std::vector<std::string> result;
            std::string word;

            while (iss >> word) {
                result.push_back(word);
            }

            return result;
        }

        static std::vector<std::string> split(const std::string& str, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(str);
            while (std::getline(tokenStream, token, delimiter)) {
                tokens.push_back(token);
            }
            return tokens;
        }

        CommandPrompt();
        void processInput(std::string& input);
        void registerCommand(const std::string& command, IActionCmd* func);
        void appendCommand(const std::string& input);
		IActionCmd* getCommand(const std::string& command) {
			return commandMap.at(command);
		}
        std::map<std::string, IActionCmd*> commandMap;
    private:
        std::string currentCommand;
        std::vector<std::string> History;
        bool executeAllCommand();
    };
}

