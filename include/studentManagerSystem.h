#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* 学生*/
typedef struct _student
{
    int stuNum;
    char name[20];
    int score;

} Student;

/* 节点*/
typedef struct _node
{
    Student student;
    struct _node *next;
} Node;

/* 欢迎界面*/
void welcome();

/* 录入学生信息*/
void inputeStudentInfo(Node *head);

/* 打印学生信息*/
void printStudentInfo(Node *head);

/* 统计学生人数*/
void countStudent(Node *head);

/* 查找学生信息*/
void findStudentInfo(Node *head);

/* 修改学生信息*/
void updateStudentInfo(Node *head);

/* 删除学生信息*/
void deleteStudentInfo(Node *head);

/* 按照成绩排序*/
void sortStudentInfoByScore(Node *head);

/* 写出数据*/
void saveStudentInfoToBinaryFile(Node *head, const char *filename);

/* 加载数据*/
Node *loadStudentInfoFromBinaryFile(const char *filename);
