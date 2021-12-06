#pragma once
#ifndef _EQUIP_
#define _EQUIP_
#include <string>
using namespace std;
class Equip {
public:
	string name; //装备名称
	int bloodAdd; //装备的生命加成
	int atkAdd;  //装备的攻击力加成
	int atkSpeedAdd;//装备的攻速加成
	int price;  //装备价格
};

#endif // !_EQUIP_

