#pragma once

#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "Enrollment.h"

#include <iostream>

// Presentation formatting is inherently field-specific per struct, so it
// stays outside the generic storage engine (Table<Record>). These are the
// only per-entity functions left in the whole codebase.

inline void printStudent(const Student& student)
{
    std::cout << "Student ID: " << student.studentID << "\n";
    std::cout << "Student Name: " << student.studentName << "\n";
    std::cout << "Email: " << student.email << "\n";
    std::cout << "-------------------------\n";
}

inline void printTeacher(const Teacher& teacher)
{
    std::cout << "Teacher ID: " << teacher.teacherID << "\n";
    std::cout << "Teacher Name: " << teacher.teacherName << "\n";
    std::cout << "Subject: " << teacher.subject << "\n";
    std::cout << "Email: " << teacher.email << "\n";
    std::cout << "-------------------------\n";
}

inline void printCourse(const Course& course)
{
    std::cout << "Course ID: " << course.courseID << "\n";
    std::cout << "Course Name: " << course.courseName << "\n";
    std::cout << "Description: " << course.description << "\n";
    std::cout << "-------------------------\n";
}

inline void printEnrollment(const Enrollment& enrollment)
{
    std::cout << "Enrollment ID: " << enrollment.enrollmentID << "\n";
    std::cout << "Student ID: " << enrollment.studentID << "\n";
    std::cout << "Course ID: " << enrollment.courseID << "\n";
    std::cout << "Teacher ID: " << enrollment.teacherID << "\n";
    std::cout << "Enrollment Date: " << enrollment.enrollmentDate << "\n";
    std::cout << "Grade: " << enrollment.grade << "\n";
    std::cout << "-------------------------\n";
}
