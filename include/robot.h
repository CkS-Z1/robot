#ifndef ROBOT_H
#define ROBOT_H
#include "allfunc.h"


// typedef struct Robot
// {
//     RoomID inRoom;            //机器人现在在哪个房间
//     RoomID toRoom;            //机器人将要移动到哪个房间，如果是NONE表示不移动到其他房间
//     int x;                    //机器人在对应房间的位置的坐标
//     int y;
//     int width;
//     int height;//包含完整机器人图形
//     //int to_x;                 //机器人将要移动到哪里
//     //int to_y;
//     int battery;              //机器人还有百分之多少的电
//     //Incidentcode incident;    //机器人现在正在干什么
// } Robot;


void robot_set(Robot* Rob);
void Save_image(int x1, int y1, int x2, int y2, char *bmpname);
void Load_image(int x1, int y1, int x2, int y2, char *bmpname);
Robot init_robot();
void robot_uphand(Robot *Rob);


/*
Baseimages 动画用基础图像：
各种动画需要用到的基础Baseimage的文件路径序号n，对应"C://cks//bmp//baseimage(n).dat"
typedef enum
{
    Robotimage = 0,//机器人图像

    pan = 1,  //存储锅的图像，用于擦除或增添
    dish,     //存储做好的菜和餐盘
    plate,    //存储空盘
    emptycup, //存储空水杯
    fullcup,  //存储满水杯
    boiler,   //存储烧水壶
    flowercan //存储花洒

} Baseimages;
*/



#endif