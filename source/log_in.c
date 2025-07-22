#include <allfunc.h>


//1、初始登录界面
void log_in(int* page,int* unum)//登陆函数
{
	char name[10]="\0";		//temp_name
	char code[10]="\0";		//temp_code
    int i=-5;
	int privacy=0;//隐私政策是否勾选

    UserList UL={0};//储存用户信息的结构体，未来做好链表再弄
	InitUList(&UL);
	ReadAllUser(&UL);

	mouse_off(&mouse);
	delay(100);

	Readbmp64k(0, 0, "bmp\\logo4.bmp"); //加载图像
	//draw_basic();//绘制所有界面共同的基本元素



	//按钮*3：注册、登录、退出登录
	//登录按钮
	draw_botton(730,520,900,580,0x00FF,0xDDDD);
	prt_hz16_size(780,535, 2, 2, "登录", 0xFFFFFF, "HZK\\HZK16s");
	//注册按钮
    bar1(570,700,780,740,0x0000FF);
	bar2(570,700,780,740,0x00477D);
	puthz(650,708,"注册",24,24,0xFFFFFF);
	//退出按钮
    bar1(800,700,1010,740,0x0000FF);
	bar2(800,700,1010,740,0x00477D);
	puthz(880,708,"退出",24,24,0xFFFFFF);


	
	//输入栏：家庭账号
	puthz(630, 200, "家庭账号", 32, 27, 0xFFFFFF);
	draw_commoninput(630,290,"请输入您的账号"); 

	//输入栏：家庭密码
	puthz(630, 390, "家庭密码", 32, 27, 0xFFFFFF);
    draw_commoninput(630,480,"请输入您的密码"); 


	//隐私政策
	prt_hz16_size(790,600, 1, 1, "已阅读并同意《系统隐私政策》", 0x000000, "HZK\\HZK16s");
	bar2(755,598,775,618,0x704214);//确认按钮
	Save_image(755,598,777,620,"privabt");//确认按钮的空白态

	Line2(755,608,765,618,0xDEB887);
	Line2(765,618,775,598,0xDEB887);//打勾
	Save_image(755,598,777,620,"privaim");//确认按钮的打勾态

	Load_image(755,598,777,620,"privabt");//还原确认按钮的空白态



	//保存隐私政策提示背景
	Save_image(650, 640, 1000, 700, "pritpbg");
	

	mouse_on(mouse);


	while(1)
    {
        mouse_show(&mouse);

		if(mouse_press(630, 240, 970, 290)==1)//家庭账号输入栏
		{
			mouse_off(&mouse);
			strcpy(name,"\0");
			bar1(630, 240, 970, 280,0xffffff);
			Getinfo(630,240,name,10,630,240,970,290);
			mouse_on(mouse);
		}
		else if(mouse_press(630, 430, 970, 480)==1)//家庭密码输入栏
		{
			mouse_off(&mouse);
			strcpy(code,"\0");
			bar1(630, 430, 970, 470,0xffffff);
			Getinfo(630,430,code,10,630, 430, 970, 480);
			mouse_on(mouse);
		}
		else if(mouse_press(755,598,775,618)==1)//隐私政策
		{
			if(privacy==0)
			{
				mouse_off(&mouse);
				privacy=1;
				Load_image(755,598,777,620,"privaim");//打勾
				delay(200);
				mouse_on(mouse);
			}	
			else if(privacy==1)
			{
				mouse_off(&mouse);
				privacy=0;
				Load_image(755,598,777,620,"privabt");//擦除勾
				delay(200);
				mouse_on(mouse); 
			}
		}
		else if(mouse_press(730, 520, 900, 580)==1)//点击登录
		{
			if(privacy==0)//没确认
			{
				mouse_off(&mouse);
				prt_hz16_size(650, 640, 2, 2, "请先确认隐私政策", 0xFFFFFF, "HZK\\HZK16s");
				delay(2000);
				Load_image(650, 640, 1000, 700, "pritpbg");//擦除隐私政策提示背景
				mouse_show(&mouse);
			}
			else if(privacy==1)
			{
				i=Check_info(UL,name,code);
            	if(i>=0)
				{
					*unum=i;
					DestroyUList(&UL);
					*page=4;      //进入主界面
            		break;
				}
				if(i==-2)//密码输入错误 
				{
					bar1(630, 430, 970, 470,0xffff);
					prt_hz24(635, 432,"密码错误！",0,"HZK\\Hzk24h");
			    	delay(1500);
					bar1(630, 430, 970, 470,0xffff);
				}
				if(i==-3)//用户不存在 
				{
					bar1(630, 240, 970, 280,0xffff);
					prt_hz24(635, 242,"用户不存在！",0,"HZK\\Hzk24h");
			    	delay(1500);
					bar1(630, 240, 970, 280,0xffff);
				} 
			}
			
		}
        else if(mouse_press(570,700,780,740)==1)//进入注册
        {
            *page=3;
            break;
        }
		else if(mouse_press(800,700,1010,740)==1)//退出按钮
		{
			exit(0);
		}


    }


}



void draw_basic()//绘制所有界面共同的基本元素
{

	Readbmp64k(0, 0, "bmp\\logo4.bmp"); //加载图像

}



//画按钮函数
void draw_botton(int x1 ,int y1,int x2,int y2,int Cowercolor,int Bordercolor)
{
	Cirbar(x1,y1,x2,y2, Bordercolor);
	Cirbar(x1,y1+2,x2,y2-2, Cowercolor);
}

//画出普通输入栏
void draw_commoninput(int x1,int y1,char *s)
{
	prt_hz16_size(x1 + 16, y1 - 46, 2, 2, s, 0xBD32, "HZK\\HZK16s");
	Line_Thick(x1, y1, x1 + 380, y1, 1, 0xBD32 );
}

//画出确认按钮
void draw_confirmbotton(int x1,int y1,char *s)
{
	draw_botton(x1, y1, x1+236, y1+55, 0xFFFFFF, 0x00FF);
	puthz(x1+12,y1+4,s, 48,55, 0x000000);
}