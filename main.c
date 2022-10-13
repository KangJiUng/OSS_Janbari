#include <stdio.h>

int main ()
{
  int n, m;
  char op;
  
  printf("두 정수의 연산식을 입력해주세요.(ex: 2+6): %d%c%d");
  scanf("%d%c%d", &n, &op, &m);
  
  if(op=='+') printf("답: %d", );
  else if(op=='-') printf("답: %d", );
  else if(op=='*') printf("답: %d", );
  else if(op=='/') printf("답: %d", );
  else printf("다시 입력해주세요.");
    
  return 0;
}
