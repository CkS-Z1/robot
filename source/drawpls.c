#include<allfunc.h>


void DrawEllipse(int xc, int yc, int a, int b, unsigned int color) 
{
    int x, y;
    double theta;
    
    // 设置步长，控制绘制精度
    double step = 0.01;
    
    // 遍历角度，计算椭圆上的点并绘制
    for (theta = 0; theta < 2 * 3.14159265358979323846; theta += step) {
        x = xc + (int)(a * cos(theta));
        y = yc + (int)(b * sin(theta));
        
        // 调用画点函数绘制椭圆上的点
        Putpixel64k(x, y, color);
    }
}

void FillEllipse(int xc, int yc, int a, int b, unsigned int color)
 {
    int x, y;
    double theta;
    int i,j;
    // 设置步长，控制绘制精度
    double step = 0.01;
    
    // 遍历角度，计算椭圆上的点并填充
    for (theta = 0; theta < 2 * 3.14159265358979323846; theta += step) {
        x = xc + (int)(a * cos(theta));
        y = yc + (int)(b * sin(theta));
        
        // 绘制从椭圆中心到当前点的水平线
        for (i= xc; i <= x; i++) {
            Putpixel64k(i, y, color);
        }
        for (j = xc; j>= x; j--) {
            Putpixel64k(j, y, color);
        }
    }
}

void ThickDiagonalLine(int x1, int y1, int x2, int y2, int radius, unsigned int color)//画粗斜线
{
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    // 绘制主对角线上的点
    while (1)
    {
        // 在当前点绘制一个圆形
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

    // 计算起始和结束点的坐标
    start_x = xc + radius * cos(start_angle * PI / 180);
    start_y = yc + radius * sin(start_angle * PI / 180);
    end_x = xc + radius * cos(end_angle * PI / 180);
    end_y = yc + radius * sin(end_angle * PI / 180);

    // 绘制圆弧的起始点
    Putpixel64k(start_x, start_y, color);

    // 绘制圆弧
    for (i = start_angle; i <= end_angle; i++)
    {
        x = xc + radius * cos(i * PI / 180);
        y = yc + radius * sin(i * PI / 180);
        Putpixel64k(x, y, color);
    }

    // 绘制圆弧的结束点
    Putpixel64k(end_x, end_y, color);
}


void FillArc(int xc, int yc, int radius, float startAngle, float endAngle, unsigned int color) 
{
    int x, y;
    float angle;
    float startRad;
    float endRad;
    // 确保结束角度大于起始角度
    if (endAngle < startAngle) {
        endAngle += 360.0;
    }

    // 将角度转换为弧度
    startRad = startAngle *PI / 180.0;
    endRad = endAngle * PI / 180.0;

    // 填充扇形区域
    for (angle = startRad; angle <= endRad; angle += 0.01) {
        int i;
        // 计算边缘点
        x = xc + (int)(radius * cos(angle));
        y = yc + (int)(radius * sin(angle));
        
        // 填充从圆心到边缘的像素
        for (i = 0; i <= radius; i++) {
            int fillX = xc + (int)(i * cos(angle));
            int fillY = yc + (int)(i * sin(angle));
            Putpixel64k(fillX, fillY, color); // 使用64K色模式绘制点
        }
    }
}
