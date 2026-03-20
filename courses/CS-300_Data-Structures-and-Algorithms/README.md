# CS-300: Data Structures and Algorithms Analysis and Design

## Course Description

This repository contains coursework from **CS-300: Data Structures and Algorithms Analysis and Design** at Southern New Hampshire University (SNHU). The course focuses on implementing and analyzing fundamental data structures and algorithms, with emphasis on efficiency, Big O notation, and practical application development.

**Completed:** 2025

## Topics Covered

- **Data Structures Implementation**
  - Binary Search Trees (BST)
  - Hash Tables with Chaining
  - Linked Lists
  - Vectors and Arrays
  - Maps (Standard Template Library)

- **Algorithm Analysis**
  - Big O Notation and Time Complexity
  - Selection Sort
  - Quick Sort
  - Insertion Sort
  - Search Algorithms

- **Software Development Practices**
  - Algorithm Design with Pseudocode
  - CSV File Parsing
  - Menu-Driven Applications
  - Code Documentation
  - Performance Benchmarking

## Languages & Tools

- **Primary Language:** C++
- **Development Tools:** Visual Studio / g++ compiler
- **Data Processing:** CSV parsing and file I/O
- **STL Components:** `map`, `vector`, `string`, `algorithm`

## Projects & Assignments

### Final Project: ABCU Advising Program
**File:** `CS300_Project_Two_Heath_Davis.cpp`

A course management system for ABCU (Academic Advising) that loads course data from CSV files, stores it in an efficient data structure (map), and provides functionality to:
- Load course catalog from file
- Display all courses in alphanumeric order
- Search for individual courses and display prerequisites
- Implement O(log n) lookup using C++ STL map

**Key Features:**
- Case-insensitive course number search
- Prerequisite tracking and display
- Input validation and error handling
- CSV parsing with comma-separated values

### Binary Search Tree Assignment
**Location:** `CS 300 Binary Search Tree Assignment Student Files/`

Implementation of a Binary Search Tree for managing bid data from eBay monthly sales. Demonstrates:
- BST node insertion and traversal
- In-order traversal for sorted output
- Search operations
- CSV data import from `eBid_Monthly_Sales_Dec_2016.csv`

**Files:**
- `BinarySearchTreeHeathDavis.cpp` - Complete BST implementation
- `BinarySearchTree.cpp` - Base template file
- `CSVparser.cpp/hpp` - CSV parsing utilities

### Hash Table Assignment
**Location:** `CS 300 Hash Table Assignment Student Files/`

Implementation of a hash table with chaining for collision resolution. Features:
- Hash function design
- Chaining collision handling
- Insert, search, and remove operations
- Performance analysis with DEFAULT_SIZE = 179

**Files:**
- `HashTableHeathDavis.cpp` - Complete hash table implementation
- `HashTable.cpp` - Base template file
- `eBid_Monthly_Sales_Dec_2016.csv` - Test dataset

### Vector Sorting Assignment
**Location:** `CS 300 Vector Sorting Assignment Student Files/`

Implementation and comparison of multiple sorting algorithms using C++ vectors:
- Selection Sort
- Quick Sort
- Insertion Sort (implied)
- Performance benchmarking with timing analysis

**Files:**
- `VectorSorting.cpp` - Sorting algorithm implementations
- `eBid_Monthly_Sales_Dec_2016.csv` - Test dataset

### Pseudocode Documentation
Multiple iterations of algorithm design documents demonstrating the planning phase before implementation:
- `CS 300 Pseudocode Document Heath Davis Updated 6-15.docx` (Final version)
- `CS 300 Pseudocode Document Heath Davis.docx`
- `Linked Lists Psuedocode Heath Davis.docx`

These documents outline the logic for data structure operations before coding.

## Key Concepts Demonstrated

### Algorithm Analysis
- **Big O Notation:** Analysis of time and space complexity for all data structures
- **Performance Comparison:** Empirical testing of different approaches
- **Trade-offs:** Understanding when to use each data structure

### Data Structure Selection
- **Vectors:** Good for sequential access, poor for insertion/deletion
- **Linked Lists:** Efficient insertion/deletion, poor random access
- **Hash Tables:** O(1) average case lookup, potential collision handling
- **Binary Search Trees:** O(log n) balanced operations, in-order traversal
- **Maps (STL):** Self-balancing BST implementation for guaranteed O(log n)

### Software Engineering
- **Incremental Development:** Building on template code
- **Code Reusability:** CSV parser used across multiple assignments
- **Documentation:** Inline comments and external pseudocode
- **Testing:** Menu-driven interfaces for comprehensive testing

## File Index

| File/Directory | Description |
|----------------|-------------|
| `CS300_Project_Two_Heath_Davis.cpp` | Final project - ABCU Course Advising Program using STL map |
| `CS 300 ABCU_Advising_Program_Input.csv` | Course catalog data with prerequisites |
| `CS 300 Binary Search Tree Assignment Student Files/` | BST implementation for bid management |
| `CS 300 Hash Table Assignment Student Files/` | Hash table with chaining implementation |
| `CS 300 Vector Sorting Assignment Student Files/` | Multiple sorting algorithm implementations |
| `CS 300 Pseudocode Document Heath Davis Updated 6-15.docx` | Algorithm design documentation (final) |
| `CS 300 Project Two Sample Program Output.pdf` | Expected output specifications |
| `CS 300 Course Information.pdf` | Complete course syllabus and requirements |

## Learning Outcomes

Through this course, the following competencies were developed:

1. **Analyze and evaluate data structures** for efficiency and appropriateness
2. **Implement fundamental data structures** from scratch in C++
3. **Design algorithms** using pseudocode before implementation
4. **Apply Big O notation** to analyze algorithm complexity
5. **Develop menu-driven applications** with file I/O
6. **Parse and process CSV data** for real-world applications
7. **Compare algorithm performance** through empirical testing

## Sample Output

The ABCU Advising Program provides an interactive menu:

```
Welcome to the course planner.
1. Load Data Structure.
2. Print Course List.
3. Print Course.
9. Exit
What would you like to do?
```

After loading data, users can view all courses or search for specific courses with prerequisites:
```
CSCI300, Introduction to Algorithms
Prerequisites: CSCI200, MATH201
```

## Technical Highlights

- **CSV Parsing:** Custom string splitting with delimiter handling
- **Case-Insensitive Search:** Uppercase conversion for robust lookups
- **STL Integration:** Leveraging `std::map` for automatic sorting and O(log n) operations
- **Memory Management:** Proper use of references and avoiding memory leaks
- **Error Handling:** File validation, input sanitization, and user feedback

---

**Course:** CS-300 Data Structures and Algorithms
**Institution:** Southern New Hampshire University
**Student:** Heath Davis
**Semester:** Spring/Summer 2025
