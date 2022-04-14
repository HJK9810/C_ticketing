#include <stdio.h>
#include <time.h> // ���ó�¥ ���ϴ� ���

void printError() {
	printf("�߸��Ȱ��� �Է���ϴ�. �ٽ� �Է��ϼ���.\n");
}

int inputTxt(int max) {
	int input = 0;
	do{
		scanf("%d", &input);
	} while(input < 1 || input > n);
	return input;
}

int yearCal(int yourAge) { // �ֹι�ȣ�� ���� ���̱��ϱ� 
	time_t t = time(NULL); // ���ó�¥ 
	struct tm tm = *localtime(&t);
	int nyear = tm.tm_year + 1900; // �⵵ - 1900����� ���ر����� �����⵵ 
	int nmonth = tm.tm_mon + 1; // ��  - 0~11 
	int nday = tm.tm_mday;
	
	int yyear = yourAge / 10000; // �ֹι�ȣ = �⵵���� ���ڸ� + �� ���ڸ� + ��¥ ���ڸ� 
	int ymonth = yourAge % 10000 / 100;
	int yday = yourAge % 100;
	
	if(nyear % 100 < yyear) yyear += 1900; // ���� �⵵ ���� ���ڸ����� ũ��? 1900���� 
	else yyear += 2000; // �۰ų� ����? 2000���� 
	
	int age = nyear - yyear; // ���� ���  
	
	if(nmonth < ymonth) age -= 1; // ������ ������ �ʾ������ 
	else if(nmonth == ymonth && nday >= yday) age -=1;	// �ش� ���ӿ��� ��¥�� ���� ������ �ʾ������
	
	if(age < 0 || ymonth > 12 || ymonth < 0 || yday > 31 || yday < 0) age = -1;
	
	return age;
}

int ticketCal(int typeAll, int typeDay, int age, int type) { // ����or��ũ, ����or����, ����, �������
 	const float percent[7] = {0, 1, 0.5, 0.5, 0.51, 0.5, 0.7}; // ������ ���η� 
	const int ADULT = {62000, 50000, 59000, 47000}; // ����-����, ����-����, ��ũ-����, ��ũ-���� 
	const int TEEN = {54000, 43000, 52000, 41000};
	const int CHILD = {47000, 36000, 46000, 35000};
	const int BABY = 15000; 
	int price = 0;
	int idx = 0;
	
	if(typeAll == 1) idx = typeDay - 1;
	else if(typeAll == 2) idx = typeDay + 1;
	
	if(age < 3 && age > 1) price = BABY;
	else if(age > 64) price = CHILD[idx]; // 65�� �̻� = ��̿�� 
	else if(age > 19) price = ADULT[idx];
	else if(age < 18 && age > 12) price = TEEN[idx];
	else if(age < 13 && age > 3) price = CHILD[idx];
	
	price *= percent[type]; // �� ������ ����� ����
	price = (price / 100) * 100; // �Ե����� ���ΰ��� 100�� �ڸ����� ������ �� 
	
	return price;
}

void saveOrder(int ticketAll, int ticketDay, int age, int count, int price, int sales, int *position, int (*orderlist)[6]) {
	orderlist[*position][0] = ticketAll; // ���� or ��ũ 
	orderlist[*position][1] = ticketDay; // ���� or ���ı� 
	orderlist[*position][2] = age; // ���� 
	orderlist[*position][3] = count; // �Ǽ� 
	orderlist[*position][4] = price; // �Ǵ� ���� - ������� ����� 
	orderlist[*position][5] = sales; // ������λ��� 
	(*position)++;
}

