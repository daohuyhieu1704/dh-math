#pragma once
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <stack>
#include "IActionCmd.h"

namespace EditorInput {

    class CommandPrompt : public OdObjectBase {
    public:
        ODBASE_DECLARE_MEMBERS(CommandPrompt);
        CommandPrompt();

        bool processInput(std::string& input);
        void registerCommand(const std::string& command, IActionCmdPtr func);
        void appendCommand(const std::string& input);
        void appendPrompt(const std::string& input);
        IActionCmdPtr getCommand(const std::string& command);

        int historySize() const;
        std::vector<std::string> getHistory() const;
        void removeLast(int total);
        bool executeAllPrompts();

        void undo();
        void redo();

        static std::vector<std::string> split(const std::string& str);
        static std::vector<std::string> split(const std::string& str, char delimiter);
    private:

        void saveStateForUndo();

        std::map<std::string, IActionCmdPtr> commandMap;
        std::vector<std::string> History;
        std::stack<std::string> undoStack;
        std::stack<std::string> redoStack;

        // Inherited via OdObjectBase
        void addRef() override;
        void release() override;
    };

    typedef OdSmartPtr<CommandPrompt> CommandPromptPtr;
}