#pragma once

#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName();

	const char* GetDescription();

	bool Execute(const std::vector<std::string>& params);
};