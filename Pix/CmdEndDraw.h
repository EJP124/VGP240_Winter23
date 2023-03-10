#pragma once

#include "Command.h"

class CmdEndDraw : public Command
{
public:
	const char* GetName ();

	const char* GetDescription();

	bool Execute(const std::vector<std::string>& params);
};