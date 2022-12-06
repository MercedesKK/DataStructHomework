#include "List.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>

using namespace MercedesKK;

static const std::string select_string = "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������";

void EnterToExit()
{
    system("pause");
    exit(1);
}

/// @brief �ڵ�ǰ��ҵ���趨��ѧ����
class Student
{
public:
    int number;             ///< ����
    std::string name;       ///< ѧ������
    std::string gender;     ///< �Ա�
    int age;                ///< ����
    std::string category;   ///< ��������

    /// constructor
    Student() : number(-1), name(""), gender(""), age(-1), category("") {}

    bool operator==(const Student& s)
    {
        return s.number == number;
    }

    /// overloading << operator
    friend std::ostream& operator<<(std::ostream& output, const Student& s)
    {
        output << std::left << std::setw(14) << s.number << std::setw(14) << s.name << std::setw(14) << s.gender << std::setw(14) << s.age << std::setw(14) << s.category;
        return output;
    }
};

/// ת��һ�£�����ӿ�����ѧ���ҵ������еĽڵ�i
int findNodeFromNumber(List<Student>& List, int num)
{
    for (int i = 1; i <= List.size(); i++)
    {
        Student stu = List.getElement(i);
        if (stu.number == num)
            return i;
    }
    return -1;
}


/// detail operation in mainScene func
void mainPrint(List<Student>& List)
{
//#if defined(__WIN32__)
    std::cout << std::endl << std::left << std::setw(14) << "����" << std::setw(14) << "����" << std::setw(14) << "�Ա�" << std::setw(14) << "����" << std::setw(14) << "�������" << std::endl;
//#elif defined(__linux__)
//    std::cout << std::endl << std::left << std::setw(16) << "����" << std::setw(16) << "����" << std::setw(16) << "�Ա�" << std::setw(16) << "����" << std::setw(18) << "�������" << std::endl;
//#endif
    PrintCon(List);
}

Student readStudent()
{
    Student student;
    while (1)
    {
        std::cin >> student.number >> student.name >> student.gender >> student.age >> student.category;
        if (student.number < 0 || student.number > 0x3f3f3f3f || student.age < 0 || student.age > 150 || !std::cin)
        {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cerr << "���뿼��/���䲻����, ����������" << std::endl;
            continue;
        }
        break;
    }
    return student;
}

void mainInsert(int i, List<Student>& List)
{
    Student student = readStudent();
    if (List.getElement(List.find(student)).number == student.number)
    {
        std::cout << "�����ظ���" << endl;
        return;
    }

    List.insert(i, student);
    if (i == List.size() + 1)
        List.push_back(student);
}

/// scene where main function go in
void mainScene(List<Student>& List)
{
    std::cout << "�����뽨��������Ϣϵͳ��" << std::endl;
    std::cout << "�����뿼��������";


    int n;      ///< student number
    std::cin >> n;
    if (!cin || n < 0 || n > 0x3f3f3f3f)
    {
        std::cout << "�����������󣬳����˳�" << std::endl;
        EnterToExit();
    }



    std::cout << "���������뿼���Ŀ��š��������Ա����估�������" << std::endl;
    for (int i = 1; i <= n; i++)
    {
        Student student = readStudent();

        if (List.getElement(List.find(student)).number == student.number)
        {
            std::cout << "�����ظ��������˳��������´򿪣�" << endl;
            return;
        }

        List.push_back(student);
    }

    mainPrint(List);
    // the begin input is over 
    /// ****************************************************************
    // 0~4 operation
    while (1)
    {
        std::cout << std::endl << select_string << std::endl;
        int n;          ///< select operation
        std::cin >> n;

        if (n == 1)
        {
            int i;                ///< �ڵ�λ��
            std::cout << "��������Ҫ����Ŀ�����λ�ã�";
            std::cin >> i;
            if (i <= 0 || i > List.size() + 1)
            {
                std::cerr << "����λ�÷Ƿ���" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                continue;
            }
            std::cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << std::endl;
            mainInsert(i, List);
            mainPrint(List);
        }
        else if (n == 2)
        {
            int num;              ///< ����
            std::cout << "��������Ҫɾ���Ŀ����Ŀ��ţ�";
            std::cin >> num;
            int i = findNodeFromNumber(List, num);

            //�쳣����

            if (i == -1)
            {
                std::cout << "�������" << std::endl;
                EnterToExit();
            }
            std::cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << List.getElement(i) << std::endl;
            List.erase(i);
            mainPrint(List);


        }
        else if (n == 3)
        {
            int num;              ///< ����
            std::cout << "��������Ҫ���ҵĿ����Ŀ��ţ�";
            std::cin >> num;
            int i = findNodeFromNumber(List, num);
            if (i == -1)
            {
                std::cerr << "���ҷǷ���" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                continue;
            }
            //#if defined(__WIN32__)
                std::cout << std::endl << std::left << std::setw(14) << "����" << std::setw(14) << "����" << std::setw(14) << "�Ա�" << std::setw(14) << "����" << std::setw(14) << "�������" << std::endl;
            //#elif defined(__linux__)
            //    std::cout << std::endl << std::left << std::setw(16) << "����" << std::setw(16) << "����" << std::setw(16) << "�Ա�" << std::setw(16) << "����" << std::setw(18) << "�������" << std::endl;
            //#endif
            std::cout << List.getElement(i) << std::endl;
        }
        else if (n == 4)
        {
            int num;              ///< ����
            std::cout << "��������Ҫ�޸ĵĿ����Ŀ��ţ�";
            std::cin >> num;
            int i = findNodeFromNumber(List, num);
            if (i == -1)
            {
                std::cerr << "���ҷǷ���" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                continue;
            }
            std::cout << "�ÿ����޸�ǰ����ϢΪ��" << List.getElement(i) << std::endl;
            std::cout << "������Ҫ�޸ĵ���Ϣ��";
            List.modify(i, readStudent());
            mainPrint(List);
        }
        else if (n == 5)
        {
            mainPrint(List);
        }
        else if (n == 0)
        {
            break;
        }
    }
}

int main()
{
    List<Student> List;
    mainScene(List);
    return 0;
}