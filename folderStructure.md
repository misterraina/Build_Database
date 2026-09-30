MiniDB/
│
├── CMakeLists.txt          # or Makefile
├── README.md
├── main.cpp
│
├── include/
│   ├── database/
│   │     Database.h
│   │     Table.h
│   │
│   ├── storage/
│   │     FileManager.h
│   │     RecordFile.h
│   │     FreeList.h
│   │
│   ├── index/
│   │     Index.h
│   │     HashIndex.h
│   │     BTreeIndex.h      # future
│   │
│   ├── query/
│   │     Filter.h
│   │     Sort.h
│   │     QueryEngine.h
│   │
│   ├── models/
│   │     Student.h
│   │     Teacher.h
│   │     Course.h
│   │
│   ├── utils/
│   │     Serializer.h
│   │     Constants.h
│   │     Logger.h
│   │
│   └── common/
│         Record.h
│
├── src/
│   ├── database/
│   │     Database.cpp
│   │     Table.cpp
│   │
│   ├── storage/
│   │     FileManager.cpp
│   │     RecordFile.cpp
│   │     FreeList.cpp
│   │
│   ├── index/
│   │     HashIndex.cpp
│   │
│   ├── query/
│   │     Filter.cpp
│   │     Sort.cpp
│   │     QueryEngine.cpp
│   │
│   ├── models/
│   │     Student.cpp
│   │     Teacher.cpp
│   │     Course.cpp
│   │
│   └── utils/
│         Serializer.cpp
│
├── data/
│   ├── students.dat
│   ├── teachers.dat
│   ├── courses.dat
│   │
│   ├── students.idx
│   ├── teachers.idx
│   ├── courses.idx
│   │
│   ├── students.fre
│   ├── teachers.fre
│   └── courses.fre
│
├── tests/
│   ├── test_insert.cpp
│   ├── test_delete.cpp
│   ├── test_index.cpp
│   └── test_filter.cpp
│
└── docs/
    ├── Architecture.md
    ├── StorageEngine.md
    └── FuturePlans.md