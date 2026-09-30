# Stage 2: Don't Load the Whole File

## Problem with the Current Approach

Currently, every database operation follows this process:

```text
Open File
    ↓
Read Entire File
    ↓
Modify Data
    ↓
Rewrite Entire File
```

This approach works for small files, but it becomes **slow and inefficient** as the database grows.

---

## How Real Databases Work

Instead of loading the entire file into memory, real databases perform operations directly on the required record.

```text
Open File
    ↓
Seek to Required Position
    ↓
Read One Record
    ↓
Update One Record
```

This significantly improves performance because only the necessary data is accessed.

---

## File Position Functions

C++ provides several functions for random file access.

### `seekg()`

Moves the **read pointer** to a specific position in the file.

```cpp
file.seekg(position);
```

---

### `seekp()`

Moves the **write pointer** to a specific position in the file.

```cpp
file.seekp(position);
```

---

### `tellg()`

Returns the current position of the **read pointer**.

```cpp
long pos = file.tellg();
```

---

### `tellp()`

Returns the current position of the **write pointer**.

```cpp
long pos = file.tellp();
```

---

## Why Random File Access?

Random access allows you to:

* Read only the required record.
* Update only the required record.
* Avoid rewriting the entire database.
* Improve performance for large files.

This is one of the core techniques used in real database systems.

---

# Stage 3: Indexing

## Searching Without an Index

Suppose you want to find a record with **ID = 5000**.

Without an index, the database must scan every record one by one.

```text
Search ID = 5000
        ↓
Read Record 1
        ↓
Read Record 2
        ↓
Read Record 3
        ↓
...
        ↓
Read Record 5000
```

### Time Complexity

```
O(n)
```

The search time increases as the number of records increases.

---

## Using an Index

Instead of searching every record, maintain an **index** that stores the file position of each record.

### Example Index

| ID | File Position (Bytes) |
| -- | --------------------: |
| 1  |                     0 |
| 2  |                    64 |
| 3  |                   128 |
| 4  |                   192 |

---

## Searching with an Index

Now, when searching for **ID = 4**:

```text
Search ID = 4
        ↓
Lookup Index
        ↓
Position = 192
        ↓
Jump Directly to Byte 192
        ↓
Read Record
```

No unnecessary records are read.

---

## Benefits of Indexing

* Much faster searching.
* Direct access to records.
* Reduces disk I/O.
* Scales well for large databases.

---

## Time Complexity Comparison

| Method         | Time Complexity         |
| -------------- | ----------------------- |
| Linear Search  | O(n)                    |
| Indexed Search | O(1) *(Hash Index)*     |
| Indexed Search | O(log n) *(Tree Index)* |

---

# Summary

## Stage 2: Random File Access

* Avoid loading the entire file.
* Use `seekg()` and `seekp()` to jump to a specific location.
* Use `tellg()` and `tellp()` to determine the current file position.
* Read and update only the required record.

---

## Stage 3: Indexing

* Maintain a mapping from **Record ID → File Position**.
* Jump directly to the required record instead of scanning the entire file.
* Improve search performance from **O(n)** to **O(1)** or **O(log n)** depending on the indexing method.

---

## Real-World Database Workflow

```text
User Requests Record
          ↓
Search Index
          ↓
Get File Position
          ↓
seekg()/seekp()
          ↓
Read or Update Record
          ↓
Save Changes
```

This is the fundamental approach used by modern database systems such as SQLite, MySQL, PostgreSQL, and many file-based storage engines.


# Stage 4: Proper Record Deletion (Free List)

## Problem with Physical Deletion

Currently, when a record is deleted, it is removed from the container.

Example:

```text
Before Deletion

1 John   25
2 Alice  30
3 Bob    18

Delete Alice

1 John   25
3 Bob    18
```

Removing records changes their positions and may require shifting data or rewriting the file.

---

## Logical Deletion

Instead of physically removing the record, mark it as deleted.

```text
Before Deletion

1 John   25
2 Alice  30
3 Bob    18

Delete Alice

1 John   25
2 DELETED
3 Bob    18
```

The deleted slot remains in the file and can be reused later.

---

## Free List

Maintain a list of deleted record positions.

```text
Delete Record
       ↓
Mark as DELETED
       ↓
Store File Position
       ↓
Free List
```

