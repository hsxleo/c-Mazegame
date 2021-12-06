#pragma once
#ifndef _MONSTER_H
#define _MONSTER_H
#include "equip.h"
#include <string>
using namespace std;
class Monster{
public:
	string name;  //怪物名
	int blood;    //怪物血量
	int atk;	  //怪物攻击力
	int atkSpeed; //怪物攻击速度  （每秒攻击的次数）
	int exp;      //打死怪物获得的经验
	Equip equip;  //怪物的装备
	void equipAdd() {  //怪物装备加成
		blood += equip.bloodAdd;
		atk += equip.atkAdd;
		atkSpeed += equip.atkSpeedAdd;
	}
};
#endif // !_MONSTER_H

