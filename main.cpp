//九月五日
//删除功能待写
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct person {
	char name[100];
	char gender[20];
	int age;
	int phone;
	char address[20];
};

void show();
void add();
void del();
int search(char [100], int);
void change();
void clear();
int num;
int f = 1;
char name[100];
int main() {
	
	
	int choice = 0;
	
	while (choice != 6) {
		

		fstream nf("num", ios::out | ios::in | ios::binary | ios::app);
		if (!nf.good()) {
			nf.write((const char*)&num, sizeof(int));//首次初始化num为零
		}else {
			nf.read((char*)&num, sizeof(int));
		}
		nf.close();
		
		choice = 0;
		cout << "||通讯录||" << endl << "0.显示所有 " << endl << "1.添加" << endl << "2.删除" << endl << "3.查找" << endl << "4.修改" << endl << "5.清空" << endl << "6.退出" << endl;

		cin >> choice;
		switch (choice)
		{
		case 0:
			show();
			break;

		case 1:
			add();
			break;
		case 2:
			del();
			break;

		case 3:
			cout << "输入要查找的名字：";
			cin >> name;
			search(name,0);
			break;
		case 4:
			change();
			break;

		case 5:
			clear();
			break;
		default:
			break;
			return 0;
		}

		
	}
	
	return 0;
}

void show() {
	if (num == 0) {
		cout << "null" << endl;
	}
	else {
		fstream list("save", ios::in | ios::out | ios::binary);
		
		for (int i = 0; i < num; i++){
			person* p = new person;
			list.read((char*)p, sizeof(person));
			cout << "联系人" << i + 1 << ":" << endl;
			cout << "姓名：" << p->name << endl << "性别：" << p->gender << endl << "年龄：" << p->age << endl << "电话：" << p->phone << endl << "地址：" << p->address << endl;
			cout << endl;
			delete p;
		}
		list.close();
	}
	
}
void add() {
	person *p = new person;
	cout << "姓名：";
	cin >> p->name;
	cout << "性别：";
	cin >> p->gender;
	cout << "年龄：";
	cin >> p->age;
	cout << "电话：";
	cin >> p->phone;
	cout << "地址：";
	cin >> p->address;

	fstream list("save", ios::in | ios::out | ios::app | ios::binary | ios::ate);
	list.write((const char*)p, sizeof(person));
	list.close();
	num++;
	
	fstream n("num", ios::in | ios::out | ios::binary );
	n.write((const char*)&num, sizeof(int));
	n.close();

	delete p;
	list.close();
	
}
void del() {
	cout << "输入要删除的联系人名字：";
	cin >> name;
	search(name, 1);
}
int search(char name[100], int arg) {
	person *buff = new person;
	
	person* p = new person;
	fstream list("save", ios::in | ios::out | ios::binary);
	int i = 0;
	while (i<num) {
		
		list.read((char*)buff, sizeof(person));
		if (!strcmp(buff->name,name)) {
			list.seekg(sizeof(person)*i, ios::beg);//回退
			list.read((char*)p, sizeof(person));
			if (arg == 0) {
				cout << "姓名：" << p->name << endl << "性别：" << p->gender << endl << "年龄：" << p->age << endl << "电话：" << p->phone << endl << "地址：" << p->address << endl;
				delete p;
				delete buff;
				list.close();
				return 0;
			}
			else if (arg == 1) {
				num--;
				fstream n;
				n.open("num", ios::in | ios::out | ios::app | ios::binary);
				n.write((const char*)&num, sizeof(int));
				n.close();	
				list.seekg(sizeof(person) * i, ios::beg);//回退
								
				person* del = new person;
				memset(del, 0, sizeof(person));
				list.write((const char*)del, sizeof(person));//删除
				//
				//
				//
				cout << "NONE" << endl;

				/*{
					list.write("", sizeof(person));
				}*/

				delete del;
				delete p;
				delete buff;
				list.close();
				return 0;
			}
			else if (arg == 2) {
				list.seekg(sizeof(person) * i, ios::beg);//回退
				person *change = new person;
				cout << "修改为：" << endl;
				cout << "姓名：";
				cin >> change->name;
				cout << "性别：";
				cin >> change->gender;
				cout << "年龄：";
				cin >> change->age;
				cout << "电话：";
				cin >> change->phone;
				cout << "地址：";
				cin >> change->address;
				list.write((const char*)change, sizeof(person));

				delete change;
				delete p;
				delete buff;
				return 0;
				list.close();
			}
		}
		i++;
	}
	cout << "未找到该名称的联系人" << endl;
	list.close();
}
void change() {
	cout << "输入要更改的联系人名字：";
	cin >> name;
	search(name, 2);
}
void clear() {
	num = 0;
	fstream n;
	n.open("num", ios::in | ios::out | ios::binary | ios::trunc);
	n.close();
	fstream list;
	list.open("save", ios::in | ios::out | ios::binary | ios::trunc);
	list.close();
}