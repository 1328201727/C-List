#include <iostream>
#include "List.h"
using namespace std;
int main()
{
	int a[11] = { 15,1,8,3,4,5,6,7,8,9,10 };
	List b(a, 11);
	List c = b;
	b.print();					//15 1 8 3 4 5 6 7 8 9 10
	b.reverse();
	b.print();					//10 9 8 7 6 5 4 3 8 1 15
	b.reverse();
	b.update(3, 11);
	b.print();					//15 1 11 3 4 5 6 7 8 9 10
	b.update(b.find(6), 12);
	b.print();					//15 1 11 3 4 5 12 7 8 9 10
	b._print();					//10 9 8 7 12 5 4 3 11 1 15
	b.erase(b.find(8),1);
	b.print();					//15 1 11 3 4 5 12 7 9 10
	c.print();					//15 1 8 3 4 5 6 7 8 9 10
	c.pop_back();
	c.print();					//15 1 8 3 4 5 6 7 8 9
	c.push_back(50);
	c.print();					//15 1 8 3 4 5 6 7 8 9 50
	c.pop_front();
	c.print();					//1 8 3 4 5 6 7 8 9 50
	c.push_front(12);
	c.print();					//12 1 8 3 4 5 6 7 8 9 50
	List d = c;
	d.insert(d.find(1), 20);
	d.print();					//12 1 20 8 3 4 5 6 7 8 9 50
	d.swap(d, d.begin(), d.find(20));
	d.print();					//20 1 12 8 3 4 5 6 7 8 9 50
	d.sort(d.begin(), d.end());
	d.print();					//1 3 4 5 6 7 8 8 9 12 20 50
	cout << b.getval(3) << endl;	//11
	d.clear();
	d.push_back(12);
	d.push_back(23);
	d.print();					//12 23
	c += d;
	c.print();					//12 1 8 3 4 5 6 7 8 9 50 12 23
	c.erase(c.find(12), 2);
	c.print();					//1 8 3 4 5 6 7 8 9 50 23
	cout << c.getsize();			//11
	return 0;
}