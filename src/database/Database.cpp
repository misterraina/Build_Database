#include "../../include/database/Database.h"

namespace
{
    constexpr const char* kStudentFilename = "../../data/students.dat";
    constexpr const char* kStudentFreeFilename = "../../data/students.fre";

    constexpr const char* kTeacherFilename = "../../data/teachers.dat";
    constexpr const char* kTeacherFreeFilename = "../../data/teachers.fre";

    constexpr const char* kCourseFilename = "../../data/courses.dat";
    constexpr const char* kCourseFreeFilename = "../../data/courses.fre";

    constexpr const char* kEnrollmentFilename = "../../data/enrollments.dat";
    constexpr const char* kEnrollmentFreeFilename = "../../data/enrollments.fre";
}

Database::Database()
    : students(kStudentFilename, kStudentFreeFilename, "Student",
          [](const Student& student) { return student.studentID; })
    , teachers(kTeacherFilename, kTeacherFreeFilename, "Teacher",
          [](const Teacher& teacher) { return teacher.teacherID; })
    , courses(kCourseFilename, kCourseFreeFilename, "Course",
          [](const Course& course) { return course.courseID; })
    , enrollments(kEnrollmentFilename, kEnrollmentFreeFilename, "Enrollment",
          [](const Enrollment& enrollment) { return enrollment.enrollmentID; })
{
}
