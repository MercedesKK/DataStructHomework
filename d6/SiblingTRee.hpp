/* @author 张靖凯 */
#pragma once 
#include <string>
#include <iostream>
using namespace std;

/// @brief 家庭类
struct Family
{
	using FamilyPtr = Family*;

	string name;		///< 成员名字
	int childCnt;		///< 该成员所有孩子数
	FamilyPtr father;	///< 父指针
	FamilyPtr broNext;	///< 兄弟后指针
	FamilyPtr broPrev;	///< 兄弟前指针
	FamilyPtr child;	///< 孩子指针

	Family() : name(""), childCnt(0), father(nullptr), broNext(nullptr), broPrev(nullptr), child(nullptr) {}
};

/**
* @class SiblingList
* @brief 兄弟姐妹树
*/
class SiblingTree
{
public:
	using FamilyPtr = Family*;

public:
	SiblingTree() :ancestor(new Family()) {}
	~SiblingTree() { destroy(ancestor); }

	FamilyPtr findMember(string name, FamilyPtr key);
	void destroy(FamilyPtr familyNode);

	void setAncestor();
	void showChild(FamilyPtr familyNode) const;

	/// @name operations
	/// @{
	void perfectFamily();
	void addMember();
	void divMember();
	void changeMember();
	/// @}
	// end of operations

private:
	FamilyPtr ancestor;	///< 祖先
};

void SiblingTree::setAncestor()
{
	cout << "首先建立一个家谱" << endl << "请输入祖先的姓名：";
	cin >> ancestor->name;
	cout << "此家谱的祖先是：" << ancestor->name << endl << endl;
	cout << "请选择要执行的操作：";
}

void SiblingTree::showChild(FamilyPtr familyNode) const
{
	if (familyNode->childCnt == 0)
	{
		cout << familyNode->name << "没有后代" << endl;
		return;
	}

	FamilyPtr temp = familyNode->child;
	cout << familyNode->name << "的第一代子孙是：";
	for (int i = 0; i < familyNode->childCnt; i++)
	{
		cout << temp->name << " ";
		if (temp->broNext)
			temp = temp->broNext;
	}
}

void SiblingTree::perfectFamily()
{
	string name;
	cout << "请输入要建立家庭的人的姓名：";
	cin >> name;
	FamilyPtr p = findMember(name, ancestor);
	if (p == nullptr)
	{
		cout << "查无此人" << endl;
		return;
	}

	if (p->child)
	{
		cout << p->name << "已经组建家庭" << endl;
		return;
	}

	cout << "请输入" << p->name << "的儿女个数：";
	cin >> p->childCnt;
	if (p->childCnt == 0)
		return;

	cout << "请依次输入" << p->name << "的儿女的姓名：";
	p->child = new Family();
	FamilyPtr temp = p->child;
	cin >> temp->name;
	temp->father = p;
	for (int i = 1; i < p->childCnt; i++)
	{
		FamilyPtr bro = new Family();
		cin >> bro->name;
		bro->father = p;
		bro->broPrev = temp;
		temp->broNext = bro;
		temp = temp->broNext;
	}

	showChild(p);
}

void SiblingTree::addMember()
{
	cout << "请输入要添加儿子（女儿）的人的姓名：";
	string name;
	cin >> name;
	FamilyPtr p = findMember(name, ancestor);

	if (p == nullptr) 
	{
		cout << "查无此人" << endl;
		return;
	}

	cout << "请输入" << name << "新添加的儿子（或女儿）的姓名：";
	FamilyPtr child = new Family();
	child->father = p;
	p->childCnt++;
	cin >> child->name;

	// 原来没有孩子
	if (!p->child)
	{
		p->child = child;
		showChild(p);
		return;
	}
	// 原来有孩子，需要在兄弟上操作
	FamilyPtr temp = p->child;
	while (temp->broNext)
		temp = temp->broNext;
	temp->broNext = child;
	child->broPrev = temp;
	showChild(p);
}

void SiblingTree::divMember()
{
	cout << "请输入要解散的家庭的人的姓名：";
	string name;
	cin >> name;
	Family* p = findMember(name, ancestor);
	if (p == nullptr)
	{
		cout << "查无此人" << endl;
		return;
	}
	cout << "要解散家庭的人是：" << p->name << endl;

	showChild(p);
	if (p->child == nullptr)
		cout << "仅移除此人" << endl;

	//分情况讨论解散家庭成员，主要分为是否有前兄弟和后兄弟
	if (p->broPrev && p->broNext)
	{
		p->broNext->broPrev = p->broPrev;
		p->broPrev->broNext = p->broNext;
		p->father->childCnt--;
	}
	if (p->broPrev && !p->broNext)
	{
		p->broPrev->broNext = nullptr;
		p->father->childCnt--;
	}
	if (!p->broPrev && p->broNext)
	{
		p->father->child = p->broNext;
		p->broNext->broPrev = nullptr;
		p->father->childCnt--;
	}
	if (!p->broNext && !p->broPrev)
	{
		p->father->child = nullptr;
		p->father->childCnt--;
	}
	if (p->child)
		destroy(p->child);

	delete p;
}

void SiblingTree::changeMember()
{
	cout << "请输入要更改姓名的人的目前的姓名：";
	string name;
	cin >> name;
	FamilyPtr p = findMember(name, ancestor);
	cout << "请输入更改后的姓名：";
	cin >> p->name;
	cout << name << "已更名为：" << p->name;
}


Family* SiblingTree::findMember(string name, FamilyPtr key)
{
	FamilyPtr ans = nullptr, p = key;
	
	if (p->name == name)
		return p;

	// 兄弟指针中寻找
	while (p->broNext)
	{
		ans = findMember(name, p->broNext);
		if (ans)
			return ans;
		p = p->broNext;
	}

	// 孩子中寻找
	p = key;
	if (p->child)
	{
		ans = findMember(name, p->child);
		if (ans)
			return ans;
	}

	return ans;
}

void SiblingTree::destroy(FamilyPtr familyNode)
{
	FamilyPtr temp = familyNode;

	while (temp->broNext)
		temp = temp->broNext;

	while (temp->broPrev)
	{
		temp = temp->broPrev;
		temp->broNext->broPrev = nullptr;
		temp->broNext->broNext = nullptr;
		destroy(temp->broNext);		// 孤立该节点后删除此节点(含child)
	}

	if (temp->child)
		destroy(temp->child);

	delete familyNode;
}