void printTickets(int sum, int *position, int(*orderlist)[6]) { // �׵��� �߱��� �κ� ��� 
	printf("Ƽ�� �߱��� �����մϴ�. �����մϴ�.\n\n");
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
		
		if(typeDay == 1) printf("%6s ", "���ϱ�");
		else if(typeDay == 2) printf("%6s ", "���ı�");
		
		if(age > 19) { // � 
			printf("%6s ", "�");
		} else if(age < 18 && age > 12) { // û�ҳ�
			printf("%6s ", "û�ҳ�"); 
		} else if(age < 13 && age > 3) { // ��� 
			printf("%6s ", "���");
		} else printf("%6s ", "���̺�");
		
		printf("X%-6d %-10d    ", count, price);
		
		if(sales == 1) printf("*������� ����\n");
		else{
			if(sales == 2) printf("*����� ");
			else if(sales == 3) printf("*���������� ");
			else if(sales == 4) printf("*�ް��庴 ");
			else if(sales == 5) printf("*�ӻ�� ");
			else if(sales == 6) printf("*�ٵ��� ");
			
			printf("�������\n");
		}
	}
	printf("\n����� �Ѿ��� %d�� �Դϴ�.\n", sum);
	printf("** �ӻ�ο� �ٵ����ູī�带 ������ �������� ���� 1�α��� ��밡 ����˴ϴ�.\n");
	printf("==============================================================\n\n"); 
}

int main() {
	int typeAll = 0; // ���� or ��ũ 
	int typeDay = 0; // ���� or ���� 
	int residentNum = 0; // �ֹι�ȣ ���ڸ� 
	int count = 0; // Ƽ�ϼ� 
	int forsales = 0; // ����������� 
	int check = 0; // �ݺ� üũ 
	int isExit = 0; // �ش� �ֹ� ���� 
	int position = 0; // �ֹ� �迭 Ž����
	int totalSum = 0;  // ��� Ƽ�� �� 
	int orderList[100][6] = {0}; // �ֹ����� ���� 
	
	do {
		while(true) {
			printf("������ �����ϼ���.\n");
			printf("1. �����̿��\n2. ��ũ�̿��\n");
			typeAll = inputTxt(2);
			
			printf("������ �����ϼ���.\n");
			printf("1. ���ϱ�\n2. ���ı�\n");
			typeDay = inputTxt(2);
			
			printf("�ֹι�ȣ�� �Է��ϼ���.(6�ڸ�����)\n");
			residentNum = inputTxt(1000000);
			printf("��� �ֹ��Ͻðڽ��ϱ�? (�ִ� 10��)\n"); 
			count = inputTxt(10);
			
			printf("�������� �����ϼ���.\n");
			printf("1. ���� ( ���� ���� �ڵ�ó��)\n");
			printf("2. �����\n");
			printf("3. ����������\n");
			printf("4. �ް��庴\n");
			printf("5. �ӻ��\n");
			printf("6. �ٵ����ູī��\n");
			forsales = inputTxt(6);
			
			// ��� 
			int age = yearCal(residentNum); // ������ ��� 
			int saleprice = ticketCal(typeAll, typeDay, age, forsales); // ����� ���� Ƽ�ϰ�
			int sum = 0; // ���ϱ� ������ 
			
			if((forsales > 1 && forsales < 5) && count > 1) { // �ӻ�� & �ٵ��̴� ���θ� �� �ܴ� ���� 1�� ���� 
				sum = saleprice * 2 + price * (count - 2);
			} else if(forsales > 1) {
				sum = saleprice + price * (count - 1);
			} else sum = price * count;
			totalSum += sum;
			saveOrder(typeAll, typeDay, age, count, saleprice, forsales, &position, orderList);
			
			printf("������ %d �� �Դϴ�. \n", sum);
			printf("�����մϴ�.\n\n"); 
			
			printf("��� �߱� �Ͻðڽ��ϱ�?\n");
			printf("1. Ƽ�� �߱�\n2.����\n");
			check = inputTxt(2);
			if(check == 2) break;
		}
		printTickets(totalSum, &position, orderList);
		
		printf("��� ����(1: ���ο� �ֹ�, 2: ���α׷� ����) : ");
		scanf("%d", &isExit);
		position = 0;
		totalSum = 0;
	} while (isExit == 1);

	return 0;
}
