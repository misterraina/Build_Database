#pragma once
#include <cstring>
#include <string>

struct Enrollment
{
	int enrollmentID;
	int studentID;
	int courseID;
	int teacherID;
	char enrollmentDate[11];
	char grade[3];
	bool isDeleted;

	void setEnrollmentDate(const std::string& date)
	{
		std::strncpy(enrollmentDate, date.c_str(), sizeof(enrollmentDate) - 1);
		enrollmentDate[sizeof(enrollmentDate) - 1] = '\0';
	}

	void setGrade(const std::string& value)
	{
		std::strncpy(grade, value.c_str(), sizeof(grade) - 1);
		grade[sizeof(grade) - 1] = '\0';
	}

};