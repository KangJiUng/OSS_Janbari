#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER 256

typedef struct sing {
	char singer[NUMBER];
	char lyrics[NUMBER];
	char lyrics1[NUMBER];
	char answer1[NUMBER];
	char hint[NUMBER];
}sing_info;

void GotoXY(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
void sing_main();
void correct_question();
void fail_question();
void end_question();
void sing_answer(int count, sing_info sing,int random);
void hint(sing_info sing);

sing_info sings[50];

int main() {
	system("mode con:cols=55 lines=20");
	char enter = '\n';
	char answer[5][50];
	int hint1[5];
	int i = 0, j = 0, count = 1, count1 = 0;

	FILE* fp;
	fp = fopen("노래가사.txt", "r");

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

		sing_main();
		srand(time(NULL));

		for (i = 0; i < 5; i++) {
			int random = rand() % 21;
			hint1[i] = random;
			for (j = 0; j < i; j++) {
				if (hint1[i] == hint1[j])i--;
			}
		}
		scanf("%c", &enter);
		if (enter == '\n') {
			while (count <= 5) {
				system("cls"); //메인화면 지우기
				sing_answer(count, sing,hint1[j]); //노래가사 맞히기 화면

				printf("정답을 입력하세요..  ");
				gets(answer[j]);
				system("cls");

				if (strcmp(answer[j], sings[hint1[j]].answer1) == 0) {
					correct_question();
					Sleep(3000);
					system("cls");
					j++;
					count++;
				}
				else if (strcmp(answer[j], "1" )== 0) {
					sing_answer(count, sing, hint1[j]);
					hint(sing, hint1[j]);
					Sleep(3000);
					system("cls");
				}
				else {
					fail_question();
					Sleep(3000);
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
	return 0;
}
//노래가사 메인
void sing_main() 
{
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("                         203호                         \n");
	printf("                   노래 가사 맞히기  \n");
	textcolor(15);
	printf("\n");
	printf("=====================================================\n");
	printf("\n");
	printf("         빈칸에 알맞은 노래 가사를 넣으세요\n");
	printf("          총 다섯 문제를 맞추면 통과입니다\n");
	printf("         힌트는 한 문제당 한번만 제공됩니다 \n");
	printf("\n");
	printf("                    GOOD LUCK..\n");
	printf("=====================================================\n");
	printf("\n");
	printf("	   계속하려면 Enter를 누르세요..\n");
}
//힌트 제공화면
void hint(sing_info sing, int random) {
	GotoXY(0, 16);
	printf("%s", sings[random].hint);
}
//노래가사 맞히기
void sing_answer(int count,sing_info sing,int random)
{	
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("   203호         Score :   %d / %d      \n", count, 5);
	textcolor(15);
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
	printf("%s  \n",sings[random].singer);
	printf("\n");
	printf("%s\n",sings[random].lyrics);
	printf("%s\n", sings[random].lyrics1);
	printf("\n");
	printf("\n");
	printf("             힌트를 보려면 1을 누르세요\n");
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
}
//정답화면
void correct_question() 
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("              정답이다.....힘을 내라..\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
}
//오답화면
void fail_question()
{
	printf("\n");
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("=======================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("           틀렸다.. 호텔이 무너져 내린다....\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
}

//문제 다 맞추었을시 ui
void end_question()
{
	printf("\n");
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("=======================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("            다섯 문제를 모두 맞춘건가..\n");
	printf("               나가는 길은 저쪽이다..\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	textcolor(15);
	printf("\n");
}