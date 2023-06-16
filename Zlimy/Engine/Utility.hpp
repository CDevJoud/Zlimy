#pragma once
#include "zlib.h"
#include <vector>
#include <string>
#include <fstream>
#include "logger.hpp"
#include <SFML/System/Clock.hpp>

namespace IExtreme::Engine::Ugr
{
	void Compress(std::string in, std::string& out);
	void Decompress(std::string in, std::string& out);
	void CompileRecourceFile(std::string in, std::string out, const char* outFileName);
	class ID
	{
	public:
		static size_t GenerateID();
	private:
		static std::vector<size_t> IDs;
	};
}