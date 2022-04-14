#include <stdio.h>
#include <time.h> // 오늘날짜 구하는 헤더

void printError() {
	printf("잘못된값이 입력됬습니다. 다시 입력하세요.\n");
}

int inputTxt(int max) {
	int input = 0;
	do{
		scanf("%d", &input);
	} while(input < 1 || input > n);
	return input;
}

int yearCal(int yourAge) { // 주민번호에 따른 나이구하기 
	time_t t = time(NULL); // 오늘날짜 
	struct tm tm = *localtime(&t);
	int nyear = tm.tm_year + 1900; // 년도 - 1900년부터 올해까지의 누적년도 
	int nmonth = tm.tm_mon + 1; // 월  - 0~11 
	int nday = tm.tm_mday;
	
	int yyear = yourAge / 10000; // 주민번호 = 년도뒤의 두자리 + 월 두자리 + 날짜 두자리 
	int ymonth = yourAge % 10000 / 100;
	int yday = yourAge % 100;
	
	if(nyear % 100 < yyear) yyear += 1900; // 올해 년도 뒤의 두자리보다 크다? 1900년대생 
	else yyear += 2000; // 작거나 같다? 2000년대생 
	
	int age = nyear - yyear; // 양쪽 모두  
	
	if(nmonth < ymonth) age -= 1; // 생일이 지나지 않았을경우 
	else if(nmonth == ymonth && nday >= yday) age -=1;	// 해당 달임에도 날짜가 아직 지나지 않았을경우
	
	if(age < 0 || ymonth > 12 || ymonth < 0 || yday > 31 || yday < 0) age = -1;
	
	return age;
}

int ticketCal(int typeAll, int typeDay, int age, int type) { // 종합or파크, 종일or오후, 나이, 우대할인
 	const float percent[7] = {0, 1, 0.5, 0.5, 0.51, 0.5, 0.7}; // 각각의 할인률 
	const int ADULT = {62000, 50000, 59000, 47000}; // 종합-종일, 종합-오후, 파크-종일, 파크-오후 
	const int TEEN = {54000, 43000, 52000, 41000};
	const int CHILD = {47000, 36000, 46000, 35000};
	const int BABY = 15000; 
	int price = 0;
	int idx = 0;
	
	if(typeAll == 1) idx = typeDay - 1;
	else if(typeAll == 2) idx = typeDay + 1;
	
	if(age < 3 && age > 1) price = BABY;
	else if(age > 64) price = CHILD[idx]; // 65세 이상 = 어린이요금 
	else if(age > 19) price = ADULT[idx];
	else if(age < 18 && age > 12) price = TEEN[idx];
	else if(age < 13 && age > 3) price = CHILD[idx];
	
	price *= percent[type]; // 각 할인이 적용된 가격
	price = (price / 100) * 100; // 롯데월드 할인가는 100의 자리에서 버림한 값 
	
	return price;
}

void saveOrder(int ticketAll, int ticketDay, int age, int count, int price, int sales, int *position, int (*orderlist)[6]) {
	orderlist[*position][0] = ticketAll; // 종합 or 파크 
	orderlist[*position][1] = ticketDay; // 종일 or 오후권 
	orderlist[*position][2] = age; // 나이 
	orderlist[*position][3] = count; // 권수 
	orderlist[*position][4] = price; // 권당 가격 - 우대할인 적용시 
	orderlist[*position][5] = sales; // 우대할인사항 
	(*position)++;
}

