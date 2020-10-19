#include<stdio.h>
#include<malloc.h>
/*
使用栈结构实现含括号的算术四则运算的表达式求值
*/
typedef struct node {
	char sym;
	float num;
	node *next;
} *link;
typedef struct stack {
	link head;
	int len;
	bool f;//ture is num;false is sym;
};
void init(stack &s,bool f) {
	s.head = NULL;
	s.len = 0;
	s.f = f;
}
void push(stack &s, char c) {
	link p = (link)malloc(sizeof(node));
	p->sym = c;
	if (s.head == NULL) {
		p->next = NULL;
		s.head = p;
	}
	else {
		p->next = s.head;
		s.head = p;
	}
	s.len++;
}
void push(stack &s, float c) {
	link p = (link)malloc(sizeof(node));
	p->num = c;
	if (s.head == NULL) {
		p->next = NULL;
		s.head = p;
	}
	else {
		p->next = s.head;
		s.head = p;
	}
	s.len++;
}
char popC(stack &s) {
	link p = s.head;
	if (!p)return 0;
	char e;
	e = p->sym;
	s.head = p->next;
	free(p);
	return e;
}
float popN(stack &s) {
	link p = s.head;
	if (!p)return 0;
	float e;
	e = p->num;
	s.head = p->next;
	free(p);
	return e;
}
void visit(stack s) {
	link p = s.head;
	while (p) {
		if (s.f)
			printf("%.0f ", p->num);
		else
			printf("%c", p->sym);
		p = p->next;
	}
	printf("\n");
}
char getHead(stack &s) {
		return s.head->sym;
}
char cmp(char a, char b) {
	switch (a) {
	case '+':
		switch (b) {
		case '*': return '<'; break;
		case '/': return '<'; break;
		case '(': return '<'; break;
		default:return '>'; break;
		}
	case '-':
		switch (b) {
		case '*': return '<'; break;
		case '/': return '<'; break;
		case '(': return '<'; break;
		default:return '>'; break;
		}
	case '*':
		switch (b) {
		case '(': return '<'; break;
		default:return '>'; break;
		}
	case '/':
		switch (b) {
		case '(': return '<'; break;
		default:return '>'; break;
		}
	case '(':
		switch (b) {
		case ')': return '='; break;
		case '#': return 'E'; break;
		default:return '<'; break;
		}
	case ')':
		switch (b) {
		case '(': return 'E'; break;
		default:return '>'; break;
		}
	case '#':
		return '<';
	}
}
float jisuan(float n1, char c, float n2) {
	switch (c)
	{
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	case '*':
		return n1 * n2;
	case '/':
		return n1 / n2;
	}
}
void main() { 
	stack OPTR, OPND;
	init(OPTR, false); init(OPND, true);
	push(OPTR, '#');
	char s, c;
	float n1, n2;
	scanf("%c", &s);
	while (true) {
		//visit(OPTR);
		//visit(OPND);
		if (s >= '0'&&s <= '9') {
			push(OPND, float(s - '0'));
		}
		else {
			switch (cmp(getHead(OPTR), s)) {
			case '<':
				push(OPTR, s); break;
			case '=':
				popC(OPTR); break;
			case '>':
				n2 = popN(OPND); c = popC(OPTR); n1 = popN(OPND); push(OPND, jisuan(n1, c, n2)); continue;
			}
		}
		if (s == '#')break;
		scanf("%c", &s);
	}
	printf("计算结果：%f\n", popN(OPND));
}