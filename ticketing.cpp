#include <stdio.h>
#include <time.h> // ���ó�¥ ���ϴ� ���
const int MIN_BABY = 1, MIN_CHILD = 3, MIN_TEEN = 13, MIN_ADULT = 19, MAX_CHILD = 12, MAX_TEEN = 18, MAX_ADULT = 64;

void printError() { // error��� 
	printf("�߸��Ȱ��� �Է���ϴ�. �ٽ� �Է��ϼ���.\n");
}

int inputTxt(int max) { // �Է� - max������ ���ų� 0�ϰ��, �ٽ��Է� 
	int input = 0;
	if(max < 20) {
		do{
			printf("�Է��ϼ��� : ");
			scanf("%d", &input);
		} while(input < 1 || input > max);
	} else {
		while(true){
			printf("�Է��ϼ��� : ");
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
	printf("������ �����ϼ���.\n");
	printf("1. �����̿��\n2. ��ũ�̿��\n");
	*typeAll = inputTxt(2);
		
	printf("������ �����ϼ���.\n");
	printf("1. ���ϱ�\n2. ���ı�\n");
	*typeDay = inputTxt(2);
		
	printf("�ֹι�ȣ�� �Է��ϼ���.(6�ڸ�����)\n");
	*residentNum = inputTxt(1000000);
	printf("��� �ֹ��Ͻðڽ��ϱ�? (�ִ� 10��)\n"); 
	*count = inputTxt(10);
		
	printf("�������� �����ϼ���.\n");
	printf("1. ���� ( ���� ���� �ڵ�ó��)\n");
	printf("2. �����\n");
	printf("3. ����������\n");
	printf("4. �ް��庴\n");
	printf("5. �ӻ��\n");
	printf("6. �ٵ����ູī��\n");
	*forsales = inputTxt(6);
}

// �����Ʈ 
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

int ticketCal(int typeAll, int typeDay, int *age, int type, int count, int *saleprice) { // ����or��ũ, ����or����, ����
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
	if(age < MIN_CHILD  && age > MIN_BABY) price = BABY;
	else if(age > MAX_TEEN) price = CHILD[idx]; // 65�� �̻� = ��̿�� 
	else if(age > MIN_ADULT) price = ADULT[idx];
	else if(age < MIN_ADULT && age > MAX_CHILD) price = TEEN[idx];
	else if(age < MIN_TEEN && age >= MIN_CHILD) price = CHILD[idx];

	price *= percent[type]; // �� ������ ����� ����
	*saleprice = (price / 100) * 100; // �Ե����� ���ΰ��� 100�� �ڸ����� ������ ��
	
	int sum = 0;
	if((type > 1 && type < 5) && count > 1) { // �ӻ�� & �ٵ��̴� ���θ� �� �ܴ� ���� 1�� ���� 
		sum = *saleprice * 2 + price * (count - 2);
	} else if(type > 1) {
		sum = *saleprice + price * (count - 1);
	} else sum = price * count;
	
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
	printf("������ %d �� �Դϴ�. \n", sum);
	printf("�����մϴ�.\n\n"); 
			
	printf("��� �߱� �Ͻðڽ��ϱ�?\n");
	printf("1. Ƽ�� �߱�\n2.����\n");
	
	return inputTxt(2);
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
		
		if(age > MAX_ADULT){
			printf("%6s ", "����");
		} else if(age > MAX_TEEN) { // � 
			printf("%6s ", "�");
		} else if(age < MIN_ADULT && age > MAX_CHILD) { // û�ҳ�
			printf("%6s ", "û�ҳ�"); 
		} else if(age < MIN_TEEN && age >= MIN_CHILD) { // ��� 
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
	int isExit = 0; // �ش� �ֹ� ���� 
	int position = 0; // �ֹ� �迭 Ž����
	int totalSum = 0;  // ��� Ƽ�� �� 
	int orderList[100][6] = {0}; // �ֹ����� ���� 
	
	do {
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
			int sum = ticketCal(typeAll, typeDay, &age, forsales, count, &saleprice); // ���ϱ� ������
			saveOrder(typeAll, typeDay, age, count, saleprice, forsales, &position, orderList);
			totalSum += sum;
			int check = printRepeat(sum);
			if(check == 2) break;
		}
		printTickets(totalSum, &position, orderList);
		
		printf("��� ����(1: ���ο� �ֹ�, 2: ���α׷� ����) : ");
		isExit = inputTxt(2);
		position = 0;
		totalSum = 0;
	} while (isExit == 1);

	return 0;
}
