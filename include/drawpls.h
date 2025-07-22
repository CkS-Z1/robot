#ifndef __login_H
#define __login_H
#define PI 3.14159265358979323846
#include<allfunc.h>
void DrawEllipse(int xc, int yc, int a, int b, unsigned int color);//»­ÍÖÔ²²»Ìî³ä
void FillEllipse(int xc, int yc, int a, int b, unsigned int color);//»­ÍÖÔ²Ìî³äÑÕÉ«
void ThickDiagonalLine(int x1, int y1, int x2, int y2, int radius, unsigned int color);//»­´ÖĞ±Ïß
void Arc(int xc, int yc, int radius, int start_angle, int end_angle, unsigned int color);//»­»¡º¯Êı
void FillArc(int xc, int yc, int radius, float startAngle, float endAngle, unsigned int color) ;
#endif