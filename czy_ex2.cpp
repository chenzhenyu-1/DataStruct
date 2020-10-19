#include<iostream>
/*
编写一个一元多项式相加的程序。要求利用单链表表示一元多项式，
并且能实现两个一元多项式的输入，并能进行建立、输出以及相加操作
*/
using namespace std;
typedef struct node{
	double coef;
	int expn;
	node* next;
};
typedef struct Polyn{
	node* head;
	int len;
};
//void initPolyn(Polyn &a,int m) {
//	a.head = new node;
//	a.head->expn = -1;
//	a.len = m;
//	node *p = a.head;
//	for (int i = 0; i < m; i++) {
//		p->next = new node;
//		p = p->next;
//		cout << "输入第" << i + 1 << "项系数和指数：" << endl;
//		cin >> p->coef >> p->expn;
//		if (i == m - 1)
//			p->next = NULL;
//	}
//}
void initPolyn(Polyn &a, int m,double c[],int e[]) {
	a.head = new node;
	a.head->expn = -1;
	a.len = m;
	node *p = a.head;
	for (int i = 0; i < m; i++) {
		p->next = new node;
		p = p->next;
		p->coef = c[i];
		p->expn = e[i];
		if (i == m - 1)
			p->next = NULL;
	}
}
void dispPolyn(Polyn a) {
	if (a.head->expn != -1)exit(1);
	node *p = a.head->next;
	while (p!=NULL)
	{
		cout << "(" << p->coef << "*x^" << p->expn << ")";
		if (p->next != NULL)cout << "+";
		else cout << endl;
		p = p->next;
	}
}
void addPolyn(Polyn &a,Polyn &b) {
	node *pa, *ha, *pb, *hb;
	ha = a.head; hb = b.head;
	pa = a.head->next; pb = b.head->next;
	while (pa != NULL&&pb != NULL) {
		if (pa->expn < pb->expn) {
			ha = pa; pa = pa->next;
		}
		else if (pa->expn == pb->expn) {
			pa->coef += pb->coef;
			hb->next = pb->next;
			if (pa->coef == 0) {
				ha->next = pa->next;
				delete pa;
				pa = ha->next;
				a.len--;
			}
			delete pb;
			pb = hb->next;
			b.len--;
		}
		else {
			hb->next = pb->next;
			ha->next = pb;
			pb->next = pa;
			ha = pa;
			pb = hb->next;
			pa = pa->next;
			a.len++;
			b.len--;
		}
		if (pa == NULL) {
			if (hb != b.head)
				ha->next = hb;
			else if (pb != NULL)
				ha->next = pb;
			pb = NULL;
			a.len += b.len;
			delete b.head;
		}
		else if(pb == NULL){
			if (hb != b.head) {
				hb->next = pa->next;
				pa->next = hb;
				pa = NULL;
				a.len++;
			}
			delete b.head;
		}
	}
}
Polyn multiPolyn(Polyn a, Polyn b) {
	Polyn res,temp;
	res.head = new node; temp.head = new node;
	res.head->expn = -1; temp.head->expn = -1;
	res.head->next = NULL; temp.head->next = NULL;
	res.len = 0; temp.len = 0;
	node *p = res.head, *pa = a.head->next, *pb = b.head->next;
	for (int i = 0; i < a.len; i++) {
		p->next = new node;
		p = p->next;
		p->coef = (pa->coef) * (pb->coef);
		p->expn = (pa->expn) + (pb->expn);
		pa = pa->next;
		res.len++;
		if (i == a.len - 1)p->next = NULL;
	}
	p = temp.head; pa = a.head->next; pb = b.head->next;
	for (int j = 1; j < b.len; j++) {
		pb = pb->next;
		for (int k = 0; k < a.len; k++) {
			p->next = new node;
			p = p->next;
			p->coef = (pa->coef) * (pb->coef);
			p->expn = (pa->expn) + (pb->expn);
			pa = pa->next;
			temp.len++;
			if (k == a.len - 1)p->next = NULL;
		}
		addPolyn(res, temp);
		temp.head = new node;
		temp.head->expn = -1;
		temp.head->next = NULL;
		temp.len = 0;
		pa = a.head->next;
	}
	return res;
}

int main() {
	Polyn a,b,c;
	double x1[4] = { 2,2.3,1.2,7 }, x2[4] = {-2,-1.3,3,-6};
	int z1[4] = { 1,2 ,10,15}, z2[4] = {1,2,3,15};
	initPolyn(a, 4, x1, z1);
	initPolyn(b, 4, x2, z2);
	dispPolyn(a);
	dispPolyn(b);
	addPolyn(a, b);
	dispPolyn(a);
	return 0;
}