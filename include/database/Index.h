#pragma once

#include <fstream>
#include <streambuf>
#include <unordered_map>

template <typename Record>
class BinaryIndex
{
public:
    template <typename IdGetter>
    void build(const char* filename, IdGetter getId)
    {
        if (built)
        {
            return;
        }

        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            built = true;
            return;
        }

        Record record;
        while (true)
        {
            std::streampos position = file.tellg();

            if (!file.read(reinterpret_cast<char*>(&record), sizeof(Record)))
            {
                break;
            }

            if (!record.isDeleted)
            {
                positions[getId(record)] = static_cast<std::streamoff>(position);
            }
        }

        built = true;
    }

    bool find(int id, std::streamoff& position) const
    {
        auto result = positions.find(id);
        if (result == positions.end())
        {
            return false;
        }

        position = result->second;
        return true;
    }

    bool contains(int id) const
    {
        return positions.find(id) != positions.end();
    }

    void add(int id, std::streamoff position)
    {
        positions[id] = position;
    }

    void remove(int id)
    {
        positions.erase(id);
    }

private:
    std::unordered_map<int, std::streamoff> positions;
    bool built = false;
};