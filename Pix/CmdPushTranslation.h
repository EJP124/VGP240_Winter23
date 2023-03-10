#pragma once

#include "Command.h"

class CmdPushTranslation : public Command
{
public:
	const char* GetName() override
	{
		return "PushTranslation";
	}

	const char* GetDescription() override
	{
		return
			"Push"
			"\n"
			"- Draws a single pixel at position (x, y).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

