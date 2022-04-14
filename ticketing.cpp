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
	float percent = 0.0;
	switch(type) {
		case 2:
			percent = 0.5;
			break;
		case 3:
			percent = 0.5;
			break;
		case 4:
			percent = 0.51;
			break;
		case 5:
			percent = 0.5;
			break;
		case 6:
			percent = 0.7;
			break;
		default:
			percent = 1;
			break;
	}
	
	return percent;
}

int main() {
	int typeAll = 0;
	int typeDay = 0;
	int residentNum = 0;
	int count = 0;
	int forsales = 0;
	
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
	int saleprice = (percent * price / 100) * 100; // ��ȣ�� ������� ����� ���õ� 
	int sum = 0;
	
	if((forsales > 1 && forsales < 5) && count > 1) { // �ӻ�� & �ٵ��̴� ���θ� �� �ܴ� ���� 1�� ���� 
		sum = saleprice * 2 + price * (count - 2);
	} else if(forsales > 1) {
		sum = saleprice + price * (count - 1);
	} else sum = price * count;
	
	printf("������ %d �� �Դϴ�. \n", sum);
	printf("�����մϴ�.\n"); 
	
	printf("residentNum : %d, age : %d, price : %d, saleprice : %d, percet : %f", residentNum, age, price, saleprice, percent);
	
	
	
	return 0;
}