void printTickets(int sum, int *position, int(*orderlist)[6]) { // 그동안 발권한 부분 출력 
	printf("티켓 발권을 종료합니다. 감사합니다.\n\n");
	printf("===========================롯데월드===========================\n");
	for(int idx = 0; idx < *position; idx++) {
		int typeAll = orderlist[idx][0];
		int typeDay = orderlist[idx][1];
		int age = orderlist[idx][2];
		int count = orderlist[idx][3];
		int price = orderlist[idx][4] / 100 * 100;
		int sales = orderlist[idx][5];
		
		if(typeAll == 1) printf("%12s ", "종합이용권");
		else if(typeAll == 2) printf("%12s ", "파크이용권");
		
		if(typeDay == 1) printf("%6s ", "종일권");
		else if(typeDay == 2) printf("%6s ", "오후권");
		
		if(age > 19) { // 어른 
			printf("%6s ", "어른");
		} else if(age < 18 && age > 12) { // 청소년
			printf("%6s ", "청소년"); 
		} else if(age < 13 && age > 3) { // 어린이 
			printf("%6s ", "어린이");
		} else printf("%6s ", "베이비");
		
		printf("X%-6d %-10d    ", count, price);
		
		if(sales == 1) printf("*우대적용 없음\n");
		else{
			if(sales == 2) printf("*장애인 ");
			else if(sales == 3) printf("*국가유공자 ");
			else if(sales == 4) printf("*휴가장병 ");
			else if(sales == 5) printf("*임산부 ");
			else if(sales == 6) printf("*다둥이 ");
			
			printf("우대적용\n");
		}
	}
	printf("\n입장료 총액은 %d원 입니다.\n", sum);
	printf("** 임산부와 다둥이행복카드를 제외한 우대사항은 동반 1인까지 우대가 적용됩니다.\n");
	printf("==============================================================\n\n"); 
}

int main() {
	int typeAll = 0; // 종합 or 파크 
	int typeDay = 0; // 종일 or 오후 
	int residentNum = 0; // 주민번호 앞자리 
	int count = 0; // 티켓수 
	int forsales = 0; // 우대할인적용 
	int check = 0; // 반복 체크 
	int isExit = 0; // 해당 주문 종료 
	int position = 0; // 주문 배열 탐색용
	int totalSum = 0;  // 모든 티켓 합 
	int orderList[100][6] = {0}; // 주문내역 저장 
	
	do {
		while(true) {
			printf("권종을 선택하세요.\n");
			printf("1. 종합이용권\n2. 파크이용권\n");
			typeAll = inputTxt(2);
			
			printf("권종을 선택하세요.\n");
			printf("1. 종일권\n2. 오후권\n");
			typeDay = inputTxt(2);
			
			printf("주민번호를 입력하세요.(6자리까지)\n");
			residentNum = inputTxt(1000000);
			printf("몇개를 주문하시겠습니까? (최대 10개)\n"); 
			count = inputTxt(10);
			
			printf("우대사항을 선택하세요.\n");
			printf("1. 없음 ( 나이 우대는 자동처리)\n");
			printf("2. 장애인\n");
			printf("3. 국가유공자\n");
			printf("4. 휴가장병\n");
			printf("5. 임산부\n");
			printf("6. 다둥이행복카드\n");
			forsales = inputTxt(6);
			
			// 계산 
			int age = yearCal(residentNum); // 만나이 계산 
			int saleprice = ticketCal(typeAll, typeDay, age, forsales); // 권종등에 따른 티켓값
			int sum = 0; // 동일권 가격합 
			
			if((forsales > 1 && forsales < 5) && count > 1) { // 임산부 & 다둥이는 본인만 그 외는 동반 1인 할인 
				sum = saleprice * 2 + price * (count - 2);
			} else if(forsales > 1) {
				sum = saleprice + price * (count - 1);
			} else sum = price * count;
			totalSum += sum;
			saveOrder(typeAll, typeDay, age, count, saleprice, forsales, &position, orderList);
			
			printf("가격은 %d 원 입니다. \n", sum);
			printf("감사합니다.\n\n"); 
			
			printf("계속 발권 하시겠습니까?\n");
			printf("1. 티켓 발권\n2.종료\n");
			check = inputTxt(2);
			if(check == 2) break;
		}
		printTickets(totalSum, &position, orderList);
		
		printf("계속 진행(1: 새로운 주문, 2: 프로그램 종료) : ");
		scanf("%d", &isExit);
		position = 0;
		totalSum = 0;
	} while (isExit == 1);

	return 0;
}
