#include <stdio.h>
#include <float.h>

int main() 
{
  printf("float �洢����ֽ�����%lu \n", sizeof(float));
  printf("float ��Сֵ��%E\n" ,FLT_MIN);
  printf("float ���ֵ��%E\n", FLT_MAX);
  printf("����ֵ��%d\n", FLT_DIG);
  
  return 0;
}