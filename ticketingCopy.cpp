#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <time.h> // ���ó�¥ ���ϴ� ���
// ��� 
const int MIN_BABY = 1, MIN_CHILD = 3, MIN_TEEN = 13, MIN_ADULT = 19, MAX_CHILD = 12, MAX_TEEN = 18, MAX_ADULT = 64;
// ����, ���, ������, �ް��庴, �ӻ��, �ٵ��� 
const int NONE = 1, DISABLE = 2, MERIT = 3, VACSOLD = 4, PREGNANT = 5, MULTICHILD = 6;
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5;
int today = 0; // ���ó�¥ 

void printError() { // error��� 
	printf("�߸��Ȱ��� �Է���ϴ�. �ٽ� �Է��ϼ���.\n");
}

int inputTxt(int max) { // �Է� - max������ ���ų� 0�ϰ��, �ٽ��Է� 
	int input = 0;
	if(max < 20) {
		do{
			printf("\t\t => ");
			scanf("%d", &input);
		} while(input < 1 || input > max);
	} else {
		while(true){
			printf("\t\t => ");
			scanf("%d", &input);
			int year = input / 10000;
			int month = input % 10000 / 100;
			int day = input % 100;
			if(year < 100 && (month < 13 && month > 0) && (day < 32 && day > 0)) break;
		} 
	}
	
	return input;
}
// �Է���Ʈ 
void inputData(int *typeAll, int *typeDay, int *residentNum, int *count, int *forsales) {
	printf("  ������ �����ϼ���.\n");
	printf("\t1. �����̿��\n\t2. ��ũ�̿��\n");
	*typeAll = inputTxt(2);
		
	printf("  ������ �����ϼ���.\n");
	printf("\t1. 1DAY\n\t2. After4(���� 4�� ���� ����)\n");
	*typeDay = inputTxt(2);
		
	printf("  �ֹι�ȣ�� �Է��ϼ���.(6�ڸ�����)\n");
	*residentNum = inputTxt(1000000);
	printf("  ��� �ֹ��Ͻðڽ��ϱ�? (�ִ� 10��)\n"); 
	*count = inputTxt(10);
		
	printf("  �������� �����ϼ���.\n");
	printf("\t1. ���� ( ���� ���� �ڵ�ó��)\n");
	printf("\t2. �����\n");
	printf("\t3. ����������\n");
	if(*typeAll == 1) {
		printf("\t4. �ް��庴\n");
		printf("\t5. �ӻ��\n");
		printf("\t6. �ٵ����ູī��\n");
		*forsales = inputTxt(6);	
	} else *forsales = inputTxt(3);
	
}

// �����Ʈ 
int yearCal(int yourAge) { // �ֹι�ȣ�� ���� ���̱��ϱ� 
	time_t t = time(NULL); // ���ó�¥ 
	struct tm tm = *localtime(&t);
	int nyear = tm.tm_year + 1900; // �⵵ - 1900����� ���ر����� �����⵵ 
	int nmonth = tm.tm_mon + 1; // ��  - 0~11 
	int nday = tm.tm_mday;
	today = nyear * 10000 + nmonth * 100 + nday; // ���ó�¥ǥ�� - yyyymmdd 
	
	int yyear = yourAge / 10000; // �ֹι�ȣ = �⵵���� ���ڸ� + �� ���ڸ� + ��¥ ���ڸ� 
	int ymonth = yourAge % 10000 / 100;
	int yday = yourAge % 100;
	
	if(nyear % 100 < yyear) yyear += 1900; // ���� �⵵ ���� ���ڸ����� ũ��? 1900���� 
	else yyear += 2000; // �۰ų� ����? 2000���� 
	
	int age = nyear - yyear; // ���� ���  
	
	if(nmonth < ymonth) age -= 1; // ������ ������ �ʾ������ 
	else if(nmonth == ymonth && nday >= yday) age -=1;	// �ش� ���ӿ��� ��¥�� ���� ������ �ʾ������
	
	return age;
}

