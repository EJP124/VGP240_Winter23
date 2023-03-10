#include "CmdSetUseFilter.h"

#include "VariableCache.h"
#include "TextureCache.h"

bool CmdSetUseFilter::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;
	bool useFilter = VariableCache::Get()->GetBool(params[0]);
	TextureCache::Get()->SetUseFilter(useFilter);
	return true;
}
