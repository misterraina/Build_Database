#pragma once

#include "../include/database/Table.h"
#include "../include/models/Student.h"
#include "../include/models/Teacher.h"
#include "../include/models/Course.h"
#include "../include/models/Enrollment.h"

// Application-level wiring: owns one generic Table<Record> per entity and
// binds each struct to its data file, free-list file, and id accessor.
//
// This lives outside the storage engine on purpose. The engine
// (include/database + src/database: Table, Index, FreeList) has no knowledge
// of Student/Teacher/Course/Enrollment - adding a new entity only requires
// editing this file and Database.cpp, never the engine.
class Database
{
public:
    Database();

    Table<Student> students;
    Table<Teacher> teachers;
    Table<Course> courses;
    Table<Enrollment> enrollments;
};