int ticketCal(int typeAll, int typeDay, int residentNum, int *age, int type, int count, int *saleprice) { // ����or��ũ, ����or����, ����
	const float percent[7] = {0, 1, 0.5, 0.5, 0.51, 0.5, 0.7}; // ������ ���η� 
	const int ADULT[4] = {62000, 50000, 59000, 47000}; // ����-����, ����-����, ��ũ-����, ��ũ-���� 
	const int TEEN[4] = {54000, 43000, 52000, 41000};
	const int CHILD[4] = {47000, 36000, 46000, 35000};
	const int BABY = 15000; 
	int price = 0;
	int idx = 0;
	
	if(typeAll == 1) idx = typeDay - 1;
	else if(typeAll == 2) idx = typeDay + 1;
	
	*age = yearCal(residentNum); // ������ ���
	if(*age < MIN_CHILD  && *age >= MIN_BABY) {
		price = BABY_FEE;
		*age = BABY;
	} else if(*age > MAX_ADULT) {
		price = CHILD_FEE[idx]; // 65�� �̻� = ��̿��
		*age = OLD;
	} else if(*age > MAX_TEEN) {
		price = ADULT_FEE[idx];	
		*age = ADULT;
	} else if(*age < MIN_ADULT && *age > MAX_CHILD) {
		price = TEEN_FEE[idx];
		*age = TEEN;
	} else if(*age < MIN_TEEN && *age >= MIN_CHILD) {
		price = CHILD_FEE[idx];
		*age = CHILD;
	}

	// �� ������ ����� ����
	*saleprice = (price * percent[type] / 100) * 100; // �Ե����� ���ΰ��� 100�� �ڸ����� ������ ��
	
	int sum = 0;
	if(type == NONE) sum = price * count;
	else if((type != PREGNANT || type != MULTICHILD) && count > 1) { // �ӻ�� & �ٵ��̴� ���θ� �� �ܴ� ���� 1�� ���� 
		sum = *saleprice * 2 + price * (count - 2);
	} else sum = *saleprice + price * (count - 1);
	
	return sum;
}

// save data 
void saveOrder(int ticketAll, int ticketDay, int age, int count, int price, int sales, int *position, int (*orderlist)[6]) {
	orderlist[*position][0] = ticketAll; // ���� or ��ũ 
	orderlist[*position][1] = ticketDay; // ���� or ���ı� 
	orderlist[*position][2] = age; // ���� 
	orderlist[*position][3] = count; // �Ǽ� 
	orderlist[*position][4] = price; // �Ǵ� ���� - ������� ����� 
	orderlist[*position][5] = sales; // ������λ��� 
	(*position)++;
}
// print
int printRepeat(int sum) { // �߱� ���� ���� 
	printf("  ������ %d �� �Դϴ�. \n", sum);
	printf("  �����մϴ�.\n\n"); 
			
	printf("  ��� �߱� �Ͻðڽ��ϱ�?\n");
	printf("\t1. Ƽ�� �߱�\n\t2.����\n");
	
	return inputTxt(2);
}

void printTickets(int sum, int *position, int(*orderlist)[6]) { // �׵��� �߱��� �κ� ��� 
	printf("  Ƽ�� �߱��� �����մϴ�. �����մϴ�.\n\n");
	printf("===========================�Ե�����===========================\n");
	for(int idx = 0; idx < *position; idx++) {
		int typeAll = orderlist[idx][0];
		int typeDay = orderlist[idx][1];
		int age = orderlist[idx][2];
		int count = orderlist[idx][3];
		int price = orderlist[idx][4] / 100 * 100;
		int sales = orderlist[idx][5];
		
		if(typeAll == 1) printf("%12s ", "�����̿��");
		else if(typeAll == 2) printf("%12s ", "��ũ�̿��");
		
		if(typeDay == 1) printf("%6s ", "1DAY");
		else if(typeDay == 2) printf("%6s ", "After4");
		
		if(age == OLD){
			printf("%6s ", "����");
		} else if(age == ADULT) { // � 
			printf("%6s ", "�");
		} else if(age == TEEN) { // û�ҳ�
			printf("%6s ", "û�ҳ�"); 
		} else if(age == CHILD) { // ��� 
			printf("%6s ", "���");
		} else printf("%6s ", "���̺�");
		
		printf("X%-6d %-10d    ", count, price);
		
		if(sales == NONE) printf("*������� ����\n");
		else{
			if(sales == DISABLE) printf("*����� ");
			else if(sales == MERIT) printf("*���������� ");
			else if(sales == VACSOLD) printf("*�ް��庴 ");
			else if(sales == PREGNANT) printf("*�ӻ�� ");
			else if(sales == MULTICHILD) printf("*�ٵ��� ");
			
			printf("�������\n");
		}
	}
	printf("\n\t����� �Ѿ��� %d�� �Դϴ�.\n", sum);
	printf(" ** �ӻ�ο� �ٵ����ູī�带 ������ �������� ���� 1�α��� ��밡 ����˴ϴ�.\n");
	printf("==============================================================\n\n"); 
}

