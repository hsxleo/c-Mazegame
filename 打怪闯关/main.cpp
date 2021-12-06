#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include "player.h"
#include "monster.h"
#include "equip.h"
#include "map.h"

using namespace std;


void movePlayer(vector<Map> map);  //����ƶ�

//��ҽ�ɫ
Player player;
//װ������
vector<Equip> equip;
//��������
vector<Monster> monster;
//���صĵ�ͼ
vector<Map> map1;
vector<Map> map2;


//��ȡװ����Ϣ
void readEquip() {
	ifstream inf;  //�ļ�ָ��
	string str;
	inf.open("equip.txt");
	while (getline(inf, str)) {
		istringstream input(str);  //����һ��istringstream����input
		string s;

		//��ȡһ�е����ݵ���ʱ����t����
		Equip t;
		input >> s;
		t.name = s;
		input >> s;
		t.bloodAdd = stoi(s);
		input >> s;
		t.atkAdd = stoi(s);
		input >> s;
		t.atkSpeedAdd = stoi(s);
		input >> s;
		t.price = stoi(s);

		//����ʱ����t����equip����
		equip.push_back(t);
	}
	inf.close();
}

//��ȡ������Ϣ
void readMonster() {
	ifstream inf;  //�ļ�ָ��
	string str;
	inf.open("monster.txt");
	while (getline(inf, str)) {
		istringstream input(str);  //����һ��istringstream����input
		string s;

		//��ȡһ�е����ݵ���ʱ����t����
		Monster t;
		input >> s;
		t.name = s;
		input >> s;
		t.blood = stoi(s);
		input >> s;
		t.atk = stoi(s);
		input >> s;
		t.atkSpeed = stoi(s);
		input >> s;
		t.exp = stoi(s);
		t.equip = equip[rand() % equip.size()];   //�����Ұ�����װ��

		//����ʱ����t����monster����
		monster.push_back(t);
	}
	inf.close();
}

//��ȡ��ͼ�ļ�
void readMap() {  
	ifstream inf;  //�ļ�ָ��
	string str;
	int x;  //������
	int y;  //������

	//��ȡmap1
	inf.open("map1.txt");
	x = 0;
	while (getline(inf, str)) {
		istringstream input(str);  //����һ��istringstream����input
		string s;
		y = 0;
		while (input >> s) {
			Map t;
			t.x = x;
			t.y = y;
			t.sige = stoi(s);
			if (t.sige == 1) {   //С��
				t.monster = monster[rand() % (monster.size() - 2)];   
			}
			else if (t.sige == 8) {  //boss
				t.monster = monster[monster.size() - 2]; 
			}
			map1.push_back(t);  //��������ӵ�map1��
			y++;
		}
		x++;
	}
	inf.close();


	//��ȡmap2
	inf.open("map2.txt");
	x = 0;
	while (getline(inf, str)) {
		istringstream input(str);  //����һ��istringstream����input
		string s;
		y = 0;
		while (input >> s) {
			Map t;
			t.x = x;
			t.y = y;
			t.sige = stoi(s);
			if (t.sige == 1) {   //С��
				t.monster = monster[rand() % (monster.size() - 2)];
			}
			else if (t.sige == 8) {  //boss
				t.monster = monster[monster.size() - 1];  //�������Ϊboss
			}

			map2.push_back(t);  //��������ӵ�map2��
			y++;
		}
		x++;
	}
	inf.close();
}

//��ҽ�ɫ����
void createPlayer() {
	cout << "���´��ң�Ұ�޺��У���ҪӢ��������..." << endl;
	Sleep(1000);
	cout << "����������Ҫ�Ľ�ɫ����:";
	cin >> player.name;
	player.blood = 2500;
	player.atk = 250;
	player.atkSpeed = 2;
	player.x = 0;
	player.y = 0;
	cout << "��ɫ���ɳɹ�:" << endl;
	cout << "����:" << player.name << endl;
	cout << "Ѫ��:" << player.blood << endl;
	cout << "������:" << player.atk << endl;
	cout << "�����ٶ�:" << player.atkSpeed << endl;
	cout << "�밴�������ʼ���Ӣ��֮��..." << endl;
	_getch();
}

