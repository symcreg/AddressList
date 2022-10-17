//��������
//ɾ�����ܴ�д
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
			nf.write((const char*)&num, sizeof(int));//�״γ�ʼ��numΪ��
		}else {
			nf.read((char*)&num, sizeof(int));
		}
		nf.close();
		
		choice = 0;
		cout << "||ͨѶ¼||" << endl << "0.��ʾ���� " << endl << "1.���" << endl << "2.ɾ��" << endl << "3.����" << endl << "4.�޸�" << endl << "5.���" << endl << "6.�˳�" << endl;

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
			cout << "����Ҫ���ҵ����֣�";
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
			cout << "��ϵ��" << i + 1 << ":" << endl;
			cout << "������" << p->name << endl << "�Ա�" << p->gender << endl << "���䣺" << p->age << endl << "�绰��" << p->phone << endl << "��ַ��" << p->address << endl;
			cout << endl;
			delete p;
		}
		list.close();
	}
	
}
void add() {
	person *p = new person;
	cout << "������";
	cin >> p->name;
	cout << "�Ա�";
	cin >> p->gender;
	cout << "���䣺";
	cin >> p->age;
	cout << "�绰��";
	cin >> p->phone;
	cout << "��ַ��";
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
	cout << "����Ҫɾ������ϵ�����֣�";
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
			list.seekg(sizeof(person)*i, ios::beg);//����
			list.read((char*)p, sizeof(person));
			if (arg == 0) {
				cout << "������" << p->name << endl << "�Ա�" << p->gender << endl << "���䣺" << p->age << endl << "�绰��" << p->phone << endl << "��ַ��" << p->address << endl;
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
				list.seekg(sizeof(person) * i, ios::beg);//����
								
				person* del = new person;
				memset(del, 0, sizeof(person));
				list.write((const char*)del, sizeof(person));//ɾ��
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
				list.seekg(sizeof(person) * i, ios::beg);//����
				person *change = new person;
				cout << "�޸�Ϊ��" << endl;
				cout << "������";
				cin >> change->name;
				cout << "�Ա�";
				cin >> change->gender;
				cout << "���䣺";
				cin >> change->age;
				cout << "�绰��";
				cin >> change->phone;
				cout << "��ַ��";
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
	cout << "δ�ҵ������Ƶ���ϵ��" << endl;
	list.close();
}
void change() {
	cout << "����Ҫ���ĵ���ϵ�����֣�";
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