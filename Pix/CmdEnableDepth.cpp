#include "CmdEnableDepth.h"
#include "DepthBuffer.h"

const char* CmdEnableDepth::GetName()
{
	return "EnableDepth";
}

const char* CmdEnableDepth::GetDescription()
{
	return "EnableDepth() enable or disable depth buffer";
}

bool CmdEnableDepth::Execute(const std::vector<std::string>& params)
{
	
	if (params.size() < 1) return false;

	bool enable = params[0] == "true";
	DepthBuffer::Get()->SetEnabled(enable);

	return true;
}
