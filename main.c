#include <stdio.h>

int add(int a, int b);
int mod(int a, int b);
int Gop(int a, int b);

int main ()
{
  int n, m;
  char op;
  
  printf("두 정수의 연산식을 입력해주세요.(ex: 2+6): ");
  scanf("%d%c%d", &n, &op, &m);
  
  if(op=='+') printf("답: %d", add(n,m));
  else if(op=='-') printf("답: %d", );
  else if(op=='*') printf("답: %d", Gop(n,m));
  else if(op=='/') printf("답: %d",mod(n,m));
  else printf("다시 입력해주세요.");
    
  return 0;
}

int add(int a, int b){
  return a+b;
}
int mod(int a, int b){
  return a/b;
}
int Gop(int a, int b){
  return a*b;
}
