#pragma once
#include <cstring>
#include <string>

struct Teacher
{
	int teacherID;
	char teacherName[50];
	char subject[50];
	char email[100];
	bool isDeleted;

	void setTeacherName(const std::string& name)
	{
		std::strncpy(teacherName, name.c_str(), sizeof(teacherName) - 1);
		teacherName[sizeof(teacherName) - 1] = '\0';
	}

	void setSubject(const std::string& name)
	{
		std::strncpy(subject, name.c_str(), sizeof(subject) - 1);
		subject[sizeof(subject) - 1] = '\0';
	}

	void setEmail(const std::string& address)
	{
		std::strncpy(email, address.c_str(), sizeof(email) - 1);
		email[sizeof(email) - 1] = '\0';
	}

};
