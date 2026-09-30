#include <iostream>
#include <cstring>

std::string input_name = "Johnathan Alexander Smith";
// char input_name[] = "John Doe";

int main(){

    std::cout << "Input name: " << input_name << std::endl;

    // char student_name[10];
    char student_name[10];
    // strcpy(student_name, input_name);

    strncpy(student_name, input_name.c_str(), sizeof(student_name) - 1);
    student_name[sizeof(student_name) - 1] = '\0';

    student_name[0] = 'A';
    std::cout << "Student name: " << student_name << std::endl;
    return 0;
}