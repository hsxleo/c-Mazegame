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


void movePlayer(vector<Map> map);  //玩家移动

//玩家角色
Player player;
//装备数组
vector<Equip> equip;
//怪物数组
vector<Monster> monster;
//两关的地图
vector<Map> map1;
vector<Map> map2;


//读取装备信息
void readEquip() {
	ifstream inf;  //文件指针
	string str;
	inf.open("equip.txt");
	while (getline(inf, str)) {
		istringstream input(str);  //创建一个istringstream对象input
		string s;

		//读取一行的内容到临时变量t里面
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

		//将临时变量t存入equip数组
		equip.push_back(t);
	}
	inf.close();
}

//读取怪物信息
void readMonster() {
	ifstream inf;  //文件指针
	string str;
	inf.open("monster.txt");
	while (getline(inf, str)) {
		istringstream input(str);  //创建一个istringstream对象input
		string s;

		//读取一行的内容到临时变量t里面
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
		t.equip = equip[rand() % equip.size()];   //随机给野怪佩戴装备

		//将临时变量t存入monster数组
		monster.push_back(t);
	}
	inf.close();
}

//读取地图文件
void readMap() {  
	ifstream inf;  //文件指针
	string str;
	int x;  //横坐标
	int y;  //纵坐标

	//读取map1
	inf.open("map1.txt");
	x = 0;
	while (getline(inf, str)) {
		istringstream input(str);  //创建一个istringstream对象input
		string s;
		y = 0;
		while (input >> s) {
			Map t;
			t.x = x;
			t.y = y;
			t.sige = stoi(s);
			if (t.sige == 1) {   //小怪
				t.monster = monster[rand() % (monster.size() - 2)];   
			}
			else if (t.sige == 8) {  //boss
				t.monster = monster[monster.size() - 2]; 
			}
			map1.push_back(t);  //将对象添加到map1中
			y++;
		}
		x++;
	}
	inf.close();


	//读取map2
	inf.open("map2.txt");
	x = 0;
	while (getline(inf, str)) {
		istringstream input(str);  //创建一个istringstream对象input
		string s;
		y = 0;
		while (input >> s) {
			Map t;
			t.x = x;
			t.y = y;
			t.sige = stoi(s);
			if (t.sige == 1) {   //小怪
				t.monster = monster[rand() % (monster.size() - 2)];
			}
			else if (t.sige == 8) {  //boss
				t.monster = monster[monster.size() - 1];  //最后两个为boss
			}

			map2.push_back(t);  //将对象添加到map2中
			y++;
		}
		x++;
	}
	inf.close();
}

//玩家角色生成
void createPlayer() {
	cout << "天下大乱，野兽横行，需要英雄来拯救..." << endl;
	Sleep(1000);
	cout << "请输入你想要的角色名称:";
	cin >> player.name;
	player.blood = 2500;
	player.atk = 250;
	player.atkSpeed = 2;
	player.x = 0;
	player.y = 0;
	cout << "角色生成成功:" << endl;
	cout << "名称:" << player.name << endl;
	cout << "血量:" << player.blood << endl;
	cout << "攻击力:" << player.atk << endl;
	cout << "攻击速度:" << player.atkSpeed << endl;
	cout << "请按任意键开始你的英雄之旅..." << endl;
	_getch();
}

//商店
void shop(vector<Map> map) {
	system("cls");
	using std::cout;
	cout.setf(std::ios::left);  //左对齐
	cout << "英雄商店" << endl;
	cout << setw(10) << "装备名称" << setw(10) << "血量加成"
		<< setw(10) << "攻击力加成" << setw(10) << "攻速加成" << setw(10) << "价格" << endl;
	for (int i = 0; i < equip.size(); i++) {
		cout << setw(10) <<equip[i].name << setw(10) << equip[i].bloodAdd << setw(10)
			<< equip[i].atkAdd << setw(10) << equip[i].atkSpeedAdd << setw(10) << equip[i].price << endl;
	}
	while (true) {
		cout << "输入‘n’退出英雄商店" << endl;
		cout << "您当前拥有" << player.money << "个金币，" << "请输入你想要购买装备的名称:";
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
					cout << "购买成功！" << endl;
					break;
				}
				cout << "金钱不足!" << endl;
			}
		}
		if (flag == 0) {
			cout << "该装备不存在!" << endl;
		}
	}
	movePlayer(map);
}

