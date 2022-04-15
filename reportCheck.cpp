#define _CRT_SECURE_NO_WARNINGS // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
// 없음, 장애, 유공자, 휴가장병, 임산부, 다둥이 
const int NONE = 1, DISABLE = 2, MERIT = 3, VACSOLD = 4, PREGNANT = 5, MULTICHILD = 6;
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5;

// save data 
void saveOrder(int *position, int (*orderlist)[7], char pLine[]) {
	int date = 0;
	int ticketAll = 0; // 종합 or 파크 
	int ticketDay = 0; // 종일 or 오후 
	int age = 0; // 연령 
	int count = 0; // 티켓수
	int price = 0; // 가격 
	int sales = 0; // 우대사항 
	
	char *ptr = strtok(pLine, ","); // 해당 열 ,단위로 분리
	while(ptr != NULL) { // , 로 분류된 문자들 각 변수에 입력 
		// 이용권 체크 strcmp : c 문자열 비교 => 같으면 0
		if(strcmp(ptr, "종합이용권  ") == 0) ticketAll = 1;
		else if(strcmp(ptr, "파크이용권  ") == 0) ticketAll = 2;
		// 권종 체크 
		if(strcmp(ptr, "종일권") == 0) ticketDay = 1;
		else if(strcmp(ptr, "오후권") == 0) ticketDay = 2;
		// 연령 체크 
		if(strcmp(ptr, "노인  ") == 0) age = OLD;
		else if(strcmp(ptr, "어른  ") == 0) age = ADULT;
		else if(strcmp(ptr, "청소년") == 0) age = TEEN;
		else if(strcmp(ptr, "어린이") == 0) age = CHILD;
		else if(strcmp(ptr, "베이비") == 0) age = BABY;
		// 우대사항 체크 
		if(strcmp(ptr, "없음\n") == 0) sales = NONE;
		else if(strcmp(ptr, "장애인\n") == 0) sales = DISABLE;
		else if(strcmp(ptr, "국가유공자\n") == 0) sales = MERIT;
		else if(strcmp(ptr, "휴가장병\n") == 0) sales = VACSOLD;
		else if(strcmp(ptr, "임산부\n") == 0) sales = PREGNANT;
		else if(strcmp(ptr, "다둥이\n") == 0) sales = MULTICHILD;
		// 숫자 구분
		int number = strtol(ptr, NULL, 10);
		if(number > 0 && number < 11) count = number; // 수량은 1~10사이 
		else if(number % 100 != 0) date = number; // 100으로 나눴을때 나머지가 날짜에 해당하기에 0 불가 
		else if(number > 10) price = number; // 가격은 0 존재 가능 & 최소 단위가 100원이기에 나머지 무조건 0
		ptr = strtok(NULL, ","); 
	}
	// 입력받은 변수값, 배열 입력 
	orderlist[*position][0] = date;
	orderlist[*position][1] = ticketAll; // 종합 or 파크 
	orderlist[*position][2] = ticketDay; // 종일 or 오후권 
	orderlist[*position][3] = age; // 나이 
	orderlist[*position][4] = count; // 권수 
	orderlist[*position][5] = price; // 권당 가격 - 우대할인 적용시 
	orderlist[*position][6] = sales; // 우대할인사항 
	(*position)++;
}

void printTickets(int position, int(*orderlist)[7]) { // 기록 출력 
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
	char line[MAX]; // 읽기위한 배열
	char *pLine; 
	int position = 0;
	int orderList[100][7] = {0}; // 주문내역 저장
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
