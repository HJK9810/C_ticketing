#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <time.h> // 오늘날짜 구하는 헤더
// 상수 
const int MIN_BABY = 1, MIN_CHILD = 3, MIN_TEEN = 13, MIN_ADULT = 19, MAX_CHILD = 12, MAX_TEEN = 18, MAX_ADULT = 64;
// 없음, 장애, 유공자, 휴가장병, 임산부, 다둥이 
const int NONE = 1, DISABLE = 2, MERIT = 3, VACSOLD = 4, PREGNANT = 5, MULTICHILD = 6;
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5;
int today = 0; // 오늘날짜 

void printError() { // error출력 
	printf("잘못된값이 입력됬습니다. 다시 입력하세요.\n");
}

int inputTxt(int max) { // 입력 - max값보다 많거나 0일경우, 다시입력 
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
// 입력파트 
void inputData(int *typeAll, int *typeDay, int *residentNum, int *count, int *forsales) {
	printf("  권종을 선택하세요.\n");
	printf("\t1. 종합이용권\n\t2. 파크이용권\n");
	*typeAll = inputTxt(2);
		
	printf("  권종을 선택하세요.\n");
	printf("\t1. 1DAY\n\t2. After4(오후 4시 이후 입장)\n");
	*typeDay = inputTxt(2);
		
	printf("  주민번호를 입력하세요.(6자리까지)\n");
	*residentNum = inputTxt(1000000);
	printf("  몇개를 주문하시겠습니까? (최대 10개)\n"); 
	*count = inputTxt(10);
		
	printf("  우대사항을 선택하세요.\n");
	printf("\t1. 없음 ( 나이 우대는 자동처리)\n");
	printf("\t2. 장애인\n");
	printf("\t3. 국가유공자\n");
	if(*typeAll == 1) {
		printf("\t4. 휴가장병\n");
		printf("\t5. 임산부\n");
		printf("\t6. 다둥이행복카드\n");
		*forsales = inputTxt(6);	
	} else *forsales = inputTxt(3);
	
}

// 계산파트 
int yearCal(int yourAge) { // 주민번호에 따른 나이구하기 
	time_t t = time(NULL); // 오늘날짜 
	struct tm tm = *localtime(&t);
	int nyear = tm.tm_year + 1900; // 년도 - 1900년부터 올해까지의 누적년도 
	int nmonth = tm.tm_mon + 1; // 월  - 0~11 
	int nday = tm.tm_mday;
	today = nyear * 10000 + nmonth * 100 + nday; // 오늘날짜표기 - yyyymmdd 
	
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

int ticketCal(int typeAll, int typeDay, int residentNum, int *age, int type, int count, int *saleprice) { // 종합or파크, 종일or오후, 나이
	const float percent[7] = {0, 1, 0.5, 0.5, 0.51, 0.5, 0.7}; // 각각의 할인률 
	const int ADULT[4] = {62000, 50000, 59000, 47000}; // 종합-종일, 종합-오후, 파크-종일, 파크-오후 
	const int TEEN[4] = {54000, 43000, 52000, 41000};
	const int CHILD[4] = {47000, 36000, 46000, 35000};
	const int BABY = 15000; 
	int price = 0;
	int idx = 0;
	
	if(typeAll == 1) idx = typeDay - 1;
	else if(typeAll == 2) idx = typeDay + 1;
	
	*age = yearCal(residentNum); // 만나이 계산
	if(*age < MIN_CHILD  && *age >= MIN_BABY) {
		price = BABY_FEE;
		*age = BABY;
	} else if(*age > MAX_ADULT) {
		price = CHILD_FEE[idx]; // 65세 이상 = 어린이요금
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

	// 각 할인이 적용된 가격
	*saleprice = (price * percent[type] / 100) * 100; // 롯데월드 할인가는 100의 자리에서 버림한 값
	
	int sum = 0;
	if(type == NONE) sum = price * count;
	else if((type != PREGNANT || type != MULTICHILD) && count > 1) { // 임산부 & 다둥이는 본인만 그 외는 동반 1인 할인 
		sum = *saleprice * 2 + price * (count - 2);
	} else sum = *saleprice + price * (count - 1);
	
	return sum;
}

// save data 
void saveOrder(int ticketAll, int ticketDay, int age, int count, int price, int sales, int *position, int (*orderlist)[6]) {
	orderlist[*position][0] = ticketAll; // 종합 or 파크 
	orderlist[*position][1] = ticketDay; // 종일 or 오후권 
	orderlist[*position][2] = age; // 나이 
	orderlist[*position][3] = count; // 권수 
	orderlist[*position][4] = price; // 권당 가격 - 우대할인 적용시 
	orderlist[*position][5] = sales; // 우대할인사항 
	(*position)++;
}
// print
int printRepeat(int sum) { // 발권 지속 여부 
	printf("  가격은 %d 원 입니다. \n", sum);
	printf("  감사합니다.\n\n"); 
			
	printf("  계속 발권 하시겠습니까?\n");
	printf("\t1. 티켓 발권\n\t2.종료\n");
	
	return inputTxt(2);
}

void printTickets(int sum, int *position, int(*orderlist)[6]) { // 그동안 발권한 부분 출력 
	printf("  티켓 발권을 종료합니다. 감사합니다.\n\n");
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
		
		if(typeDay == 1) printf("%6s ", "1DAY");
		else if(typeDay == 2) printf("%6s ", "After4");
		
		if(age == OLD){
			printf("%6s ", "노인");
		} else if(age == ADULT) { // 어른 
			printf("%6s ", "어른");
		} else if(age == TEEN) { // 청소년
			printf("%6s ", "청소년"); 
		} else if(age == CHILD) { // 어린이 
			printf("%6s ", "어린이");
		} else printf("%6s ", "베이비");
		
		printf("X%-6d %-10d    ", count, price);
		
		if(sales == NONE) printf("*우대적용 없음\n");
		else{
			if(sales == DISABLE) printf("*장애인 ");
			else if(sales == MERIT) printf("*국가유공자 ");
			else if(sales == VACSOLD) printf("*휴가장병 ");
			else if(sales == PREGNANT) printf("*임산부 ");
			else if(sales == MULTICHILD) printf("*다둥이 ");
			
			printf("우대적용\n");
		}
	}
	printf("\n\t입장료 총액은 %d원 입니다.\n", sum);
	printf(" ** 임산부와 다둥이행복카드를 제외한 우대사항은 동반 1인까지 우대가 적용됩니다.\n");
	printf("==============================================================\n\n"); 
}

void orderFilePrint(int totalSum, int *position, int(*orderList)[6]) { // 파일에 저장 
	FILE *fp = fopen("report.csv", "a"); // 이어쓰기
	for(int idx = 0; idx < *position; idx++) {
		fprintf(fp, "%d,", today); // 날짜 저장 
		int typeAll = orderList[idx][0];
		int typeDay = orderList[idx][1];
		int age = orderList[idx][2];
		int count = orderList[idx][3];
		int price = orderList[idx][4] / 100 * 100;
		int sales = orderList[idx][5];
		// 이용권 
		if(typeAll == 1) fprintf(fp, "%-12s,", "종합이용권");
		else if(typeAll == 2) fprintf(fp, "%-12s,", "파크이용권");
		// 권종 
		if(typeDay == 1) fprintf(fp, "%-6s,", "1DAY");
		else if(typeDay == 2) fprintf(fp, "%-6s,", "After4");
		// 연령 
		if(age == OLD){
			fprintf(fp, "%-6s,", "노인");
		} else if(age == ADULT) { // 어른 
			fprintf(fp, "%-6s,", "어른");
		} else if(age == TEEN) { // 청소년
			fprintf(fp, "%-6s,", "청소년"); 
		} else if(age == CHILD) { // 어린이 
			fprintf(fp, "%-6s,", "어린이");
		} else fprintf(fp, "%-6s,", "베이비");
		// 수량 & 가격 
		fprintf(fp, "%d,%d,", count, price);
		// 우대사항 
		if(sales == NONE) fprintf(fp, "없음\n");
		else{
			if(sales == DISABLE) fprintf(fp, "장애인\n");
			else if(sales == MERIT) fprintf(fp, "국가유공자\n");
			else if(sales == VACSOLD) fprintf(fp, "휴가장병\n");
			else if(sales == PREGNANT) fprintf(fp, "임산부\n");
			else if(sales == MULTICHILD) fprintf(fp, "다둥이\n");
		}
	}
	fclose(fp);
}

int main() {
	int isExit = 0; // 해당 주문 종료 
	int orderList[100][6] = {0}; // 주문내역 저장 
	
	do {
		int totalSum = 0;  // 모든 티켓 합 
		int position = 0; // 주문 배열 탐색용
		while(true) {
			int typeAll = 0; // 종합 or 파크 
			int typeDay = 0; // 종일 or 오후 
			int residentNum = 0; // 주민번호 앞자리 
			int count = 0; // 티켓수 
			int forsales = 0; // 우대할인적용
			int saleprice = 0; // 할인가 적용 티켓값 
			int age = 0;
			
			inputData(&typeAll, &typeDay, &residentNum, &count, &forsales); // 데이터 입력
			
			// 계산 
			int sum = ticketCal(typeAll, typeDay, residentNum, &age, forsales, count, &saleprice); // 동일권 가격합
			saveOrder(typeAll, typeDay, age, count, saleprice, forsales, &position, orderList);
			totalSum += sum;
			int check = printRepeat(sum);
			if(check == 2) break;
		}
		printTickets(totalSum, &position, orderList);
		orderFilePrint(totalSum, &position, orderList);
		
		printf("  계속 진행(1: 새로운 주문, 2: 프로그램 종료) : \n");
		isExit = inputTxt(2);
	} while (isExit == 1);

	return 0;
}
