#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <unistd.h> //sleep 기능 구현 위해, windows.h 대체 < 맥북;
#define _CRT_SECURE_NO_WARNINGS
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45
#define NUMBER 256

typedef struct sing {
	char singer[NUMBER];
	char lyrics[NUMBER];
	char lyrics1[NUMBER];
	char answer1[NUMBER];
	char hint[NUMBER];
}sing_info;

void Gotoxy(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void SetConsoleView()
{
	system("mode con:cols=100 lines=25");
	system("title Google Dinosaurs. By BlockDMask.");
}


void sing_main();
void correct_question();
void fail_question();
void end_question();
void sing_answer(int count, sing_info sing, int random);
void hint(sing_info sing);

sing_info sings[50];

//-------------------------------방선택화면----------------------------------------
int roomselect() {
	int room = 0;
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	system("mode con:cols=75 lines=20");
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("\t\t         Janbari Hotel Escape Game\n\n\n");
	textcolor(15);
	printf("\t=========== \t=========== \t=========== \t===========\n\n");
	if (c1 == 0) {
		textcolor(12);
		printf("\t    201");
	}
	else {
		textcolor(0);
		printf("\t    201");
	}
	if (c2 == 0) {
		textcolor(12);
		printf("\t\t    202");
	}
	else {
		textcolor(0);
		printf("\t\t    202");
	}
	if (c3 == 0) {
		textcolor(12);
		printf("\t\t    203");
	}
	else {
		textcolor(0);
		printf("\t\t    203");
	}
	if (c4 == 0) {
		textcolor(12);
		printf("\t\t    204\n\n");
	}
	else {
		textcolor(0);
		printf("\t\t    204\n\n");
	}
	textcolor(15);
	printf("\t=========== \t=========== \t=========== \t===========\n\n\n\n\n");

	printf("\t\t\t   입장할 방을 입력하시오.\n\n");
	printf("\t\t\t\t     ");
	scanf("%d", &room);

	if (room == 201) {
		word_main();
		c1 += 1;
	}
	else if (room == 202) {
		dinosaur_main();
		c2 += 1;
	}
	else if (room == 203) {
		sing_main();
		c3 += 1;
	}
	else if (room == 204) {
		baseball_main();
		c4 += 1;
	}
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

void intro_engame() {
	system("cls");

	printf("\n");
	printf("\n");
	printf("\x1b[31m                                               201호\x1b[0m\n");
	printf("                                         사자성어 네글자 퀴즈\n");
	printf("\n");
	printf("====================================================================================================\n");
	printf("\n");
	printf("                                  힌트를 보고 사자성어를 맞추시오.\n");
	printf("                                             - 5문제 -\n");
	printf("\n");
	printf("                                            GOOD LUCK..\n\n");
	printf("====================================================================================================\n");
	printf("\n\n");
	char b;
	printf("PRESS ENTER TO START...");
	scanf("%c", &b);
}

void Right() {
	system("cls");
	printf("====================================================================================================\n\n\n\n\n\n");
	printf("                                           욜 ㅋ 쫌 치는데?\n\n\n\n\n\n");
	printf("====================================================================================================\n");
	Sleep(1000);
}

void Wrong() {
	system("cls");
	printf("====================================================================================================\n\n\n\n\n\n");
	printf("                                      이러다가 다~ 죽어~!\n\n\n\n\n\n");
	printf("====================================================================================================\n");
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

void engame_ending() {
	system("cls");
	printf("====================================================================================================\n\n\n\n\n\n");
	printf("                               이걸 다 맞혔어?...\n\n\n\n\n\n");
	printf("                               비밀번호(첫 번째 자리) : 3\n\n\n\n\n\n");
	printf("====================================================================================================\n");
	Sleep(5000);
}

int Check(int pw1, int pw2, int pw3, int pw4) {
	int ck1 = pw1 == 3 ? 0 : 1;
	int ck2 = pw2 == 7 ? 0 : 1;
	int ck3 = pw3 == 0 ? 0 : 1;
	int ck4 = pw4 == 6 ? 0 : 1;

	if (ck1 + ck2 + ck3 + ck4 > 0) { //정답 아닌 경우
		return 0;
	}
	else { //정답인 경우
		return 1;
	}
}

void en_main() {
	save_problem(); //문제 & 힌트 저장
	set_idx(); //랜덤 index 5개 추출
	intro_engame(); //시작 화면 출력
	eng_game(); //게임 실행
	engame_ending(); //엔딩 화면
}

void total_ending() {
	system("cls");
	printf("====================================================================================================\n\n\n\n\n\n");
	printf("                              ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n\n\n\n\n");
	printf("====================================================================================================\n");
	Sleep(5000);
}
int p1; int p2; int p3; int p4;

void ck() {
	while (1) {
		system("clear");
		printf("비밀번호를 입력하시오: ");
		scanf("%d %d %d %d", &p1, &p2, &p3, &p4);
		if (Check(p1, p2, p3, p4)) break;
	}
}

void word_main() {
	en_main();
	ck();
	total_ending();
}



//---------------------------공룡게임----------------------------------------


void intro()
{
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("                                               202호\n");
	printf("                                             공룡 게임\n");
	textcolor(15);
	printf("\n");
	printf("====================================================================================================\n");
	printf("\n");
	printf("                                점프하여 장애물을 피하시오. (점프:z)\n");
	printf("                                        - 최소 15점 이상 -\n");
	printf("\n");
	printf("                                            GOOD LUCK..\n\n");
	printf("====================================================================================================\n");
	printf("\n\n");

	system("pause");
	system("cls");
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
	printf("\n\n                                             SCORE : %d", score);
	textcolor(12);
	printf("\n\n                                      비밀번호(두 번째 자리) : 7");
	printf("\n\n\n");
	textcolor(15);
	printf("====================================================================================================\n\n\n\n\n");
	system("pause");
}

void DrawGameOver(const int score)
{
	system("cls");
	printf("\n\n\n\n\n\n");
	textcolor(15);
	printf("====================================================================================================\n");
	printf("\n\n\n");
	textcolor(12);
	printf("                                      점프실력을 키워오시오 ㅋ");
	printf("\n\n                                             SCORE : %d", score);
	printf("\n\n\n");
	textcolor(15);
	printf("====================================================================================================\n\n\n\n\n");
	system("pause");
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

			if (GetKeyDown() == 'z' && isBottom)
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
			return 0;
		}
		else
			DrawGameOver(score);
	}

}

//---------------------------노래가사 맞히기 게임----------------------------------------



void sing_main() {
	//콘솔 크기 설정
	system("mode con:cols=55 lines=20");
	char enter = '\n';
	char answer[5][50];
	int hint1[5];
	int i = 0, j = 0, count = 1, count1 = 0;

	FILE* fp;
	fp = fopen("노래가사.txt", "r");

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
					Sleep(3000);
					system("cls");
					j++;
					count++;
				}
				//힌트를 원할 때
				else if (strcmp(answer[j], "1") == 0) {
					sing_answer(count, sing, hint1[j]);
					hint(sing, hint1[j]);
					Sleep(3000);
					system("cls");
				}
				//오답일때
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
	Gotoxy(0, 16);
	printf("%s", sings[random].hint);
}
//노래가사 맞히기
void sing_answer(int count, sing_info sing, int random)
{
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("   203호         Score :   %d / %d      \n", count, 5);
	textcolor(15);
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
	printf("%s  \n", sings[random].singer);
	printf("\n");
	printf("%s\n", sings[random].lyrics);
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
			printf("실패");
			break;
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
			printf("\t\t      비밀번호(세 번째 자리) : 6");
			printf("\n\n\t\t         시간은 흐르고 있다...");
			printf("\n\n\n");
			printf("===========================================================================\n\n\n\n\n");
			break;
		}
	}
}

void baseball_main() {
	system("mode con:cols=75 lines=20");
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("\t\t\t\t   204호\n");
	printf("\t\t\t      숫자 야구 게임  \n");
	textcolor(15);
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
	printf("\n");
	printf("==========================================================================\n");
	printf("\n");
	printf("\t\t       계속하려면 Enter를 누르세요..\n");

	char enter = "\n";
	scanf("%c", &enter);
	if (enter == '\n') {
		system("cls");
		Baseballgame();
	}
}



