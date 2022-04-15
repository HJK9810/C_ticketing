#define _CRT_SECURE_NO_WARNINGS // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
// 없음, 장애, 유공자, 휴가장병, 임산부, 다둥이 
const int NONE = 1, DISABLE = 2, MERIT = 3, VACSOLD = 4, PREGNANT = 5, MULTICHILD = 6;
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5;
// 계산
int transTypeAll(char *typeAll) {
	int ticketAll = 0;
	// 이용권 체크 strcmp : c 문자열 비교 => 같으면 0
	if(strcmp(typeAll, "종합이용권  ") == 0) ticketAll = 1;
	else if(strcmp(typeAll, "파크이용권  ") == 0) ticketAll = 2;
	return ticketAll;
}
int transTypeDay(char *typeDay) {
	int ticketDay = 0;
	// 권종 체크 
	if(strcmp(typeDay, "종일권") == 0) ticketDay = 1;
	else if(strcmp(typeDay, "오후권") == 0) ticketDay = 2;
	return ticketDay;
}
int trasAge(char *ageCount) {
	int age = 0;
	// 연령 체크 
	if(strcmp(ageCount, "노인  ") == 0) age = OLD;
	else if(strcmp(ageCount, "어른  ") == 0) age = ADULT;
	else if(strcmp(ageCount, "청소년") == 0) age = TEEN;
	else if(strcmp(ageCount, "어린이") == 0) age = CHILD;
	else if(strcmp(ageCount, "베이비") == 0) age = BABY;
	return age;
}
int trasSales(char *forsale) {
	int sales = 0;
	// 우대사항 체크 
	if(strcmp(forsale, "없음\n") == 0) sales = NONE;
	else if(strcmp(forsale, "장애인\n") == 0) sales = DISABLE;
	else if(strcmp(forsale, "국가유공자\n") == 0) sales = MERIT;
	else if(strcmp(forsale, "휴가장병\n") == 0) sales = VACSOLD;
	else if(strcmp(forsale, "임산부\n") == 0) sales = PREGNANT;
	else if(strcmp(forsale, "다둥이\n") == 0) sales = MULTICHILD;
	return sales;
}

// 입력
int fileRead(int (*orderList)[7]) {
	FILE *fp = fopen("report.csv", "r+"); // only read
	const int MAX = 1024;
	char line[MAX]; // 읽기위한 배열
	int lastLine = 0;
	char *typeAll;
	char *typeDay;
	char *age;
	char *sales;
	
	while(fscanf(fp, "%d,%-12s,%-6s,%-6s,%d,%d,%s", 
	orderList[lastLine][0], typeAll, typeDay, age, orderList[lastLine][4], orderList[lastLine][5], sales)); {
		orderList[lastLine][1] = transTypeAll(typeAll);
		orderList[lastLine][2] = transTypeDay(typeDay);
		orderList[lastLine][3] = trasAge(age);
		orderList[lastLine][6] = trasSales(sales);
	}
	fclose(fp);
	return lastLine;
}  
// 출력 
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
	int orderList[100][7] = {0}; // 주문내역 저장
	int i = 0;
	
	int position = fileRead(orderList);
	printf("=========================== report.csv ===========================\n");
	printf("%d%5d%5d%5d%5d%10d%6d\n", "날짜", "이용권", "권종", "연령", "수량", "가격", "우대사항");
	printTickets(position, orderList);
	printf("==============================================================\n\n"); 
		
	return 0;
}
