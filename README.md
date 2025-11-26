# Student Management System

<p align="center">
<strong>Language:</strong>&nbsp; <strong>English</strong> | <a href="README_zh.md">中文</a>
</p>

## 1. Project Overview

The Student Management System is a desktop application developed based on the Qt framework, designed to provide educational institutions with convenient functions for student information management, financial record-keeping, schedule arrangement, and honor display. The system uses an SQLite database for data storage, featuring a user-friendly interface and well-structured functional modules.

## 2. Functional Features

### 1. Student Information Management

*   Add, query, and manage basic student information


*   Support editing and updating of student profiles


*   Implement structured storage and display of student data


### 2. Financial Record Management

*   Add and manage student expense-related records


*   Query and delete financial data


*   Visualize financial information for clear presentation


### 3. Schedule Arrangement

*   View and manage daily/weekly schedules


*   Support switching between previous and next week schedules


*   Record and display schedule information systematically


### 4. Honor Display Module

*   Showcase student honorary achievements


*   Design and layout for an honor wall interface


*   Visual presentation of honorary information

## 3. Technical Architecture

### 1. Development Environment

*   Framework: Qt 6.9.0


*   Compiler: MinGW 64-bit


*   Database: SQLite


### 2. Project Structure

```
StudentManagementSystem/  
├── build/                              # Build-generated debug files  
├── icon/                               # Project icon resources  
├── sqllite/                            # SQLite database-related files  
├── style/                              # Styling-related resources  
├── CMakeLists.txt                      # Project build configuration  
├── README.md                           # Project documentation  
├── TechDocs.docx                       # Technical documentation  
├── TechDocs.md                         # Technical documentation (Markdown)  
├── databasemanager.cpp/.h              # Database management module  
├── financialwidget.cpp/.h/.ui          # Financial management module  
├── honorwallwidget.cpp/.h/.ui          # Honor wall display module  
├── main.cpp                            # Main program entry point  
├── mainwindow.cpp/.h/.ui               # Main window module  
├── res.qrc                             # Resource configuration file  
├── schedulewidget.cpp/.h/.ui           # Schedule management module  
├── studentinfowidget.cpp/.h/.ui        # Student information module  
└── tabledelegates.h                    # Table delegate module  
```

## 4.Module Descriptions

### 1. Database Management Module

*   **Function**: Manages database initialization and student information addition


*   **Key Files**: `databasemanager.cpp/.h`, `main.cpp`

### 2. Financial Management Module

*   **Function**: Implements financial record management (add, query, delete)


*   **Key Files**: `financialwidget.cpp/.h/.ui`

### 3. Honor Wall Module

*   **Function**: Provides honor information display functionality


*   **Key Files**: `honorwallwidget.cpp/.h/.ui`, `mainwindow.ui`

### 4. Schedule Module

*   **Function**: Manages weekly schedule viewing and switching


*   **Key Files**: `schedulewidget.cpp/.h/.ui`

### 5. Student Information Module

*   **Function**: Manages basic student profiles


*   **Key Files**: `studentinfowidget.cpp/.h/.ui`

### 6. Main Window Module

*   **Function**: Establishes the basic framework and UI styling


*   **Key Files**: `mainwindow.cpp/.h/.ui`

## 5.Compilation and Execution

### 1. Environment Requirements

*   Qt 6.9.0 or higher


*   MinGW 64-bit compiler


*   CMake 3.10 or higher


### 2. Compilation Steps

1.  Clone the project: `git clone ``https://github.com/savvyinsight/StudentManagementSystem.git`

2.  Enter the project root directory


3.  Create and enter the build directory: `mkdir build && cd build`

4.  Generate build files with CMake: `cmake ..`

5.  Compile the project: `make`

### 3. Execution Guide

*   Locate the generated executable file in the build directory and run it

## 6.What It's Look Like?

1. Login

![image-20251016233714446](assets/README/image-20251016233714446.png)

2. Student Info

![image-20251016234638188](assets/README/image-20251016234638188.png)

3.Course Schedule

![image-20251016234747689](assets/README/image-20251016234747689.png)

4.Finance

![image-20251016235043033](assets/README/image-20251016235043033.png)

5.Awards

![image-20251016235422478](assets/README/image-20251016235422478.png)

## 7.Contact Information

For issues or suggestions, please submit an Issue through the project repository or contact the developer directly.