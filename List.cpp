#include <iostream>
#include "List.h"
using namespace std;
List::List(int* array, int cap = 1)			//通过数组构造链表
{
	if (!cap) { first = last = 0; size = 0; }		//如果cap=0，构造空链表
	else
	{
		Node* p = new Node(array[0]);		//构造首结点
		first = p;
		last = p;
		for (int i = 1; i < cap; ++i)
		{
			p = new Node(array[i]);		//构造其余结点并连接
			last->next = p;
			(p->pre) = last;
			last = p;
		}
		size = cap;						//更新size
		last->next = 0;
	}
}
List::List(const List& a)		//链表拷贝构造
{
	if (a.empty())
	{
		first = 0; last = 0; size = 0; return;		//a链表为空，构造空链表
	}
	first = new Node((a.first)->val);			//构造首结点
	last = first;
	size = a.size;
	for (Node* p1 = ((a.first)->next); p1; p1 = p1->next)	//遍历
	{
		Node* p2 = new Node(p1->val);			//构造其余结点并连接
		last->next = p2;
		p2->pre = last;
		last = p2;
	}
}
List::~List()		//链表析构，释放存储空间
{
	if (size > 0) {
		Node* p;
		for (p = first; first != last;)		//析构除尾结点之外的所有结点
		{
			first = first->next;
			delete p;
			p = first;
		}
		delete last;		//析构尾结点
	}
}
bool List::insert(Node* posi, const int& d)		//插入数据d
{
	if (posi == 0) return false;	//若地址无效，返回false
	Node* p = new Node(d);		//构造数据为d的结点
	Node* p2 = posi->next;		//保存该地址指向结点的下一结点
	p->next = p2;					//调整指针将p连入链表
	posi->next = p;
	p->pre = posi;
	p2->pre = p;
	if (posi == last) last = p;		//如果posi指向尾结点，更新last
	size++;						//更新size
	return true;
}
bool List::erase(Node* posi, int h = 1)		//删除特定数据，可指定删除几个，默认删除第一个
{
	int n;					//该函数与查找函数配合删除特定数据
	if (posi == 0)
		return false;		//地址无效，返回false
	else if (posi == first)	//地址指向首结点
	{
		n = first->val;
		first = first->next;	//调整指针
		first->pre = 0;
		delete posi;		//释放空间
	}
	else if (posi == last)		//地址指向尾结点
	{
		n = last->val;
		last = last->pre;		//调整指针
		last->next = 0;
		if(posi!=0) delete posi;		//释放空间
	}
	else					//其余情况
	{
		n = posi->val;
		posi->pre->next = posi->next;		//调整指针
		posi->next->pre = posi->pre;
		if (posi != 0) delete posi;		//释放空间
	}
	size--;					//更新size
	if (h > 1) erase(find(n), --h);			//如果指定个数大于1，继续删除
	return true;			//返回true
}
List& List::operator=(const List& a)		//链表类=的重载
{
	if (a.empty())		//a链表为空链表
	{
		first = last = 0; size = 0; return *this;	//构造空链表
	}
	else				//a链表非空
	{
		if (this != &a)	//当前链表与a链表不同
		{
			this->~List();					//析构当前链表
			new (this) List(a);				//拷贝a链表
		}
		return *this;
	}
}
Node* List::find(const int& d)				//查找特定数据的地址
{
	Node* p = first;			//从首结点开始
	for (; p; p = p->next)		//遍历
		if ((p->val) == d)
			break;			//找到则跳出循环
	return p;				//找到则返回地址，找不到或者链表为空时，p都指向无效地址
}
void List::print() const			//正向全链表输出
{
	if (size == 0) cout << "List is empty!" << endl;	//链表为空时输出
	else
	{
		Node* p = first;
		for (; p != last; p = p->next)		//链表非空时从头遍历
			cout << p->val << " ";		//逐个输出
		cout << last->val << endl;		//输出尾结点数据及换行
	}
}
void List::_print()					//反向全链表输出
{
	if (size == 0) cout << "List is empty!" << endl;	//链表为空时输出
	else
	{
		Node* p = last;
		for (; p != first; p = p->pre)			//链表非空时从尾遍历
			cout << p->val << " ";			//逐个输出
		cout << first->val << endl;			//输出头结点数据及换行
	}
}
void List::clear()					//清除链表所有数据
{
	if (this->size != 0) 
	{
		this->~List();					//析构链表
		first = last = 0;				//构造空链表
		size = 0;						//更新size
	}
}
void List::swap(List& H, Node* p, Node* t)		//交换H链表特定位置的数据，p为前结点，t为后结点
{
	Node* temp;
	if (p == 0 || t == 0) return;	//若地址无效，跳出函数
	if (t->next == 0)			//t是尾结点
	{
		if (p->next == t)		//p与t相邻
		{
			t->next = p;		//调整指针
			t->pre = p->pre;
			t->pre->next = t;
			p->pre = t;
			p->next = 0;
			H.last = p;
		}
		else				//p与t不相邻
		{
			t->next = p->next;		//调整指针
			t->pre->next = p;
			temp = t->pre;
			t->pre = p->pre;
			p->next->pre = t;
			if (p->pre != 0)			//p不是首结点
				p->pre->next = t;
			else H.first = t;			//p是首结点
			p->pre = temp;
			p->next = 0;
			H.last = p;
		}
	}
	else 					//t不是尾结点
	{
		if (p->next == t)		//p与t相邻
		{
			t->next->pre = p;		//调整指针
			temp = t->next;
			t->next = p;
			p->next = temp;
			t->pre = p->pre;
			if (p->pre != 0)		//p不是首结点
				p->pre->next = t;
			else H.first = t;		//p是首结点
			p->pre = t;
		}
		else				//p与t不相邻
		{
			t->next->pre = p;		//调整指针
			temp = t->next;
			t->next = p->next;
			p->next->pre = t;
			p->next = temp;
			t->pre->next = p;
			temp = t->pre;
			t->pre = p->pre;
			if (p->pre != 0)		//p不是首结点
				p->pre->next = t;
			else H.first = t;		//p是首结点
			p->pre = temp;
		}
	}
}
bool List::sort(Node* s, Node* e)			//对特定位置之间的数据按升序排序
{
	if (s == 0 || e == 0) return false;			//若地址无效，返回false
	if (s == e || empty()) return false;			//s与e之间无结点或者链表为空返回false
	Node* i, * j, * k;
	for (i = s; i != e->next; i = k->next)			//遍历s指针指向结点与e指针指向结点之间
	{
		for (j = i->next, k = i; j != e->next; j = j->next)
			if (k->val > j->val)				//按升序排序
				k = j;
		if (i != k)							//需要进行交换
			swap(*this, i, k);				//调用函数交换
	}
	return true;							//排序完成，返回true
}
void List::push_front(const int& d)			//头插
{
	Node* p = new Node(d);		//构造数据为d的结点
	Node* temp = first;			//保存原first指针地址
	first = p;					//调整指针
	temp->pre = p;
	p->next = temp;
	if (!last)					//原链表为空
		last = p;					//调整last
	size++;						//更新size
}
void List::push_back(const int& d)			//尾插
{
	Node* p = new Node(d);		//构造数据为d的结点
	if (!empty())				//原链表非空
	{
		p->pre = last;			//调整指针
		last->next = p;
		last = p;
	}
	else						//原链表为空
	{
		first = last = p;			//更新first及last
	}
	size++;						//更新size
}
void List::pop_front()			//头删
{
	if (first)					//原链表非空
	{
		Node* p = first;			//调整指针
		first = first->next;
		first->pre = 0;
		size--;					//更新size
		delete p;				//释放空间
	}
	if (!first)					//头删后链表为空
		last = 0;					//更新last
}
void List::pop_back()			//尾删
{
	if (last)					//原链表非空
	{
		Node* p = last;			//调整指针
		last = last->pre;
		last->next = 0;
		size--;					//更新size
		delete p;				//释放空间
	}
	if (!last)					//尾删后链表为空
		first = 0;				//更新first
}
bool List::update(int i, int val = 0)	//对第i个结点的数据进行修改
{
	if (i > size || i <= 0) return false;	//此时无法更改，直接返回空信息
	if (i == 1)						//对第一个结点数据进行修改
	{
		first->val = val;				//修改数据
		return true;				//修改成功，返回true
	}
	Node* p = first;
	for (int j = 1; j < i; ++j)			//遍历查找第i个结点
		p = p->next;
	p->val = val;						//进行修改
	return true;					//修改成功，返回true
}
bool List::update(Node* z, int da)		//修改指针z指向结点的数据
{
	if (z == 0) return false;			//地址无效，返回false
	z->val = da;						//地址有效，进行修改
	return true;					//返回true
}
List& List::operator+=(List& a)		//链表类+=的重载
{
	if (a.size > 0)
	{
		int b = a.size;
		Node* p = a.first;
		while (b--)
		{
			push_back(p->val);		//将节点接入
			p = p->next;			//转到下一个
		}
	}
	return *this;
}
bool List::empty() const			//判断链表是否为空
{
	if (first == last && first == 0)		//此时链表为空
		return true;				//返回true
	else return false;				//链表非空返回false
}
int List::getval(int i)				//获取第i个结点的数据
{
	if (i == 1 || i > size || i <= 0)			//第i个结点不存在或者i=1
		return first->val;			//返回第一个结点的数据
	Node* p = first;
	for (int j = 1; j < i; ++j)			//遍历查找第i个结点
		p = p->next;
	return p->val;					//返回该结点的值
}
bool List::reverse()			//链表进行反转
{
	if (getsize() > 1)				//size>1反转才有意义
	{
		Node* i = 0;
		Node* j = 0;
		Node* k = first;			//
		Node* temp = first;
		while (k != 0)				//对所有结点指针进行修改
		{
			j = k->next;
			k->next = i;			//修改当前结点后继指针
			k->pre = j;			//修改当前结点前驱指针
			i = k;
			k = j;				//转到下一结点
		}
		first = i;				//更新first
		last = temp;				//更新last
		return true;			//反转成功返回true
	}
	return false;				//未反转返回false
}