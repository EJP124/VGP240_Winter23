#include "CmdBeginDraw.h"
#include "PrimitivesManager.h"


const char* CmdBeginDraw::GetName()
{
	return "BeginDraw";
}

const char* CmdBeginDraw::GetDescription()
{
	return "BeginDraw(topology) begins drawing a parimitive";
}

bool CmdBeginDraw::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1) { return false; }

	Topology topology = Topology::Point;
	if (params[0] == "point") { topology = Topology::Point; }
	else if (params[0] == "line") { topology = Topology::Line; }
	else if (params[0] == "triangle") { topology = Topology::Triangle; }
	else { return false; }

	bool applytransform = params.size() > 1 && params[1] == "true";

	return PrimitivesManager::Get()->BeginDraw(topology, applytransform);
	
}
