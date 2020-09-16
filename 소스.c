#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

char *host = "localhost";
char *user = "root";
char *pwd = "root";
char *db = "dgu";

MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

void animation(); // 초기 애니매이션 함수
void start_menu(); //초기메뉴 함수
void make_account(); //회원가입
void delete_account(); //회원탈퇴
void check_reservation(); //예약정보 확인

void check_date();//출발,도착 날짜 설정

void select_Dcity(int index); //출발도시 선택
void select_Acity(int index);//도착도시 선택
void check_flight(int index);//항공목록 확인
void select_seat(int index);//항공좌석 선택

void select_hotel(int index); //호텔 선택
void check_hotel(int index); // 호텔 정보 확인

void log_in(int index);//로그인

void R_reservation(int index);//예약한 예약정보 확인
 
void payment(int index);//결제

typedef struct reservation_node {
	char reservation_id[100];

	char Ddate[100];
	char Adate[100];

	char Dcity[100];
	char Acity[200];
	char flight_id[100];
	char Seat[100];

	char hotel_name[100];

	char user_id[100];

	int total_price;
	 

}reservation_node; // 예약정보 구조체

reservation_node *guest[100];

guest_num = 0;

int main(void) 
{
	animation();

	srand(time(NULL)); // 랜덤으로 애니메이션 시간 설정

	system("pause");
	return 0;
}

void animation()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE| FOREGROUND_INTENSITY); //색을 넣어주는 함수
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t      *************************************************************");
	printf("\n\t\t\t      *                                                           *");
	printf("\n\t\t\t      *                                                           *");
	printf("\n\t\t\t      *                          하나투어                         *");
	printf("\n\t\t\t      *                                                           *");
	printf("\n\t\t\t      *                                                           *");
	printf("\n\t\t\t      *************************************************************");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Sleep(1500); //애니메이션 실행시간
	system("cls");

	start_menu(); // 시작메뉴로

}

void start_menu() 
{

	int check_num;

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");
	mysql_real_connect(&mysql, host, user, pwd, db, 3306, NULL, 0);
	mysql_query(&mysql, "USE db_dgu");

	//DB 연결
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 시작 메뉴 ]==========================\n\n");
	printf("\t\t\t   ||  1. 예약하기                                                  ||\n\n");
	printf("\t\t\t   ||  2. 예약정보 확인                                             ||\n\n");
	printf("\t\t\t   ||  3. 회원가입                                                  ||\n\n");
	printf("\t\t\t   ||  4. 회원탈퇴                                                  ||\n");
	printf("\n\t\t\t    =================================================================\n\n\n\n");
	printf("\t\t\t   원하는 메뉴를 선택하세요>>  ");
	scanf_s("%d", &check_num); //메뉴 선택

	
	if (check_num == 1) {
		system("cls");
		check_date();//1번을 눌렀을 경우 예약하기 시작
	}
	
	if (check_num == 2) {
		system("cls");
		check_reservation();//2번을 눌렀을 경우 예약목록 확인
	}

	if (check_num == 3) {
		system("cls");
		make_account();//3번을 눌렀을 경우 회원가입
	}

	if (check_num == 4) {
		system("cls");
		delete_account();//4번을 눌렀을 경우 예약하기 시작
	}

}

