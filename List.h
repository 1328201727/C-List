#pragma once
struct Node
{
	Node(const int& d) :val(d), pre(0), next(0) {}
	int val;
	Node* pre;				//前驱结点指针
	Node* next;				//后继结点指针
};
class List
{
	Node* first, * last;		//first指针与last指针
	int size;				//链表长度
public:
	List() { first = 0; last = 0; size = 0; }
	List(int* array, int cap);				//通过数组构造链表
	List(const List& a);					//链表拷贝构造
	~List();								//链表析构，释放存储空间
	bool insert(Node* posi, const int& d);	//插入数据d
	bool erase(Node* posi, int h);			//删除特定数据，可指定删除几个
	List& operator=(const List& a);			//链表类=的重载
	Node* find(const int& d);				//查找特定数据的地址
	void print() const;						//正向全链表输出
	void _print();							//反向全链表输出
	void clear();							//清除链表所有数据
	void swap(List& H, Node* p, Node* t);		//交换H链表特定位置的数据，p为前结点，t为后结点
	bool sort(Node* p, Node* t);				//对特定位置之间的数据按升序排序
	void push_front(const int& d);			//头插
	void push_back(const int& d);			//尾插
	void pop_front();						//头删
	void pop_back();						//尾删
	bool update(int i, int val);				//对第i个结点的数据进行修改
	bool update(Node* z, int da);			//修改指针z指向结点的数据
	List& operator+=(List& a);				//链表类+=的重载
	bool empty() const;						//判断链表是否为空
	int getval(int i);						//获取第i个结点的数据
	int getsize() { return size; }			//获取链表长度
	bool reverse();							//链表进行反转
	Node* begin() { return first; }			//获取链表首结点地址
	Node* end() { return last; }				//获取链表尾结点地址
};