#include "pch.h"
#include "CommandPrompt.h"
#include <sstream>
#include <stdexcept>

namespace EditorInput
{
	CommandPrompt::CommandPrompt()
	{
	}

	static std::vector<std::string> split(const std::string& str) {
		std::istringstream iss(str);
		std::vector<std::string> result;
		std::string word;

		while (iss >> word) {
			result.push_back(word);
		}

		return result;
	}

	void CommandPrompt::processInput(std::string& input)
	{
		auto words = split(input);
		if (words.size() == 0)
		{
			return;
		}

		auto& command = words[0];
		if (commandMap.find(command) == commandMap.end())
		{
			throw std::runtime_error("Command not found");
		}

		commandMap[command]->serialize(words);
	}
	void CommandPrompt::registerCommand(const std::string& command, IActionCmd* func)
	{
		if (commandMap.find(command) != commandMap.end())
		{
			throw std::runtime_error("Command already exists");
		}
		commandMap.insert(std::make_pair(command, func));
	}

	bool CommandPrompt::executeAllCommand()
	{
		for (auto& command : commandMap)
		{
			if (!command.second->execute())
			{
				return false;
			}
		}
	}
}
