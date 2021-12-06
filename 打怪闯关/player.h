#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H
#include "equip.h"
#include <string>
#include <vector>
using namespace std;
class Player {
public:
	int x;   //����ڵ�ͼ�ϵĺ�����
	int y;   //����ڵ�ͼ�ϵ�������
	string name;  //�����
	int exp;      //��Ҿ��� (��200��һ��)
	int money;    //��ҽ��
	int blood;    //���Ѫ��
	int atk;	  //��ҹ�����
	int atkSpeed;  //��ҹ����ٶ�  ��ÿ�빥���Ĵ���)
	vector<Equip> equip;  //��ҵ�װ��

	//���װ���ӳ�
	void equipAdd() {  
		for (int i = 0; i < equip.size(); i++) {
			blood += equip[i].bloodAdd;
			atk += equip[i].atkAdd;
			atkSpeed += equip[i].atkSpeedAdd;
		}
	}
	//������200��һ��  ��һ������300��������� 50�㹥���� 1�㹥���ٶ�  �����500�����
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
