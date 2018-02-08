/*
添加curses.h头文件
*/
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main() {
    initscr(); //初始化curses库的函数调用
    //############################//
    /*
    
    */
    move(5, 15); //将光标移动到逻辑屏幕上的坐标（5, 15）处
    printw("%s", "hello");
    refresh(); //刷新物理屏幕

    sleep(2); //将程序暂停 2s，以便在程序结束前看到输出的结果
    //###########################//
    endwin(); //重置curses库的函数调用
    exit(EXIT_SUCCESS);
}