void check_reservation()
{
	char id[100];
	char pass[100];

	char function_re[100];
	int check_num;
	int fields = 0;
	int i = 0;
	int j = 0;
	int k = 0;


	printf("\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 예약 정보 ]==========================\n\n");
	printf("\t\t\t\t 1. ID 입력 >> ");
	scanf_s("%s", id, sizeof(id));

	sprintf_s(function_re, sizeof(function_re), "SELECT DISTINCT user_id  FROM user_ WHERE user_id = \"%s\";", id); //유저 아이디 선택
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	while ((row = mysql_fetch_row(res)))
	{
		i++;
	}

	if (i == 1)
	{
		printf("\n\t\t\t\t 2. 암호 입력 >> ");
		scanf_s("%s", pass, sizeof(pass));
		sprintf_s(function_re, sizeof(function_re), "SELECT DISTINCT user_Password  FROM user_ WHERE user_Password = \"%s\";", pass); //입력된 ID 의 비밀번호 목록
		mysql_query(&mysql, function_re);
		res = mysql_store_result(&mysql);
		fields = mysql_num_fields(res);

		while ((row = mysql_fetch_row(res)))
		{
			j++;
		}

		if (j == 1)
		{
			sprintf_s(function_re, sizeof(function_re), "select * from reservation where user_id = \"%s\";", id); //예약정보 모두 불러오기

			if (mysql_real_query(&mysql, &function_re, strlen(function_re))) {
				printf("Send query Failed");
			}

			res = mysql_store_result(&mysql);
			fields = mysql_num_fields(res);
			printf("\n\t\t\t    =================================================================\n\n\n\n");

			while (row = mysql_fetch_row(res))
			{
				printf("\t =====================================================================================================\n\n\n");
				printf("\t   ");

				for (k = 0; k < fields; k++)
				{
					printf("%s\t", row[k]);
				}
				printf("%\n\n\n");
			}
			mysql_free_result(res);
			printf("\t =====================================================================================================\n\n\n");
			printf("\t\t\t    초기화면으로 돌아가시려면 1번을 누르세요. >>  ");
			scanf_s("%d", &check_num);

			if (check_num == 1) {
				system("cls");
				start_menu(); // 1번 눌렀을때 시작메뉴
			}

		}

		else
		{
			system("cls");
			printf("\n");
			printf("\t\t\t   PW 가 일치하지 않습니다. ");
			check_reservation();
		}
	}

	else
	{
		system("cls");
		printf("\n");
		printf("\t\t\t   ID 가 일치하지 않습니다. ");
		check_reservation();
	}

}

 void make_account()
{
	char id[100];
	char pass[100];
	char num[100];
	char sex[10];
	char birth[100];
	char function_re[100];
	int fields, i = 0;

	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 회원 가입 ]==========================\n\n");
	printf("\t\t\t\t 1. ID 입력 >> ");
	scanf_s("%s", id, sizeof(id));

	sprintf_s(function_re, sizeof(function_re), "SELECT DISTINCT user_id  FROM user_ WHERE user_id = \"%s\";", id); //유저 테이블에서 유저 아이디 검색
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	while ((row = mysql_fetch_row(res)))
	{
		i++;
	}

	if (i == 1) {
		system("cls");
		printf("\n");
		printf("\t\t\t   이 ID는 이미 존재합니다. ");
		make_account(); //ID 가 이미 존재하면 처음으로
	}
	else {
		printf("\n\t\t\t\t 2. 암호 입력 >> ");
		scanf_s("%s", pass, sizeof(pass));
		printf("\n\t\t\t\t 3. 연락처 입력 >> ");
		scanf_s("%s", num, sizeof(num));
		printf("\n\t\t\t\t 4. 성별 입력 (M or F) >> ");
		scanf_s("%s", sex, sizeof(sex));
		printf("\n\t\t\t\t 5. 생일 입력 (yyyy-mm-dd) >> ");
		scanf_s("%s", birth, sizeof(birth));

		sprintf_s(function_re, sizeof(function_re), "INSERT into user_ values(\'%s\', \'%s\', \'%s\',\'%s\',\'%s\')", id, pass, num, sex, birth); // 유저 테이블에 유저 정보 삽입
		mysql_query(&mysql, function_re);
		system("cls");
		printf("\n");
		printf("\t\t\t   회원가입 완료 ");

		start_menu();// 시작메뉴
	}

}

