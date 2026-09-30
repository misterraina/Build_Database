#pragma once
#include <cstring>
#include <string>

struct Student
{
	int studentID;
	char studentName[50];
	char email[100];
	bool isDeleted;

	void setStudentName(const std::string& name)
	{
		std::strncpy(studentName, name.c_str(), sizeof(studentName) - 1);
		studentName[sizeof(studentName) - 1] = '\0';
	}

	void setEmail(const std::string& address)
	{
		std::strncpy(email, address.c_str(), sizeof(email) - 1);
		email[sizeof(email) - 1] = '\0';
	}

};