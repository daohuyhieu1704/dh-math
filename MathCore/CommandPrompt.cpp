#include "pch.h"
#include "CommandPrompt.h"
#include <stdexcept>
#include <iostream>

namespace EditorInput
{
	CommandPrompt::CommandPrompt()
	{
		commandMap = std::map<std::string, IActionCmd*>();
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
		commandMap[command]->execute();
	}
	void CommandPrompt::registerCommand(const std::string& command, IActionCmd* func)
	{
		auto& commandMap = this->commandMap;
		try {
			if (func == nullptr)
			{
				throw std::runtime_error("Command function is null");
			}
			if (commandMap.find(command) != commandMap.end())
			{
				throw std::runtime_error("Command already exists");
			}
			commandMap.insert(std::make_pair(command, func));
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}


	void CommandPrompt::appendCommand(const std::string& input)
	{
		std::string inputCopy = input;
		processInput(inputCopy);
		History.push_back(input);
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