//打怪兽
void fightMonster(vector<Map> map,int index) {
	system("cls");
	cout << "遇到怪兽" << endl;

	//输出双方基本属性
	cout << setw(10) << "名称" << setw(10) << "血量"
		<< setw(10) << "攻击力" << setw(10) << "攻速" << setw(10) << "装备" << endl;
	cout << "\n怪兽属性:" << endl;
	cout << setw(10) << map[index].monster.name << setw(10) << map[index].monster.blood
		<< setw(10) << map[index].monster.atk << setw(10) << map[index].monster.atkSpeed 
		<< setw(10) << map[index].monster.equip.name << endl;
	cout << "\n玩家属性:" << endl;
	cout << setw(10) << player.name << setw(10) << player.blood
		<< setw(10) << player.atk << setw(10) << player.atkSpeed;
	for (int i = 0; i < player.equip.size(); i++) {
		cout << setw(10) << player.equip[i].name;
	}
	cout << endl;


	cout << "\n双方准备战斗中  进行装备加成...\n";
	map[index].monster.equipAdd();
	player.equipAdd();
	Sleep(2000);

	//输出双方加有装备的属性
	cout << setw(10) << "名称" << setw(10) << "血量"
		<< setw(10) << "攻击力" << setw(10) << "攻速" << setw(10) << "装备" << endl;
	cout << "\n怪兽属性:" << endl;
	cout << setw(10) << map[index].monster.name << setw(10) << map[index].monster.blood
		<< setw(10) << map[index].monster.atk << setw(10) << map[index].monster.atkSpeed
		<< setw(10) << map[index].monster.equip.name << endl;
	cout << "\n玩家属性:" << endl;
	cout << setw(10) << player.name << setw(10) << player.blood
		<< setw(10) << player.atk << setw(10) << player.atkSpeed;
	for (int i = 0; i < player.equip.size(); i++) {
		cout << setw(10) << player.equip[i].name;
	}
	cout << endl;
	
	cout << "\n请按任意键开始战斗:\n";
	_getch();
	cout << "双方正在战斗中，请等待...\n";
	Sleep(3000);
	for (int i = 1;; i++) {
		if (player.atk * player.atkSpeed * i >= map[index].monster.blood) {
			//掉落装备
			cout << "恭喜你杀死" << map[index].monster.name << "并获得" << map[index].monster.equip.name
				<< "和" << map[index].monster.exp << "经验" << endl;
			player.exp += map[index].monster.exp;
			player.equip.push_back(map[index].monster.equip);
			if (player.isUpGrade()) {  //判断英雄是否升级
				cout << "英雄升级，基础属性增加，并获得金币奖赏！" << endl;
			}
			cout << "请按任意键继续...";
			_getch();
			movePlayer(map);
		}
		else if (map[index].monster.atk * map[index].monster.atkSpeed * i >= player.blood) {
			cout << "战斗失败！英雄阵亡" << endl;
			cout << "5秒后在商店复活...";
			Sleep(5000);
			shop(map1);
		}
	}
	
}

