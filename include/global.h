/*
 * @Author: WTY
 * @Date:
 * @Description: 全局的一些定义，包括报错
 */
#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

//布尔类型
typedef enum
{
    false_0,
    true_0
} global_0;

//定义报错信息函数 SHOW_ERROR and SHOW_WARNING
#define SHOW_ERROR(str)                                         \
    printf("[Error]%s,line %d: %s\n", __FILE__, __LINE__, str); \
    perror("%s\n",str);                                         \
    printf("press any button to exit\n");                       \
    getchar();                                                  \
    exit(-1);

#ifdef DEBUG
#define SHOW_WARNING(str)   \
    printf("[Warning]%s,line %d: %s\n", __FILE__, __LINE__, str);
#else
#define SHOW_WARNING(str)
#endif

//房间编号
typedef enum
{
    NONE = 0,
    LIVINGROOM = 1,
    KITCHEN,
    MASTERBEDROOM,
    SECONDBEDROOM,
    BATHROOM,
    DININGROOM,
    BALCONY,
    TOILET
} RoomID;


//incidentcode事件代码
typedef enum{
    light_on=1,     //开灯
    light_off,      //关灯
    window_on,      //开窗
    window_off,     //关窗
    door_off,       //关门
    cook,           //做饭
    cleanup,        //打扫
    boilwater,      //烧水倒水
    plants,         //浇花
    battery,        //充电
    //emergency
    firealarm=11,  //火灾报警
    electricity,    //电源故障
    grandfather,    //老爷爷身体不适
    grandmother,    //老奶奶身体不适
    windowstrange,  //窗户异常开
    doorstrange,    //门异常开
    floorwet,       //地面潮湿
    falldown,       //成员跌倒
    gasleak        //煤气泄漏
}Incidentcode;


// 天气
typedef enum {
    Sunny,
    Cloudy, 
    Rainy, 
    Snowy
} Weather;

// 星期几
typedef enum {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
} Weekday;

//Todatdata今日参数
typedef struct {
    int year;
    int month;
    int day;
    Weekday weekday;
    Weather weather;
    int temperature;
} Todaydata;

//Windowstate窗户状态
typedef enum {
    WindowClose,
    WindowOpen
}Windowstate;

//临时把robot定义放这里，debug用
typedef struct
{
    RoomID inRoom;            //机器人现在在哪个房间
    RoomID toRoom;            //机器人将要移动到哪个房间，如果是NONE表示不移动到其他房间
    int x;                    //机器人在对应房间的位置的坐标
    int y;
    int width;
    int height;//包含完整机器人图形
    //int to_x;                 //机器人将要移动到哪里
    //int to_y;
    int battery;              //机器人还有百分之多少的电
    //Incidentcode incident;    //机器人现在正在干什么
} Robot;


#endif