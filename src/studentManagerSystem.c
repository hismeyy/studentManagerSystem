#include "studentManagerSystem.h"

void welcome()
{
    printf("*********************************\n");
    printf("*\t学生成绩管理系统\t*\n");
    printf("*********************************\n");
    printf("*\t请选择功能列表\t\t*\n");
    printf("*********************************\n");
    printf("*\t1.录入学生信息\t\t*\n");
    printf("*\t2.打印学生信息\t\t*\n");
    printf("*\t3.统计学生信息\t\t*\n");
    printf("*\t4.查找学生信息\t\t*\n");
    printf("*\t5.修改学生信息\t\t*\n");
    printf("*\t6.删除学生信息\t\t*\n");
    printf("*\t7.按照成绩排序\t\t*\n");
    printf("*\t8.退出系统\t\t*\n");
    printf("*********************************\n");
}

void inputeStudentInfo(Node *head)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;

    printf("请输入学生的学号，姓名，成绩：");
    scanf("%d%s%d", &newNode->student.stuNum, newNode->student.name, &newNode->student.score);

    Node *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;

    system("pause");
}

void printStudentInfo(Node *head)
{

    if (head->next == NULL)
    {
        printf("当前没有任何学生信息！\n");
        system("pause");
        system("cls");
        return;
    }

    Node *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
        printf("学号：%d，姓名：%s，成绩：%d\n", temp->student.stuNum, temp->student.name, temp->student.score);
    }
    system("pause");
}

void countStudent(Node *head)
{
    int count = 0;

    Node *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
        count++;
    }

    printf("学生总人数为：%d\n", count);
    system("pause");
}

void findStudentInfo(Node *head)
{
    int stuNum;
    printf("请输入学号：");
    scanf("%d", &stuNum);

    Node *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;

        if (temp->student.stuNum == stuNum)
        {
            printf("学号：%d，姓名：%s，成绩：%d\n", temp->student.stuNum, temp->student.name, temp->student.score);
            system("pause");
            return;
        }
    }

    printf("未查询到学生信息！\n");
    system("pause");
}

void updateStudentInfo(Node *head)
{
    int stuNum;
    printf("请输入你要更新学生信息的学号：");
    scanf("%d", &stuNum);

    Node *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;

        if (temp->student.stuNum == stuNum)
        {
            printf("学号：%d，姓名：%s，成绩：%d\n", temp->student.stuNum, temp->student.name, temp->student.score);
            printf("请输入学生新的学号，姓名，成绩：");
            scanf("%d%s%d", &temp->student.stuNum, temp->student.name, &temp->student.score);
            system("pause");
            return;
        }
    }

    printf("未查询到学生信息！\n");
    system("pause");
}

void deleteStudentInfo(Node *head)
{
    int stuNum;
    printf("请输入学号：");
    scanf("%d", &stuNum);

    Node *temp = head;
    Node *preTemp = NULL;

    while (temp->next != NULL)
    {

        preTemp = temp;

        temp = temp->next;

        if (temp->student.stuNum == stuNum)
        {
            preTemp->next = temp->next;
            printf("学号：%d，姓名：%s，成绩：%d的信息已删除！\n", temp->student.stuNum, temp->student.name, temp->student.score);
            free(temp);
            system("pause");
            return;
        }
    }

    printf("未查询到学生信息！\n");
    system("pause");
}

// 找到链表的中间节点
Node *getMiddle(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    Node *slow = head;
    Node *fast = head->next;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// 合并两个有序链表
Node *merge(Node *l1, Node *l2)
{
    Node *dummy = (Node *)malloc(sizeof(Node));
    Node *current = dummy;
    while (l1 != NULL && l2 != NULL)
    {
        if (l1->student.score > l2->student.score)
        {
            current->next = l1;
            l1 = l1->next;
        }
        else
        {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }

    current->next = l1 ? l1 : l2;

    Node *result = dummy->next;
    free(dummy); // 释放哑节点的内存
    return result;
}

// 归并排序主函数
Node *mergeSort(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    Node *middle = getMiddle(head);
    Node *nextToMiddle = middle->next;
    middle->next = NULL;

    Node *left = mergeSort(head);
    Node *right = mergeSort(nextToMiddle);

    return merge(left, right);
}

void sortStudentInfoByScore(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        printf("未查询到学生信息！\n");
        system("pause");
        return;
    }
    head->next = mergeSort(head->next);
    printf("排序完成\n");
    system("pause");
}

void saveStudentInfoToBinaryFile(Node *head, const char *filename)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        perror("打开文件错误");
        return;
    }

    Node *current = head->next;
    while (current != NULL)
    {
        fwrite(&(current->student), sizeof(Student), 1, file);
        current = current->next;
    }

    fclose(file);
}

Node *loadStudentInfoFromBinaryFile(const char *filename)
{
    Node *head = head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("打开文件错误");
        return head;
    }

    Student student;
    Node* temp = head;

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->student = student;
        newNode->next = NULL;

        temp->next = newNode;
        temp = temp->next;
    }

    fclose(file);
    return head;
}