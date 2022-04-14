#include <stdio.h>
#include <time.h> // ���ó�¥ ���ϴ� ��� 

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

int ticketCal(int typeAll, int typeDay, int age) { // ����or��ũ, ����or����, ���� 
	int price = 0;
	
	if(age < 3 && age > 1) { // ���̺��� 
		price = 15000;
	} else if(typeAll == 1) { // �����̿�� 
		if(age > 19) { // � 
			if(typeDay == 1) price = 62000;
			else if(typeDay == 2) price = 50000;
		} else if(age < 18 && age > 12) { // û�ҳ� 
			if(typeDay == 1) price = 54000;
			else if(typeDay == 2) price = 43000;
		} else if(age < 13 && age > 3) { // ��� 
			if(typeDay == 1) price = 47000;
			else if(typeDay == 2) price = 36000;
		}
	} else if(typeAll == 2) { // ��ũ�̿�� 
		if(age > 19) { // � 
			if(typeDay == 1) price = 59000;
			else if(typeDay == 2) price = 47000;
		} else if(age < 18 && age > 12) { // û�ҳ� 
			if(typeDay == 1) price = 52000;
			else if(typeDay == 2) price = 41000;
		} else if(age < 13 && age > 3) { // ��� 
			if(typeDay == 1) price = 46000;
			else if(typeDay == 2) price = 35000;
		}
	}
	
	return price;
}

float sales(int type) {
	const float percent[7] = {0, 1, 0.5, 0.5, 0.51, 0.5, 0.7};
	
	return percent[type];
}

void saveOrder(int ticketAll, int ticketDay, int age, int count, int price, int sales, int *position, int (*orderlist)[6]) {
	orderlist[*position][0] = ticketAll;
	orderlist[*position][1] = ticketDay;
	orderlist[*position][2] = age;
	orderlist[*position][3] = count;
	orderlist[*position][4] = price;
	orderlist[*position][5] = sales;
	(*position)++;
}

void printTickets(int sum, int *position, int(*orderlist)[6]) {
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
		else {
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
	int typeAll = 0;
	int typeDay = 0;
	int residentNum = 0;
	int count = 0;
	int forsales = 0;
	int check = 0; // �ݺ� üũ 
	int isExit = 0;
	int position = 0; // �ֹ� �迭 Ž����
	int totalSum = 0; 
	int orderList[100][6] = {0}; // �ֹ����� ���� 
	
	do {
		while(true) {
			printf("������ �����ϼ���.\n");
			printf("1. �����̿��\n2. ��ũ�̿��\n");
			scanf("%d", &typeAll);
			
			printf("������ �����ϼ���.\n");
			printf("1. ���ϱ�\n2. ���ı�\n");
			scanf("%d", &typeDay); 
			
			printf("�ֹι�ȣ�� �Է��ϼ���.(6�ڸ�����)\n");
			scanf("%d", &residentNum);
			printf("��� �ֹ��Ͻðڽ��ϱ�? (�ִ� 10��)\n"); 
			scanf("%d", &count);
			
			printf("�������� �����ϼ���.\n");
			printf("1. ���� ( ���� ���� �ڵ�ó��)\n");
			printf("2. �����\n");
			printf("3. ����������\n");
			printf("4. �ް��庴\n");
			printf("5. �ӻ��\n");
			printf("6. �ٵ����ູī��\n");
			scanf("%d", &forsales);
			
			// ��� 
			int age = yearCal(residentNum); // ������ ��� 
			int price = ticketCal(typeAll, typeDay, age); // ����� ���� Ƽ�ϰ�
			float percent = sales(forsales);
			int saleprice = percent * price;
			saleprice = (saleprice / 100) * 100;
			int sum = 0;
			
			if(age == -1 || count < 0) continue; // error
			
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
			scanf("%d", &check);
			if(check == 2) break;
		}
		printf("Ƽ�� �߱��� �����մϴ�. �����մϴ�.\n\n");
		printTickets(totalSum, &position, orderList);
		
		printf("��� ����(1: ���ο� �ֹ�, 2: ���α׷� ����) : ");
		scanf("%d", &isExit);
		position = 0;
		totalSum = 0;
	} while (isExit == 1);

	return 0;
}
