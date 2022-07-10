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

typedef struct Information_cost{
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
void search_goods(good* a,vip*b);
void print_goods(good* a);
void edit_vips(vip* a, int i);
void edit_vip_money(vip* a, double tips);
int vip_cost(vip* des, double cost);
void delete_vip(vip* a);
good* create_good_file(good* a_vip);
void sum_vip_total(vip* a, good* b);
void sum_month(good* a);
void sort(struct sum* p);
void swop(struct sum * a, struct sum * b);
void Bubble(vip* head);
void loading();
vip* create_vip(vip* a_vip) {
	vip* p1;
	p1 = a_vip;
	while (p1->next != NULL) {
		p1 = p1->next;
	}
	vip* s = (vip*)(calloc(1,LEN1));
	p1->next = s;
	printf("\n\n\n���������ĸ��������س����� ");
	scanf("%s", p1->name);
	printf("\n�����������Ա� ");
	scanf("%s", p1->sex);
	printf("\n���������ĵ绰���� ");
	scanf("%s", p1->tel);
	printf("\n����������Ӧ�Ļ�Ա����� ");
	scanf("%s", p1->num);
	printf("\n���������ĳ�ֵ��� ");
	scanf("%lf", &p1->money);
	s->next = NULL;
	printf("\n");
	loading();
	printf("\n��Ļ�Ա�Ѿ�ע��ɹ���");
	system("pause"); system("cls");
	getchar();
	return p1->next;
}//�Ӽ��̴�����Ա��Ϣ
void save_vip(vip* a) {
	vip* p8 = a->next;
	FILE* fp = NULL;
	if ((fp = fopen("date_vip.txt", "w")) == NULL) {
		printf("The file can't be opend.\n");
		return;
	}
	while (p8->next != NULL) {
		fprintf(fp, "%s %s %s %s %.2f %.2f\n", p8->name, p8->sex, p8->tel, p8->num, p8->money,p8->sum_cost);
		p8 = p8->next;
	}
	fclose(fp);
}//����Ա��Ϣ���浽�ļ�
vip* create_vip_file(vip* a_vip) {
	vip* p1;
	p1 = a_vip;
	while (p1->next != NULL) {
		p1 = p1->next;
	}
	FILE* fp = NULL;
	if ((fp = fopen("date_vip.txt", "r")) == NULL) {
		printf("The file can't be opend.\n");
		return NULL;
	}
	vip* s = (vip*)(calloc(1, LEN1));
	while ((fscanf(fp, "%s %s %s %s %lf %lf", s->name, s->sex, s->tel, s->num, &s->money,&s->sum_cost)) != EOF) {
		s->next = NULL;
		p1->next = s;
		p1 = p1->next;
		s = (vip*)(calloc(1, LEN1));
	}
	p1->next = s;
	p1 = p1->next;
	fclose(fp);
	return p1->next;
}//���ļ��ж�ȡ��Ա��Ϣ
void print_vip(vip* a) {
	vip* p11 = a->next;
	printf("����     �Ա�     �绰����      ��Ա�����     ʣ����\n");
	while (p11->next != NULL) {
		printf("%-8s  %-4s  %-15s   %-6s     %9.2f\n", p11->name, p11->sex, p11->tel, p11->num, p11->money);
		p11 = p11->next;
	}
}//��ӡ�����еĻ�Ա��Ϣ
good* creat_goods(good* a_goods,vip* b) {
	good* p2;
	p2 = a_goods;
	time_t t;
	struct tm* lt;
	time(&t);
	lt = localtime(&t);
	while (p2->next != NULL) {
		p2 = p2->next;
	}
	good* s = (good*)(calloc(1, LEN2));
	p2->next = s;
	p2->year = lt->tm_year + 1900; p2->month = lt->tm_mon + 1; p2->day = lt->tm_mday; p2->hour = lt->tm_hour; p2->min = lt->tm_min;
	int sign = 0;
	const char* pay[10] = { "�ֽ�","��Ա��","΢��","֧����","������","����" };
	printf("\n\n\n���������Ļ�Ա����� ");
	scanf("%s", p2->nu);
	printf("\n������������������ ");
	scanf("%s", p2->name_cost);
	printf("\n�����������ܽ�� ");
	scanf("%lf", &p2->cost);
	printf("\n��ѡ������շѷ�ʽ\n0.�ֽ�\n1.��Ա�����\n2.΢��\n3.֧����\n4.������\n5.����\n�������Ӧ�����ֱ�� ");
	scanf("%d", &sign);
	strcpy(p2->payment, pay[sign]);
	if (sign == 5) {
		printf("��������ѡ���֧����ʽ");
		scanf("%s", p2->payment);
	}
	s->next = NULL;
	vip* dest = b;
	while (1) {
		while (strcmp(p2->nu, dest->num) != 0&&dest->next!=NULL) {
			dest = dest->next;
			if (strcmp(p2->nu, dest->num) == 0 && dest != NULL)
				break;
		}
		if (dest->next == NULL) {
			printf("δ���ҵ����ĸ�����Ϣ����ȷ�Ϻ��������� ");
			scanf("%s", p2->nu);
			dest = b;
			continue;
		}
		break;
	}
	if (strcmp(p2->payment,"��Ա��")==0) {
		if(vip_cost(dest,p2->cost)==-1) {
			printf("��������ĸ��ʽ��ֱ�������Ų����س���¼");
			scanf("%d", &sign);
			strcpy(p2->payment, pay[sign]);
			if (sign == 5) {
				printf("��������ѡ���֧����ʽ");
				scanf("%s", p2->payment);
			}
		}
	}
	dest->sum_cost = dest->sum_cost + p2->cost;
	loading();
	printf("������Ϣ�ѱ��档");
	system("pause"); system("cls");
	return p2->next;
}//�Ӽ��̴�����Ա��������Ϣ
int vip_cost(vip* des, double cost) {
	if (des->money >= cost) {
		double temp = des->money;
		des->money = temp- cost;
		printf("���Ļ�Ա��ʣ����Ϊ %.2f \n", des->money);
		return 1;
	}
	else {
		printf("���Ļ�Ա������,");
		return -1;
	}//�����Աʹ�û�Ա��֧�����ж�����Ƿ��㹻
}
good* create_good_file(good* a_vip) {
	good* p10;
	p10 = a_vip;
	while (p10->next != NULL) {
		p10 = p10->next;
	}
	FILE* fp3 = NULL;
	if ((fp3 = fopen("date_good.txt", "r")) == NULL) {
		printf("The file can't be opend.\n");
		return NULL;
	}
	good* s = (good*)(calloc(1, LEN2));
	while ((fscanf(fp3, "%d %d %d %d %d %s %s %lf %s \n", &s->year, &s->month, &s->day, &s->hour, &s->min, s->nu, s->name_cost, &s->cost, s->payment)) != EOF) {
		//s = (good*)(calloc(1, LEN2));
		s->next = NULL;
		p10->next = s;
		p10 = p10->next;
		s = (good*)(calloc(1, LEN2));
	}
	p10->next = s;
	p10 = p10->next;
	fclose(fp3);
	return p10->next;
}/*���ļ��ж�ȡ��Ա��������Ϣ*/
void save_good(good* a) {
	good* p9 = a->next;
	FILE* fp2 = NULL;
	if ((fp2 = fopen("date_good.txt", "w")) == NULL) {
		printf("The file can't be opend.\n");
		return;
	}
	while (p9->next != NULL) {
		fprintf(fp2, "%d %d %d %d %d %s %s %lf %s \n", p9->year,p9->month,p9->day,p9->hour,p9->min,p9->nu, p9->name_cost, p9->cost, p9->payment);
		p9 = p9->next;
	}
	fclose(fp2);
}/*����Ա��������Ϣ���浽�ļ�*/
void print_goods(good* a) {
	good* p13 = a->next;
	int cnt = 0;
	printf("    ��������      ��Ա�����   ������Ʒ    ���ѽ��    ֧����ʽ   \n");
	while (p13->next != NULL) {
		printf("%2d/%2d/%2d %2d:%2d   %6s  %10s   %10.2f     %-19s\n", p13->year, p13->month, p13->day, p13->hour, p13->min, p13->nu, p13->name_cost, p13->cost, p13->payment);
		p13 = p13->next;
	}
}//��Ա��������Ϣȫ����ӡ����
vip* search_vip(vip* a) {
	vip* p3 = a;
	printf("\n\n�����������ֻ�������߻�Ա����� ");
	char com[20];
	while (1) {
		gets_s(com, 20);
		if (strlen(com) != 0)
			break;
		else continue;
	}
	loading();
	while (p3->next != NULL) {
		if (strcmp(p3->num, com) == 0|| strcmp(p3->tel, com)==0) {
			return p3;
		}
		p3 = p3->next;
	}
	return NULL;
}/*���һ�Ա����Ϣ����Χ����λ�õ�ָ��*/
void search_goods(good* a,vip* b) {
	char compare[20];
	good* p4 = a;
	vip* p1 = search_vip(b);
	if (p1 == NULL) {
		printf("δ���ҵ����ĸ�����Ϣ�����֤���ٴ�����.\n");
		system("pause");  system("cls");
		return;
	}
	strcpy(compare, p1->num);
	int i = 1;
	while (p4!= NULL) {
		if (i++ == 1) {
			printf("    ��������     ��Ա�����   ������Ʒ    ���ѽ��    ֧����ʽ   \n");
		}
		if (strcmp(p4->nu, compare) == 0) {
			printf("%2d/%2d/%2d %2d:%2d   %6s  %10s   %10.2f     %-19s\n", p4->year, p4->month, p4->day, p4->hour, p4->min, p4->nu, p4->name_cost, p4->cost, p4->payment);
		}
		p4 = p4->next;
	}
	system("pause"); system("cls");
}/*���һ�Ա�����Ѽ�¼�����ҵ���ֱ�������ӡ����*/
void edit_vips(vip* a,int i) {
	vip* p5 = NULL;
	while (1) {
		p5 = search_vip(a);
		if (p5 == NULL) {
			printf("δ���ҵ����ĸ�����Ϣ�����֤���ٴ�����.\n");
		}
		else
			break;
	}//�Ȳ�����û�������
	printf("����     �Ա�     �绰����      ��Ա�����     ʣ����\n");
	printf("%-8s  %-4s  %-15s   %-6s     %9.2f\n", p5->name, p5->sex, p5->tel, p5->num, p5->money);
	switch (i) {
	case 0: {
		char new_name[10];
		printf("���������ĸ������� ");
		gets_s(new_name, 10);
		strcpy(p5->name, new_name);
		printf("���޸ĺ�Ļ�Ա��ϢΪ \n");
		printf("%-8s  %-4s  %-15s   %-6s     %9.2f\n", p5->name, p5->sex, p5->tel, p5->num, p5->money);
		break;
	}//�޸��û��ĸ�������
	case 1: {
		char new_tele[13];
		printf("�������������ֻ����� ");
		gets_s(new_tele,13 );
		strcpy(p5->tel, new_tele);
		printf("���޸ĺ�Ļ�Ա��ϢΪ \n");
		printf("%-8s  %-4s  %-15s   %-6s     %9.2f\n", p5->name, p5->sex, p5->tel, p5->num, p5->money);
		break;
	}//�޸��û����ֻ�����
	}
}
void edit_vip_money(vip* a, double tips) {
	vip* p10 = a;
	while (1) {
		char tele[12] = "\0";
		gets_s(tele, 12);
		p10 = search_vip(a);
		if (p10 == NULL) {
			printf("δ���ҵ����ĸ�����Ϣ�����֤���ٴ�����.\n");
		}
		else
			break;
	}
	printf("����     �Ա�     �绰����      ��Ա�����     ʣ����\n");
	printf("%-8s  %-4s  %-15s   %-6s     %9.2f\n", p10->name, p10->sex, p10->tel, p10->num, p10->money);
	p10->money = p10->money + tips;
	printf("��ֵ�ɹ�������ǰ��Ա�����Ϊ %.2fԪ\n",p10->money);
}//�Ի�Ա�����г�ֵ
void delete_vip(vip* a) {
	vip* p6 = NULL;
	int cnt = 0;
	while (1) {
		p6 = search_vip(a);
		cnt++;
		if (p6 == NULL)
			printf("�����Ϣû�б��ҵ�����ȷ��������ٴ�����. \n");
		else
			break;
		if (cnt == 3) {
			printf("�����Ϣ�Ѿ���������������󣬱������˳�.\n");
			return ;
		}
	}
	printf("����     �Ա�     �绰����      ��Ա�����     ʣ����\n");
	printf("%-8s  %-4s  %-15s   %-6s     %9.2f\n", p6->name, p6->sex, p6->tel, p6->num, p6->money);
	printf("�����Ϣ�Ѿ����ҵ�����ȷ�ϰ�Yȷ�� ");
	char sign = getchar();
	if (sign == 'y' || sign == 'Y') {
		vip* p7 = p6->next;
		if (p7->next == NULL) {
			strcpy(p6->name, p7->name); strcpy(p6->sex, p7->sex); strcpy(p6->num, p7->num); strcpy(p6->tel, p7->tel); p6->money = p7->money; p6->next = p7->next;
			p6->next = NULL;
		}
		while (p7->next != NULL) {
			strcpy(p6->name, p7->name); strcpy(p6->sex, p7->sex); strcpy(p6->num, p7->num); strcpy(p6->tel, p7->tel); p6->money = p7->money; p6->next = p7->next;
			p6 = p6->next; p7 = p7->next;
		}
		printf("���Ѿ��ɹ�ע�����Ļ�Ա�˺�.");
	}
	
}/*ע����Ա*/
void sum_vip_total(vip* a, good* b) {
	vip * p16 = a;
	Bubble(a);
	printf("����     ��Ա�����   �����ܶ�    ����\n");
	int i = 1;
	p16 = p16->next;
	while (p16 != NULL) {
		printf("%-10s %6s    %7.2f   %6d\n", p16->name, p16->num, p16->sum_cost,i++);
		if (i > 5)
			break;
		p16 = p16->next;
	}
}/*��Ա�����Ѳ�ѯ���Ѳ���*/
void sum_month(good* a) {
	good* p15 = a;
	struct sum mark[13] = { 0,0 };
	for (int j = 1; j < 13; j++) {
		mark[j].month = j;
	}
	while (p15 != NULL)
	{
		int i = p15->month;
		mark[i].sum = mark[i].sum + p15->cost;
		p15 = p15->next;
	};
	sort(mark);
	for (int i = 1; i < 13; i++) {
		printf("�� %2d �µ������۶�Ϊ%9.2f,����Ϊ��%-2d\n", mark[i].month,mark[i].sum,i);
	}
}
void sort(struct sum* p) {
	for (int x = 1; x < 13; x++) {
		for (int y = 1; y < 13 - x; y++) {
			if (p[y].sum < p[y + 1].sum) {
				swop(&p[y], &p[y + 1]);
			}
		}
	}
}//�������۶��������
void swop(struct sum *a,struct sum *b) {
	struct sum temp = {0,0};
	temp.month = a->month; a->month = b->month; b->month = temp.month;
	temp.sum = a->sum; a->sum = b->sum; b->sum = temp.sum;
}
void Bubble(vip* head)
{
	vip* pre; 
	vip* cur; 
	vip* next;
	vip* end;
	end = NULL;
	while (head->next != end){
		for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next){
			if (cur->sum_cost < next->sum_cost) {
				pre->next = next;
				cur->next = next->next;
				next->next = cur;
				vip* temp = cur; cur = next; next = temp;
			}
		}
		end = cur;
	}
}
void loading() {
	printf("ϵͳ���ڴ������Ե�");
	for (int i = 1; i <= 5; i++) {
		printf(".");
		Sleep(300);
	}
	printf("\n");
}//����Ϊ�����Ĳ���