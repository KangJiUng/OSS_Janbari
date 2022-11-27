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
	fp = fopen("�뷡����.txt", "r");

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
				system("cls"); //����ȭ�� �����
				sing_answer(count, sing,hint1[j]); //�뷡���� ������ ȭ��

				printf("������ �Է��ϼ���..  ");
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
		printf("���� ���� x");
		return;
	}
	end_question();
	return 0;
}
//�뷡���� ����
void sing_main() 
{
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("                         203ȣ                         \n");
	printf("                   �뷡 ���� ������  \n");
	textcolor(15);
	printf("\n");
	printf("=====================================================\n");
	printf("\n");
	printf("         ��ĭ�� �˸��� �뷡 ���縦 ��������\n");
	printf("          �� �ټ� ������ ���߸� ����Դϴ�\n");
	printf("         ��Ʈ�� �� ������ �ѹ��� �����˴ϴ� \n");
	printf("\n");
	printf("                    GOOD LUCK..\n");
	printf("=====================================================\n");
	printf("\n");
	printf("	   ����Ϸ��� Enter�� ��������..\n");
}
//��Ʈ ����ȭ��
void hint(sing_info sing, int random) {
	GotoXY(0, 16);
	printf("%s", sings[random].hint);
}
//�뷡���� ������
void sing_answer(int count,sing_info sing,int random)
{	
	printf("\n");
	printf("\n");
	textcolor(12);
	printf("   203ȣ         Score :   %d / %d      \n", count, 5);
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
	printf("             ��Ʈ�� ������ 1�� ��������\n");
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
}
//����ȭ��
void correct_question() 
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("              �����̴�.....���� ����..\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
}
//����ȭ��
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
	printf("           Ʋ�ȴ�.. ȣ���� ������ ������....\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	printf("\n");
}

//���� �� ���߾����� ui
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
	printf("            �ټ� ������ ��� ����ǰ�..\n");
	printf("               ������ ���� �����̴�..\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	textcolor(15);
	printf("\n");
}