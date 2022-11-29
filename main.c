#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define _CRT_SECURE_NO_WARNINGS
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//---------------------------공룡게임----------------------------------------
//콘솔 창의 크기와 제목을 지정하는 함수

int main()
{
	int count;
	
	printf("게임을 할 숫자를 입력하세요.");
	printf("1. 공룡게임\n");
	printf("2. 공룡게임\n");
	printf("3. 공룡게임\n");
	printf("4. 공룡게임\n");
	scanf("%d",&count);
	SingGame_main();
}
void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Google Dinosaurs. By BlockDMask.");
}

//커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
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

//(v2.0) 충돌 했을때 게임오버 그려줌
void DrawGameOver(const int score)
{
    system("cls");
    int x = 18;
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);

    printf("\n\n\n\n\n\n\n\n\n");
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

        //(v2.0) 게임 오버 메뉴
        DrawGameOver(score);
    }

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

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
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
			printf("\t\t\t\t\t\t\t    정답\n");
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
			printf("\t\t\t\t\t\t\t    정답!\n");
			FILE* fs2;
			fs2 = fopen("gloveball.txt", "r");
			while (feof(fs2) == 0) {
				char str[20];
				fgets(str, 20, fs2);
				printf("%s", str);
			}
			break;
		}
	}
}

int baseball_main() {
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("                                  204호                         \n");
	printf("                              숫자 야구 게임  \n");
	textcolor(15);
	printf("\n");
	printf("=========================================================================\n");
	printf("\n");
	printf(" 4자리 랜덤 숫자를 맞히는 게임으로, 각 자리의 숫자는 중복되지 않습니다.\n");
	printf("              입력한 숫자 중 동일한 숫자가 있으면");
	textcolor(9);
	printf(" BALL\n");
	textcolor(15);
	printf("                   자릿수까지 동일하면");
	textcolor(12);
	printf(" STRIKE\n");
	textcolor(15);
	printf("          8번의 기회 안에 숫자를 정확히 맞히면 게임은 끝이 납니다.\n");
	printf("\n");
	printf("========================================================================\n");
	printf("\n");
	printf("	               계속하려면 Enter를 누르세요..\n");
	
	char enter = "\n";
	scanf("%c", &enter);
	if (enter == '\n') {
		system("cls");
		basenum_main();
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

int SingGame_main() {
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
				sing_answer(count, sing,hint1[j]); //노래가사 맞히기 화면
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
				else if (strcmp(answer[j], "1" )== 0) {
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
