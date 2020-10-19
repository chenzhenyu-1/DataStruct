#include<iostream>
#include<fstream>
using namespace std;
#define MAX 10
/*�����ܣ�
���������Ȳ�����10��������������A��B�ϲ�Ϊһ��������������C��
�����飨˳��洢�ṹ����ʾ���������ϣ�������ִ洢�ṹ����㷨��
*/

//����һ�����������˳�����Ա�
typedef struct {
	int data[MAX];
	int len;//ָʾ���Ա���
} sqlist;

//��ʼ�����Ա�
void initSqlist(sqlist &li){ 
	cout << "���ϳ��ȣ�";
	cin>>li.len;
	cout<<"���뼯�����ݣ�"<<endl;
	for(int i =0;i < li.len;i++){
		cin>>li.data[i];
	}
}
//�����ļ����ݳ�ʼ�����Ա�
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

//�������ĳ�ʼ�����Ա�
void initSqlist(sqlist &li, int n, int data[]) {
	li.len = n;
	for (int i = 0; i < li.len; i++) {
		li.data[i] = data[i];
	}
}

//���������Ա�a��b�ϲ�Ϊ�µ����Ա�c
void merge(sqlist a,sqlist b,sqlist &c){
	int la = a.len;int lb = b.len;
	c.len = 0;
	int pc = 0, pa = 0, pb = 0;//paָʾ���Ա�a��Ԫ�أ�pbָʾ���Ա�b��Ԫ��,pcָʾ���Ա�c��Ԫ��
	//�Ƚ�pa��pb��ָԪ�أ��ѽ�С�Ĵ������Ա�c
	for(;pa < la && pb < lb;pc++){
		if(a.data[pa] <= b.data[pb]){
			if (a.data[pa] == b.data[pb])pb++;//��pa��pb��ָԪ����ͬ����pbָ�����ĺ�̣���������Ԫ���ظ�
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
	//��ʣ���Ԫ�ش������Ա�c
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

//��ʾ���Ա�����
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
	cout << "���򼯺ϵĺϲ�" << endl;
	/*cout << "����A:" << endl;
	initSqlist(A);
	cout << "����B:" << endl;
	initSqlist(B);*/
	/*cout << "���뼯��A���ļ�����";
	char fname[50];
	cin >> fname;
	initSqlist(A, fname);*/
	cout << "����A:" << endl;
	dispSqlist(A);
	/*cout << "���뼯��B���ļ�����";
	cin >> fname;
	initSqlist(B, fname);*/
	cout << "����B" << endl;
	dispSqlist(B);
	cout<<"�ϲ���......"<<endl;
	merge(A,B,C);
	cout<<"�ϲ���ļ���C��"<<endl;
	dispSqlist(C);
	//cout << C.len << endl;
	return 0;
}
