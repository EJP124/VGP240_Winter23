#pragma once

#include "Command.h"

class CmdSetMaterialAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialAmbient";
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

class CmdSetMaterialDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialDiffuse";
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

class CmdSetMaterialSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialSpecular";
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

class CmdSetShininess : public Command
{
public:
	const char* GetName() override
	{
		return "SetShininess";
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


