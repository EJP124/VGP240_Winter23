#pragma once

#include "Command.h"

class CmdSetShadeMode : public Command
{
public:
	const char* GetName()
	{
		return "SetShading";
	}
	const char* GetDescription()
	{
		return "SetShading(shadeMode) sets the triangle shade mode";
	}

	bool Execute(const std::vector<std::string>& params);
};