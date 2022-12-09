#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
//#include <unistd.h> //sleep 기능 구현 위해, windows.h 대체 < 맥북;
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

void roomselect();
void print_main();

int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
//--------------------------사자성어 --------------------------------------

// 사자성어 네글자 퀴즈
struct Problem {
	char answer[100];
	char hint[100];
};

struct Problem problem[20];

int rand_idx[5] = { 0 };


void set_idx() {
	int random = 0; // 정수형 변수 선언
	int i = 0;
	srand(time(NULL));

	while (1) {
		int ck = 0;
		random = rand() % 20; // 난수 생성
		for (int j = 0; j < i; j++) {
			if (random == rand_idx[j])
				ck = 1;
		}
		if (ck) continue;
		rand_idx[i] = random;
		i += 1;
		if (i == 5) break;
	}
}

void save_problem() {
	const int max = 1024;
	char line[1024];
	char* pLine;
	FILE* in = fopen("problems.txt", "r");
	int cnt1 = 0;
	int cnt2 = 0;

	while (!feof(in)) {
		pLine = fgets(line, sizeof(line), in);
		if (pLine == NULL)
			break;
		if (cnt2 == 0) {
			strcpy(problem[cnt1].answer, pLine);
			cnt2 += 1;
		}
		else if (cnt2 == 1) {
			strcpy(problem[cnt1].hint, pLine);
			cnt2 = 0; cnt1 += 1;
		}
	}
	fclose(in);
}

void Right() {
	system("cls");
	printf("\n\n\n===========================================================================\n\n\n\n\n");
	printf("                              욜 ㅋ 쫌 치는데?\n\n\n\n\n");
	printf("===========================================================================\n\n\n");
	Sleep(1000);
}

void Wrong() {
	system("cls");
	printf("\n\n\n===========================================================================\n\n\n\n\n");
	printf("                            이러다가 다~ 죽어~!\n\n\n\n\n");
	printf("===========================================================================\n\n\n");
	Sleep(1000);
}


void eng_game() {
	system("cls");

	for (int k = 0; k < 5; k++) {
		char answ[30]; // 답 저장
		char prob[30];
		char* temp = strtok(problem[rand_idx[k]].answer, " ");
		temp = strtok(NULL, " ");
		strcpy(prob, temp);
		temp = strtok(NULL, "\n");
		while (1) {
			system("cls");

			printf("\x1b[31m                              ROUND : %d/5    \x1b[0m\n\n\n\n", k + 1);
			printf("                          %s", prob);

			for (int i = 0; i < strlen(temp); i++) {
				printf("_");
			}
			printf("\n\n                     %s\n\n\n\n", problem[rand_idx[k]].hint);
			printf("빈칸을 입력하시오...");
			scanf("%s", answ);
			if (!strcmp(temp, answ)) {
				Right();
				break;
			}
			else {
				Wrong();
			}
		}
		system("cls");
	}
}


void intro_engame() {
	system("cls");

	printf("\n");
	printf("\n");
	printf("\t\t\t\t\x1b[31m   201호\x1b[0m\n");
	printf("\t\t\x1b[31m           사자성어 네글자 퀴즈\x1b[0m\n");
	textcolor(15);
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("                      힌트를 보고 사자성어를 맞히시오.\n");
	printf("                                 - 5문제 -\n");
	printf("\n");
	printf("                                GOOD LUCK..\n\n");
	printf("===========================================================================\n");
	printf("\n\n");

	system("pause");
	eng_game();
}


void engame_ending() {
	system("cls");
	printf("\n\n\n===========================================================================\n\n\n\n");
	printf("                             이걸 다 맞혔어?...\n");
	printf("\x1b[31m                        비밀번호(첫 번째 자리) : 3\x1b[0m\n\n\n\n");
	printf("===========================================================================\n\n\n");
	Sleep(1000);
	roomselect();
}



void en_main() {
	save_problem(); //문제 & 힌트 저장
	set_idx(); //랜덤 index 5개 추출
	intro_engame(); //시작 화면 출력
	//게임 실행 
	engame_ending();//엔딩 화면
}


//--------------------비밀번호 입력화면--------------------------
void Password() {
	system("cls");
	printf("\n");
	printf("\n");
	printf("\t\t\x1b[31m         Janbari Hotel Escape Game\x1b[0m\n\n\n");
	textcolor(15);
	printf("\t\t       -----------------------------\n");
	printf("\t\t       |             |             |\n");
	printf("\t\t       |             |             |\n");
	printf("\t\t       |             |             |\n");
	printf("\t\t       |          ● |  ●         |\n");
	printf("\t\t       |             |             |\n");
	printf("\t\t       |             |             |\n");
	printf("\t\t       |             |             |\n");
	printf("\t\t       -----------------------------\n\n");
	printf("                       비밀번호 네 자리를 입력하시오.\n");
	printf("\t\t\t\t  : ");
}

