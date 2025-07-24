#pragma once

#include <string>
#include <vector>
#include <fstream>

struct CacheEntry
{
	dword fileSize;
	std::string filename;
	std::string cachename;
};

class SharedCache
{
	public:
		bool LoadDir(const std::string& eveDir);
		void SaveFile(const CacheEntry& file, const CString& path, bool folder = false);

		std::vector<CacheEntry> index;
		std::vector<std::unique_ptr<std::ifstream>> handles;
};