#pragma once
#ifndef _MAP_H
#define _MAP_H
#include <iostream>
#include "monster.h"
#include "equip.h"
using namespace std;
class Map {
public:
	int x;  //��ͼ�ĺ�����
	int y;  //��ͼ��������
	int sige;  //��ͼ���  0Ϊ½�� 9Ϊ�������̵�  1ΪҰ�� 8Ϊboss
	Monster monster;
};

#endif // !_MAP_H
