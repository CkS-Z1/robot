/*initfund.c
    <initialize fundation.c>
功能：
    1.读取Todaydata，进行相应"全局变量"的赋值和文件存储
    2.初始化窗户状态，写入<windowstate.dat>;
    3.
文件：
    <winstate.dat>:只存入一个bool变量windowstate，用于记录窗户的开关状态
*/

#include "initfund.h"

void read_todaydata(Todaydata *todaydata);
void initialize_windowstate(Todaydata *todaydata);
void initialize_fundation();

//初始化函数，读取Todaydata，进行相应全局变量的赋值;传出todaydata
void read_todaydata(Todaydata *todaydata)
{
    FILE *fp = NULL;

    // 打开文件以二进制读取todaydata
    fp = fopen("Data\\diary.dat", "rb");
    if (fp == NULL) 
    {
        perror("can't open diary.dat file");
        exit(1);
    }

    // 从文件中读取 Todaydata 数据
    if (fread(todaydata, sizeof(Todaydata), 1, fp) != 1)
    {
        perror("error in read_todaydata reading diary.dat file");
        fclose(fp);
        exit(1);
    } 

    // 关闭文件
    fclose(fp);
}

//根据接收到的todaydata初始化窗户状态，写入<winstate.dat>
void initialize_windowstate(Todaydata *todaydata) 
{
    FILE *fp = NULL;
    Windowstate windowstate;

    // 根据天气情况初始化窗户状态
    if (todaydata->weather == Rainy || todaydata->weather == Snowy) 
    {
        windowstate = WindowClose;
    } 
    else 
    {
        windowstate = WindowOpen;
    }

    // 打开文件以二进制更新写入winstate.dat
    fp = fopen("Data\\winstate.dat", "wb");
    if (fp == NULL) 
    {
        perror("can't open winstate.dat file");
        exit(1);
    }

    // 将窗户状态写入文件
    if (fwrite(&windowstate, sizeof(Windowstate), 1, fp) != 1) {
        perror("error in writing into winstate.dat file");
        fclose(fp);
        exit(1);
    }

    // 关闭文件
    fclose(fp);
}

//总的初始化fundation data函数
void initialize_fundation() 
{
    Todaydata todaydata;

    // 读取Todaydata
    read_todaydata(&todaydata);

    // 初始化窗户状态，bool值存入<winstate.dat>
    initialize_windowstate(&todaydata);
}