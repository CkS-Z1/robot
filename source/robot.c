#include "robot.h"

void robot_set(Robot* Rob);
void Save_image(int x1, int y1, int x2, int y2, char *bmpname);
void Load_image(int x1, int y1, int x2, int y2, char *bmpname);
Robot init_robot();
void robot_uphand(Robot *Rob);


// ����robot
void robot_set(Robot* Rob) 
{
    // �����õĻ�׼����
    int base_x = Rob->x + 62;  // ��̬��׼��X
    int base_y = Rob->y + 24;  // ��̬��׼��Y

    //��ͷ
    Line1(base_x, base_y, base_x + 90, base_y, 0x000000);
    Arc(base_x + 45, base_y, 20, 180.0, 360.0, 0x000000);
    Arc(base_x, base_y + 30, 30, 180.0, 270.0, 0x000000);
    Arc(base_x + 90, base_y + 30, 30, -90.0, 0.0, 0x000000);
    Line1(base_x - 30, base_y + 30, base_x - 30, base_y + 81, 0x000000);
    Line1(base_x + 120, base_y + 30, base_x + 120, base_y + 81, 0x000000);
    Arc(base_x + 120, base_y + 56, 24, -90.0, 90.0, 0x000000);
    Arc(base_x - 30, base_y + 56, 24, 90.0, 270.0, 0x000000);
    Arc(base_x, base_y + 81, 30, 90.0, 180.0, 0x000000);
    Arc(base_x + 90, base_y + 81, 30, 0.0, 90.0, 0x000000);
    Line1(base_x, base_y + 111, base_x + 90, base_y + 111, 0x000000);
    Line1(base_x + 20, base_y + 35, base_x + 70, base_y + 35, 0x000000);
    Line1(base_x + 20, base_y + 86, base_x + 70, base_y + 86, 0x000000);
    Arc(base_x + 20, base_y + 55, 20, 180.0, 270.0, 0x000000);
    Arc(base_x + 70, base_y + 55, 20, -90.0, 0.0, 0x000000);
    
    //����
    Line1(base_x, base_y + 55, base_x, base_y + 66, 0x000000);
    Line1(base_x + 90, base_y + 55, base_x + 90, base_y + 66, 0x000000);
    Arc(base_x + 20, base_y + 66, 20, 90.0, 180.0, 0x000000);
    Arc(base_x + 70, base_y + 66, 20, 0.0, 90.0, 0x000000);
    Circlefill(base_x + 18, base_y + 56, 5, 0x000000);
    Circlefill(base_x + 78, base_y + 56, 5, 0x000000);
    Arc(base_x + 47, base_y + 56, 18, 30.0, 150.0, 0x000000);
    Line1(base_x - 48, base_y + 41, base_x - 48, base_y + 73, 0x000000);
    Line1(base_x - 39, base_y + 34, base_x - 39, base_y + 79, 0x000000);
    Line1(base_x + 127, base_y + 34, base_x + 127, base_y + 79, 0x000000);
    Line1(base_x + 136, base_y + 41, base_x + 136, base_y + 73, 0x000000);
    
    //����
    Line1(base_x - 11, base_y + 112, base_x - 11, base_y + 203, 0x000000);
    Line1(base_x + 101, base_y + 112, base_x + 101, base_y + 203, 0x000000);
    Line1(base_x - 11, base_y + 203, base_x + 101, base_y + 203, 0x000000);
    Line1(base_x + 8, base_y + 151, base_x + 8, base_y + 203, 0x000000);
    Line1(base_x + 80, base_y + 151, base_x + 80, base_y + 203, 0x000000);
    Arc(base_x + 44, base_y + 151, 36, 180.0, 360.0, 0x000000);
    Line1(base_x + 44, base_y + 133, base_x + 44, base_y + 148, 0x4D1F00);
    Arc(base_x + 44, base_y + 144, 8, -60.0, 240.0, 0x4D1F00);
    Line1(base_x + 8, base_y + 186, base_x + 80, base_y + 186, 0x000000);
    Line1(base_x + 8, base_y + 166, base_x + 80, base_y + 166, 0x000000);
    
    //��
    Line1(base_x + 4, base_y + 203, base_x + 4, base_y + 223, 0x000000);
    Line1(base_x + 24, base_y + 203, base_x + 24, base_y + 223, 0x000000);
    Line1(base_x + 73, base_y + 203, base_x + 73, base_y + 223, 0x000000);
    Line1(base_x + 93, base_y + 203, base_x + 93, base_y + 223, 0x000000);
    Arc(base_x + 14, base_y + 236, 15, 180.0, 360.0, 0x000000);
    Arc(base_x + 83, base_y + 236, 15, 180.0, 360.0, 0x000000);
    Line1(base_x - 1, base_y + 236, base_x + 29, base_y + 236, 0x000000);
    Line1(base_x + 68, base_y + 236, base_x + 98, base_y + 236, 0x000000);
    
    //�ֱ�
    Arc(base_x + 72, base_y + 206, 110, 190.0, 220.0, 0x000000);
    Arc(base_x + 119, base_y + 231, 175, 196.0, 220.0, 0x000000);
    Arc(base_x + 25, base_y + 221, 110, -45.0, -18.0, 0x000000);
    Arc(base_x - 20, base_y + 250, 175, -45.0, -22.0, 0x000000);
    Circle(base_x - 46, base_y + 195, 12, 0x000000);
    Circle(base_x + 138, base_y + 195, 12, 0x000000);
}



