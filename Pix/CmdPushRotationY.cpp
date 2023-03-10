#include "CmdPushRotationY.h"
#include  "MatrixStack.h"
#include "VariableCache.h"


bool CmdPushRotationY::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;

	auto vc = VariableCache::Get();
	float y = vc->GetFloat(params[0]) * 3.1416f / 180.0f;

	MatrixStack::Get()->PushRotationY(y);
	return true;
}