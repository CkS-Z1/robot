#include <allfunc.h>


//1����ʼ��¼����
void log_in(int* page,int* unum)//��½����
{
	char name[10]="\0";		//temp_name
	char code[10]="\0";		//temp_code
    int i=-5;
	int privacy=0;//��˽�����Ƿ�ѡ

    UserList UL={0};//�����û���Ϣ�Ľṹ�壬δ������������Ū
	InitUList(&UL);
	ReadAllUser(&UL);

	mouse_off(&mouse);
	delay(100);

	Readbmp64k(0, 0, "bmp\\logo4.bmp"); //����ͼ��
	//draw_basic();//�������н��湲ͬ�Ļ���Ԫ��



	//��ť*3��ע�ᡢ��¼���˳���¼
	//��¼��ť
	draw_botton(730,520,900,580,0x00FF,0xDDDD);
	prt_hz16_size(780,535, 2, 2, "��¼", 0xFFFFFF, "HZK\\HZK16s");
	//ע�ᰴť
    bar1(570,700,780,740,0x0000FF);
	bar2(570,700,780,740,0x00477D);
	puthz(650,708,"ע��",24,24,0xFFFFFF);
	//�˳���ť
    bar1(800,700,1010,740,0x0000FF);
	bar2(800,700,1010,740,0x00477D);
	puthz(880,708,"�˳�",24,24,0xFFFFFF);


	
	//����������ͥ�˺�
	puthz(630, 200, "��ͥ�˺�", 32, 27, 0xFFFFFF);
	draw_commoninput(630,290,"�����������˺�"); 

	//����������ͥ����
	puthz(630, 390, "��ͥ����", 32, 27, 0xFFFFFF);
    draw_commoninput(630,480,"��������������"); 


	//��˽����
	prt_hz16_size(790,600, 1, 1, "���Ķ���ͬ�⡶ϵͳ��˽���ߡ�", 0x000000, "HZK\\HZK16s");
	bar2(755,598,775,618,0x704214);//ȷ�ϰ�ť
	Save_image(755,598,777,620,"privabt");//ȷ�ϰ�ť�Ŀհ�̬

	Line2(755,608,765,618,0xDEB887);
	Line2(765,618,775,598,0xDEB887);//��
	Save_image(755,598,777,620,"privaim");//ȷ�ϰ�ť�Ĵ�̬

	Load_image(755,598,777,620,"privabt");//��ԭȷ�ϰ�ť�Ŀհ�̬



	//������˽������ʾ����
	Save_image(650, 640, 1000, 700, "pritpbg");
	

	mouse_on(mouse);


	while(1)
    {
        mouse_show(&mouse);

		if(mouse_press(630, 240, 970, 290)==1)//��ͥ�˺�������
		{
			mouse_off(&mouse);
			strcpy(name,"\0");
			bar1(630, 240, 970, 280,0xffffff);
			Getinfo(630,240,name,10,630,240,970,290);
			mouse_on(mouse);
		}
		else if(mouse_press(630, 430, 970, 480)==1)//��ͥ����������
		{
			mouse_off(&mouse);
			strcpy(code,"\0");
			bar1(630, 430, 970, 470,0xffffff);
			Getinfo(630,430,code,10,630, 430, 970, 480);
			mouse_on(mouse);
		}
		else if(mouse_press(755,598,775,618)==1)//��˽����
		{
			if(privacy==0)
			{
				mouse_off(&mouse);
				privacy=1;
				Load_image(755,598,777,620,"privaim");//��
				delay(200);
				mouse_on(mouse);
			}	
			else if(privacy==1)
			{
				mouse_off(&mouse);
				privacy=0;
				Load_image(755,598,777,620,"privabt");//������
				delay(200);
				mouse_on(mouse); 
			}
		}
		else if(mouse_press(730, 520, 900, 580)==1)//�����¼
		{
			if(privacy==0)//ûȷ��
			{
				mouse_off(&mouse);
				prt_hz16_size(650, 640, 2, 2, "����ȷ����˽����", 0xFFFFFF, "HZK\\HZK16s");
				delay(2000);
				Load_image(650, 640, 1000, 700, "pritpbg");//������˽������ʾ����
				mouse_show(&mouse);
			}
			else if(privacy==1)
			{
				i=Check_info(UL,name,code);
            	if(i>=0)
				{
					*unum=i;
					DestroyUList(&UL);
					*page=4;      //����������
            		break;
				}
				if(i==-2)//����������� 
				{
					bar1(630, 430, 970, 470,0xffff);
					prt_hz24(635, 432,"�������",0,"HZK\\Hzk24h");
			    	delay(1500);
					bar1(630, 430, 970, 470,0xffff);
				}
				if(i==-3)//�û������� 
				{
					bar1(630, 240, 970, 280,0xffff);
					prt_hz24(635, 242,"�û������ڣ�",0,"HZK\\Hzk24h");
			    	delay(1500);
					bar1(630, 240, 970, 280,0xffff);
				} 
			}
			
		}
        else if(mouse_press(570,700,780,740)==1)//����ע��
        {
            *page=3;
            break;
        }
		else if(mouse_press(800,700,1010,740)==1)//�˳���ť
		{
			exit(0);
		}


    }


}



void draw_basic()//�������н��湲ͬ�Ļ���Ԫ��
{

	Readbmp64k(0, 0, "bmp\\logo4.bmp"); //����ͼ��

}



//����ť����
void draw_botton(int x1 ,int y1,int x2,int y2,int Cowercolor,int Bordercolor)
{
	Cirbar(x1,y1,x2,y2, Bordercolor);
	Cirbar(x1,y1+2,x2,y2-2, Cowercolor);
}

//������ͨ������
void draw_commoninput(int x1,int y1,char *s)
{
	prt_hz16_size(x1 + 16, y1 - 46, 2, 2, s, 0xBD32, "HZK\\HZK16s");
	Line_Thick(x1, y1, x1 + 380, y1, 1, 0xBD32 );
}

//����ȷ�ϰ�ť
void draw_confirmbotton(int x1,int y1,char *s)
{
	draw_botton(x1, y1, x1+236, y1+55, 0xFFFFFF, 0x00FF);
	puthz(x1+12,y1+4,s, 48,55, 0x000000);
}