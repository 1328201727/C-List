#include <iostream>
#include "List.h"
using namespace std;
List::List(int* array, int cap = 1)			//ͨ�����鹹������
{
	if (!cap) { first = last = 0; size = 0; }		//���cap=0�����������
	else
	{
		Node* p = new Node(array[0]);		//�����׽��
		first = p;
		last = p;
		for (int i = 1; i < cap; ++i)
		{
			p = new Node(array[i]);		//���������㲢����
			last->next = p;
			(p->pre) = last;
			last = p;
		}
		size = cap;						//����size
		last->next = 0;
	}
}
List::List(const List& a)		//����������
{
	if (a.empty())
	{
		first = 0; last = 0; size = 0; return;		//a����Ϊ�գ����������
	}
	first = new Node((a.first)->val);			//�����׽��
	last = first;
	size = a.size;
	for (Node* p1 = ((a.first)->next); p1; p1 = p1->next)	//����
	{
		Node* p2 = new Node(p1->val);			//���������㲢����
		last->next = p2;
		p2->pre = last;
		last = p2;
	}
}
List::~List()		//�����������ͷŴ洢�ռ�
{
	if (size > 0) {
		Node* p;
		for (p = first; first != last;)		//������β���֮������н��
		{
			first = first->next;
			delete p;
			p = first;
		}
		delete last;		//����β���
	}
}
bool List::insert(Node* posi, const int& d)		//��������d
{
	if (posi == 0) return false;	//����ַ��Ч������false
	Node* p = new Node(d);		//��������Ϊd�Ľ��
	Node* p2 = posi->next;		//����õ�ַָ�������һ���
	p->next = p2;					//����ָ�뽫p��������
	posi->next = p;
	p->pre = posi;
	p2->pre = p;
	if (posi == last) last = p;		//���posiָ��β��㣬����last
	size++;						//����size
	return true;
}
bool List::erase(Node* posi, int h = 1)		//ɾ���ض����ݣ���ָ��ɾ��������Ĭ��ɾ����һ��
{
	int n;					//�ú�������Һ������ɾ���ض�����
	if (posi == 0)
		return false;		//��ַ��Ч������false
	else if (posi == first)	//��ַָ���׽��
	{
		n = first->val;
		first = first->next;	//����ָ��
		first->pre = 0;
		delete posi;		//�ͷſռ�
	}
	else if (posi == last)		//��ַָ��β���
	{
		n = last->val;
		last = last->pre;		//����ָ��
		last->next = 0;
		if(posi!=0) delete posi;		//�ͷſռ�
	}
	else					//�������
	{
		n = posi->val;
		posi->pre->next = posi->next;		//����ָ��
		posi->next->pre = posi->pre;
		if (posi != 0) delete posi;		//�ͷſռ�
	}
	size--;					//����size
	if (h > 1) erase(find(n), --h);			//���ָ����������1������ɾ��
	return true;			//����true
}
List& List::operator=(const List& a)		//������=������
{
	if (a.empty())		//a����Ϊ������
	{
		first = last = 0; size = 0; return *this;	//���������
	}
	else				//a����ǿ�
	{
		if (this != &a)	//��ǰ������a����ͬ
		{
			this->~List();					//������ǰ����
			new (this) List(a);				//����a����
		}
		return *this;
	}
}
Node* List::find(const int& d)				//�����ض����ݵĵ�ַ
{
	Node* p = first;			//���׽�㿪ʼ
	for (; p; p = p->next)		//����
		if ((p->val) == d)
			break;			//�ҵ�������ѭ��
	return p;				//�ҵ��򷵻ص�ַ���Ҳ�����������Ϊ��ʱ��p��ָ����Ч��ַ
}
void List::print() const			//����ȫ�������
{
	if (size == 0) cout << "List is empty!" << endl;	//����Ϊ��ʱ���
	else
	{
		Node* p = first;
		for (; p != last; p = p->next)		//����ǿ�ʱ��ͷ����
			cout << p->val << " ";		//������
		cout << last->val << endl;		//���β������ݼ�����
	}
}
void List::_print()					//����ȫ�������
{
	if (size == 0) cout << "List is empty!" << endl;	//����Ϊ��ʱ���
	else
	{
		Node* p = last;
		for (; p != first; p = p->pre)			//����ǿ�ʱ��β����
			cout << p->val << " ";			//������
		cout << first->val << endl;			//���ͷ������ݼ�����
	}
}
void List::clear()					//���������������
{
	if (this->size != 0) 
	{
		this->~List();					//��������
		first = last = 0;				//���������
		size = 0;						//����size
	}
}
void List::swap(List& H, Node* p, Node* t)		//����H�����ض�λ�õ����ݣ�pΪǰ��㣬tΪ����
{
	Node* temp;
	if (p == 0 || t == 0) return;	//����ַ��Ч����������
	if (t->next == 0)			//t��β���
	{
		if (p->next == t)		//p��t����
		{
			t->next = p;		//����ָ��
			t->pre = p->pre;
			t->pre->next = t;
			p->pre = t;
			p->next = 0;
			H.last = p;
		}
		else				//p��t������
		{
			t->next = p->next;		//����ָ��
			t->pre->next = p;
			temp = t->pre;
			t->pre = p->pre;
			p->next->pre = t;
			if (p->pre != 0)			//p�����׽��
				p->pre->next = t;
			else H.first = t;			//p���׽��
			p->pre = temp;
			p->next = 0;
			H.last = p;
		}
	}
	else 					//t����β���
	{
		if (p->next == t)		//p��t����
		{
			t->next->pre = p;		//����ָ��
			temp = t->next;
			t->next = p;
			p->next = temp;
			t->pre = p->pre;
			if (p->pre != 0)		//p�����׽��
				p->pre->next = t;
			else H.first = t;		//p���׽��
			p->pre = t;
		}
		else				//p��t������
		{
			t->next->pre = p;		//����ָ��
			temp = t->next;
			t->next = p->next;
			p->next->pre = t;
			p->next = temp;
			t->pre->next = p;
			temp = t->pre;
			t->pre = p->pre;
			if (p->pre != 0)		//p�����׽��
				p->pre->next = t;
			else H.first = t;		//p���׽��
			p->pre = temp;
		}
	}
}
bool List::sort(Node* s, Node* e)			//���ض�λ��֮������ݰ���������
{
	if (s == 0 || e == 0) return false;			//����ַ��Ч������false
	if (s == e || empty()) return false;			//s��e֮���޽���������Ϊ�շ���false
	Node* i, * j, * k;
	for (i = s; i != e->next; i = k->next)			//����sָ��ָ������eָ��ָ����֮��
	{
		for (j = i->next, k = i; j != e->next; j = j->next)
			if (k->val > j->val)				//����������
				k = j;
		if (i != k)							//��Ҫ���н���
			swap(*this, i, k);				//���ú�������
	}
	return true;							//������ɣ�����true
}
void List::push_front(const int& d)			//ͷ��
{
	Node* p = new Node(d);		//��������Ϊd�Ľ��
	Node* temp = first;			//����ԭfirstָ���ַ
	first = p;					//����ָ��
	temp->pre = p;
	p->next = temp;
	if (!last)					//ԭ����Ϊ��
		last = p;					//����last
	size++;						//����size
}
void List::push_back(const int& d)			//β��
{
	Node* p = new Node(d);		//��������Ϊd�Ľ��
	if (!empty())				//ԭ����ǿ�
	{
		p->pre = last;			//����ָ��
		last->next = p;
		last = p;
	}
	else						//ԭ����Ϊ��
	{
		first = last = p;			//����first��last
	}
	size++;						//����size
}
void List::pop_front()			//ͷɾ
{
	if (first)					//ԭ����ǿ�
	{
		Node* p = first;			//����ָ��
		first = first->next;
		first->pre = 0;
		size--;					//����size
		delete p;				//�ͷſռ�
	}
	if (!first)					//ͷɾ������Ϊ��
		last = 0;					//����last
}
void List::pop_back()			//βɾ
{
	if (last)					//ԭ����ǿ�
	{
		Node* p = last;			//����ָ��
		last = last->pre;
		last->next = 0;
		size--;					//����size
		delete p;				//�ͷſռ�
	}
	if (!last)					//βɾ������Ϊ��
		first = 0;				//����first
}
bool List::update(int i, int val = 0)	//�Ե�i���������ݽ����޸�
{
	if (i > size || i <= 0) return false;	//��ʱ�޷����ģ�ֱ�ӷ��ؿ���Ϣ
	if (i == 1)						//�Ե�һ��������ݽ����޸�
	{
		first->val = val;				//�޸�����
		return true;				//�޸ĳɹ�������true
	}
	Node* p = first;
	for (int j = 1; j < i; ++j)			//�������ҵ�i�����
		p = p->next;
	p->val = val;						//�����޸�
	return true;					//�޸ĳɹ�������true
}
bool List::update(Node* z, int da)		//�޸�ָ��zָ���������
{
	if (z == 0) return false;			//��ַ��Ч������false
	z->val = da;						//��ַ��Ч�������޸�
	return true;					//����true
}
List& List::operator+=(List& a)		//������+=������
{
	if (a.size > 0)
	{
		int b = a.size;
		Node* p = a.first;
		while (b--)
		{
			push_back(p->val);		//���ڵ����
			p = p->next;			//ת����һ��
		}
	}
	return *this;
}
bool List::empty() const			//�ж������Ƿ�Ϊ��
{
	if (first == last && first == 0)		//��ʱ����Ϊ��
		return true;				//����true
	else return false;				//����ǿշ���false
}
int List::getval(int i)				//��ȡ��i����������
{
	if (i == 1 || i > size || i <= 0)			//��i����㲻���ڻ���i=1
		return first->val;			//���ص�һ����������
	Node* p = first;
	for (int j = 1; j < i; ++j)			//�������ҵ�i�����
		p = p->next;
	return p->val;					//���ظý���ֵ
}
bool List::reverse()			//������з�ת
{
	if (getsize() > 1)				//size>1��ת��������
	{
		Node* i = 0;
		Node* j = 0;
		Node* k = first;			//
		Node* temp = first;
		while (k != 0)				//�����н��ָ������޸�
		{
			j = k->next;
			k->next = i;			//�޸ĵ�ǰ�����ָ��
			k->pre = j;			//�޸ĵ�ǰ���ǰ��ָ��
			i = k;
			k = j;				//ת����һ���
		}
		first = i;				//����first
		last = temp;				//����last
		return true;			//��ת�ɹ�����true
	}
	return false;				//δ��ת����false
}