#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DELAY 120000
#define NUMBER 256

// 노래 정보를 담는 구조체
typedef struct sing {
	char singer[NUMBER];
	char lyrics[NUMBER];
	char lyrics1[NUMBER];
	char answer1[NUMBER];
	char hint[NUMBER];
}sing_info;

// 커서를 이동하는 함수
void GotoXY1(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
// 글자 색깔을 바꾸는 함수
void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
void print_main();
void sing_main();
void correct_question();
void fail_question();
void end_question();
void sing_answer(int count, sing_info sing,int random);
void hint(sing_info sing);
void ending();
void ending_timer();

sing_info sings[50];

// 메인 함수
int main() {
	//콘솔 크기 설정
	system("mode con:cols=75 lines=20");

	char enter = '\n';
	char answer[5][50];		
	int hint1[5];
	int i = 0, j = 0, count = 1, count1 = 0;

	FILE* fp;
	fp = fopen("노래가사.txt", "r");
		
	//sing.txt파일을 읽어와 구조체 배열에 저장
	if (fp != NULL) {
		char buffer[NUMBER];
		sing_info sing;
		while (!feof(fp)) {
			fgets(buffer, sizeof(buffer), fp);
			char* ptr = strtok(buffer, ",");
			strcpy(sing.singer, ptr);
			ptr = strtok(NULL, "/");
			strcpy(sing.lyrics, ptr);
			ptr = strtok(NULL, ",");
			strcpy(sing.lyrics1, ptr);
			ptr = strtok(NULL, ",");
			strcpy(sing.answer1, ptr);
			ptr = strtok(NULL, "\n");
			strcpy(sing.hint, ptr);
			sings[count1++] = sing;
		}
		fclose(fp);

		sing_main(); //메인화면 출력
		srand(time(NULL));

		//랜덤의 문제 번호를 배열에 저장함
		for (i = 0; i < 5; i++) {
			int random = rand() % 21;
			hint1[i] = random;
		}

		scanf("%c", &enter);
		if (enter == '\n') {
			while (count<=5) {
				system("cls"); //메인화면 지우기
				sing_answer(count, sing, hint1[j]); //노래가사 맞히기 화면
				printf("정답을 입력하세요..  ");
				gets(answer[j]);
				system("cls");

				//정답일때
				if (strcmp(answer[j], sings[hint1[j]].answer1) == 0) {
					correct_question();
					Sleep(1000);
					system("cls");
					j++;
					count++;
				}
				//힌트를 원할 때
				else if (strcmp(answer[j], "1") == 0) {
					sing_answer(count, sing, hint1[j]);
					hint(sing, hint1[j]);
					Sleep(1000);
						system("cls");			
				}
					//오답일때
				else {
					fail_question();
					Sleep(1000);
					system("cls");
				}
			}
		}
	}
	else {
		printf("파일 존재 x");
		return;
	}
	end_question();
	Sleep(2000);
	system("cls");
	ending();
	
		
		
}
//노래가사 메인 UI
void sing_main() 
{
		printf("\n");
		textcolor(12);
		printf("\t\t\t\t   203호\n");
		printf("\t\t         ♬ 노래가사 맞히기 게임 ♬\n");
		textcolor(15);
		printf("\n");
		printf("===========================================================================\n");
		textcolor(15);
		printf("\n");
		printf("\n");
		printf("         \t  ♪ 빈칸에 알맞은 노래 가사를 넣으세요\n");
		printf("         \t  ♪ 총 5 문제를 맞추면 통과입니다\n");
		printf("         \t  ♪ 힌트는 한 문제당 한번만 제공됩니다 \n");
		printf("\n");
		printf("\n");
		printf(" \t\t\t     ♬ GOOD LUCK..\n");
		printf("===========================================================================\n");
		printf("\n");
		printf("\t\t       계속하려면 Enter를 누르세요..\n");
}
//힌트 제공화면
void hint(sing_info sing, int random) {
	GotoXY1(0, 16);
	printf("%s", sings[random].hint);
}
//노래가사 맞히기 UI
void sing_answer(int count,sing_info sing,int random)
{	
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("   203호\t\t    Score :   %d / %d      \n", count, 5);
	textcolor(15);
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("\t\t   ♬ %s ♬\n",sings[random].singer); //파일에서 가수와 노래 제목을 불러온 결과
	printf("\n");
	printf("\t\t   %s\n",sings[random].lyrics);  //파일에서 노래 가사를 불러옴
	printf("\t\t   %s\n", sings[random].lyrics1); //파일에서 노래 가사를 불러옴
	printf("\n");
	printf("\n");
	printf("\t\t   힌트를 간절히 원한다면 1을 누르세요\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
}
//정답화면 UI
void correct_question() 
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                         정답이다.....힘을 내라..\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
}
//오답화면 UI
void fail_question()
{
	printf("\n");
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("===========================================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                      틀렸다.. 호텔이 무너져 내린다....\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
}

//문제 다 맞추었을시 UI
	void end_question()
	{
		printf("\n");
		printf("\n");
		printf("\n");
		textcolor(12);
		printf("===========================================================================\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("                        다섯 문제를 모두 맞춘건가..\n");
		printf("                           나가는 길은 저쪽이다..\n");
		printf("\n");
		printf("\n");
		printf("===========================================================================\n");
		textcolor(15);
		printf("\n");
	}
	//비밀번호 획득 함수
	void ending()
	{
		printf("\n");
		printf("\n");
		printf("\n");
		textcolor(12);
		printf("===========================================================================\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("                        어이!! 비밀번호 가져가라...\n");
		printf("                             (세번째 자리) 6..\n");
		printf("\n");
		printf("\n");
		printf("===========================================================================\n");
		textcolor(15);
		printf("\n");
	}
	//시간이 다 지나면 표시되는 UI
	void ending_timer()
	{
		printf("\n");
		printf("\n");
		printf("\n");
		printf("===========================================================================\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("                         시간이 다 지났다.. 넌 죽는다..\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("===========================================================================\n");
		printf("\n");
	}
