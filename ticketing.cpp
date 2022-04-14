#include <stdio.h>
#include <time.h> // 오늘날짜 구하는 헤더 

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
	
	return age;
}

int ticketCal(int typeAll, int typeDay, int age) { // 종합or파크, 종일or오후, 나이 
	int price = 0;
	
	if(age < 3 && age > 1) { // 베이비요금 
		price = 15000;
	} else if(typeAll == 1) { // 종합이용권 
		if(age > 19) { // 어른 
			if(typeDay == 1) price = 62000;
			else if(typeDay == 2) price = 50000;
		} else if(age < 18 && age > 12) { // 청소년 
			if(typeDay == 1) price = 54000;
			else if(typeDay == 2) price = 43000;
		} else if(age < 13 && age > 3) { // 어린이 
			if(typeDay == 1) price = 47000;
			else if(typeDay == 2) price = 36000;
		}
	} else if(typeAll == 2) { // 파크이용권 
		if(age > 19) { // 어른 
			if(typeDay == 1) price = 59000;
			else if(typeDay == 2) price = 47000;
		} else if(age < 18 && age > 12) { // 청소년 
			if(typeDay == 1) price = 52000;
			else if(typeDay == 2) price = 41000;
		} else if(age < 13 && age > 3) { // 어린이 
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
	
	printf("권종을 선택하세요.\n");
	printf("1. 종합이용권\n2. 파크이용권\n");
	scanf("%d", &typeAll);
	
	printf("권종을 선택하세요.\n");
	printf("1. 종일권\n2. 오후권\n");
	scanf("%d", &typeDay); 
	
	printf("주민번호를 입력하세요.(6자리까지)\n");
	scanf("%d", &residentNum);
	printf("몇개를 주문하시겠습니까? (최대 10개)\n"); 
	scanf("%d", &count);
	
	printf("우대사항을 선택하세요.\n");
	printf("1. 없음 ( 나이 우대는 자동처리)\n");
	printf("2. 장애인\n");
	printf("3. 국가유공자\n");
	printf("4. 휴가장병\n");
	printf("5. 임산부\n");
	printf("6. 다둥이행복카드\n");
	scanf("%d", &forsales);
	
	// 계산 
	int age = yearCal(residentNum); // 만나이 계산 
	int price = ticketCal(typeAll, typeDay, age); // 권종등에 따른 티켓값
	float percent = sales(forsales);
	int saleprice = (percent * price / 100) * 100; // 괄호가 없을경우 계산이 무시됨 
	int sum = 0;
	
	if((forsales > 1 && forsales < 5) && count > 1) { // 임산부 & 다둥이는 본인만 그 외는 동반 1인 할인 
		sum = saleprice * 2 + price * (count - 2);
	} else if(forsales > 1) {
		sum = saleprice + price * (count - 1);
	} else sum = price * count;
	
	printf("가격은 %d 원 입니다. \n", sum);
	printf("감사합니다.\n"); 
	
	printf("residentNum : %d, age : %d, price : %d, saleprice : %d, percet : %f", residentNum, age, price, saleprice, percent);
	
	
	
	return 0;
}
