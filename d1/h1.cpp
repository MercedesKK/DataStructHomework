#include "List.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>

/// using my namespace in case of member function used
using namespace MercedesKK;

static const std::string select_string = "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作";


/// @brief class for student only in this cpp
class Student
{
public:
    int number;             ///< exam number
    std::string name;       ///< student name
    std::string gender;     ///< gender
    int age;                ///< age
    std::string category;   ///< exam for direction

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

/// 转换一下，方便从考生的学号找到链表中的节点i
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
    std::cout << std::endl << std::left << std::setw(14) << "考号" << std::setw(14) << "姓名" << std::setw(14) << "性别" << std::setw(14) << "年龄" << std::setw(14) << "报考类别" << std::endl;
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
            std::cerr << "输入考号/年龄不合理, 请重新输入" << std::endl;
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
        std::cout << "考号重复！" << endl;
        return;
    }

    List.insert(i, student);
    if (i == List.size() + 1)
        List.push_back(student);
}

/// scene where main function go in
void mainScene(List<Student>& List)
{
    std::cout << "首先请建立考生信息系统！" << std::endl;
    std::cout << "请输入考生人数：";


    int n;      ///< student number
    std::cin >> n;
    assert(n >= 0), assert(n < 0x3f3f3f3f);



    std::cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别！" << std::endl;
    for (int i = 1; i <= n; i++)
    {
        Student student = readStudent();

        if (List.getElement(List.find(student)).number == student.number)
        {
            std::cout << "考号重复！程序退出！请重新打开！" << endl;
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
            int i;                ///< 节点位置
            std::cout << "请输入你要插入的考生的位置：";
            std::cin >> i;
            if (i <= 0 || i > List.size() + 1)
            {
                std::cerr << "插入位置非法！" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                continue;
            }
            std::cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << std::endl;
            mainInsert(i, List);
            mainPrint(List);
        }
        else if (n == 2)
        {
            int num;              ///< 考号
            std::cout << "请输入你要删除的考生的考号：";
            std::cin >> num;
            int i = findNodeFromNumber(List, num);

            //异常处理

            if (i == -1)
            {
                throw "未找到";
            }
            std::cout << "你删除的考生信息是：" << List.getElement(i) << std::endl;
            List.erase(i);
            mainPrint(List);


        }
        else if (n == 3)
        {
            int num;              ///< 考号
            std::cout << "请输入你要查找的考生的考号：";
            std::cin >> num;
            int i = findNodeFromNumber(List, num);
            if (i == -1)
            {
                std::cerr << "查找非法！" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                continue;
            }
            std::cout << std::endl << std::left << std::setw(14) << "考号" << std::setw(14) << "姓名" << std::setw(14) << "性别" << std::setw(14) << "年龄" << std::setw(14) << "报考类别" << std::endl;
            std::cout << List.getElement(i) << std::endl;
        }
        else if (n == 4)
        {
            int num;              ///< 考号
            std::cout << "请输入你要修改的考生的考号：";
            std::cin >> num;
            int i = findNodeFromNumber(List, num);
            if (i == -1)
            {
                std::cerr << "查找非法！" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                continue;
            }
            std::cout << "该考生修改前的信息为：" << List.getElement(i) << std::endl;
            std::cout << "请输入要修改的信息：";
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