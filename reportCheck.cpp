#define _CRT_SECURE_NO_WARNINGS // fopen ���� ���� ���� ������ ���� ����
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
// ����, ���, ������, �ް��庴, �ӻ��, �ٵ��� 
const int NONE = 1, DISABLE = 2, MERIT = 3, VACSOLD = 4, PREGNANT = 5, MULTICHILD = 6;
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5;
// ���
int transTypeAll(char *typeAll) {
	int ticketAll = 0;
	// �̿�� üũ strcmp : c ���ڿ� �� => ������ 0
	if(strcmp(typeAll, "�����̿��  ") == 0) ticketAll = 1;
	else if(strcmp(typeAll, "��ũ�̿��  ") == 0) ticketAll = 2;
	return ticketAll;
}
int transTypeDay(char *typeDay) {
	int ticketDay = 0;
	// ���� üũ 
	if(strcmp(typeDay, "���ϱ�") == 0) ticketDay = 1;
	else if(strcmp(typeDay, "���ı�") == 0) ticketDay = 2;
	return ticketDay;
}
int trasAge(char *ageCount) {
	int age = 0;
	// ���� üũ 
	if(strcmp(ageCount, "����  ") == 0) age = OLD;
	else if(strcmp(ageCount, "�  ") == 0) age = ADULT;
	else if(strcmp(ageCount, "û�ҳ�") == 0) age = TEEN;
	else if(strcmp(ageCount, "���") == 0) age = CHILD;
	else if(strcmp(ageCount, "���̺�") == 0) age = BABY;
	return age;
}
int trasSales(char *forsale) {
	int sales = 0;
	// ������ üũ 
	if(strcmp(forsale, "����\n") == 0) sales = NONE;
	else if(strcmp(forsale, "�����\n") == 0) sales = DISABLE;
	else if(strcmp(forsale, "����������\n") == 0) sales = MERIT;
	else if(strcmp(forsale, "�ް��庴\n") == 0) sales = VACSOLD;
	else if(strcmp(forsale, "�ӻ��\n") == 0) sales = PREGNANT;
	else if(strcmp(forsale, "�ٵ���\n") == 0) sales = MULTICHILD;
	return sales;
}

// �Է�
int fileRead(int (*orderList)[7]) {
	FILE *fp = fopen("report.csv", "r+"); // only read
	const int MAX = 1024;
	char line[MAX]; // �б����� �迭
	int lastLine = 0;
	char *typeAll;
	char *typeDay;
	char *age;
	char *sales;
	
	while(fscanf(fp, "%d,%-12s,%-6s,%-6s,%d,%d,%s", 
	orderList[lastLine][0], typeAll, typeDay, age, orderList[lastLine][4], orderList[lastLine][5], sales)); {
		orderList[lastLine][1] = transTypeAll(typeAll);
		orderList[lastLine][2] = transTypeDay(typeDay);
		orderList[lastLine][3] = trasAge(age);
		orderList[lastLine][6] = trasSales(sales);
	}
	fclose(fp);
	return lastLine;
}  
// ��� 
void printTickets(int position, int(*orderlist)[7]) { // ��� ��� 
	int date = orderlist[position][0];
	int typeAll = orderlist[position][1];
	int typeDay = orderlist[position][2];
	int age = orderlist[position][3];
	int count = orderlist[position][4];
	int price = orderlist[position][5];
	int sales = orderlist[position][6];
	printf("%d%5d%5d%5d%5d%10d%6d\n", date, typeAll, typeDay, age, count, price, sales);
}

int main() {
	int orderList[100][7] = {0}; // �ֹ����� ����
	int i = 0;
	
	int position = fileRead(orderList);
	printf("=========================== report.csv ===========================\n");
	printf("%d%5d%5d%5d%5d%10d%6d\n", "��¥", "�̿��", "����", "����", "����", "����", "������");
	printTickets(position, orderList);
	printf("==============================================================\n\n"); 
		
	return 0;
}
