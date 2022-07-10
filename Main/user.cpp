/*以下为用户操作页面*/
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include"fun.h"
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0))
enum {
	UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13, ESC = 27,
};
char* menu_1[] = {
	"*会员信息管理*","*商品信息管理*","*  信息统计  *","*  退出程序  *",
};
char* menu_2_1[] = {
	"*添加会员信息*","*查询会员信息*","*修改会员信息*","*删除会员信息*","*返回上级菜单*"
};
char* menu_2_2[] = {
	"*添加货物消费信息*","*查询货物消费信息*","*  返回上级菜单  *"
};
char* menu_2_3[] = {
	"*会员消费统计*","*店月消费统计*","*返回上级菜单*",
};
char* menu_3_1[] = {
	"*修改用户姓名*","*修改手机号码*","*卡内余额充值*","*返回上级菜单*",
};
CONSOLE_CURSOR_INFO cci;
COORD pos = { 0, 0 };
void load();
void print_head();
void print_last(int);
void showmenu_1(HANDLE hOut, char** menu_1, int size, int index);
void showmenu_2_1(HANDLE hOut, char** menu_2_1, int size, int index);
void showmenu_2_2(HANDLE hOut, char** menu_2_2, int size, int index);
void showmenu_3_1(HANDLE hOut, char** menu_3_1, int size, int index);
int  get_userinput(int* index, int size);
int main2_1();
int main2_2();
int main2_3();
int main3_1();
vip* head_vip = (vip*)(calloc(1, LEN1));
good* head_goods = (good*)(calloc(1, LEN2));
int main() {
	create_vip_file(head_vip);
	create_good_file(head_goods);
	int ret; int index = 0;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hOut, &cci);
	cci.dwSize = 1; cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
	load();
	print_head();
	while (1) {
		showmenu_1(hOut, menu_1, NR(menu_1), index);
		ret = get_userinput(&index, NR(menu_1));
		if (ret == ESC)
			break;
		if (ret == ENTER) {
			switch (index) {
			case 0:
				main2_1();
				break;
			case 1:
				main2_2();
				break;
			case 2:
				main2_3();
				break;
			case 3:
				return 0;
			}
		}
	}
	return 0;
}
int main2_1() {//对于会员信息管理的子菜单
	system("cls");
	int ret1; int index = 0;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char temp1 = '\0';
	int sign1 = 0;
	while (1) {
		if (sign1 == 0) {
			HANDLE hOut;
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			pos.X = 8;	pos.Y = 4;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, 12);
			printf("是否打印出所有的会员信息？\n");
			SetConsoleTextAttribute(hOut, 0x7);
			printf("\t是请按Y，否请按N");
			if ((temp1 = _getch()) == 'y' || temp1 == 'Y') {
				system("cls");
				showmenu_2_1(hOut, menu_2_1, NR(menu_2_1), index);
				print_vip(head_vip);
				SetConsoleTextAttribute(hOut, 10);
				printf("            以 上 为 全 部 的 会 员 数 据               \n");
				SetConsoleTextAttribute(hOut, 0x7);
				system("pause");
			}
			else system("cls");
		}
		sign1++;
		showmenu_2_1(hOut, menu_2_1, NR(menu_2_1), index);
		ret1 = get_userinput(&index, NR(menu_2_1));
		if (ret1 == ESC) {
			system("cls");
			break;
		}
		if (ret1 == ENTER) {
			switch (index) {
			case 0:
				system("cls");
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				create_vip(head_vip);
				save_vip(head_vip);
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				sign1 = 0;
				break;
			case 1: {
				system("cls");
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				vip* sign = search_vip(head_vip);
				if (sign == NULL) {
					printf("没有找到您的相关信息，请确认后再次输入\n");
					system("pause"); system("cls");
				}
				else {
					printf("姓名     性别     电话号码      会员卡编号     剩余金额\n");
					printf("%-8s  %-4s  %-15s   %-6s     %9.2f\n", sign->name, sign->sex, sign->tel, sign->num, sign->money);
					system("pause"); system("cls");
				}
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				//sign1 = 0;
			}
				  break;
			case 2:
				system("cls");
				main3_1();
				//sign1 = 0;
				break;
			case 3:
				system("cls");
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				delete_vip(head_vip);
				save_vip(head_vip);
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				system("pause"); system("cls"); getchar();
				sign1 = 0;
				break;
			case 4:
				system("cls");
				sign1 = 0;
				return 0;
			}
		}
	}
	return 0;
}
int main2_2() {//商品添加的菜单
	system("cls");
	int ret; int index = 0;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char temp2 = '\0';
	int sign2 = 0;
	while (1) {
		if (sign2 == 0) {
			HANDLE hOut;
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			pos.X = 8;	pos.Y = 4;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, 12);
			printf("是否打印出所有的商店销售信息？\n");
			SetConsoleTextAttribute(hOut, 0x7);
			printf("\t是请按Y，否请按N");
			if ((temp2 = _getch()) == 'y' || temp2 == 'Y') {
				system("cls");
				showmenu_2_2(hOut, menu_2_2, NR(menu_2_2), index);
				print_goods(head_goods);
				SetConsoleTextAttribute(hOut, 10);
				printf("         以 上 为 全 部 的 商 店 销 售 数 据               \n");
				SetConsoleTextAttribute(hOut, 0x7);
				system("pause");
			}
			else system("cls");
		}
		sign2++;
		showmenu_2_2(hOut, menu_2_2, NR(menu_2_2), index);
		ret = get_userinput(&index, NR(menu_2_2));
		if (ret == ESC) {
			system("cls");
			break;
		}
		if (ret == ENTER) {
			switch (index) {
			case 0:
				system("cls");
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				creat_goods(head_goods, head_vip);
				save_good(head_goods);
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				sign2 = 0;
				break;
			case 1:
				system("cls");
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				search_goods(head_goods, head_vip);
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				sign2 = 0;
				break;
			case 2:
				system("cls");
				sign2 = 0;
				return 0;
			}
		}
	}
	return 0;
}
int main2_3() {//信息统计菜单
	system("cls");
	int ret; int index = 0;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1) {
		showmenu_2_2(hOut, menu_2_3, NR(menu_2_3), index);
		ret = get_userinput(&index, NR(menu_2_3));
		if (ret == ESC) {
			system("cls");
			break;
		}
		if (ret == ENTER) {
			switch (index) {
			case 0: {
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				sum_vip_total(head_vip, head_goods);
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				system("pause"); system("cls");
				break;
			}
			case 1: {
				sum_month(head_goods);
				system("pause"); system("cls");
				break;
			}
			case 2:
				system("cls");
				return 0;
			}
		}
	}
	return 0;
}
int main3_1() {//用户信息编辑选择的菜单
	system("cls");
	int ret;
	int index = 0;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1) {
		showmenu_3_1(hOut, menu_3_1, NR(menu_3_1), index);
		ret = get_userinput(&index, NR(menu_3_1));
		if (ret == ESC) {
			system("cls");
			break;
		}
		if (ret == ENTER) {
			switch (index) {
			case 0:
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				edit_vips(head_vip, 0);
				save_vip(head_vip);
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				system("pause"); system("cls");
				break;
			case 1:
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				edit_vips(head_vip, 1);
				save_vip(head_vip);
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				system("pause"); system("cls");
				break;
			case 2: {
				double a;
				cci.bVisible = 1;
				SetConsoleCursorInfo(hOut, &cci);
				printf("请输入您的充值金额 ");
				scanf("%lf", &a);
				edit_vip_money(head_vip, a);
				save_vip(head_vip);
				cci.bVisible = 0;
				SetConsoleCursorInfo(hOut, &cci);
				system("pause"); system("cls");
				break;
			}
			case 3:
				system("cls");
				return 0;
			}
		}
	}
	return 0;
}
void load() {
	int i, j, count = 5;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (i = 0; i < 14; count += 5, i++) {
		pos.X = 15; pos.Y = 5;
		SetConsoleCursorPosition(hOut, pos);
		SetConsoleTextAttribute(hOut, 6);
		printf(" 欢迎使用本商店会员信息与货品管理系统\n");
		printf("\t\t程序正在进入，请稍后          ");
		printf("\n\n\n\n\n\t\tLoading");
		for (j = 0; j < i % 3 + 1; j++)
			printf(".");
		printf("\n\t\t");
		for (j = 0; j <= i; j++)
			printf("■");
		for (j = 14 - i; j >= 0; j--)
			printf("  ");
		Sleep(300);
		system("CLS");
	}
	SetConsoleTextAttribute(hOut, 0x7);
}
void print_head() {//打印出表头
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = 8;	pos.Y = 0;
	SetConsoleCursorPosition(hOut, pos);
	SetConsoleTextAttribute(hOut, 12);
	printf("欢迎使用本会员管理以及商店货物管理程序.\n");
	pos.X = 0;	pos.Y = 1;
	SetConsoleCursorPosition(hOut, pos);
	printf("******************************************************\n");
	SetConsoleTextAttribute(hOut, 0x7);
}
void print_last(int y) {//打印出尾部，y表示高度
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = 0;	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
	SetConsoleTextAttribute(hOut, 12);
	printf("******************************************************\n");
	SetConsoleTextAttribute(hOut, 0x7);
}
void showmenu_1(HANDLE hOut, char** menu_1, int size, int index) {
	int i;
	print_head();
	for (i = 0; i < size; i++) {
		if (i == index) {
			pos.X = 15;	pos.Y = 2 + i;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | 0x70);
			printf("%s", menu_1[i]);
		}
		else {
			pos.X = 15;	pos.Y = 2 + i;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, 0x7);
			printf("%s", menu_1[i]);
		}
	}
	print_last(6);
}//第一层菜单
void showmenu_2_1(HANDLE hOut, char** menu_2_1, int size, int index) {
	int i;
	print_head();
	for (i = 0; i < size; i++) {
		if (i == index) {
			pos.X = 15;	pos.Y = 2 + i;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | 0x70);
			printf("%s", menu_2_1[i]);
		}
		else {
			pos.X = 15;	pos.Y = 2 + i;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, 0x7);
			printf("%s", menu_2_1[i]);
		}
	}
	print_last(7);
}//对于会员信息管理的子菜单
void showmenu_2_2(HANDLE hOut, char** menu_2_2, int size, int index) {
	int i;
	print_head();
	for (i = 0; i < size; i++) {
		if (i == index) {
			pos.X = 15;	pos.Y = 2 + i;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | 0x70);
			printf("%s", menu_2_2[i]);
		}
		else {
			pos.X = 15;	pos.Y = 2 + i;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, 0x7);
			printf("%s", menu_2_2[i]);
		}
	}
	print_last(5);
}//对于商品信息管理的子菜单以及数据统计的子菜单
void showmenu_3_1(HANDLE hOut, char** menu_3_2, int size, int index) {
	int i;
	print_head();
	for (i = 0; i < size; i++) {
		if (i == index) {
			pos.X = 15; pos.Y = 2 + i;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | 0x70);
			printf("%s", menu_3_2[i]);
		}
		else {
			pos.X = 15; pos.Y = 2 + i;
			SetConsoleCursorPosition(hOut, pos);
			SetConsoleTextAttribute(hOut, 0x7);
			printf("%s", menu_3_2[i]);
		}
	}
	print_last(6);
}//用户对于编辑会员信息时选择的三级菜单
int  get_userinput(int* index, int size) {
	int ch;
	ch = _getch();
	switch (ch) {
	case UP:
		if (*index > 0)
			*index -= 1;
		break;
	case DOWN:
		if (*index < size - 1)
			*index += 1;
		break;
	case LEFT:
		if (*index > 0)
			*index -= 1;
		break;
	case RIGHT:
		if (*index < size - 1)
			*index += 1;
		break;
	case ENTER:
		return ENTER;
	case ESC:
		return ESC;
	}
	return 0;
}
//以上为用户界面的操作部分