void Ending()
{
	int i = 0;
	system("cls");
	char end[6][500] = { {" 덜컥... 마침내 문이 열렸다... \n"} ,
		{" (그때 뒤에서 들려오는 발걸음 소리...)\n"},
		{" 터벅\n"},
		{" 터벅...\n"},
		{"\x1b[31m 콰직!\x1b[0m\n"},
		{"\t\t\t\t  \x1b[31mThe End\x1b[0m\n"}

	};

	while (i <= 5) {
		printf("\n");
		printf("\t\t\x1b[31m         Janbari Hotel Escape Game\x1b[0m\n\n\n");
		textcolor(15);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("===========================================================================\n");
		printf("\n");
		printf("%s", end[i]);
		printf("\n");
		printf("===========================================================================\n\n\n");
		i++;
		Sleep(2000);

		system("cls");
	}

	Sleep(1000);
	system("cls");
}

/*void Fail() {
	system("cls");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("\x1b[31m                    You Die\x1b[0m\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n\n");
	Sleep(1000);
	print_main();
}*/

void ck() {

	system("mode con:cols=75 lines=20");
	while (1) {
		int p1 = 3760;
		int cnt = 0;
		system("cls");
		printf("\n\n\n\n\n\n");
		Password();
		scanf("%d", &p1);

		if (p1 == 3760) {
			Ending();
			print_main();
		}
	}
}




//---------------------------공룡게임----------------------------------------


void intro()
{
	printf("\n");
	printf("\n");
	printf("\x1b[31m                                               202호\x1b[0m\n");
	printf("\x1b[31m                                             공룡 게임\x1b[0m\n");
	printf("\n");
	printf("====================================================================================================\n");
	printf("\n");
	printf("                                점프하여 장애물을 피하시오. (점프:1)\n");
	printf("                                        - 최소 15점 이상 -\n");
	printf("\n");
	printf("                                            GOOD LUCK..\n\n");
	printf("====================================================================================================\n");
	printf("\n\n");

	system("pause");
	system("cls");
}
//커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}




void SetConsoleView()
{
	system("mode con:cols=100 lines=25");
	system("title Google Dinosaurs. By BlockDMask.");
}

//키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

//공룡을 그리는 함수
void DrawDino(int dinoY)
{
	GotoXY(0, dinoY);
	static bool legFlag = true;
	printf("        $$$$$$$ \n");
	printf("       $$ $$$$$$\n");
	printf("       $$$$$$$$$\n");
	printf("$      $$$      \n");
	printf("$$     $$$$$$$  \n");
	printf("$$$   $$$$$     \n");
	printf(" $$  $$$$$$$$$$ \n");
	printf(" $$$$$$$$$$$    \n");
	printf("  $$$$$$$$$$    \n");
	printf("    $$$$$$$$    \n");
	printf("     $$$$$$     \n");
	if (legFlag)
	{
		printf("     $    $$$    \n");
		printf("     $$          ");
		legFlag = false;
	}
	else
	{
		printf("     $$$  $     \n");
		printf("          $$    ");
		legFlag = true;
	}
}

//나무를 그리는 함수
void DrawTree(int treeX)
{
	GotoXY(treeX, TREE_BOTTOM_Y);
	printf("$$$$");
	GotoXY(treeX, TREE_BOTTOM_Y + 1);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 2);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 3);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 4);
	printf(" $$ ");
}

//충돌 했을때 화면 보여줌
void Correct(const int score)
{
	system("cls");
	printf("\n\n\n\n\n\n");
	textcolor(15);
	printf("====================================================================================================\n");
	printf("\n\n\n");
	printf("                                     축하한다! 어서 탈출하러 가라!");
	printf("\n\n                                             SCORE : %d\x1b[0m", score);
	printf("\n\n\x1b[31m                                      비밀번호(두 번째 자리) : 7");
	printf("\n\n\n");
	printf("====================================================================================================\n\n\n\n\n");
	Sleep(1000);
	roomselect();
}

