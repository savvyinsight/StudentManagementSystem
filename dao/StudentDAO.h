#pragma once
#include "model/Student.h"
#include <QList>

class StudentDAO {
public:
    QList<Student> fetchAll();
    bool insert(const Student &student);
    bool update(const Student &student);
    bool remove(int studentId);
};