// ������۾��Ŷ����Ļ����ˣ�δ��ɣ�
void robot_uphand(Robot *Rob) 
{
    // �����õĻ�׼����
   int base_x = Rob->x + 62;  // ��̬��׼��X
   int base_y = Rob->y + 24;  // ��̬��׼��Y

    //��ͷ
    Line1(base_x, base_y, base_x + 90, base_y, 0x000000);
    Arc(base_x + 45, base_y, 20, 180.0, 360.0, 0x000000);
    Arc(base_x, base_y + 30, 30, 180.0, 270.0, 0x000000);
    Arc(base_x + 90, base_y + 30, 30, -90.0, 0.0, 0x000000);
    Line1(base_x - 30, base_y + 30, base_x - 30, base_y + 81, 0x000000);
    Line1(base_x + 120, base_y + 30, base_x + 120, base_y + 81, 0x000000);
    Arc(base_x + 120, base_y + 56, 24, -90.0, 90.0, 0x000000);
    Arc(base_x - 30, base_y + 56, 24, 90.0, 270.0, 0x000000);
    Arc(base_x, base_y + 81, 30, 90.0, 180.0, 0x000000);
    Arc(base_x + 90, base_y + 81, 30, 0.0, 90.0, 0x000000);
    Line1(base_x, base_y + 111, base_x + 90, base_y + 111, 0x000000);
    Line1(base_x + 20, base_y + 35, base_x + 70, base_y + 35, 0x000000);
    Line1(base_x + 20, base_y + 86, base_x + 70, base_y + 86, 0x000000);
    Arc(base_x + 20, base_y + 55, 20, 180.0, 270.0, 0x000000);
    Arc(base_x + 70, base_y + 55, 20, -90.0, 0.0, 0x000000);
    
    //����
    Line1(base_x, base_y + 55, base_x, base_y + 66, 0x000000);
    Line1(base_x + 90, base_y + 55, base_x + 90, base_y + 66, 0x000000);
    Arc(base_x + 20, base_y + 66, 20, 90.0, 180.0, 0x000000);
    Arc(base_x + 70, base_y + 66, 20, 0.0, 90.0, 0x000000);
    Circlefill(base_x + 18, base_y + 56, 5, 0x000000);
    Circlefill(base_x + 78, base_y + 56, 5, 0x000000);
    Arc(base_x + 47, base_y + 56, 18, 30.0, 150.0, 0x000000);
    Line1(base_x - 48, base_y + 41, base_x - 48, base_y + 73, 0x000000);
    Line1(base_x - 39, base_y + 34, base_x - 39, base_y + 79, 0x000000);
    Line1(base_x + 127, base_y + 34, base_x + 127, base_y + 79, 0x000000);
    Line1(base_x + 136, base_y + 41, base_x + 136, base_y + 73, 0x000000);
    
    //����
    Line1(base_x - 11, base_y + 112, base_x - 11, base_y + 203, 0x000000);
    Line1(base_x + 101, base_y + 112, base_x + 101, base_y + 203, 0x000000);
    Line1(base_x - 11, base_y + 203, base_x + 101, base_y + 203, 0x000000);
    Line1(base_x + 8, base_y + 151, base_x + 8, base_y + 203, 0x000000);
    Line1(base_x + 80, base_y + 151, base_x + 80, base_y + 203, 0x000000);
    Arc(base_x + 44, base_y + 151, 36, 180.0, 360.0, 0x000000);
    Line1(base_x + 44, base_y + 133, base_x + 44, base_y + 148, 0x4D1F00);
    Arc(base_x + 44, base_y + 144, 8, -60.0, 240.0, 0x4D1F00);
    Line1(base_x + 8, base_y + 186, base_x + 80, base_y + 186, 0x000000);
    Line1(base_x + 8, base_y + 166, base_x + 80, base_y + 166, 0x000000);
    
    //��
    Line1(base_x + 4, base_y + 203, base_x + 4, base_y + 223, 0x000000);
    Line1(base_x + 24, base_y + 203, base_x + 24, base_y + 223, 0x000000);
    Line1(base_x + 73, base_y + 203, base_x + 73, base_y + 223, 0x000000);
    Line1(base_x + 93, base_y + 203, base_x + 93, base_y + 223, 0x000000);
    Arc(base_x + 14, base_y + 236, 15, 180.0, 360.0, 0x000000);
    Arc(base_x + 83, base_y + 236, 15, 180.0, 360.0, 0x000000);
    Line1(base_x - 1, base_y + 236, base_x + 29, base_y + 236, 0x000000);
    Line1(base_x + 68, base_y + 236, base_x + 98, base_y + 236, 0x000000);
    
    //�ֱ�
    Arc(base_x + 30, base_y , 130, 110.0, 140.0, 0x000000);
    Arc(base_x + 45, base_y-26, 175, 110.0, 140.0, 0x000000);
    Arc(base_x + 25, base_y + 221, 110, -45.0, -18.0, 0x000000);
    Arc(base_x - 20, base_y + 250, 175, -45.0, -22.0, 0x000000);
    Circle(base_x - 83, base_y + 75, 12, 0x000000);
    Circle(base_x + 138, base_y + 195, 12, 0x000000);
}