//�̵�
void shop(vector<Map> map) {
	system("cls");
	using std::cout;
	cout.setf(std::ios::left);  //�����
	cout << "Ӣ���̵�" << endl;
	cout << setw(10) << "װ������" << setw(10) << "Ѫ���ӳ�"
		<< setw(10) << "�������ӳ�" << setw(10) << "���ټӳ�" << setw(10) << "�۸�" << endl;
	for (int i = 0; i < equip.size(); i++) {
		cout << setw(10) <<equip[i].name << setw(10) << equip[i].bloodAdd << setw(10)
			<< equip[i].atkAdd << setw(10) << equip[i].atkSpeedAdd << setw(10) << equip[i].price << endl;
	}
	while (true) {
		cout << "���롮n���˳�Ӣ���̵�" << endl;
		cout << "����ǰӵ��" << player.money << "����ң�" << "����������Ҫ����װ��������:";
		string name;
		cin >> name;
		if (name == "n") {
			break;
		}
		int flag = 0;
		for (int i = 0; i < equip.size(); i++) {
			if (equip[i].name == name) {
				flag = 1;
				if (equip[i].price <= player.money) {
					player.equip.push_back(equip[i]);
					player.money -= equip[i].price;
					cout << "����ɹ���" << endl;
					break;
				}
				cout << "��Ǯ����!" << endl;
			}
		}
		if (flag == 0) {
			cout << "��װ��������!" << endl;
		}
	}
	movePlayer(map);
}

//�����
void fightMonster(vector<Map> map,int index) {
	system("cls");
	cout << "��������" << endl;

	//���˫����������
	cout << setw(10) << "����" << setw(10) << "Ѫ��"
		<< setw(10) << "������" << setw(10) << "����" << setw(10) << "װ��" << endl;
	cout << "\n��������:" << endl;
	cout << setw(10) << map[index].monster.name << setw(10) << map[index].monster.blood
		<< setw(10) << map[index].monster.atk << setw(10) << map[index].monster.atkSpeed 
		<< setw(10) << map[index].monster.equip.name << endl;
	cout << "\n�������:" << endl;
	cout << setw(10) << player.name << setw(10) << player.blood
		<< setw(10) << player.atk << setw(10) << player.atkSpeed;
	for (int i = 0; i < player.equip.size(); i++) {
		cout << setw(10) << player.equip[i].name;
	}
	cout << endl;


	cout << "\n˫��׼��ս����  ����װ���ӳ�...\n";
	map[index].monster.equipAdd();
	player.equipAdd();
	Sleep(2000);

	//���˫������װ��������
	cout << setw(10) << "����" << setw(10) << "Ѫ��"
		<< setw(10) << "������" << setw(10) << "����" << setw(10) << "װ��" << endl;
	cout << "\n��������:" << endl;
	cout << setw(10) << map[index].monster.name << setw(10) << map[index].monster.blood
		<< setw(10) << map[index].monster.atk << setw(10) << map[index].monster.atkSpeed
		<< setw(10) << map[index].monster.equip.name << endl;
	cout << "\n�������:" << endl;
	cout << setw(10) << player.name << setw(10) << player.blood
		<< setw(10) << player.atk << setw(10) << player.atkSpeed;
	for (int i = 0; i < player.equip.size(); i++) {
		cout << setw(10) << player.equip[i].name;
	}
	cout << endl;
	
	cout << "\n�밴�������ʼս��:\n";
	_getch();
	cout << "˫������ս���У���ȴ�...\n";
	Sleep(3000);
	for (int i = 1;; i++) {
		if (player.atk * player.atkSpeed * i >= map[index].monster.blood) {
			//����װ��
			cout << "��ϲ��ɱ��" << map[index].monster.name << "�����" << map[index].monster.equip.name
				<< "��" << map[index].monster.exp << "����" << endl;
			player.exp += map[index].monster.exp;
			player.equip.push_back(map[index].monster.equip);
			if (player.isUpGrade()) {  //�ж�Ӣ���Ƿ�����
				cout << "Ӣ�������������������ӣ�����ý�ҽ��ͣ�" << endl;
			}
			cout << "�밴���������...";
			_getch();
			movePlayer(map);
		}
		else if (map[index].monster.atk * map[index].monster.atkSpeed * i >= player.blood) {
			cout << "ս��ʧ�ܣ�Ӣ������" << endl;
			cout << "5������̵긴��...";
			Sleep(5000);
			shop(map1);
		}
	}
	
}

