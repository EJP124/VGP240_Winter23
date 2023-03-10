#include "CmdVertex.h"
#include "PrimitivesManager.h"

const char* CmdVertex::GetName()
{
	return "Vertex";
}

const char* CmdVertex::GetDescription()
{
	return "Vertex(x, y)\n"
		"Vertex(x, y, x)\n"
		"Vertex(x, y, r, g, b)\n"
		"Vertex(x, y, z, r, g, b)\n"
		"\n"
		"-adds a Vertex to the primitives manager";

}

bool CmdVertex::Execute(const std::vector<std::string>& params)
{	
	Vertex v;
	v.color.w = 1.0f;

	if (params.size() == 2) //x, y
	{
		v.pos.x = stof(params[0]);
		v.pos.y = stof(params[1]);
	}
	else if (params.size() == 3)
	{
		v.pos.x = stof(params[0]);
		v.pos.y = stof(params[1]);
		v.pos.z = stof(params[2]);
	}
	else if (params.size() == 5)
	{
		v.pos.x = stof(params[0]);
		v.pos.y = stof(params[1]);
		v.color.r = stof(params[2]);
		v.color.g = stof(params[3]);
		v.color.b = stof(params[4]);
	}
	else if (params.size() == 6)
	{
		v.pos.x = stof(params[0]);
		v.pos.y = stof(params[1]);
		v.pos.z = stof(params[2]);
		v.color.r = stof(params[3]);
		v.color.g = stof(params[4]);
		v.color.b = stof(params[5]);
	}
	else
	{
		return false;
	}

	

	PrimitivesManager::Get()->AddVertex(v);
	return true;
}
