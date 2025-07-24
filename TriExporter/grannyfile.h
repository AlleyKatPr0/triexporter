#pragma once

#include "SharedCache.h"
#include "trifile.h"

class GrannyTriFile : public TriFile
{
	public:
		GrannyTriFile() = default;
		bool LoadFile(CacheEntry &sce) override;
		bool LoadFile(const std::string& filename) override;
		bool LoadFile(std::ifstream &is) override;

	private:
		static bool loadedstuff;
		static bool dllloaded;
};