void delete_account()
{
	char id[100];
	char pass[100];

	char function_re[100];

	int fields = 0;
	int i = 0;
	int j = 0;
 
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 회원 탈퇴 ]==========================\n\n");
	printf("\t\t\t\t 1. ID 입력 >> ");
	scanf_s("%s", id, sizeof(id));

	sprintf_s(function_re, sizeof(function_re), "SELECT DISTINCT user_id  FROM user_ WHERE user_id = \"%s\";", id); //유저 테이블에서 유저 아이디 검색
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);
	while ((row = mysql_fetch_row(res)))
	{
		i++;
	}
	if (i == 1) //유저 아이디가 있으면 PW 입력
	{
		printf("\n\t\t\t\t 2. 암호 입력 >> ");
		scanf_s("%s", pass, sizeof(pass));
		sprintf_s(function_re, sizeof(function_re), "SELECT DISTINCT user_Password  FROM user_ WHERE user_Password = \"%s\";", pass); //유저아이디가 일치한 패스웓 검색
		mysql_query(&mysql, function_re);
		res = mysql_store_result(&mysql);
		fields = mysql_num_fields(res);
		
		while ((row = mysql_fetch_row(res)))
		{
			j++;
		}

		if (j == 1)

		{
			sprintf_s(function_re, sizeof(function_re), "DELETE FROM user_ WHERE user_id = \"%s\";", id); //유저정보 삭제
			mysql_query(&mysql, function_re);
			system("cls");
			printf("\n");
			printf("\t\t\t   탈퇴 완료 "); 
			start_menu();
		}
		else
		{
			system("cls");
			printf("\n");
			printf("\t\t\t   PW 가 일치하지 않습니다. "); 
			delete_account(); //PW 일치하지않으면 처음으로
		}
	}

	else 
	{
		system("cls");
		printf("\n");
		printf("\t\t\t   ID 가 일치하지 않습니다. ");
		delete_account();
	}

}

void check_date() {

	char Ddate[100];
	char Adate[100];
	char select_check[10][100];
	int guest_check = guest_num;

	guest[guest_check] = (reservation_node*)malloc(sizeof(reservation_node));
	guest_num++; //구조체 형성

	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t   ==========================[ 출발 날짜 ]==========================\n\n\n");
	printf("\t\t\t     원하는 출발 날짜를 입력하세요(yyyy-mm-dd)>>  ");
	scanf_s("%s", Ddate, sizeof(Ddate)); //입력 받은 날짜를 Ddate에 저장
	printf("\n\n");
	printf("\t\t\t   =================================================================\n\n\n\n");
	printf("\t\t\t   ==========================[ 도착 날짜 ]==========================\n\n\n");
	printf("\t\t\t     원하는 도착 날짜를 입력하세요(yyyy-mm-dd)>>  ");
	scanf_s("%s", Adate, sizeof(Adate)); //입력 받은 날짜를 Adate에 저장
	printf("\n\n\t\t\t   =================================================================\n\n\n\n");
	system("cls");

	strcpy_s(guest[guest_check]->Ddate, sizeof(guest[guest_check]->Ddate), Ddate); //입력 받은 날짜를 구조체 Ddate에 저장
	strcpy_s(guest[guest_check]->Adate, sizeof(guest[guest_check]->Adate), Adate); //입력 받은 날짜를 구조체 Ddate에 저장

	select_Dcity(guest_check); // 항공 예약으로 넘어감

}

void select_Dcity(int index) {
	int fields;
	int i = 0;
	int cnt = 0;
	char select_check[10][100];

	mysql_query(&mysql, "SELECT DISTINCT Depature_City FROM Flight"); //FLIGHT 테이블에서 출발 도시 검색 및 출력
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 출발 도시 ]==========================\n\n");

	while ((row = mysql_fetch_row(res)))
	{
		printf("\t\t\t\t  %d. %s \n\n", i + 1, row[0]);
		i++;
		strcpy_s(select_check[i], sizeof(select_check[i]), row[0]); 
	}

	printf("\t\t\t    =================================================================\n\n\n\n");
	printf("\t\t\t    원하는 도시를 선택하세요>>  ");
	scanf_s("%d", &cnt, sizeof(cnt));
	system("cls");
	strcpy_s(guest[index]->Dcity, sizeof(guest[index]->Dcity), select_check[cnt]); //출력 받은 도시중 원하는 도시를 선택한후 구조체 Dcity 에저장
	select_Acity(index);

}

