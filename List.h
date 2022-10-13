#pragma once
struct Node
{
	Node(const int& d) :val(d), pre(0), next(0) {}
	int val;
	Node* pre;				//ǰ�����ָ��
	Node* next;				//��̽��ָ��
};
class List
{
	Node* first, * last;		//firstָ����lastָ��
	int size;				//������
public:
	List() { first = 0; last = 0; size = 0; }
	List(int* array, int cap);				//ͨ�����鹹������
	List(const List& a);					//����������
	~List();								//�����������ͷŴ洢�ռ�
	bool insert(Node* posi, const int& d);	//��������d
	bool erase(Node* posi, int h);			//ɾ���ض����ݣ���ָ��ɾ������
	List& operator=(const List& a);			//������=������
	Node* find(const int& d);				//�����ض����ݵĵ�ַ
	void print() const;						//����ȫ�������
	void _print();							//����ȫ�������
	void clear();							//���������������
	void swap(List& H, Node* p, Node* t);		//����H�����ض�λ�õ����ݣ�pΪǰ��㣬tΪ����
	bool sort(Node* p, Node* t);				//���ض�λ��֮������ݰ���������
	void push_front(const int& d);			//ͷ��
	void push_back(const int& d);			//β��
	void pop_front();						//ͷɾ
	void pop_back();						//βɾ
	bool update(int i, int val);				//�Ե�i���������ݽ����޸�
	bool update(Node* z, int da);			//�޸�ָ��zָ���������
	List& operator+=(List& a);				//������+=������
	bool empty() const;						//�ж������Ƿ�Ϊ��
	int getval(int i);						//��ȡ��i����������
	int getsize() { return size; }			//��ȡ������
	bool reverse();							//������з�ת
	Node* begin() { return first; }			//��ȡ�����׽���ַ
	Node* end() { return last; }				//��ȡ����β����ַ
};