#pragma once

#include "Table.h"
#include "../models/Student.h"
#include "../models/Teacher.h"
#include "../models/Course.h"
#include "../models/Enrollment.h"

// Owns one generic Table<Record> per entity. This is the only place that
// wires a struct type to its data file / free-list file / id accessor -
// there is no per-entity CRUD code anywhere else in the codebase.
class Database
{
public:
    Database();

    Table<Student> students;
    Table<Teacher> teachers;
    Table<Course> courses;
    Table<Enrollment> enrollments;
};
