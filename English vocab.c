#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct Problem{
    char answer[100];
    char hint[100];
};
struct Problem problem[20];
int main(){
    const int max=1024;
    char line[max];
    char *pLine;
    FILE *in = fopen("/Users/jeong-ujin/Desktop/충북대학교3/충북대학교3/problems.txt", "r");
    int cnt1=0;
    int cnt2=0;
    
    while(!feof(in)){
        pLine=fgets(line,max, in);
        if(pLine==NULL)
            break;
        if(cnt2==0){
            strcpy(problem[cnt1].answer,pLine);
            cnt2+=1;
        }
        else if(cnt2==1){
            strcpy(problem[cnt1].hint,pLine);
            cnt2=0; cnt1+=1;
        }
    }
    fclose(in);
    
    srand(time(NULL));
    int cnt=0;
    int ck[5]={-1,};
    
    while(1){
        int check=1;
        if(cnt==5){
            break;
        }
        int ran_num =rand()%20;
        for(int i=0; i<cnt; i++){
            if(ck[i]==ran_num){
                check=0;
                break;
            }
        }
        if(check){
            ck[cnt]=ran_num;
            cnt++;
        }
        
        char*temp=strtok(problem[ran_num].answer," ");
        temp=strtok(NULL," ");
        printf("[%d]%s", cnt ,temp);
        temp=strtok(NULL,"\n");
        for(int j=0; j<strlen(temp); j++){
            printf("_");
            
        }
        printf("\n");
        printf("%s\n",problem[ran_num].hint);
        
        while(1){
            char answer[20];
            printf("정답 입력: ");
            scanf("%s", answer);
            strcmp(answer, temp);
            if(strcmp(answer, temp)==0){
                printf("정답입니다~\n");
                break;
            }
            else{
                printf("틀렸습니다~\n");
            }
        }
    }
}
