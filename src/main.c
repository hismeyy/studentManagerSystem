#include "studentManagerSystem.h"

const char *STUDENT_INFO_FILE = "./studentInfo.data";

int main()
{
    system("chcp 65001");
    Node *head = loadStudentInfoFromBinaryFile(STUDENT_INFO_FILE);

    while (1)
    {
        system("cls");
        welcome();

        char c = _getch();

        switch (c)
        {
        case '1':
            inputeStudentInfo(head);
            break;
        case '2':
            printStudentInfo(head);
            break;
        case '3':
            countStudent(head);
            break;
        case '4':
            findStudentInfo(head);
            break;
        case '5':
            updateStudentInfo(head);
            break;
        case '6':
            deleteStudentInfo(head);
            break;
        case '7':
            sortStudentInfoByScore(head);
            break;
        case '8':
            saveStudentInfoToBinaryFile(head, STUDENT_INFO_FILE);
            exit(0);
            break;
        default:
            printf("请输入1-8\n");
            system("pause");
            break;
        }
    }

    return 0;
}