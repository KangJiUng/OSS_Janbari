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
	printf("\n\n\n=================================================================\n\n\n\n\n");
	printf("                              욜 ㅋ 쫌 치는데?\n\n\n\n\n");
	printf("=================================================================\n\n\n");
	Sleep(1000);
}

void Wrong() {
	system("cls");
	printf("\n\n\n=================================================================\n\n\n\n\n");
	printf("                            이러다가 다~ 죽어~!\n\n\n\n\n");
	printf("=================================================================\n\n\n");
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
	textcolor(12);
	printf("\t\t\t\t   201호\n");
	printf("\t\t           사자성어 네글자 퀴즈\n");
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
	textcolor(12);
	printf("                        비밀번호(첫 번째 자리) : 3\n\n\n\n");
	textcolor(15);
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
void Password(){
    system("cls");
    printf("\n");
    printf("\n");
    printf("\x1b[31m                               Janbari Hotel Escape Game\x1b[0m\n");
    printf("====================================================================================================\n");
    printf("\n");
    printf("                                  비밀번호 네자리를 입력하시오.\n");
    printf("                                      [            ]\n");
    printf("\n");
    printf("====================================================================================================\n");
    printf("\n\n");
}
void Ending()
{
	int i = 0;

	char end[4][500] = { {"덜컥... 마침내 문이 열렸다... \n"} ,
		{"        (그때 뒤에서 들려오는 발걸음 소리...)\n"},
		{"            터벅... 터벅... 콰직!\n"},
		{"                  The End\n"}
	};
	while (i <= 3) {
		printf("\n");
		printf("\x1b[31m                      Janbari Hotel Escape Game\x1b[0m\n");
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
		printf("%s", end[i]);
		printf("\n");
		printf("===========================================================================\n");
		i++;
		sleep(5);
        system("cls");
	}
}
void Fail(){
    system("cls");
    printf("\n");
    printf("\n");
    printf("====================================================================================================\n");
    printf("\n");
    printf("\x1b[31m                                  You Die\x1b[0m\n");
    printf("\n");
    printf("====================================================================================================\n");
    printf("\n\n");
}

void ck() {
	while (1) {
		int p1 = 3760;
		system("cls");	
		printf("\n\n\n\n\n\n");
		Password();
		scanf("%d", &p1);
		if (p1==3760) {
			Ending();
		}else{
			Fail();
		}
	}
}