void DrawGameOver(const int score)
{
	system("cls");
	printf("\n\n\n\n\n\n");
	textcolor(15);
	printf("====================================================================================================\n");
	printf("\n\n\n");
	printf("       \x1b[31m                               점프실력을 키워오시오 ㅋ\x1b[0m");
	printf("\n\n                                             SCORE : %d", score);
	printf("\n\n\n");
	textcolor(15);
	printf("====================================================================================================\n\n\n\n\n");
	Sleep(1000);
	void dinosaur_main();
}

//(v2.0) 충돌했으면 true, 아니면 false
bool isCollision(const int treeX, const int dinoY)
{
	GotoXY(0, 0);
	printf("treeX : %d, dinoY : %d", treeX, dinoY);
	if (treeX <= 8 && treeX >= 4 &&
		dinoY > 8)
	{
		return true;
	}
	return false;
}

void dinosaur_main()
{
	SetConsoleView();

	intro();

	while (true)
	{
		//게임 시작시 초기화
		bool isJumping = false;
		bool isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int treeX = TREE_BOTTOM_X;

		int score = 0;
		clock_t start, curr;
		start = clock();

		while (true)
		{
			if (isCollision(treeX, dinoY))
				break;

			if (GetKeyDown() == '1' && isBottom)
			{
				isJumping = true;
				isBottom = false;
			}

			if (isJumping)
			{
				dinoY -= gravity;
			}
			else
			{
				dinoY += gravity;
			}

			if (dinoY >= DINO_BOTTOM_Y)
			{
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}

			treeX -= 2;
			if (treeX <= 0)
			{
				treeX = TREE_BOTTOM_X;
			}

			if (dinoY <= 3)
			{
				isJumping = false;
			}

			DrawDino(dinoY);
			DrawTree(treeX);

			//(v2.0)
			curr = clock();
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)
			{
				score++;
				start = clock();
			}
			Sleep(60);
			system("cls");

			GotoXY(22, 0);
			printf("Score : %d ", score);
		}

		//게임 오버 메뉴
		if (score >= 15)
		{
			Correct(score);
			return;
		}
		else
			DrawGameOver(score);
	}

}

//---------------------------노래가사 맞히기 게임----------------------------------------
#define NUMBER 256

typedef struct sing {
	char singer[NUMBER];
	char lyrics[NUMBER];
	char lyrics1[NUMBER];
	char answer1[NUMBER];
	char hint[NUMBER];
}sing_info;

