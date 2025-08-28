#include "StudentDAO.h"
#include "model/Student.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QList>

QList<Student> StudentDAO::fetchAll() {
    QList<Student> students;
    QSqlQuery query("SELECT id, name, gender, major FROM studentInfo");
    while(query.next()) {
        Student student;
        student.id = query.value(0).toInt();
        student.name = query.value(1).toString();
        student.gender = query.value(2).toString();
        student.major = query.value(3).toString();
        // ...其他字段赋值...
        students.append(student);
    }
    return students;
}

bool StudentDAO::insert(const Student &student) {
    QSqlQuery query;
    query.prepare("INSERT INTO studentInfo (id, name, gender, major) VALUES (?, ?, ?, ?)");
    query.addBindValue(student.id);
    query.addBindValue(student.name);
    query.addBindValue(student.gender);
    query.addBindValue(student.major);
    // ...其他字段绑定...
    return query.exec();
}

bool StudentDAO::update(const Student &student) {
    QSqlQuery query;
    query.prepare("UPDATE studentInfo SET name = ?, gender = ?, major = ? WHERE id = ?");
    query.addBindValue(student.name);
    query.addBindValue(student.gender);
    query.addBindValue(student.major);
    query.addBindValue(student.id);
    // ...其他字段绑定...
    return query.exec();
}

bool StudentDAO::remove(int studentId) {
    QSqlQuery query;
    query.prepare("DELETE FROM studentInfo WHERE id = ?");
    query.addBindValue(studentId);
    return query.exec();
}