void select_Acity(int index) {

	int fields;
	int i = 0, cnt;
	char function_re[200];
	char select_check_id[10][100];
	char select_check_Acity[10][200];

	sprintf_s(function_re, sizeof(function_re), "SELECT DISTINCT Flight_Number,Arrival_city from flight WHERE Depature_city = \"%s\";", guest[index]->Dcity); //선택한 출발도시의 도착도시와 항공번호를 검색
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 도착 도시 ]==========================\n\n");

	while ((row = mysql_fetch_row(res)))
	{
		printf("\t\t\t\t  %d. %s\n\n ", i + 1, row[1]);
		i++;
		strcpy_s(select_check_id[i], sizeof(select_check_id[i]), row[0]);
		strcpy_s(select_check_Acity[i], sizeof(select_check_Acity[i]), row[1]);
	}
	//도착 도시만 출력

	printf("\t\t\t    =================================================================\n\n\n\n");
	printf("\t\t\t    원하는 도시를 선택하세요>>  ");
	scanf_s("%d", &cnt, sizeof(cnt));
	strcpy_s(guest[index]->flight_id, sizeof(guest[index]->flight_id), select_check_id[cnt]);
	strcpy_s(guest[index]->Acity, sizeof(guest[index]->Acity), select_check_Acity[cnt]);
	//원하는 도시와 항공번호를 구조체에 저장
	
	system("cls");
	
	check_flight(index);
}

void check_flight(int index) {

	int fields;
	int check_num;
	int i = 0;
	char function_re[200];

	sprintf_s(function_re, sizeof(function_re), "SELECT * from flight WHERE flight_number = \"%s\";", guest[index]->flight_id); //flight 테이블에서 위에 선택한 항공번호가 일치한 모든 정보를 검색및 출력
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 항공 목록 ]==========================\n\n");

	while ((row = mysql_fetch_row(res)))
	{
		printf("%\n\t\t\t        ");
		//printf("   Flight Number  Depature City  Arrival City  Price  Airline\n");
		for (i = 0; i < fields; i++)
		{
			printf("%s\t", row[i]);
		}
		
	}
	printf("\n\n\n\t\t\t    =================================================================\n\n\n\n");
	printf("\t\t\t    항공 예약을 하시겠습니까?\n\n\t\t\t    1.예\n\t\t\t    2.아니요(초기화면)\n\n\t\t\t    >>  ");
	scanf_s("%d", &check_num);

	if (check_num == 1) {
		system("cls");
		select_seat(index); // 1번을 누르면 좌석을 고름
	}

	if (check_num == 2) {
		system("cls");
		start_menu();  // 2번을 누르면 처음으로
	}

}

void select_seat(int index)
{
	int i;
	char seat[100];

		printf("\t\t\t      ==========================[ 좌석 선택 ]==========================\n\n");
		printf("\n");
		printf("\t\t\t\t\t\t   A\t B\t C\t D\n\n");
		printf("\t\t\t\t\t  ");
		for (i = 1; i < 81; i++) {
			printf("\t[%d]", i);
			if (i % 4 == 0)
				printf("\n\t\t\t\t\t  ");
		} //4열로된 좌석을 for문을 사용해 출력
		printf("\n\t\t\t      ===============================================================");
		printf("\n\n\t\t\t      원하는 좌석을 입력하세요>>  ");
		scanf_s("%s", seat, sizeof(seat));
		system("cls");

		strcpy_s(guest[index]->Seat, sizeof(guest[index]->Seat), seat); //원하는 좌석 입력후 그 값을 구조체에 저장

		select_hotel(index); // 호텔선택창으로

}

void select_hotel(int index) {

	int fields;
	int i = 0, cnt;
	char function_re[200];
	char select_check_name[10][100];

	sprintf_s(function_re, sizeof(function_re), "SELECT Hotel_name from hotel WHERE hotel_location = \"%s\";", guest[index]->Acity); //호텔 테이블에서 도착도시와 같은 호텔이름을 모두 검색및 출력 
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 호텔 선택 ]==========================\n\n");

	while ((row = mysql_fetch_row(res)))
	{
		printf("\t\t\t\t  %d. %s \n\n", i + 1, row[0]);
		i++;
		strcpy_s(select_check_name[i], sizeof(select_check_name[i]), row[0]);
	}

	printf("\t\t\t    =================================================================\n\n\n\n");
	printf("\t\t\t    원하는 호텔을 선택하면 호텔 정보가 나옵니다. >>  ");
	scanf_s("%d", &cnt, sizeof(cnt));
	strcpy_s(guest[index]->hotel_name, sizeof(guest[index]->hotel_name), select_check_name[cnt]);
	system("cls"); //선택한 호텔을 구조체에 저장

	check_hotel(index); //호텔 정보창으로 이동

}

