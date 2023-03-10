#include "CmdSetCorrectUV.h"
#include "DepthBuffer.h"
#include "VariableCache.h"
#include "PrimitivesManager.h"

const char* CmdSetCorrectUV::GetName()
{
	return "SetCorrectUV";
}

const char* CmdSetCorrectUV::GetDescription()
{
	return "SetCorrectUV() enable or disable depth buffer";
}

bool CmdSetCorrectUV::Execute(const std::vector<std::string>& params)
{
	
	if (params.size() < 1) return false;

	bool enable = VariableCache::Get()->GetBool(params[0]);
	PrimitivesManager::Get()->SetCorrectUV(enable);

	return true;
}
