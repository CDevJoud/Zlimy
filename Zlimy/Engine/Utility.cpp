#include "Utility.hpp"

namespace IExtreme::Engine::Ugr
{
    std::vector<size_t> ID::IDs = {};
    void Compress(std::string in, std::string& out)
    {
        std::vector<unsigned char> tempc; tempc.resize(in.size());
        z_stream ss{};

        ss.zalloc = NULL;
        ss.zfree = NULL;
        ss.opaque = NULL;

        ss.avail_in = in.length() + 1;
        ss.next_in = (Bytef*)in.data();
        ss.avail_out = (uInt)tempc.size();
        ss.next_out = (Bytef*)tempc.data();

        deflateInit(&ss, Z_DEFAULT_COMPRESSION);
        deflate(&ss, Z_FINISH);
        deflateEnd(&ss);

        for (int i = 0; i < tempc.size(); i++)
        {
            out += tempc[i];
        }
    }

    void Decompress(std::string in, std::string& out)
    {
        std::vector<unsigned char> tempc; tempc.resize(in.size());

        z_stream s;
        s.zalloc = Z_NULL;
        s.zfree = Z_NULL;
        s.opaque = Z_NULL;

        s.avail_in = in.length() + 1;
        s.next_in = (Bytef*)in.data();
        s.avail_out = (uInt)tempc.size();
        s.next_out = (Bytef*)tempc.data();

        inflateInit(&s);
        inflate(&s, Z_NO_FLUSH);
        inflateEnd(&s);

        for (int i = 0; i < tempc.size(); i++)
        {
            out += tempc[i];
        }
    }
    void CompileRecourceFile(std::string in, std::string out, const char* outFileName)
    {
        sf::Clock clock;
        Logger::Debug("Compiling Resource File");
        std::ifstream fileIn;
        fileIn.open(in);
        std::string bufferOut = "";
        if (fileIn.is_open())
        {
            std::string bufferIn = "";
            std::string line = "";
            while (std::getline(fileIn, line))
                bufferIn += line;
            Compress(bufferIn, bufferOut);
            fileIn.close();
        }
        else
            Logger::Error("Could Not Find the file to compile!");

        std::ofstream fileOut;
        fileOut.open(out + outFileName);
        if (fileOut.is_open())
            fileOut << bufferOut;
        fileOut.close();
        std::string outstr = "Done! Time it Took: " + std::to_string(clock.getElapsedTime().asSeconds()) + "";
        Logger::Info(outstr.c_str());
    }
    size_t ID::GenerateID()
    {
        size_t ID;
        ID = (rand() % (9999999999 - 1000000000 + 1)) + 1000000000;
        for(auto&i:IDs)
            if (i == ID)
            {
                ID = (rand() % (9999999999 - 1000000000 + 1)) + 1000000000;
            }
        return ID;
    }
}