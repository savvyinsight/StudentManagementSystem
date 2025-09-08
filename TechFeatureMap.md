# StudentManagementSystem Feature Map

## Technologies Used
- C++
- Qt6 Framework (Signals & Slots, SQLite, Qt Designer, CMake)

## Project Overview
A cross-platform desktop application for school administration. Core features include student information management (with photo), weekly course schedule management, financial record statistics. Highlights: multi-language switching (English/Chinese), data export to Excel/CSV, custom UI themes. Solves SQLite cross-thread access, multi-window data synchronization, and ensures stable operation on Windows/macOS/Linux.

---

## Feature-to-Code Mapping

### 1. Student Information CRUD (with photo)
- **UI Page:** `studentinfowidget.ui`, `StudentInfoWidget.cpp`
- **Key Functions:**
  - `StudentInfoWidget::addStudent()` (approx. line 80)
  - `StudentInfoWidget::editStudent()` (approx. line 120)
  - `StudentInfoWidget::deleteStudent()` (approx. line 160)
  - Photo upload handled in `StudentInfoWidget::addStudent()`

### 2. Weekly Course Schedule Management
- **UI Page:** `schedulewidget.ui`, `ScheduleWidget.cpp`
- **Key Functions:**
  - `ScheduleWidget::loadSchedule()` (approx. line 60)
  - `ScheduleWidget::addCourse()` (approx. line 100)
  - `ScheduleWidget::editCourse()` (approx. line 140)
  - `ScheduleWidget::deleteCourse()` (approx. line 180)

### 3. Financial Record Statistics
- **UI Page:** `financialwidget.ui`, `FinancialWidget.cpp`
- **Key Functions:**
  - `FinancialWidget::loadFinancialRecords()` (approx. line 100)
  - `FinancialWidget::addRecord()` (approx. line 150)
  - `FinancialWidget::updateChart()` (approx. line 250)
  - `FinancialWidget::updatePieChart()` (approx. line 200)

### 4. Multi-language Switching (English/Chinese)
- **UI Page:** `systemsetting.ui`, `SystemSetting.cpp`
- **Key Functions:**
  - `SystemSetting::onLanguageChanged(int index)` (line 70)
  - Language combo box setup in `SystemSetting::createUI()` (line 35)

### 5. Data Export to Excel/CSV
- **UI Pages:** `StudentInfoWidget.cpp`, `FinancialWidget.cpp`, `ScheduleWidget.cpp`
- **Key Functions:**
  - `StudentInfoWidget::exportToCSV()` (approx. line 200)
  - `FinancialWidget::exportToExcel()` (approx. line 300)
  - `ScheduleWidget::exportToCSV()` (approx. line 220)

### 6. Custom UI Theme (QSS)
- **UI Page:** `systemsetting.ui`, `SystemSetting.cpp`
- **Key Functions:**
  - `SystemSetting::onThemeChanged(int index)` (line 85)
  - Theme combo box setup in `SystemSetting::createUI()` (line 40)

### 7. SQLite Cross-thread Access Solution
- **Service Layer:** `FinancialService.cpp`, `StudentService.cpp`, `ScheduleService.cpp`
- **Key Functions:**
  - `FinancialService::fetchRecordsAsync()` (line 20)
  - `StudentService::fetchStudentsAsync()` (approx. line 25)
  - `ScheduleService::fetchRecordsAsync()` (approx. line 30)
  - Uses `QtConcurrent::run` for thread safety

### 8. Multi-window Data Synchronization
- **UI Pages:** All main widgets
- **Key Functions:**
  - Signal-slot connections for data refresh, e.g. `connect(service, SIGNAL(dataChanged()), this, SLOT(refreshData()))` (various files, approx. line 60-120)

### 9. MVC Architecture & Database Design
- **Database Tables:** `studentInfo`, `schedule`, `financialRecords`
- **DAO/Service Layer:** `StudentDAO.cpp/h`, `ScheduleDAO.cpp/h`, `FinancialDAO.cpp/h`, `StudentService.cpp/h`, etc.
- **Key Functions:** CRUD methods in each DAO/Service file (lines 20-80)

### 10. UI Development (Qt Designer + Code)
- **UI Files:** `.ui` files for each widget (studentinfowidget.ui, schedulewidget.ui, financialwidget.ui, etc.)
- **Code Files:** Corresponding `.cpp` files for logic
- **Signal-Slot:** Used throughout for low-coupling module interaction

### 11. Internationalization & Theme Configuration
- **UI Page:** `systemsetting.ui`, `SystemSetting.cpp`
- **Key Functions:**
  - `SystemSetting::onLanguageChanged(int index)` (line 70)
  - `SystemSetting::onThemeChanged(int index)` (line 85)

### 12. Unit Testing & Bug Fixes
- **Test Files:** `tests/` directory (if present)
- **Key Functions:**
  - Test cases for core modules (student, schedule, financial)
  - Bug fixes in UI/data consistency (scattered, see commit history)

---

> **Note:** Line numbers are approximate and may vary with code changes. For exact locations, use search in your IDE.
