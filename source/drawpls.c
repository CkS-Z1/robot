#include<allfunc.h>


void DrawEllipse(int xc, int yc, int a, int b, unsigned int color) 
{
    int x, y;
    double theta;
    
    // ���ò��������ƻ��ƾ���
    double step = 0.01;
    
    // �����Ƕȣ�������Բ�ϵĵ㲢����
    for (theta = 0; theta < 2 * 3.14159265358979323846; theta += step) {
        x = xc + (int)(a * cos(theta));
        y = yc + (int)(b * sin(theta));
        
        // ���û��㺯��������Բ�ϵĵ�
        Putpixel64k(x, y, color);
    }
}

void FillEllipse(int xc, int yc, int a, int b, unsigned int color)
 {
    int x, y;
    double theta;
    int i,j;
    // ���ò��������ƻ��ƾ���
    double step = 0.01;
    
    // �����Ƕȣ�������Բ�ϵĵ㲢���
    for (theta = 0; theta < 2 * 3.14159265358979323846; theta += step) {
        x = xc + (int)(a * cos(theta));
        y = yc + (int)(b * sin(theta));
        
        // ���ƴ���Բ���ĵ���ǰ���ˮƽ��
        for (i= xc; i <= x; i++) {
            Putpixel64k(i, y, color);
        }
        for (j = xc; j>= x; j--) {
            Putpixel64k(j, y, color);
        }
    }
}

void ThickDiagonalLine(int x1, int y1, int x2, int y2, int radius, unsigned int color)//����б��
{
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    // �������Խ����ϵĵ�
    while (1)
    {
        // �ڵ�ǰ�����һ��Բ��
        Circlefill(x1, y1, radius, color);

        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void Arc(int xc, int yc, int radius, int start_angle, int end_angle, unsigned int color)
{
    int x, y, d;
    int start_x, start_y, end_x, end_y;
    int i;

    // ������ʼ�ͽ����������
    start_x = xc + radius * cos(start_angle * PI / 180);
    start_y = yc + radius * sin(start_angle * PI / 180);
    end_x = xc + radius * cos(end_angle * PI / 180);
    end_y = yc + radius * sin(end_angle * PI / 180);

    // ����Բ������ʼ��
    Putpixel64k(start_x, start_y, color);

    // ����Բ��
    for (i = start_angle; i <= end_angle; i++)
    {
        x = xc + radius * cos(i * PI / 180);
        y = yc + radius * sin(i * PI / 180);
        Putpixel64k(x, y, color);
    }

    // ����Բ���Ľ�����
    Putpixel64k(end_x, end_y, color);
}


void FillArc(int xc, int yc, int radius, float startAngle, float endAngle, unsigned int color) 
{
    int x, y;
    float angle;
    float startRad;
    float endRad;
    // ȷ�������Ƕȴ�����ʼ�Ƕ�
    if (endAngle < startAngle) {
        endAngle += 360.0;
    }

    // ���Ƕ�ת��Ϊ����
    startRad = startAngle *PI / 180.0;
    endRad = endAngle * PI / 180.0;

    // �����������
    for (angle = startRad; angle <= endRad; angle += 0.01) {
        int i;
        // �����Ե��
        x = xc + (int)(radius * cos(angle));
        y = yc + (int)(radius * sin(angle));
        
        // ����Բ�ĵ���Ե������
        for (i = 0; i <= radius; i++) {
            int fillX = xc + (int)(i * cos(angle));
            int fillY = yc + (int)(i * sin(angle));
            Putpixel64k(fillX, fillY, color); // ʹ��64Kɫģʽ���Ƶ�
        }
    }
}
