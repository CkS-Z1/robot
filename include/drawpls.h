#ifndef __login_H
#define __login_H
#define PI 3.14159265358979323846
#include<allfunc.h>
void DrawEllipse(int xc, int yc, int a, int b, unsigned int color);//����Բ�����
void FillEllipse(int xc, int yc, int a, int b, unsigned int color);//����Բ�����ɫ
void ThickDiagonalLine(int x1, int y1, int x2, int y2, int radius, unsigned int color);//����б��
void Arc(int xc, int yc, int radius, int start_angle, int end_angle, unsigned int color);//��������
void FillArc(int xc, int yc, int radius, float startAngle, float endAngle, unsigned int color) ;
#endif