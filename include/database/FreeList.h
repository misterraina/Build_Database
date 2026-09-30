#pragma once

#include <cstddef>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

class FreeList
{
public:
    static std::vector<std::streamoff> load(const std::string& filename);
    static void save(const std::string& filename, const std::vector<std::streamoff>& positions);
    static void push(const std::string& filename, std::streamoff position);
    static std::optional<std::streamoff> pop(const std::string& filename);
};
