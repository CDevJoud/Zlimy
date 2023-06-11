#pragma once
#include "zlib.h"
#include <vector>
#include <string>

namespace IExtreme::Engine::Ugr
{
	void compress(std::string in, std::string& out);
	void decompress(std::string in, std::string& out);

	class ID
	{
	public:
		static size_t GenerateID();
	private:
		static std::vector<size_t> IDs;
	};
}