Whenever a new record is inserted:

```text
Insert Record
       ↓
Free List Empty?
       ↓
   Yes       No
    ↓         ↓
Append     Reuse Deleted Slot
```

---

## Benefits

* No need to rewrite the entire file.
* Faster insert operations.
* Reduces file fragmentation.
* Efficient storage reuse.

This technique is commonly used in database storage engines and file systems.

---

# Stage 5: Sorting

Instead of displaying records in insertion order, allow users to sort records by different fields.

## Sort by ID

```cpp
std::sort(records.begin(), records.end(),
    [](const Record& a, const Record& b) {
        return a.id < b.id;
    });
```

---

## Sort by Name

```cpp
std::sort(records.begin(), records.end(),
    [](const Record& a, const Record& b) {
        return a.name < b.name;
    });
```

---

## Sort by Age

```cpp
std::sort(records.begin(), records.end(),
    [](const Record& a, const Record& b) {
        return a.age < b.age;
    });
```

---

## Why Sorting?

Sorting makes it easier to:

* Display records in a meaningful order.
* Improve readability.
* Prepare data for searching algorithms such as Binary Search.

---

## Time Complexity

| Algorithm     | Complexity |
| ------------- | ---------- |
| `std::sort()` | O(n log n) |

`std::sort()` uses **Introsort**, a hybrid algorithm combining Quick Sort, Heap Sort, and Insertion Sort for excellent real-world performance.

---

# Stage 6: Filtering

Searching by only one field is limiting.

Instead, allow users to filter records based on different conditions.

## Examples

### Age Greater Than 20

```text
Age > 20
```

Output:

```text
John 25
Alice 30
```

---

### Age Less Than 30

```text
Age < 30
```

Output:

```text
John 25
Bob 18
```

---

### Name Starts with 'A'

```text
Name starts with A
```

Output:

```text
Alice 30
```

---

### Age Between 18 and 25

```text
18 ≤ Age ≤ 25
```

Output:

```text
John 25
Bob 18
```

---

## Why Filtering?

Filtering allows users to retrieve only the records they need.

Benefits include:

* More flexible searches.
* Easier data analysis.
* Foundation for SQL-style `WHERE` clauses.

---

# Stage 7: Multiple Tables

So far, all records are stored in a single file.

Instead, separate different types of data into individual tables.

```text
students.dat

teachers.dat

courses.dat
```

---

## Database Structure

```text
Database
    │
    ├── Students Table
    │      ├── Row
    │      ├── Row
    │      └── Row
    │
    ├── Teachers Table
    │      ├── Row
    │      └── Row
    │
    └── Courses Table
           ├── Row
           ├── Row
           └── Row
```

Each table stores records of a specific type.

---

## Benefits

* Better organization.
* Easier maintenance.
* Independent storage for different entities.
* Similar structure to relational database systems.

---

# Summary

## Stage 4: Free List

* Mark records as deleted instead of removing them.
* Reuse deleted slots for future inserts.
* Reduce unnecessary file rewrites.

---

## Stage 5: Sorting

* Sort by ID.
* Sort by Name.
* Sort by Age.
* Use `std::sort()` with O(n log n) complexity.

---

## Stage 6: Filtering

Support queries such as:

* Age > 20
* Age < 30
* Name starts with A
* Age between 18 and 25

Filtering is the foundation of SQL `WHERE` clauses.

---

## Stage 7: Multiple Tables

Separate data into different files:

* `students.dat`
* `teachers.dat`
* `courses.dat`

This organizes the database into multiple tables, making the system resemble a real relational database.

---

# Final Architecture

```text
Database
      │
      ├── Students Table
      │       │
      │       ├── Free List
      │       ├── Index
      │       ├── Random File Access
      │       └── Records
      │
      ├── Teachers Table
      │       │
      │       ├── Free List
      │       ├── Index
      │       ├── Random File Access
      │       └── Records
      │
      └── Courses Table
              │
              ├── Free List
              ├── Index
              ├── Random File Access
              └── Records
```

At this stage, your project includes many core concepts used by real database systems:

* Random file access
* Indexing
* Free list management
* Sorting
* Filtering
* Multiple tables

These concepts provide a strong foundation for implementing more advanced database features such as transactions, B+ trees, query optimization, and concurrency control.
