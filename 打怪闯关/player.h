#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H
#include "equip.h"
#include <string>
#include <vector>
using namespace std;
class Player {
public:
	int x;   //玩家在地图上的横坐标
	int y;   //玩家在地图上的纵坐标
	string name;  //玩家名
	int exp;      //玩家经验 (满200升一级)
	int money;    //玩家金币
	int blood;    //玩家血量
	int atk;	  //玩家攻击力
	int atkSpeed;  //玩家攻击速度  （每秒攻击的次数)
	vector<Equip> equip;  //玩家的装备

	//玩家装备加成
	void equipAdd() {  
		for (int i = 0; i < equip.size(); i++) {
			blood += equip[i].bloodAdd;
			atk += equip[i].atkAdd;
			atkSpeed += equip[i].atkSpeedAdd;
		}
	}
	//经验满200升一级  升一级增加300点基础生命 50点攻击力 1点攻击速度  并获得500个金币
	bool isUpGrade() {
		while(exp >= 200) {
			exp -= 200;
			blood += 300;
			atk += 50;
			atkSpeed += 1;
			money += 500;
			return true;
		}
		return false;
	}
};
#endif
