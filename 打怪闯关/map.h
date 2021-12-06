#pragma once
#ifndef _MAP_H
#define _MAP_H
#include <iostream>
#include "monster.h"
#include "equip.h"
using namespace std;
class Map {
public:
	int x;  //地图的横坐标
	int y;  //地图的纵坐标
	int sige;  //地图标记  0为陆地 9为复活点和商店  1为野怪 8为boss
	Monster monster;
};

#endif // !_MAP_H
