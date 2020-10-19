#include<iostream>
#include<fstream>
using namespace std;
#define MAX 10
/*程序功能：
将两个长度不超过10的有序整数集合A和B合并为一个有序整数集合C。
用数组（顺序存储结构）表示这两个集合，针对这种存储结构设计算法。
*/

//定义一个存放整数的顺序线性表
typedef struct {
	int data[MAX];
	int len;//指示线性表长度
} sqlist;

//初始化线性表
void initSqlist(sqlist &li){ 
	cout << "集合长度：";
	cin>>li.len;
	cout<<"输入集合内容："<<endl;
	for(int i =0;i < li.len;i++){
		cin>>li.data[i];
	}
}
//读入文件内容初始化线性表
int initSqlist(sqlist &li,char *fname) {
	fstream file;
	file.open(fname);
	if (!file) { cout << "error" << endl; return 0; }
	int i = 0;
	while(!file.eof()) {
		file >> li.data[i++];
	}
	li.len = i;
	file.close();
	return 1;
}

//带参数的初始化线性表
void initSqlist(sqlist &li, int n, int data[]) {
	li.len = n;
	for (int i = 0; i < li.len; i++) {
		li.data[i] = data[i];
	}
}

//把两个线性表a、b合并为新的线性表c
void merge(sqlist a,sqlist b,sqlist &c){
	int la = a.len;int lb = b.len;
	c.len = 0;
	int pc = 0, pa = 0, pb = 0;//pa指示线性表a的元素，pb指示线性表b的元素,pc指示线性表c的元素
	//比较pa与pb所指元素，把较小的存入线性表c
	for(;pa < la && pb < lb;pc++){
		if(a.data[pa] <= b.data[pb]){
			if (a.data[pa] == b.data[pb])pb++;//当pa与pb所指元素相同，则pb指向它的后继，避免存入的元素重复
			c.data[pc] = a.data[pa];
			c.len += 1;
			pa++;
		}
		else{
			c.data[pc] = b.data[pb];
			c.len += 1;
			pb++;
		}
	}
	//把剩余的元素存入线性表c
	if((lb-pb) > (la-pa)){
		for(int j = pc;pb < lb;j++){
			c.data[j] = b.data[pb];
			c.len += 1;
			pb++;
		}
	}
	else {
		for (int j = pc; pa < la; j++) {
			c.data[j] = a.data[pa];
			c.len += 1;
			pa++;
		}
	}
}

//显示线性表内容
void dispSqlist(sqlist a){
	for(int i = 0;i < a.len;i++){
		cout<<a.data[i]<<" ";
	}
	cout<<endl;
}

int main(){
	sqlist A,B,C;
	int a[5] = { 1,5,6,7,8 };
	int b[4] = { 1,2,5,9 };
	initSqlist(A, 5, a);
	initSqlist(B, 4, b);
	cout << "有序集合的合并" << endl;
	/*cout << "集合A:" << endl;
	initSqlist(A);
	cout << "集合B:" << endl;
	initSqlist(B);*/
	/*cout << "输入集合A的文件名：";
	char fname[50];
	cin >> fname;
	initSqlist(A, fname);*/
	cout << "集合A:" << endl;
	dispSqlist(A);
	/*cout << "输入集合B的文件名：";
	cin >> fname;
	initSqlist(B, fname);*/
	cout << "集合B" << endl;
	dispSqlist(B);
	cout<<"合并中......"<<endl;
	merge(A,B,C);
	cout<<"合并后的集合C："<<endl;
	dispSqlist(C);
	//cout << C.len << endl;
	return 0;
}