void check_hotel(int index) {

	int fields;
	int check_num;
	int i = 0, cnt;

	char function_re[200];
	char select_check_id[10][100];
	char select_check_Acity[10][200];

	sprintf_s(function_re, sizeof(function_re), "SELECT * from hotel WHERE hotel_name = \"%s\";", guest[index]->hotel_name); //선택한 호텔의 모든 정보를 출력
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 호텔 정보 ]==========================\n\n");

	while ((row = mysql_fetch_row(res)))
	{
		printf("%\n\t\t\t    ");
		
		for (i = 0; i < fields; i++)
		{
			printf("\t%s", row[i]);
		}

	}

	printf("\n\n\n\t\t\t    =================================================================\n\n\n\n");
	printf("\t\t\t    1. 이 호텔로 하겠습니다. \n\n\t\t\t    2. 다른 호텔로 하겠습니다. (선택화면) \n\n\n\t\t\t    >>  ");
	scanf_s("%d", &check_num);

	if (check_num == 1) {
		system("cls");
		log_in(index); //1번을 누르면 로그인 창
	}

	if (check_num == 2) {
		system("cls");
		select_hotel(index); // 2번을 누르면 다시 호텔 선택창
	}

}

void log_in(int index)
{
	char id[100];
	char pass[100];

	char function_re[100];
	int check_num;
	int fields = 0;
	int i = 0;
	int j = 0;
	int k = 0;

	printf("\n\n\n\n\n\n");
	printf("\t\t    ==========================[ 예약을 위해 로그인을 해주세요. ]==========================\n\n");
	printf("\t\t      1. ID 입력 >> ");
	scanf_s("%s", id, sizeof(id));

	sprintf_s(function_re, sizeof(function_re), "SELECT DISTINCT user_id  FROM user_ WHERE user_id = \"%s\";", id); // 유저 테이블에서 유저이름 검색
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	while ((row = mysql_fetch_row(res)))
	{
		i++;
	}

	if (i == 1) //맞으면 암호 임력
	{
		printf("\n\t\t      2. 암호 입력 >> "); 
		scanf_s("%s", pass, sizeof(pass));
		sprintf_s(function_re, sizeof(function_re), "SELECT DISTINCT user_Password  FROM user_ WHERE user_Password = \"%s\";", pass); // 유저테이블에서 유저 PW 검색
		mysql_query(&mysql, function_re);
		res = mysql_store_result(&mysql);
		fields = mysql_num_fields(res);

		while ((row = mysql_fetch_row(res)))
		{
			j++;
		}

		if (j == 1) //[W 일치
		{
			system("cls");
			strcpy_s(guest[index]->user_id, sizeof(guest[index]->user_id), id); //입력한 유저ID를 구조체에 저장
			payment(index); //결제창
		}

		else
		{
			system("cls");
			printf("\n");
			printf("\t\t\t   PW 가 일치하지 않습니다. ");//로그인 PW가 일치하지않으면 다시 로그인창
			log_in(index);;
		}
	}

	else
	{
		system("cls");
		printf("\n");
		printf("\t\t\t   ID 가 일치하지 않습니다. ");
		log_in(index); //로그인 아이디가 일치하지않으면 다시 로그인창
	}

}

