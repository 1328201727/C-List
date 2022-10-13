# C-Projects
## 自己动手实现List链表类
### 不带头双向非循环链表
链表由许多不连续的结点连接而成，每一个结点都由三部分组成：数据域、前驱指针，后继指针，因此可以对整个链表的数据进行访问。
### 实现的主要成员函数及功能说明:
```cpp
List
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
```
### 特性
双向链表，访问更加方便高效<br>
成员函数实现较多，实现思路更加独特
## 感谢大家的支持
