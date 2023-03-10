#include "CmdPushRotationZ.h"
#include  "MatrixStack.h"
#include "VariableCache.h"


bool CmdPushRotationZ::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;

	auto vc = VariableCache::Get();
	float z = vc->GetFloat(params[0]) * 3.1416 / 180;

	MatrixStack::Get()->PushRotationZ({ z });
	return true;
}