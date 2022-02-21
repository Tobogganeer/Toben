#pragma once

#include "../core.h"

class OBJLoader
{
public:
	static HeapRef<Mesh> Load(std::string& path, float scale = 1.0f)
	{
		return Load(path.c_str(), scale);
	}

	static HeapRef<Mesh> Load(const char* path, float scale = 1.0f);
};