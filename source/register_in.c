#include <allfunc.h>


void  register_in(int*page)//注册界面
{
	struct USER temp={0};//存储信息的用户结构体 
	char judge[10]="\0";//用于判断的密码 

	mouse_off(&mouse);
	delay(100);
	draw_basic();//绘制所有界面共同的基本元素

	puthz(630, 180, "家庭账号", 32, 27, 0xFFFFFF);
	//输入栏：注册家庭账号
	draw_commoninput(640, 275,"请输入您的账号");
	puthz(630, 340, "家庭密码", 32, 27, 0xFFFFFF);
	//输入栏：第一次输入密码
	draw_commoninput(640, 450,"请输入您的密码");
	puthz(630, 500, "确认密码", 32, 27, 0xFFFFFF);
	//输入栏：再次确认密码
	draw_commoninput(640, 592,"请再次输入您的密码");

	//绘制注册按钮
	draw_botton(720, 670, 940, 735,  0x2A52BE, 0x00477D);
	prt_hz16_size(790, 690, 2, 2, "注册", 0xffffff, "HZK\\HZK16s");
	//绘制返回登录按钮
	bar1(867, 610,1005, 648,0x2A52BE);
	bar2(867, 610,1005, 648,0x00477D);
	puthz(885, 620, "返回登录", 24, 24, 0xffffff);
	mouse_on(mouse);

	while (1)
	{
		mouse_show(&mouse);

		if (mouse_press(640, 225, 940, 265) == 1)//家庭账号输入栏
		{
			mouse_off(&mouse);
			strcpy(temp.name, "\0");
			bar1(640, 225, 940, 265, 0xffff);
			Getinfo(640, 225,temp.name,10,640, 225, 940, 265);
			mouse_on(mouse);
		}
		else if (mouse_press(640, 400, 950, 440) == 1)//家庭密码输入栏
		{
			mouse_off(&mouse);
			strcpy(temp.code, "\0");
			bar1(640, 400, 950, 440, 0xffff);
			Getcode(640,400,temp.code,10,640, 400, 950, 440);
			mouse_on(mouse);
		}
		else if (mouse_press(640, 542, 950, 580) == 1)//家庭密码确认栏
		{
			mouse_off(&mouse);
			strcpy(judge, "\0");
			bar1(640, 542, 950, 580, 0xffff);
			Getcode(640,542,judge,10,640, 542, 950, 580);
			mouse_on(mouse);
			//浮现成功按钮
		}

		if (mouse_press(720, 670, 940, 735) == 1)//点击注册
		{
			if(strcmp(temp.name,"\0")!=0)//用户名不为空 
			{
				if(strcmp(temp.code,"\0")!=0)//密码不为空 
				{
					if(!strcmp(temp.code,judge))//两次密码相同 
			        {
				      if(save_user(temp)==0)
                      {
                        *page=2;
				        break;
                      }
                      else
                      {
                        prt_hz24(640, 225,"用户名已被注册！",10,"HZK\\Hzk24h");
                        delay(1500);
				        bar1(640, 225, 940, 265,0xffff);
                      }
			        }
			        else
			        {
				      prt_hz24(640, 400,"两次密码不相同！",0,"HZK\\Hzk24h");
				      delay(1500);
				      bar1(640, 400, 950, 440,0xffff);
			        }  
				}
				else
				{
					prt_hz24(640, 400,"密码为空！",0,"HZK\\Hzk24h");
				    delay(1500);
				    bar1(640, 400, 950, 440,0xffff);
				}	
			}
			else
			{
				prt_hz24(640, 225,"用户名为空！",0,"HZK\\Hzk24h");
				delay(1500);
				bar1(640, 225, 940, 265,0xffff);
			}
		}
		if (mouse_press(867, 610,1013, 648) == 1)//返回登录界面
		{
			*page = 2;
			break;
		}
		

	}



}