void payment(int index)
{
	int fields;
	int check_num;
	int i = 0;

	int x = 0; // flight price
	int y = 0; // hotel price
	int z = 0; // total price

	char function_re[200];
	char function__re[200];

	sprintf_s(function_re, sizeof(function_re), "SELECT Flight_Price from flight WHERE flight_number = \"%s\";", guest[index]->flight_id); //선택한 항공의 항공번호의 항공가격
	mysql_query(&mysql, function_re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t    ==========================[ 결제 목록 ]==========================\n\n");

	while ((row = mysql_fetch_row(res)))
	{
		printf("%\n\t\t\t\t\t\t%s", guest[index]->flight_id);
		for (i = 0; i < fields; i++)
		{
			printf("\t%s", row[i]);
		}
		x = atoi(row[0]); // atoi = 문자열의 숫자를 정수형으로 변환 ,가격을 저장
	}

	sprintf_s(function__re, sizeof(function__re), "SELECT Hotel_Price from Hotel WHERE Hotel_name = \"%s\";", guest[index]->hotel_name); //선택한 호텔의 호텔 가격 검색및 출력
	mysql_query(&mysql, function__re);
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	while ((row = mysql_fetch_row(res)))
	{
		printf("%\n\t\t\t\t\t\t%s", guest[index]->hotel_name);
		for (i = 0; i < fields; i++)
		{
			printf("\t%s", row[i]);
		}
		printf("\n");
		y = atoi(row[0]); //atoi = 문자열의 숫자를 정수형으로 변환, 가격을 저장
	}

		z = x + y; // total price 

	printf("%\n\t\t\t\t\t\tTotal Price = %d",z);
	printf("\n");
	printf("\n\t\t\t    =================================================================\n\n\n\n");
	printf("\n\t\t\t    결제목록이 맞습니까?\n\n\t\t\t    1.예\n\t\t\t    2.아니요(초기화면)\n\n\t\t\t    >>  ");
	scanf_s("%d", &check_num);

	if (check_num == 1) {
		guest[index]->total_price = z ;
		system("cls");
		R_reservation(index); //맞으면 예약확인창
	}

	if (check_num == 2) {
		system("cls");
		start_menu(); //틀리면 처음으로
	}

}

void R_reservation(index) {
	
	int i, j, check = 1, fields;
	int check_num;
	char function_re[1000];
	char R_reservation_id[100]; //예약번호를 위해 새로운 문자열변수 생성
	

	strcpy_s(R_reservation_id, sizeof(R_reservation_id), guest[index]->user_id); //생성한 변수에 입력받은 유저아이디를 넣어준다.
	strcat_s(R_reservation_id, sizeof(R_reservation_id), guest[index]->flight_id); //문자열을 합쳐주는 strcat_s 함수를 사용해 위에서 저장해준 user_id와 항공번호를 합쳐준다.
	strcpy_s(guest[index]->reservation_id, sizeof(guest[index]->reservation_id),R_reservation_id); //위에서 합쳐준 문자열을 구조체의 예약번호에 저장.

	printf("\n\n\t\t\t   -------------------------[ 예약 정보 ]-------------------------\n\n");

	for (i = 0; i < guest_num; i++) {
		
			printf("\t\t\t     =============[ %d ]=============\n", check);
			printf("\t\t\t       예약번호 : %s\n", guest[i]->reservation_id);
			printf("\t\t\t             ID : %s\n", guest[i]->user_id);
			printf("\t\t\t       출발날짜 : %s\n", guest[i]->Ddate);
			printf("\t\t\t       도착날짜 : %s\n", guest[i]->Adate);
			printf("\t\t\t       출발도시 : %s\n", guest[i]->Dcity);
			printf("\t\t\t       도착도시 : %s\n", guest[i]->Acity);
			printf("\t\t\t       항공번호 : %s\n", guest[i]->flight_id);
			printf("\t\t\t       좌석번호 : %s\n", guest[i]->Seat);
			printf("\t\t\t       호텔이름 : %s\n", guest[i]->hotel_name);
			printf("\t\t\t        총 가격 : %d\n", guest[i]->total_price);
			check++;
			printf("\t\t\t     ================================\n");
		
	}
	//위에서 저장해준 모둔 구조체 정보들을 출력
	printf("\n\n\t\t\t   ---------------------------------------------------------------\n\n\n\n");
	printf("\t\t\t   예약목록이 맞습니까?\n\n\t\t\t   1.예\n\t\t\t   2.아니요(초기화면)\n\n\t\t\t   >>  ");
	scanf_s("%d", &check_num);
	
	if (check_num == 1)
	{
		sprintf_s(function_re, sizeof(function_re), "INSERT into reservation values(\'%s\', \'%d\', \'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",guest[index]->reservation_id, guest[index]->total_price , guest[index]->user_id, guest[index]->hotel_name, guest[index]->flight_id, guest[index]->Seat, guest[index]->Ddate, guest[index]->Adate);
		mysql_query(&mysql, function_re);
		system("cls"); //1번을 누르면 구조체의 모든 예약 정보들이 RESERVATION 테이블에 저장된다.
		start_menu(); //초기화면
	}
	

	if (check_num == 2) {
		system("cls");
		start_menu(); //2번을 누르면 처음으로
	}

}