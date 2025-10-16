#include "StudentService.h"

StudentService::StudentService(QObject *parent) : QObject(parent) {}

QList<Student> StudentService::getAllStudents() {
    return m_studentDao.fetchAll();
}

bool StudentService::addStudent(const Student &student) {
    // 可加业务校验
    return m_studentDao.insert(student);
}

bool StudentService::updateStudent(const Student &student) {
    return m_studentDao.update(student);
}

bool StudentService::deleteStudent(int studentId) {
    return m_studentDao.remove(studentId);
}

// 多线程/网络通信预留接口
void StudentService::fetchStudentsAsync() {
    // TODO: 实现异步获取学生信息
}

void StudentService::syncStudentsToCloud() {
    // TODO: 实现学生信息云同步
}
