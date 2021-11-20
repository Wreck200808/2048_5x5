#include<iostream>
#include "display_start.h"
using namespace std;
void display_start();    //显示开始界面
void data();             //有上局数据就导入，无上局数据就创建
bool play();             //正儿八经游戏环节，返回值代表游戏结束或中途退出

int main(){
    display_start();
    char input;
    cin >> input;
    switch (input) {
        case 'p':
            data();
            play();
            exit(0);
            break;
        case 'e':
            exit(1);
        default:
            cout << endl << "Invalid input, please type again: ";
    }
    return 0;
}