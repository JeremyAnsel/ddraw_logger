#include "common.h"
#include "wrapper.h"

#include <unordered_map>
#include <unordered_set>

std::unordered_map<void*, void*> g_wrappersMap;
std::unordered_set<void*> g_wrappersSet;

bool IsWrapper(void* wrapper)
{
	if (wrapper == nullptr)
	{
		return false;
	}

	return g_wrappersSet.find(wrapper) != g_wrappersSet.end();
}

void* GetWrapper(void* original)
{
	return g_wrappersMap[original];
}

void AddWrapper(void* wrapper, void* original)
{
	g_wrappersSet.insert(wrapper);
	g_wrappersMap[original] = wrapper;
}

void RemoveWrapper(void* original)
{
	g_wrappersSet.erase(g_wrappersMap[original]);
	g_wrappersMap.erase(original);
}
