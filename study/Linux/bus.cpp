#include <stdio.h>

int main() {
    char *pa[] = {
        "上地",
        "五道口 ",
        "清华大学站", 
        "物理所站 ", 
        "国图站 ", 
        "苹果园站 ", 
        "八达岭站 ", 
        "新二街站 ", 
        "四通站 ", 
        "北大站 ", 
        "昌平站 "
    };
    char **p = pa;
    int start, end;

    printf("车站列表： \n");
    printf("站台号\t车站名\n");

    for (int i=0; i<10; i++) {
        printf("%4d\t%s\n", i+101, *p);
        p++;
    }

    printf("请输入起点站台号： ");
    scanf("%d", &start);

    printf("请输入终点站台号： ");
    scanf("%d", &end);

    printf("您的乘车路线为： \n");
    if (start < 101 || start >110 || end <100 || end >110) {
        printf("您输入的车站号有误！\n");

        return 1;
    } else if (start <= end) {
        while (start <= end) {
            printf("%5d =>", start);
            start ++;
        }
    } else {
        while (start >= end) {
            printf("%5d =>", start);
            start --;
        }
    }

    putchar('\n');

    return 0;

}