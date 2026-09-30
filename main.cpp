#include "include/database/Database.h"
#include "include/models/Printers.h"

int main()
{
    Course course{};
    course.courseID = 1;
    course.setCourseName("Computer Science");
    course.setDescription("Introduction to programming and databases");
    course.isDeleted = false;

    Teacher teacher{};
    teacher.teacherID = 1;
    teacher.setTeacherName("Grace Hopper");
    teacher.setSubject("Programming");
    teacher.setEmail("grace@example.com");
    teacher.isDeleted = false;

    Student student{};
    student.studentID = 1;
    student.setStudentName("Ada Lovelace");
    student.setEmail("ada@example.com");
    student.isDeleted = false;

    Enrollment enrollment{};
    enrollment.enrollmentID = 1;
    enrollment.studentID = student.studentID;
    enrollment.courseID = course.courseID;
    enrollment.teacherID = teacher.teacherID;
    enrollment.setEnrollmentDate("2026-09-26");
    enrollment.setGrade("A");
    enrollment.isDeleted = false;

    Database db;

    db.courses.insert(course);
    db.teachers.insert(teacher);
    db.students.insert(student);
    db.enrollments.insert(enrollment);

    for (const auto& c : db.courses.scanAll()) printCourse(c);
    for (const auto& t : db.teachers.scanAll()) printTeacher(t);
    for (const auto& s : db.students.scanAll()) printStudent(s);
    for (const auto& e : db.enrollments.scanAll()) printEnrollment(e);

    return 0;
}
