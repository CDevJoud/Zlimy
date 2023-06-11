#include "Utility.hpp"

namespace IExtreme::Engine::Ugr
{
    std::vector<size_t> ID::IDs = {};
    void compress(std::string in, std::string& out)
    {
        unsigned char tempc[sizeof(in)];
        memset(tempc, 0, sizeof(tempc));
        z_stream ss;

        ss.zalloc = NULL;
        ss.zfree = NULL;
        ss.opaque = NULL;

        ss.avail_in = in.length() + 1;
        ss.next_in = (Bytef*)in.data();
        ss.avail_out = (uInt)sizeof(tempc);
        ss.next_out = (Bytef*)tempc;

        deflateInit(&ss, Z_DEFAULT_COMPRESSION);
        deflate(&ss, Z_FINISH);
        deflateEnd(&ss);

        for (int i = 0; i < sizeof(tempc); i++)
        {
            out += tempc[i];
        }
    }

    void decompress(std::string in, std::string& out)
    {
        unsigned char tempc[sizeof(in)];
        memset(tempc, 0, sizeof(tempc));

        z_stream s;
        s.zalloc = Z_NULL;
        s.zfree = Z_NULL;
        s.opaque = Z_NULL;

        s.avail_in = in.length() + 1;
        s.next_in = (Bytef*)in.data();
        s.avail_out = (uInt)sizeof(tempc);
        s.next_out = (Bytef*)tempc;

        inflateInit(&s);
        inflate(&s, Z_NO_FLUSH);
        inflateEnd(&s);

        for (int i = 0; i < sizeof(tempc); i++)
        {
            out += tempc[i];
        }
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