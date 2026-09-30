4. When each is actually used
Use const char* when:
constant literal (never changes)
file names, config keys
C APIs (fopen, strcpy)
embedded systems
performance-critical low-level code
Example:
fopen(FILE_NAME, "r");
Use std::string when:
path may change
you concatenate strings
user input involved
file paths are built dynamically
Example:
std::string path = baseDir + "/" + filename;


Why static is used here
static in global scope:
static const char* FILE_NAME = "courses.dat";
Means:
👉 “this variable is only visible inside this file”
So:
not accessible from other .cpp files
avoids naming conflicts
Without static:
const char* FILE_NAME = "courses.dat";
Then:
becomes external symbol
can conflict across files in large projects

Why const is important
Both versions are:
const
Meaning:
👉 value cannot be changed
So:
FILE_NAME = "other.dat"; ❌ not allowed
7. So what is the real difference?
const char*
pointer to fixed string literal
no ownership
no memory management
std::string
owns memory
safe
flexible
resizable










What is this constructor doing?
std::ofstream file(kCourseFilename,
                   std::ios::binary | std::ios::app);
General syntax:
std::ofstream variable_name(filename, open_mode);
In your code:
file
is the object name.
kCourseFilename
is the filename.
std::ios::binary | std::ios::app
are flags (options).


What is this constructor doing?
std::ofstream file(kCourseFilename,
                   std::ios::binary | std::ios::app);
General syntax:
std::ofstream variable_name(filename, open_mode);
In your code:
file
is the object name.
kCourseFilename
is the filename.
std::ios::binary | std::ios::app
are flags (options).



What are these flags?
std::ios::binary
Open as binary.
Without it:
Hello
might be treated as text.
With binary:
01001000 01100101 ...
The file is treated as raw bytes.
This is exactly what a database wants.
std::ios::app
Append mode.
Instead of:
File:
Course A
being overwritten,
it becomes
Course A
Course B
Course C
Everything is written to the end.