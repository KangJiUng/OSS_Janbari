#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include<conio.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//콘솔 창의 크기와 제목을 지정하는 함수
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

///////////////////////////////////////////////////////////////

int* CreateRandomNums() {
	static int ranNums[4];
	int Check;

	for (int i = 0; i < 4; i++) {
		Check = 0;
		ranNums[i] = rand() % 10;
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

void Baseball_main() {
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

		if (strike == 4) {
			Beep(380, 500);
			printf("정답\n");
			break;
		}
	}
}
