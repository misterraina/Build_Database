#pragma once

#include "Index.h"
#include "FreeList.h"

#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

// Generic storage engine for a single "table" of fixed-size binary records.
//
// This class is the single place that implements insert/update/remove/find/scan
// against a binary data file, a free-list file, and an in-memory id index. It
// replaces what used to be a hand-written StudentDb/TeacherDb/CourseDb/... pair
// per entity: any POD struct with an `int` id field and a `bool isDeleted` field
// can be plugged in as `Record` without writing any new storage code.
template <typename Record>
class Table
{
public:
    using IdGetter = std::function<int(const Record&)>;

    Table(std::string dataFile, std::string freeFile, std::string label, IdGetter getId)
        : dataFile_(std::move(dataFile))
        , freeFile_(std::move(freeFile))
        , label_(std::move(label))
        , getId_(std::move(getId))
    {
    }

    bool insert(Record record)
    {
        ensureIndexBuilt();

        int id = getId_(record);
        if (index_.contains(id))
        {
            std::cerr << label_ << " ID already exists: " << id << std::endl;
            return false;
        }

        std::fstream file(dataFile_, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file for writing: " << dataFile_ << std::endl;
            return false;
        }

        std::optional<std::streamoff> freePosition = FreeList::pop(freeFile_);
        if (freePosition.has_value())
        {
            file.seekp(*freePosition);
            file.write(reinterpret_cast<const char*>(&record), sizeof(Record));
            index_.add(id, *freePosition);
            return true;
        }

        file.seekp(0, std::ios::end);
        std::streampos position = file.tellp();
        file.write(reinterpret_cast<const char*>(&record), sizeof(Record));
        index_.add(id, static_cast<std::streamoff>(position));
        return true;
    }

    bool update(int id, Record updated)
    {
        ensureIndexBuilt();

        std::streamoff position;
        if (!index_.find(id, position))
        {
            std::cerr << label_ << " not found: " << id << std::endl;
            return false;
        }

        int updatedId = getId_(updated);
        if (updatedId != id && index_.contains(updatedId))
        {
            std::cerr << label_ << " ID already exists: " << updatedId << std::endl;
            return false;
        }

        std::fstream file(dataFile_, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file for reading/writing: " << dataFile_ << std::endl;
            return false;
        }

        file.seekp(position);
        file.write(reinterpret_cast<const char*>(&updated), sizeof(Record));
        index_.remove(id);
        index_.add(updatedId, position);
        return true;
    }

    bool remove(int id)
    {
        ensureIndexBuilt();

        std::streamoff position;
        if (!index_.find(id, position))
        {
            std::cerr << label_ << " not found: " << id << std::endl;
            return false;
        }

        std::fstream file(dataFile_, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file for reading/writing: " << dataFile_ << std::endl;
            return false;
        }

        Record record;
        file.seekg(position);
        file.read(reinterpret_cast<char*>(&record), sizeof(Record));
        record.isDeleted = true;
        file.seekp(position);
        file.write(reinterpret_cast<const char*>(&record), sizeof(Record));
        FreeList::push(freeFile_, position);
        index_.remove(id);
        return true;
    }

    std::optional<Record> findById(int id)
    {
        ensureIndexBuilt();

        std::streamoff position;
        if (!index_.find(id, position))
        {
            return std::nullopt;
        }

        std::ifstream file(dataFile_, std::ios::binary);
        if (!file.is_open())
        {
            return std::nullopt;
        }

        Record record;
        file.seekg(position);
        file.read(reinterpret_cast<char*>(&record), sizeof(Record));
        return record;
    }

    std::vector<Record> scanAll()
    {
        std::vector<Record> results;

        std::ifstream file(dataFile_, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file for reading: " << dataFile_ << std::endl;
            return results;
        }

        Record record;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(Record)))
        {
            if (!record.isDeleted)
            {
                results.push_back(record);
            }
        }

        return results;
    }

private:
    void ensureIndexBuilt()
    {
        if (indexBuilt_)
        {
            return;
        }

        index_.build(dataFile_.c_str(), getId_);
        indexBuilt_ = true;
    }

    std::string dataFile_;
    std::string freeFile_;
    std::string label_;
    IdGetter getId_;
    BinaryIndex<Record> index_;
    bool indexBuilt_ = false;
};