//��boss
void fightBoss(vector<Map> map, int index) {
	system("cls");
	cout << "����boss" << endl;

	//���˫����������
	cout << setw(10) << "����" << setw(10) << "Ѫ��"
		<< setw(10) << "������" << setw(10) << "����" << setw(10) << "װ��" << endl;
	cout << "\nboss����:" << endl;
	cout << setw(10) << map[index].monster.name << setw(10) << map[index].monster.blood
		<< setw(10) << map[index].monster.atk << setw(10) << map[index].monster.atkSpeed
		<< setw(10) << map[index].monster.equip.name << endl;
	cout << "\n�������:" << endl;
	cout << setw(10) << player.name << setw(10) << player.blood
		<< setw(10) << player.atk << setw(10) << player.atkSpeed;
	for (int i = 0; i < player.equip.size(); i++) {
		cout << setw(10) << player.equip[i].name;
	}
	cout << endl;


	cout << "\n˫��׼��ս����  ����װ���ӳ�...\n";
	map[index].monster.equipAdd();
	player.equipAdd();
	Sleep(2000);

	//���˫������װ��������
	cout << setw(10) << "����" << setw(10) << "Ѫ��"
		<< setw(10) << "������" << setw(10) << "����" << setw(10) << "װ��" << endl;
	cout << "\nboss����:" << endl;
	cout << setw(10) << map[index].monster.name << setw(10) << map[index].monster.blood
		<< setw(10) << map[index].monster.atk << setw(10) << map[index].monster.atkSpeed
		<< setw(10) << map[index].monster.equip.name << endl;
	cout << "\n�������:" << endl;
	cout << setw(10) << player.name << setw(10) << player.blood
		<< setw(10) << player.atk << setw(10) << player.atkSpeed;
	for (int i = 0; i < player.equip.size(); i++) {
		cout << setw(10) << player.equip[i].name;
	}
	cout << endl;

	cout << "\n�밴�������ʼս��:\n";
	_getch();
	cout << "˫������ս���У���ȴ�...\n";
	Sleep(5000);
	for (int i = 1;; i++) {
		if (player.atk * player.atkSpeed * i >= map[index].monster.blood) {
			//�ж��ǲ��ǵڶ��ص�boss��ɱ
			if (map[index].monster.name == "��������") {
				cout << "��ϲ��Hero,���������������磡" << endl;
				cout << "��������˳���Ϸ..." << endl;
				_getch();
				exit(0);
			}
			cout << "��ϲ��ɱ��" << map[index].monster.name << "��������һ��" << endl;
			player.x = 0;
			player.y = 0;
			player.exp += map[index].monster.exp;
			if (player.isUpGrade()) {  //�ж�Ӣ���Ƿ�����
				cout << "Ӣ�������������������ӣ�����ý�ҽ��ͣ�" << endl;
			}
			cout << "�밴���������...";
			_getch();
			movePlayer(map2);
		}
		else if (map[index].monster.atk * map[index].monster.atkSpeed * i >= player.blood) {
			cout << "��սʧ�ܣ�Ӣ������" << endl;
			cout << "5������̵긴��...";
			Sleep(5000);
			shop(map);
		}
	}
}

//�ж��������������λ��
void judgePlace(vector<Map> map) {
	for (int i = 0; i < 100; i++) {
		if (player.x == map[i].x && player.y == map[i].y) {   //�ҵ���ҵ�λ��
			if (map[i].sige == 9) {  //�����
				player.x = 0;
				player.y = 0;
				shop(map);
			}
			if (map[i].sige == 1) {  //����Ұ��
				fightMonster(map,i);
			}
			else if (map[i].sige == 8) {   //����boss
				fightBoss(map, i);
			}
		}
	}
}

//����ƶ�
void movePlayer(vector<Map> map) {
	system("cls");
	while (true) {
		cout << "\n���������ڵ�λ������Ϊ:[" << player.x << "," << player.y << "]" << endl;
		cout << "������'w','s','a','d',����������ҵ��ƶ�:" << endl;
		char ch;
		cin >> ch;
		switch (ch) {
		case 'w':
		case 'W':
			if (player.x == 0) {
				cout << "�����ƶ�ʧ�ܣ�" << endl;
			}
			else {
				player.x--;
				cout << "�ƶ��ɹ�...";
				Sleep(1000);
				judgePlace(map);
			}
			break;
		case 's':
		case 'S':
			if (player.x == 9) {
				cout << "�����ƶ�ʧ�ܣ�" << endl;
			}
			else {
				player.x++;
				cout << "�ƶ��ɹ�...";
				Sleep(1000);
				judgePlace(map);
			}
			break;
		case 'a':
		case 'A':
			if (player.y == 0) {
				cout << "�����ƶ�ʧ�ܣ�" << endl;
			}
			else {
				player.y--;
				cout << "�ƶ��ɹ�...";
				Sleep(1000);
				judgePlace(map);
			}
			break;
		case 'd':
		case 'D':
			if (player.y  == 9) {
				cout << "�����ƶ�ʧ�ܣ�" << endl;
			}
			else {
				player.y++;
				cout << "�ƶ��ɹ�...";
				Sleep(1000);
				judgePlace(map);
			}
			break;
		default:
			cout << "��������!" << endl;
			break;
		}
	}
}

int main() {
	srand(time(NULL));  //�������

	//��ȡ��Ϸ��Դ�ļ�  ������Ϸ��Դ
	readEquip();
	readMonster();
	readMap();

	//������ɫ
	createPlayer();

	//�̵� -- �����
	shop(map1);


}