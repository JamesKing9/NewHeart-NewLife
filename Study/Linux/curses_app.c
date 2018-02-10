/***********6.10 CD唱片应用程序******************/

//##############开头

//声明将在后面用到的变量和函数，并 初始化一些数据结构
/*
1）包含所有必需的头文件，并定义一些全局变量
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h> //该头文件需要自己安装

#define MAX_STRING 80
#define MAX_ENTRY 1024

#define MESSAGE_LINE 6
#define ERROR_LINE  22
#define Q_LINE      20
#define PROMPT_LINE 18

/*
2)
*/
static char current_cd[MAX_STRING] = "\0";
static char current_cat[MAX_STRING];

int main() {
    printf("hello\n");
    exit(0);
}

/*
3) 文件名的声明
*/
const char *title_file = "title.cdb";
const char *tracks_file = "tracks.cdb";
const char *temp_file = "cdb.tmp";

/*
4) 给出所有函数的原型定义
*/
void clear_all_screen(void);
void get_return(void);
int get_confirm(void);
int getchoice(char *greet, char *choices[]);
void draw_menu(char *options[], int highlight, int start_row, int start_col);

/*
5）定义菜单选项的数组，当一个菜单选项被选中的时候，其中第一个字符将被返回。
*/
char *main_menu[] =
{
	"add new CD",
	"find CD",
	"count CDs and tracks in the catalog"
}

char *extended_menu[] = {
	"add new CD"
}

/*
main 函数
*/
int main() 
{
	int choice;
	
	initscr();
}

/*

*/
int getchoice(char *greet, char *choices[]) 
{

	static int selected_row = 0;
}