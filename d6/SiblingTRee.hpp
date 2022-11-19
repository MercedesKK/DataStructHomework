/* @author �ž��� */
#pragma once 
#include <string>
#include <iostream>
using namespace std;

/// @brief ��ͥ��
struct Family
{
	using FamilyPtr = Family*;

	string name;		///< ��Ա����
	int childCnt;		///< �ó�Ա���к�����
	FamilyPtr father;	///< ��ָ��
	FamilyPtr broNext;	///< �ֵܺ�ָ��
	FamilyPtr broPrev;	///< �ֵ�ǰָ��
	FamilyPtr child;	///< ����ָ��

	Family() : name(""), childCnt(0), father(nullptr), broNext(nullptr), broPrev(nullptr), child(nullptr) {}
};

/**
* @class SiblingList
* @brief �ֵܽ�����
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
	FamilyPtr ancestor;	///< ����
};

void SiblingTree::setAncestor()
{
	cout << "���Ƚ���һ������" << endl << "���������ȵ�������";
	cin >> ancestor->name;
	cout << "�˼��׵������ǣ�" << ancestor->name << endl << endl;
	cout << "��ѡ��Ҫִ�еĲ�����";
}

void SiblingTree::showChild(FamilyPtr familyNode) const
{
	if (familyNode->childCnt == 0)
	{
		cout << familyNode->name << "û�к��" << endl;
		return;
	}

	FamilyPtr temp = familyNode->child;
	cout << familyNode->name << "�ĵ�һ�������ǣ�";
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
	cout << "������Ҫ������ͥ���˵�������";
	cin >> name;
	FamilyPtr p = findMember(name, ancestor);
	if (p == nullptr)
	{
		cout << "���޴���" << endl;
		return;
	}

	if (p->child)
	{
		cout << p->name << "�Ѿ��齨��ͥ" << endl;
		return;
	}

	cout << "������" << p->name << "�Ķ�Ů������";
	cin >> p->childCnt;
	if (p->childCnt == 0)
		return;

	cout << "����������" << p->name << "�Ķ�Ů��������";
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
	cout << "������Ҫ��Ӷ��ӣ�Ů�������˵�������";
	string name;
	cin >> name;
	FamilyPtr p = findMember(name, ancestor);

	if (p == nullptr) 
	{
		cout << "���޴���" << endl;
		return;
	}

	cout << "������" << name << "����ӵĶ��ӣ���Ů������������";
	FamilyPtr child = new Family();
	child->father = p;
	p->childCnt++;
	cin >> child->name;

	// ԭ��û�к���
	if (!p->child)
	{
		p->child = child;
		showChild(p);
		return;
	}
	// ԭ���к��ӣ���Ҫ���ֵ��ϲ���
	FamilyPtr temp = p->child;
	while (temp->broNext)
		temp = temp->broNext;
	temp->broNext = child;
	child->broPrev = temp;
	showChild(p);
}

void SiblingTree::divMember()
{
	cout << "������Ҫ��ɢ�ļ�ͥ���˵�������";
	string name;
	cin >> name;
	Family* p = findMember(name, ancestor);
	if (p == nullptr)
	{
		cout << "���޴���" << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << p->name << endl;

	showChild(p);
	if (p->child == nullptr)
		cout << "���Ƴ�����" << endl;

	//��������۽�ɢ��ͥ��Ա����Ҫ��Ϊ�Ƿ���ǰ�ֵܺͺ��ֵ�
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
	cout << "������Ҫ�����������˵�Ŀǰ��������";
	string name;
	cin >> name;
	FamilyPtr p = findMember(name, ancestor);
	cout << "��������ĺ��������";
	cin >> p->name;
	cout << name << "�Ѹ���Ϊ��" << p->name;
}


Family* SiblingTree::findMember(string name, FamilyPtr key)
{
	FamilyPtr ans = nullptr, p = key;
	
	if (p->name == name)
		return p;

	// �ֵ�ָ����Ѱ��
	while (p->broNext)
	{
		ans = findMember(name, p->broNext);
		if (ans)
			return ans;
		p = p->broNext;
	}

	// ������Ѱ��
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
		destroy(temp->broNext);		// �����ýڵ��ɾ���˽ڵ�(��child)
	}

	if (temp->child)
		destroy(temp->child);

	delete familyNode;
}