#pragma once
/*自定义的头文件*/
#pragma once
#ifndef _FUN_H_
#define _FUN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include <conio.h>
#include<Windows.h>
#define LEN1 sizeof(vip)
#define LEN2 sizeof(good)
typedef struct Information_VIP {
	char name[12];
	char sex[3];
	char num[9];
	char tel[12];
	double money;
	double sum_cost;
	struct Information_VIP* next;
} vip;

typedef struct Information_cost {
	int year;
	int month;
	int day;
	int hour;
	int min;
	char nu[9];
	char name_cost[10];
	double cost;
	char payment[12];
	struct Information_cost* next;
}good;
struct sum {
	double sum;
	int month;
};
vip* create_vip(vip* a);
good* creat_goods(good* a_goods, vip* b);
vip* create_vip_file(vip* a_vip);
void print_vip(vip* a);
void save_good(good* a);
void save_vip(vip* a);
vip* search_vip(vip* a);
void search_goods(good* a, vip* b);
void print_goods(good* a);
void edit_vips(vip* a, int i);
void edit_vip_money(vip* a, double tips);
int vip_cost(vip* des, double cost);
void delete_vip(vip* a);
good* create_good_file(good* a_vip);
void sum_vip_total(vip* a, good* b);
void sum_month(good* a);
void sort(struct sum* p);
void swop(struct sum* a, struct sum* b);
void Bubble(vip* head);
void loading();
#endif // !_FUN_H_