//打boss
void fightBoss(vector<Map> map, int index) {
	system("cls");
	cout << "遇到boss" << endl;

	//输出双方基本属性
	cout << setw(10) << "名称" << setw(10) << "血量"
		<< setw(10) << "攻击力" << setw(10) << "攻速" << setw(10) << "装备" << endl;
	cout << "\nboss属性:" << endl;
	cout << setw(10) << map[index].monster.name << setw(10) << map[index].monster.blood
		<< setw(10) << map[index].monster.atk << setw(10) << map[index].monster.atkSpeed
		<< setw(10) << map[index].monster.equip.name << endl;
	cout << "\n玩家属性:" << endl;
	cout << setw(10) << player.name << setw(10) << player.blood
		<< setw(10) << player.atk << setw(10) << player.atkSpeed;
	for (int i = 0; i < player.equip.size(); i++) {
		cout << setw(10) << player.equip[i].name;
	}
	cout << endl;


	cout << "\n双方准备战斗中  进行装备加成...\n";
	map[index].monster.equipAdd();
	player.equipAdd();
	Sleep(2000);

	//输出双方加有装备的属性
	cout << setw(10) << "名称" << setw(10) << "血量"
		<< setw(10) << "攻击力" << setw(10) << "攻速" << setw(10) << "装备" << endl;
	cout << "\nboss属性:" << endl;
	cout << setw(10) << map[index].monster.name << setw(10) << map[index].monster.blood
		<< setw(10) << map[index].monster.atk << setw(10) << map[index].monster.atkSpeed
		<< setw(10) << map[index].monster.equip.name << endl;
	cout << "\n玩家属性:" << endl;
	cout << setw(10) << player.name << setw(10) << player.blood
		<< setw(10) << player.atk << setw(10) << player.atkSpeed;
	for (int i = 0; i < player.equip.size(); i++) {
		cout << setw(10) << player.equip[i].name;
	}
	cout << endl;

	cout << "\n请按任意键开始战斗:\n";
	_getch();
	cout << "双方正在战斗中，请等待...\n";
	Sleep(5000);
	for (int i = 1;; i++) {
		if (player.atk * player.atkSpeed * i >= map[index].monster.blood) {
			//判断是不是第二关的boss被杀
			if (map[index].monster.name == "火焰领主") {
				cout << "恭喜你Hero,你拯救了整个世界！" << endl;
				cout << "按任意键退出游戏..." << endl;
				_getch();
				exit(0);
			}
			cout << "恭喜你杀死" << map[index].monster.name << "晋级到下一关" << endl;
			player.x = 0;
			player.y = 0;
			player.exp += map[index].monster.exp;
			if (player.isUpGrade()) {  //判断英雄是否升级
				cout << "英雄升级，基础属性增加，并获得金币奖赏！" << endl;
			}
			cout << "请按任意键继续...";
			_getch();
			movePlayer(map2);
		}
		else if (map[index].monster.atk * map[index].monster.atkSpeed * i >= player.blood) {
			cout << "挑战失败！英雄阵亡" << endl;
			cout << "5秒后在商店复活...";
			Sleep(5000);
			shop(map);
		}
	}
}

//判断玩家现在所处的位置
void judgePlace(vector<Map> map) {
	for (int i = 0; i < 100; i++) {
		if (player.x == map[i].x && player.y == map[i].y) {   //找到玩家的位置
			if (map[i].sige == 9) {  //复活点
				player.x = 0;
				player.y = 0;
				shop(map);
			}
			if (map[i].sige == 1) {  //遇到野怪
				fightMonster(map,i);
			}
			else if (map[i].sige == 8) {   //遇到boss
				fightBoss(map, i);
			}
		}
	}
}

//玩家移动
void movePlayer(vector<Map> map) {
	system("cls");
	while (true) {
		cout << "\n你现在所在的位置坐标为:[" << player.x << "," << player.y << "]" << endl;
		cout << "请输入'w','s','a','d',完成上下左右的移动:" << endl;
		char ch;
		cin >> ch;
		switch (ch) {
		case 'w':
		case 'W':
			if (player.x == 0) {
				cout << "向上移动失败！" << endl;
			}
			else {
				player.x--;
				cout << "移动成功...";
				Sleep(1000);
				judgePlace(map);
			}
			break;
		case 's':
		case 'S':
			if (player.x == 9) {
				cout << "向下移动失败！" << endl;
			}
			else {
				player.x++;
				cout << "移动成功...";
				Sleep(1000);
				judgePlace(map);
			}
			break;
		case 'a':
		case 'A':
			if (player.y == 0) {
				cout << "向左移动失败！" << endl;
			}
			else {
				player.y--;
				cout << "移动成功...";
				Sleep(1000);
				judgePlace(map);
			}
			break;
		case 'd':
		case 'D':
			if (player.y  == 9) {
				cout << "向右移动失败！" << endl;
			}
			else {
				player.y++;
				cout << "移动成功...";
				Sleep(1000);
				judgePlace(map);
			}
			break;
		default:
			cout << "输入有误!" << endl;
			break;
		}
	}
}

int main() {
	srand(time(NULL));  //随机种子

	//读取游戏资源文件  生成游戏资源
	readEquip();
	readMonster();
	readMap();

	//创建角色
	createPlayer();

	//商店 -- 复活点
	shop(map1);


}