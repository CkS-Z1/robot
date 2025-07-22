/*
 * @Author: WTY
 * @Date:
 * @Description: ȫ�ֵ�һЩ���壬��������
 */
#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

//��������
typedef enum
{
    false_0,
    true_0
} global_0;

//���屨����Ϣ���� SHOW_ERROR and SHOW_WARNING
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

//������
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


//incidentcode�¼�����
typedef enum{
    light_on=1,     //����
    light_off,      //�ص�
    window_on,      //����
    window_off,     //�ش�
    door_off,       //����
    cook,           //����
    cleanup,        //��ɨ
    boilwater,      //��ˮ��ˮ
    plants,         //����
    battery,        //���
    //emergency
    firealarm=11,  //���ֱ���
    electricity,    //��Դ����
    grandfather,    //��үү���岻��
    grandmother,    //���������岻��
    windowstrange,  //�����쳣��
    doorstrange,    //���쳣��
    floorwet,       //���泱ʪ
    falldown,       //��Ա����
    gasleak        //ú��й©
}Incidentcode;


// ����
typedef enum {
    Sunny,
    Cloudy, 
    Rainy, 
    Snowy
} Weather;

// ���ڼ�
typedef enum {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
} Weekday;

//Todatdata���ղ���
typedef struct {
    int year;
    int month;
    int day;
    Weekday weekday;
    Weather weather;
    int temperature;
} Todaydata;

//Windowstate����״̬
typedef enum {
    WindowClose,
    WindowOpen
}Windowstate;

//��ʱ��robot��������debug��
typedef struct
{
    RoomID inRoom;            //�������������ĸ�����
    RoomID toRoom;            //�����˽�Ҫ�ƶ����ĸ����䣬�����NONE��ʾ���ƶ�����������
    int x;                    //�������ڶ�Ӧ�����λ�õ�����
    int y;
    int width;
    int height;//��������������ͼ��
    //int to_x;                 //�����˽�Ҫ�ƶ�������
    //int to_y;
    int battery;              //�����˻��аٷ�֮���ٵĵ�
    //Incidentcode incident;    //�������������ڸ�ʲô
} Robot;


#endif