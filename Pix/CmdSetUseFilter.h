#pragma once

#include "Command.h"


class CmdSetUseFilter : public Command
{

public: 

	const char* GetName()
	{
		return "SetUseFilter";
	}
	const char* GetDescription()
	{
		return "SetUseFilter sets the filter";
	}

	bool Execute(const std::vector<std::string>& params);

};