#pragma once
#ifndef _MONSTER_H
#define _MONSTER_H
#include "equip.h"
#include <string>
using namespace std;
class Monster{
public:
	string name;  //������
	int blood;    //����Ѫ��
	int atk;	  //���﹥����
	int atkSpeed; //���﹥���ٶ�  ��ÿ�빥���Ĵ�����
	int exp;      //���������õľ���
	Equip equip;  //�����װ��
	void equipAdd() {  //����װ���ӳ�
		blood += equip.bloodAdd;
		atk += equip.atkAdd;
		atkSpeed += equip.atkSpeedAdd;
	}
};
#endif // !_MONSTER_H