void orderFilePrint(int totalSum, int *position, int(*orderList)[6]) { // ���Ͽ� ���� 
	FILE *fp = fopen("report.csv", "a"); // �̾��
	for(int idx = 0; idx < *position; idx++) {
		fprintf(fp, "%d,", today); // ��¥ ���� 
		int typeAll = orderList[idx][0];
		int typeDay = orderList[idx][1];
		int age = orderList[idx][2];
		int count = orderList[idx][3];
		int price = orderList[idx][4] / 100 * 100;
		int sales = orderList[idx][5];
		// �̿�� 
		if(typeAll == 1) fprintf(fp, "%-12s,", "�����̿��");
		else if(typeAll == 2) fprintf(fp, "%-12s,", "��ũ�̿��");
		// ���� 
		if(typeDay == 1) fprintf(fp, "%-6s,", "1DAY");
		else if(typeDay == 2) fprintf(fp, "%-6s,", "After4");
		// ���� 
		if(age == OLD){
			fprintf(fp, "%-6s,", "����");
		} else if(age == ADULT) { // � 
			fprintf(fp, "%-6s,", "�");
		} else if(age == TEEN) { // û�ҳ�
			fprintf(fp, "%-6s,", "û�ҳ�"); 
		} else if(age == CHILD) { // ��� 
			fprintf(fp, "%-6s,", "���");
		} else fprintf(fp, "%-6s,", "���̺�");
		// ���� & ���� 
		fprintf(fp, "%d,%d,", count, price);
		// ������ 
		if(sales == NONE) fprintf(fp, "����\n");
		else{
			if(sales == DISABLE) fprintf(fp, "�����\n");
			else if(sales == MERIT) fprintf(fp, "����������\n");
			else if(sales == VACSOLD) fprintf(fp, "�ް��庴\n");
			else if(sales == PREGNANT) fprintf(fp, "�ӻ��\n");
			else if(sales == MULTICHILD) fprintf(fp, "�ٵ���\n");
		}
	}
	fclose(fp);
}

int main() {
	int isExit = 0; // �ش� �ֹ� ���� 
	int orderList[100][6] = {0}; // �ֹ����� ���� 
	
	do {
		int totalSum = 0;  // ��� Ƽ�� �� 
		int position = 0; // �ֹ� �迭 Ž����
		while(true) {
			int typeAll = 0; // ���� or ��ũ 
			int typeDay = 0; // ���� or ���� 
			int residentNum = 0; // �ֹι�ȣ ���ڸ� 
			int count = 0; // Ƽ�ϼ� 
			int forsales = 0; // �����������
			int saleprice = 0; // ���ΰ� ���� Ƽ�ϰ� 
			int age = 0;
			
			inputData(&typeAll, &typeDay, &residentNum, &count, &forsales); // ������ �Է�
			
			// ��� 
			int sum = ticketCal(typeAll, typeDay, residentNum, &age, forsales, count, &saleprice); // ���ϱ� ������
			saveOrder(typeAll, typeDay, age, count, saleprice, forsales, &position, orderList);
			totalSum += sum;
			int check = printRepeat(sum);
			if(check == 2) break;
		}
		printTickets(totalSum, &position, orderList);
		orderFilePrint(totalSum, &position, orderList);
		
		printf("  ��� ����(1: ���ο� �ֹ�, 2: ���α׷� ����) : \n");
		isExit = inputTxt(2);
	} while (isExit == 1);

	return 0;
}
