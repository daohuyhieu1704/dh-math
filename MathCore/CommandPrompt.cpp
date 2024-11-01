#include "pch.h"
#include "CommandPrompt.h"
#include <stdexcept>
#include <iostream>

namespace EditorInput {
    
	ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(CommandPrompt, CommandPrompt, OdObjectBase);

    CommandPrompt::CommandPrompt()
    {
        commandMap = std::map<std::string, IActionCmdPtr>();
    }

    std::vector<std::string> CommandPrompt::split(const std::string& str) {
        std::istringstream iss(str);
        std::vector<std::string> result;
        std::string word;

        while (iss >> word) {
            result.push_back(word);
        }

        return result;
    }

    std::vector<std::string> CommandPrompt::split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    bool CommandPrompt::processInput(std::string& input) {
        auto words = split(input);
        if (words.empty()) {
            return false;
        }

        auto& command = words[0];
        if (commandMap.find(command) == commandMap.end()) {
            throw std::runtime_error("Command not found");
        }

        bool validSerialize = commandMap[command]->serialize(words);
		if (!validSerialize) {
			return false;
		}
        return commandMap[command]->execute();
    }

    void CommandPrompt::registerCommand(const std::string& command, IActionCmdPtr func) {
        if (func == nullptr) {
            throw std::runtime_error("Command function is null");
        }
        if (commandMap.find(command) != commandMap.end()) {
            throw std::runtime_error("Command already exists");
        }
        commandMap.insert(std::make_pair(command, func));
    }

    void CommandPrompt::appendCommand(const std::string& input) {
        std::string inputCopy = input;
        if (processInput(inputCopy))
		{
			History.push_back(input);
			saveStateForUndo();
			redoStack = std::stack<std::string>();
		}
    }

    void CommandPrompt::appendPrompt(const std::string& input) {
        std::string inputCopy = input;
        if (processInput(inputCopy))
        {
            History.push_back(input);
            saveStateForUndo();
            redoStack = std::stack<std::string>();
        }
    }

    IActionCmdPtr CommandPrompt::getCommand(const std::string& command)
    {
		if (commandMap.find(command) == commandMap.end()) {
			return IActionCmdPtr();
		}
		return commandMap[command];
    }

    int CommandPrompt::historySize() const {
        return History.size();
    }

    std::vector<std::string> CommandPrompt::getHistory() const {
        return History;
    }

    void CommandPrompt::removeLast(int total) {
        if (total > History.size()) {
            History.clear();
        }
        else {
            History.erase(History.end() - total, History.end());
        }
    }

    void CommandPrompt::undo() {
        if (!undoStack.empty()) {
            redoStack.push(History.back());
            History.pop_back();
            undoStack.pop();
        }
    }

    void CommandPrompt::redo() {
        if (!redoStack.empty()) {
            History.push_back(redoStack.top());
            redoStack.pop();
			undoStack.push(History.back());
        }
    }

    bool CommandPrompt::executeAllPrompts() {
        for (auto& prompt : History)
        {
			processInput(prompt);
        }
        return true;
    }

    void CommandPrompt::saveStateForUndo() {
        if (!History.empty()) {
            undoStack.push(History.back());
        }
    }
    void CommandPrompt::addRef()
    {
    }
    void CommandPrompt::release()
    {
    }
}
