/*����Ϊ�û�����ҳ��*/
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
	"*��Ա��Ϣ����*","*��Ʒ��Ϣ����*","*  ��Ϣͳ��  *","*  �˳�����  *",
};
char* menu_2_1[] = {
	"*��ӻ�Ա��Ϣ*","*��ѯ��Ա��Ϣ*","*�޸Ļ�Ա��Ϣ*","*ɾ����Ա��Ϣ*","*�����ϼ��˵�*"
};
char* menu_2_2[] = {
	"*��ӻ���������Ϣ*","*��ѯ����������Ϣ*","*  �����ϼ��˵�  *"
};
char* menu_2_3[] = {
	"*��Ա����ͳ��*","*��������ͳ��*","*�����ϼ��˵�*",
};
char* menu_3_1[] = {
	"*�޸��û�����*","*�޸��ֻ�����*","*��������ֵ*","*�����ϼ��˵�*",
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
int main2_1() {//���ڻ�Ա��Ϣ������Ӳ˵�
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
			printf("�Ƿ��ӡ�����еĻ�Ա��Ϣ��\n");
			SetConsoleTextAttribute(hOut, 0x7);
			printf("\t���밴Y�����밴N");
			if ((temp1 = _getch()) == 'y' || temp1 == 'Y') {
				system("cls");
				showmenu_2_1(hOut, menu_2_1, NR(menu_2_1), index);
				print_vip(head_vip);
				SetConsoleTextAttribute(hOut, 10);
				printf("            �� �� Ϊ ȫ �� �� �� Ա �� ��               \n");
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
					printf("û���ҵ����������Ϣ����ȷ�Ϻ��ٴ�����\n");
					system("pause"); system("cls");
				}
				else {
					printf("����     �Ա�     �绰����      ��Ա�����     ʣ����\n");
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
int main2_2() {//��Ʒ��ӵĲ˵�
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
			printf("�Ƿ��ӡ�����е��̵�������Ϣ��\n");
			SetConsoleTextAttribute(hOut, 0x7);
			printf("\t���밴Y�����밴N");
			if ((temp2 = _getch()) == 'y' || temp2 == 'Y') {
				system("cls");
				showmenu_2_2(hOut, menu_2_2, NR(menu_2_2), index);
				print_goods(head_goods);
				SetConsoleTextAttribute(hOut, 10);
				printf("         �� �� Ϊ ȫ �� �� �� �� �� �� �� ��               \n");
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
int main2_3() {//��Ϣͳ�Ʋ˵�
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
int main3_1() {//�û���Ϣ�༭ѡ��Ĳ˵�
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
				printf("���������ĳ�ֵ��� ");
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
		printf(" ��ӭʹ�ñ��̵��Ա��Ϣ���Ʒ����ϵͳ\n");
		printf("\t\t�������ڽ��룬���Ժ�          ");
		printf("\n\n\n\n\n\t\tLoading");
		for (j = 0; j < i % 3 + 1; j++)
			printf(".");
		printf("\n\t\t");
		for (j = 0; j <= i; j++)
			printf("��");
		for (j = 14 - i; j >= 0; j--)
			printf("  ");
		Sleep(300);
		system("CLS");
	}
	SetConsoleTextAttribute(hOut, 0x7);
}
void print_head() {//��ӡ����ͷ
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = 8;	pos.Y = 0;
	SetConsoleCursorPosition(hOut, pos);
	SetConsoleTextAttribute(hOut, 12);
	printf("��ӭʹ�ñ���Ա�����Լ��̵����������.\n");
	pos.X = 0;	pos.Y = 1;
	SetConsoleCursorPosition(hOut, pos);
	printf("******************************************************\n");
	SetConsoleTextAttribute(hOut, 0x7);
}
void print_last(int y) {//��ӡ��β����y��ʾ�߶�
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
}//��һ��˵�
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
}//���ڻ�Ա��Ϣ������Ӳ˵�
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
}//������Ʒ��Ϣ������Ӳ˵��Լ�����ͳ�Ƶ��Ӳ˵�
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
}//�û����ڱ༭��Ա��Ϣʱѡ��������˵�
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
//����Ϊ�û�����Ĳ�������