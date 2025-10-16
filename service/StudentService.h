#pragma once
#include <QObject>
#include "dao/StudentDAO.h"
#include "model/Student.h"

class StudentService : public QObject {
    Q_OBJECT
public:
    explicit StudentService(QObject *parent = nullptr);

    QList<Student> getAllStudents();
    bool addStudent(const Student &student);
    bool updateStudent(const Student &student);
    bool deleteStudent(int studentId);

    // 多线程/网络通信预留接口
public slots:
    void fetchStudentsAsync();
    void syncStudentsToCloud();

private:
    StudentDAO m_studentDao;
};
