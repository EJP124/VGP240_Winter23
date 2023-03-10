#include "CmdEndDraw.h"
#include "PrimitivesManager.h"

const char* CmdEndDraw::GetName()
{
	return "EndDraw";
}

const char* CmdEndDraw::GetDescription()
{
	return "EndDraw() using the verticies will draw the primitive";
}

bool CmdEndDraw::Execute(const std::vector<std::string>& params)
{
	if (params.size() > 0) { return false; }

	return PrimitivesManager::Get()->EndDraw();
}
