#define _CRT_SECURE_NO_WARNINGS // fopen ���� ���� ���� ������ ���� ����
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
// ����, ���, ������, �ް��庴, �ӻ��, �ٵ��� 
const int NONE = 1, DISABLE = 2, MERIT = 3, VACSOLD = 4, PREGNANT = 5, MULTICHILD = 6;
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5;

// save data 
void saveOrder(int *position, int (*orderlist)[7], char pLine[]) {
	int date = 0;
	int ticketAll = 0; // ���� or ��ũ 
	int ticketDay = 0; // ���� or ���� 
	int age = 0; // ���� 
	int count = 0; // Ƽ�ϼ�
	int price = 0; // ���� 
	int sales = 0; // ������ 
	
	char *ptr = strtok(pLine, ","); // �ش� �� ,������ �и�
	while(ptr != NULL) { // , �� �з��� ���ڵ� �� ������ �Է� 
		// �̿�� üũ strcmp : c ���ڿ� �� => ������ 0
		if(strcmp(ptr, "�����̿��  ") == 0) ticketAll = 1;
		else if(strcmp(ptr, "��ũ�̿��  ") == 0) ticketAll = 2;
		// ���� üũ 
		if(strcmp(ptr, "���ϱ�") == 0) ticketDay = 1;
		else if(strcmp(ptr, "���ı�") == 0) ticketDay = 2;
		// ���� üũ 
		if(strcmp(ptr, "����  ") == 0) age = OLD;
		else if(strcmp(ptr, "�  ") == 0) age = ADULT;
		else if(strcmp(ptr, "û�ҳ�") == 0) age = TEEN;
		else if(strcmp(ptr, "���") == 0) age = CHILD;
		else if(strcmp(ptr, "���̺�") == 0) age = BABY;
		// ������ üũ 
		if(strcmp(ptr, "����\n") == 0) sales = NONE;
		else if(strcmp(ptr, "�����\n") == 0) sales = DISABLE;
		else if(strcmp(ptr, "����������\n") == 0) sales = MERIT;
		else if(strcmp(ptr, "�ް��庴\n") == 0) sales = VACSOLD;
		else if(strcmp(ptr, "�ӻ��\n") == 0) sales = PREGNANT;
		else if(strcmp(ptr, "�ٵ���\n") == 0) sales = MULTICHILD;
		// ���� ����
		int number = strtol(ptr, NULL, 10);
		if(number > 0 && number < 11) count = number; // ������ 1~10���� 
		else if(number % 100 != 0) date = number; // 100���� �������� �������� ��¥�� �ش��ϱ⿡ 0 �Ұ� 
		else if(number > 10) price = number; // ������ 0 ���� ���� & �ּ� ������ 100���̱⿡ ������ ������ 0
		ptr = strtok(NULL, ","); 
	}
	// �Է¹��� ������, �迭 �Է� 
	orderlist[*position][0] = date;
	orderlist[*position][1] = ticketAll; // ���� or ��ũ 
	orderlist[*position][2] = ticketDay; // ���� or ���ı� 
	orderlist[*position][3] = age; // ���� 
	orderlist[*position][4] = count; // �Ǽ� 
	orderlist[*position][5] = price; // �Ǵ� ���� - ������� ����� 
	orderlist[*position][6] = sales; // ������λ��� 
	(*position)++;
}

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
	FILE *fp = fopen("report.csv", "r"); // only read
	const int MAX = 1024;
	char line[MAX]; // �б����� �迭
	char *pLine; 
	int position = 0;
	int orderList[100][7] = {0}; // �ֹ����� ����
	int i = 0;
	
	printf("=========================== report.csv ===========================\n");
	while(!feof(fp)) {
		pLine = fgets(line, MAX, fp);
		if(!isdigit(pLine[0])) {
			printf("%s", pLine);
		} else { 
			saveOrder(&position, orderList, pLine);
			printTickets(position - 1, orderList);
		}
	}
	fclose(fp);
//	printTickets(position, orderList);
	printf("==============================================================\n\n"); 
		
	return 0;
}
