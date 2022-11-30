#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> //sleep 기능 구현 위해, windows.h 로 대체

// 사자성어 네글자 퀴즈
struct Problem{
    char answer[100];
    char hint[100];
};

struct Problem problem[20];

int rand_idx[5] = {0};


void set_idx(){
    int random = 0; // 정수형 변수 선언
    int i=0;
    srand(time(NULL));
    
    while(1){
        int ck=0;
        random = rand()%20; // 난수 생성
        for (int j=0; j<i; j++){
            if (random == rand_idx[j])
                ck=1;
        }
        if(ck) continue;
        rand_idx[i] = random;
        i+=1;
        if(i==5) break;
    }
}

void save_problem(){
    const int max = 1024;
    char line[max];
    char *pLine;
    FILE *in = fopen("/Users/jeong-ujin/Desktop/충대4/충대4/problems.txt", "r");
    int cnt1=0;
    int cnt2=0;
        
    while (!feof(in)) {
        pLine = fgets(line, sizeof(line), in);
        if(pLine == NULL)
            break;
        if(cnt2==0){
            strcpy(problem[cnt1].answer,pLine);
            cnt2+=1;
        }
        else if (cnt2==1){
            strcpy(problem[cnt1].hint,pLine);
            cnt2=0; cnt1+=1;
        }
    }
    fclose(in);
}

void intro_engame(){
    system("clear");
    
    printf("\n");
    printf("\n");
    printf("\x1b[31m                                               201호\x1b[0m\n");
    printf("                                         사자성어 네글자 게임\n");
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
    scanf("%c",&b);
}

void Right(){
    system("clear");
    printf("====================================================================================================\n\n\n\n\n\n");
    printf("                                           욜 ㅋ 쫌 치는데?\n\n\n\n\n\n");
    printf("====================================================================================================\n");
    sleep(1);
}

void Wrong(){
    system("clear");
    printf("====================================================================================================\n\n\n\n\n\n");
    printf("                                      이러다가 다~ 죽어~!\n\n\n\n\n\n");
    printf("====================================================================================================\n");
    sleep(1);
}

void eng_game(){
    system("clear");

    for (int k=0; k<5; k++){
        char answ[30]; // 답 저장
        char prob[30];
        char *temp = strtok(problem[rand_idx[k]].answer," ");
        temp = strtok(NULL, " ");
        strcpy(prob,temp);
        temp = strtok(NULL, "\n");
        while(1){
            system("clear");

            printf("\x1b[31m                              ROUND : %d/5    \x1b[0m\n\n\n\n",k+1);
            printf("                          %s",prob);
            
            for(int i=0; i<strlen(temp);i++){
                printf("_");
            }
            printf("\n\n                     %s\n\n\n\n",problem[rand_idx[k]].hint);
            printf("빈칸을 입력하시오...");
            scanf("%s",answ);
            if(!strcmp(temp,answ)){
                Right();
                break;
            }
            else{
                Wrong();
            }
        }
        system("clear");
    }
}

void engame_ending(){
    system("clear");
    printf("====================================================================================================\n\n\n\n\n\n");
    printf("                               이걸 다 맞췄어?...\n\n\n\n\n\n");
    printf("                               비밀번호(첫번째 자리)  : 3\n\n\n\n\n\n");
    printf("====================================================================================================\n");
    sleep(5);
}

int Check(int pw1, int pw2, int pw3, int pw4){
    int ck1 = pw1==3 ? 0 : 1 ;
    int ck2 = pw2==7 ? 0 : 1 ;
    int ck3 = pw3==6 ? 0 : 1 ;
    int ck4 = pw4==0 ? 0 : 1 ;

    if(ck1+ck2+ck3+ck4>0){ //정답 아닌 경우
        return 0;
    }
    else{ //정답인 경우
        return 1;
    }
}

void en_main(){
    save_problem(); //문제 & 힌트 저장
    set_idx(); //랜덤 index 5개 추출
    intro_engame(); //시작 화면 출력
    eng_game(); //게임 실행
    engame_ending(); //엔딩 화면
}

void total_ending(){
    system("clear");
    printf("====================================================================================================\n\n\n\n\n\n");
    printf("                              ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n\n\n\n\n");
    printf("====================================================================================================\n");
    sleep(5);
}
int p1; int p2; int p3; int p4;

void ck(){
    while(1){
        system("clear");
        printf("비밀번호를 입력하시오: ");
        scanf("%d %d %d %d",&p1,&p2,&p3,&p4);
        if(Check(p1,p2,p3,p4)) break;
    }
}

int main() {
    en_main();
    ck();
    total_ending();
}
