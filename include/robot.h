#ifndef ROBOT_H
#define ROBOT_H
#include "allfunc.h"


// typedef struct Robot
// {
//     RoomID inRoom;            //�������������ĸ�����
//     RoomID toRoom;            //�����˽�Ҫ�ƶ����ĸ����䣬�����NONE��ʾ���ƶ�����������
//     int x;                    //�������ڶ�Ӧ�����λ�õ�����
//     int y;
//     int width;
//     int height;//��������������ͼ��
//     //int to_x;                 //�����˽�Ҫ�ƶ�������
//     //int to_y;
//     int battery;              //�����˻��аٷ�֮���ٵĵ�
//     //Incidentcode incident;    //�������������ڸ�ʲô
// } Robot;


void robot_set(Robot* Rob);
void Save_image(int x1, int y1, int x2, int y2, char *bmpname);
void Load_image(int x1, int y1, int x2, int y2, char *bmpname);
Robot init_robot();
void robot_uphand(Robot *Rob);


/*
Baseimages �����û���ͼ��
���ֶ�����Ҫ�õ��Ļ���Baseimage���ļ�·�����n����Ӧ"C://cks//bmp//baseimage(n).dat"
typedef enum
{
    Robotimage = 0,//������ͼ��

    pan = 1,  //�洢����ͼ�����ڲ���������
    dish,     //�洢���õĲ˺Ͳ���
    plate,    //�洢����
    emptycup, //�洢��ˮ��
    fullcup,  //�洢��ˮ��
    boiler,   //�洢��ˮ��
    flowercan //�洢����

} Baseimages;
*/



#endif