void GotoXY1(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void print_main();
void sing_main();
void correct_question();
void fail_question();
void end_question();
void sing_answer(int count, sing_info sing, int random);
void hint(sing_info sing);
void ending();

sing_info sings[50];



void sings_main() {
	//콘솔 크기 설정
	system("mode con:cols=75 lines=20");
	char enter = '\n';
	char answer[5][50];
	int hint1[5];
	int i = 0, j = 0, count = 1, count1 = 0;

	FILE* fp;
	fp = fopen("sing.txt", "r");

	//파일을 읽어와 구조체 배열에 저장
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
			while (count <= 5) {
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
//노래가사 메인
void sing_main()
{
	printf("\n");
	printf("\n");
	printf("\t\t\t\t\x1b[31m   203호\x1b[0m\n");
	printf("\t\t   \x1b[31m      ♬ 노래가사 맞히기 게임 ♬\x1b[0m \n");
	printf("\n");
	printf("===========================================================================\n");
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
	system("pause");
}
//힌트 제공화면
void hint(sing_info sing, int random) {
	GotoXY1(0, 16);
	printf("%s", sings[random].hint);
}
//노래가사 맞히기
void sing_answer(int count, sing_info sing, int random)
{
	printf("\n");
	printf("\n");
	printf("\x1b[31m   203호\t\t    Score :   %d / %d \x1b[0m     \n", count, 5);
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("\t\t   ♬ %s ♬\n", sings[random].singer);
	printf("\n");
	printf("\t\t   %s\n", sings[random].lyrics);
	printf("\t\t   %s\n", sings[random].lyrics1);
	printf("\n");
	printf("\n");
	printf("\t\t   힌트를 간절히 원한다면 1을 누르세요\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
}
//정답화면
void correct_question()
{
	printf("\n");
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
//오답화면
void fail_question()
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\x1b[31m                      틀렸다.. 호텔이 무너져 내린다....\x1b[0m\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
}

//문제 다 맞추었을시 ui
void end_question()
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                        다섯 문제를 모두 맞춘건가..\n");
	printf("                           나가는 길은 저쪽이다..\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	textcolor(15);
	printf("\n");
}
void ending()
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("                        어이!! 비밀번호 가져가라...\n");
	printf("         \x1b[31m                    (세번째 자리) 6..\x1b[0m\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("===========================================================================\n");
	textcolor(15);
	printf("\n");
	Sleep(1000);
	roomselect();
}


//---------------------------숫자야구게임----------------------------------------


int* CreateRandomNums() {
	static int ranNums[4];
	int Check;

	for (int i = 0; i < 4; i++) {
		Check = 0;
		ranNums[i] = rand() % 10;
		for (int j = 0; j < i; j++) {
			if (ranNums[i] == ranNums[j]) {
				Check = 1;
				break;
			}
		}

		if (Check == 1) {
			i--;
			continue;
		}
	}
	return ranNums;
}

void GetStrikeAndBall(int n1[4], int n2[4], int* strike, int* ball) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j && n1[i] == n2[j]) {
				*strike = *strike + 1;
				break;
			}
			else if (n1[i] == n2[j]) {
				*ball = *ball + 1;
				break;
			}
		}
	}
}

void Baseballgame() {
	int* ranNums;
	int answer[4];
	int strike;
	int ball;
	int cnt = 1;

	srand((unsigned int)time(NULL));

	ranNums = CreateRandomNums();

	//테스트 코드
	printf("정답 : ");
	for (int i = 0; i < 4; i++) {
		printf("%d", ranNums[i]);
	}
	printf("\n");

	while (1) {
		printf("[%d회차] 4자리 숫자를 입력하세요. ex)1 2 3 4: ", cnt);

		strike = 0;
		ball = 0;

		scanf_s("%d %d %d %d", &answer[0], &answer[1], &answer[2], &answer[3]);

		GetStrikeAndBall(ranNums, answer, &strike, &ball);

		printf("strike : %d / ", strike);
		printf("ball : %d\n\n", ball);

		cnt++;

		if (cnt == 9) {
			system("cls");
			printf("\n\n\n\n");
			printf("===========================================================================\n");
			printf("\n\n\n");
			printf("                       좀 더 추리력을 발휘해야한다...\n");
			printf("\n\n\n");
			printf("===========================================================================\n");
			printf("\n");
			Sleep(1000);
			system("cls");
			Baseballgame();
		}

		if (strike == 4) {
			system("cls");
			printf("\n\t\t\t\t   정답\n");
			FILE* fs1;
			fs1 = fopen("glove.txt", "r");
			while (feof(fs1) == 0) {
				char str[20];
				fgets(str, 20, fs1);
				printf("%s", str);
			}
			Beep(380, 500);

			Sleep(300);
			system("cls");
			printf("\n\n\t\t\t\t   정답\n");
			FILE* fs2;
			fs2 = fopen("gloveball.txt", "r");
			while (feof(fs2) == 0) {
				char str[20];
				fgets(str, 20, fs2);
				printf("%s", str);
			}
			Sleep(900);

			system("cls");


			printf("\n\n\n\n");
			printf("===========================================================================");
			printf("\n\n\n");
			printf("\t\t\x1b[31m      비밀번호(네 번째 자리) : 0\x1b[0m");
			printf("\n\n\t\t         시간은 흐르고 있다...");
			printf("\n\n\n");
			printf("===========================================================================\n\n\n\n\n");
			Sleep(1000);
			roomselect();
		}
	}
}

void baseball_main() {
	system("mode con:cols=75 lines=20");
	printf("\n");
	printf("\n");
	printf("\t\t\t\t\x1b[31m   204호\x1b[0m\n");
	printf("\t\t\t\x1b[31m      숫자 야구 게임\x1b[0m  \n");
	printf("\n");
	printf("==========================================================================\n");
	printf("\n");
	printf("\t\t       4자리 랜덤 숫자를 맞히는 게임\n");
	printf("\t\t    각 자리의 숫자는 중복되지 않습니다.\n");
	printf("\t\t 입력한 숫자 중 동일한 숫자가 있으면");
	textcolor(9);
	printf(" BALL\n");
	textcolor(15);
	printf("\t\t\t자릿수까지 동일하면");
	textcolor(12);
	printf(" STRIKE\n");
	textcolor(15);
	printf("\t     8번의 기회 안에 숫자를 정확히 맞히면 게임은 끝.\n");
	printf("\t         실패하면 숫자는 랜덤으로 재생성됩니다.\n");
	printf("\n");
	printf("==========================================================================\n");
	printf("\n");

	system("pause");
	system("cls");
	Baseballgame();


}

//-------------------------------메인스토리 화면-------------------------------------

//게임 시작 메인 UI
void print_main() {
	system("mode con:cols=75 lines=20");
	printf("\n");
	printf("\x1b[31m                        Janbari Hotel Escape Game\x1b[0m\n");
	printf("\n");
	printf("\x1b[31m                                    *\x1b[0m\n");
	printf("\x1b[31m                                   ===\x1b[0m\n");
	printf("\x1b[31m                             =J=A=N=B=A=R=I=\x1b[0m\n");
	printf("\x1b[31m                          =====================\x1b[0m\n");
	printf("\x1b[31m                          = -- -- -- -- -- -- =\x1b[0m\n");
	printf("\x1b[31m                          = -- -- -- -- -- -- =\x1b[0m\n");
	printf("\x1b[31m                          = -- -- -- -- -- -- =\x1b[0m\n");
	printf("\x1b[31m                          = -- -- -- -- -- -- =\x1b[0m\n");
	printf("\x1b[31m                          = -- -- |   | -- -- =\x1b[0m\n");
	printf("\x1b[31m                        =========================\x1b[0m\n");
	printf("===========================================================================\n");
	printf("\n");
	system("pause");
}

void print_talk()
{
	int i = 0;

	char talk[6][500] = { {"껌뻑..껌뻑..어.. ? 여기가 어디지.. ? \n"} ,
		{"(스피커) 지직....지지직 일어났는가?\n"},
		{"너는 지금 10분 뒤에 무너지게 될 호텔 안에 갇혀있다.\n"},
		{"총 4개의 방안에 들어가 게임에서 이겨 네 자리의 비밀번호를 얻어라.\n"},
		{"그 비밀번호로 탈출구에 걸려있는 좌물쇠를 풀고 밖으로 탈출할 수 있다.\n"},
		{"명심해라 너한테 남은 시간은 10분밖에 없다는 것을... 삐이익...\n"}
	};
	while (i <= 5) {
		printf("\n\n");
		printf("\x1b[31m                        Janbari Hotel Escape Game\x1b[0m\n");
		textcolor(15);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("===========================================================================\n");
		printf("\n");
		printf("%s", talk[i]);
		printf("\n");
		printf("===========================================================================\n");
		i++;
		Sleep(2800);
		system("cls");
	}
}
//----------------------------------타이머----------------------------------------
void time_ending()
{
	int hour = 9, min = 59;
	for (int i = min; i > 55; i--) {

		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n\n===========================================================================\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t\x1b[31m                         9 : %d\x1b[0m\n", i);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("===========================================================================\n");
		printf("\n");

		Beep(380, 200);
		Sleep(1000);

		system("cls");
	}
}
//-------------------------------방선택화면----------------------------------------
void roomselect() {

	system("cls");
	int room = 0;
	system("mode con:cols=75 lines=20");
	printf("\n");
	printf("\n");
	printf("\t\t\x1b[31m         Janbari Hotel Escape Game\x1b[0m\n\n\n");
	textcolor(15);
	printf("\t=========== \t=========== \t=========== \t===========\n\n");
	if (c1 == 0) {
		printf("\t\x1b[31m    201\x1b[0m");
	}
	else {
		textcolor(0);
		printf("\t    201");
	}
	if (c2 == 0) {
		printf("\t\t\x1b[31m    202\x1b[0m");
	}
	else {
		textcolor(0);
		printf("\t\t    202");
	}
	if (c3 == 0) {
		printf("\t\t\x1b[31m    203\x1b[0m");
	}
	else {
		textcolor(0);
		printf("\t\t    203");
	}
	if (c4 == 0) {
		printf("\t\t\x1b[31m    204\x1b[0m\n\n");
	}
	else {
		textcolor(0);
		printf("\t\t    204\n\n");
	}
	textcolor(15);
	printf("\t=========== \t=========== \t=========== \t===========\n\n\n\n\n");

	if (c1 == 1 && c2 == 1 && c3 == 1 && c4 == 1) {
		ck();
	}

	else {
		printf("\t\t\t   입장할 방을 입력하시오.\n\n");
		printf("\t\t\t\t     ");
		scanf("%d", &room);

		if (room == 201) {
			c1 += 1;
			en_main();
		}
		else if (room == 202) {
			c2 += 1;
			dinosaur_main();
		}
		else if (room == 203) {
			c3 += 1;
			sings_main();
		}
		else if (room == 204) {
			c4 += 1;
			baseball_main();
		}
	}
}


int main()
{
	print_main();
	system("cls");
	print_talk();
	time_ending();
	PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP);
	roomselect();
