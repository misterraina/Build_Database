#include "../../include/database/FreeList.h"

std::vector<std::streamoff> FreeList::load(const std::string& filename)
{
    std::vector<std::streamoff> positions;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        return positions;
    }

    std::streamoff position = 0;
    while (file.read(reinterpret_cast<char*>(&position), sizeof(std::streamoff)))
    {
        positions.push_back(position);
    }

    return positions;
}

void FreeList::save(const std::string& filename, const std::vector<std::streamoff>& positions)
{
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file.is_open())
    {
        return;
    }

    for (std::streamoff position : positions)
    {
        file.write(reinterpret_cast<const char*>(&position), sizeof(std::streamoff));
    }
}

void FreeList::push(const std::string& filename, std::streamoff position)
{
    std::vector<std::streamoff> positions = load(filename);
    positions.push_back(position);
    save(filename, positions);
}

std::optional<std::streamoff> FreeList::pop(const std::string& filename)
{
    std::vector<std::streamoff> positions = load(filename);
    if (positions.empty())
    {
        return std::nullopt;
    }

    std::streamoff position = positions.back();
    positions.pop_back();
    save(filename, positions);
    return position;
}
