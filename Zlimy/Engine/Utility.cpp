#include "Utility.hpp"

namespace IExtreme::Engine::Ugr
{
    std::vector<size_t> ID::IDs = {};
    void Compress(std::string in, std::string& out)
    {
        std::vector<sf::Uint8> tempc; tempc.resize(in.size());
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

    void Compress(std::string in, std::vector<sf::Uint8>& out)
    {

        const size_t CHUNK_SIZE = 8192; // Adjust the chunk size as per your requirements

        z_stream s;
        s.zalloc = Z_NULL;
        s.zfree = Z_NULL;
        s.opaque = Z_NULL;

        deflateInit(&s, Z_DEFAULT_COMPRESSION);

        std::vector<char> inputBuffer(CHUNK_SIZE);
        std::vector<char> outputBuffer(CHUNK_SIZE);

        s.avail_in = static_cast<uInt>(in.size());
        s.next_in = reinterpret_cast<Bytef*>(in.data());

        do
        {
            s.avail_out = CHUNK_SIZE;
            s.next_out = reinterpret_cast<Bytef*>(outputBuffer.data());

            deflate(&s, Z_FINISH);

            const size_t bytesWritten = CHUNK_SIZE - s.avail_out;
            out.insert(out.end(), outputBuffer.begin(), outputBuffer.begin() + bytesWritten);
        } while (s.avail_out == 0);

        deflateEnd(&s);
    }

    void Decompress(std::string in, std::string& out)
    {
        std::vector<sf::Uint8> tempc; tempc.resize(in.size());

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
    void Decompress(std::string in, std::vector<sf::Uint8>& out)
    {
        const size_t CHUNK_SIZE = 8192; // Adjust the chunk size as per your requirements

        z_stream s;
        s.zalloc = Z_NULL;
        s.zfree = Z_NULL;
        s.opaque = Z_NULL;

        s.avail_in = in.length();
        s.next_in = (Bytef*)in.data();

        // Initialize the inflate stream
        inflateInit(&s);

        std::vector<unsigned char> buffer(CHUNK_SIZE);

        while (s.total_in < in.length())
        {
            s.avail_out = CHUNK_SIZE;
            s.next_out = buffer.data();

            // Decompress a chunk of data
            int status = inflate(&s, Z_NO_FLUSH);
            if (status != Z_OK && status != Z_STREAM_END)
            {
                inflateEnd(&s);
            }

            // Append the decompressed chunk to the output string
            out.insert(out.end(), buffer.begin(), buffer.begin() + (CHUNK_SIZE - s.avail_out));
        }

        // Finalize the inflate stream
        inflateEnd(&s);
    }
    void CompileRecourceFile(std::string in, std::string out, const char* outFileName)
    {
        sf::Clock clock;
        Logger::Debug("Compiling Resource File");
        std::ifstream fileIn;
        fileIn.open(in);
        std::vector<sf::Uint8> bufferOut;
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
        {
            for (auto& i : bufferOut)
                fileOut << i;
        }
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