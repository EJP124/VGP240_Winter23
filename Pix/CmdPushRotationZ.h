#pragma once

#include "Command.h"

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}

	const char* GetDescription() override
	{
		return
			"DrawPixel(x, y)\n"
			"\n"
			"- Draws a single pixel at position (x, y).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};