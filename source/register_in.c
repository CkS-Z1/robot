#include <allfunc.h>


void  register_in(int*page)//ע�����
{
	struct USER temp={0};//�洢��Ϣ���û��ṹ�� 
	char judge[10]="\0";//�����жϵ����� 

	mouse_off(&mouse);
	delay(100);
	draw_basic();//�������н��湲ͬ�Ļ���Ԫ��

	puthz(630, 180, "��ͥ�˺�", 32, 27, 0xFFFFFF);
	//��������ע���ͥ�˺�
	draw_commoninput(640, 275,"�����������˺�");
	puthz(630, 340, "��ͥ����", 32, 27, 0xFFFFFF);
	//����������һ����������
	draw_commoninput(640, 450,"��������������");
	puthz(630, 500, "ȷ������", 32, 27, 0xFFFFFF);
	//���������ٴ�ȷ������
	draw_commoninput(640, 592,"���ٴ�������������");

	//����ע�ᰴť
	draw_botton(720, 670, 940, 735,  0x2A52BE, 0x00477D);
	prt_hz16_size(790, 690, 2, 2, "ע��", 0xffffff, "HZK\\HZK16s");
	//���Ʒ��ص�¼��ť
	bar1(867, 610,1005, 648,0x2A52BE);
	bar2(867, 610,1005, 648,0x00477D);
	puthz(885, 620, "���ص�¼", 24, 24, 0xffffff);
	mouse_on(mouse);

	while (1)
	{
		mouse_show(&mouse);

		if (mouse_press(640, 225, 940, 265) == 1)//��ͥ�˺�������
		{
			mouse_off(&mouse);
			strcpy(temp.name, "\0");
			bar1(640, 225, 940, 265, 0xffff);
			Getinfo(640, 225,temp.name,10,640, 225, 940, 265);
			mouse_on(mouse);
		}
		else if (mouse_press(640, 400, 950, 440) == 1)//��ͥ����������
		{
			mouse_off(&mouse);
			strcpy(temp.code, "\0");
			bar1(640, 400, 950, 440, 0xffff);
			Getcode(640,400,temp.code,10,640, 400, 950, 440);
			mouse_on(mouse);
		}
		else if (mouse_press(640, 542, 950, 580) == 1)//��ͥ����ȷ����
		{
			mouse_off(&mouse);
			strcpy(judge, "\0");
			bar1(640, 542, 950, 580, 0xffff);
			Getcode(640,542,judge,10,640, 542, 950, 580);
			mouse_on(mouse);
			//���ֳɹ���ť
		}

		if (mouse_press(720, 670, 940, 735) == 1)//���ע��
		{
			if(strcmp(temp.name,"\0")!=0)//�û�����Ϊ�� 
			{
				if(strcmp(temp.code,"\0")!=0)//���벻Ϊ�� 
				{
					if(!strcmp(temp.code,judge))//����������ͬ 
			        {
				      if(save_user(temp)==0)
                      {
                        *page=2;
				        break;
                      }
                      else
                      {
                        prt_hz24(640, 225,"�û����ѱ�ע�ᣡ",10,"HZK\\Hzk24h");
                        delay(1500);
				        bar1(640, 225, 940, 265,0xffff);
                      }
			        }
			        else
			        {
				      prt_hz24(640, 400,"�������벻��ͬ��",0,"HZK\\Hzk24h");
				      delay(1500);
				      bar1(640, 400, 950, 440,0xffff);
			        }  
				}
				else
				{
					prt_hz24(640, 400,"����Ϊ�գ�",0,"HZK\\Hzk24h");
				    delay(1500);
				    bar1(640, 400, 950, 440,0xffff);
				}	
			}
			else
			{
				prt_hz24(640, 225,"�û���Ϊ�գ�",0,"HZK\\Hzk24h");
				delay(1500);
				bar1(640, 225, 940, 265,0xffff);
			}
		}
		if (mouse_press(867, 610,1013, 648) == 1)//���ص�¼����
		{
			*page = 2;
			break;
		}
		

	}



}