#pragma once
#include "Resource.h"
class ResourceManager
{

	std::unordered_map<std::string, Resource*> resources;

public:
	static ResourceManager& get();
	ResourceManager();
	~ResourceManager();
};

