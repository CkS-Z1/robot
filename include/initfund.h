/*initfund
功能：
    1.读取Todaydata，进行相应"全局变量"的赋值和文件存储
    2.初始化窗户状态，写入<windowstate.dat>;
    3.
文件：
    <winstate.dat>:只存入一个bool变量windowstate，用于记录窗户的开关状态
*/

#ifndef INITFUND_H
#define INITFUND_H
#include <stdio.h>
#include <global.h>

//初始化函数，读取Todaydata，进行相应全局变量的赋值;传出todaydata
void read_todaydata(Todaydata *todaydata);
//根据接收到的todaydata初始化窗户状态，写入<winstate.dat>
void initialize_windowstate(Todaydata *todaydata);
//总的初始化fundation data函数
void initialize_fundation();







#endif