//������д�Ĵ桢��bmp������ע�ⲻҪ��SVGA�ģ�·����ͬ��
//�������ͼ��,ע��bmpnameС��8�ַ�
void Save_image(int x1, int y1, int x2, int y2, char *bmpname)
{
	int i = 0, j = 0;
	int height = y2 - y1, width = x2 - x1;
	int color = 0;
	char f[50];
	FILE *fp = NULL;

	sprintf(f,"bmp\\%s.dat",bmpname);
	
	fp = fopen(f, "wb");
	if (fp == NULL)
	{
        perror("�޷��򿪸� baseimage �ļ�");
		exit(1);
	}
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			color = Getpixel64k(x1 + j, y1 + i);
			fwrite(&color, sizeof(int), 1, fp);
		}
	}
	fclose(fp);
	
}

//�������ͼ��
void Load_image(int x1, int y1, int x2, int y2, char *bmpname)
{
	int i = 0, j = 0;
	int height = y2 - y1, width = x2 - x1;
	int color = 0;
	char f[50];
	FILE *fp = NULL;

	sprintf(f,"bmp\\%s.dat",bmpname);

    fp = fopen(f, "rb");
	if (fp == NULL)
	{
		perror("�޸� baseimage �洢·��");
        exit(1);
	}
	else
	{
		for (i = 0; i<height; i++)
		{
			for (j = 0; j<width; j++)
			{
				fread(&color, sizeof(int), 1, fp);
				Putpixel64k(x1 + j, y1 + i, color);
			}
		}
		fclose(fp);
	}
}


//��ʼ����Robot rob����ֵ,����ֵΪһ��Robot���͵Ľṹ��
Robot init_robot()
{
    Robot rob;
    rob.inRoom = NONE;
    rob.toRoom = NONE;
    rob.x = 0;
    rob.y = 0;
    rob.width = 215;
    rob.height = 270;//��������������ͼ��
    //rob.to_x = 0;
    //rob.to_y = 0;
    rob.battery = 100;//��û�ϲ�����ǰ���ȸ���100

    return rob;
}