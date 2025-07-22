#include <allfunc.h>

void main()
{      
	/*
	********************
	func对应页面值

	2-初始菜单，登录界面；
	3-注册界面；
	4-菜单界面
	5-健康监测；
	6-平面图；
	7-浇花；
	8-扫地；
	9-端茶倒水；
	10-开窗关窗；
	11-炒菜做饭；
	12-家庭服务；
	13-机器人日志界面；
	14-点餐；
	15-聊天功能；
	16-卧室
	17-平面图
	100-退出
	
	********************
	*/
	int page=2;
    int unum=0;
    FILE *file = NULL;


	//创建roomid文件
    file = fopen("Data\\roomid.dat", "wb");
    if (file == NULL) {
        perror("Failed to create roomid.dat file");
        return;
    }
    fclose(file);
	

    SetSVGA64k();//启动SVGA画图界面
	bar1(0, 0,1024,768, 0xffffff);
	Readbmp64k(0,0,"bmp\\logo4.bmp");
    mouse_init();


	finitialize_diary();//初始化日志，写入<struct Todaydata>
	initialize_fundation();//初始化基础数据，现在只有窗户状态，写入<winstate.dat>

	

    
	while(1)   
	{
		mouse_show(&mouse);
		switch (page)
		{
		
			case 2://登陆
			{
				log_in(&page,&unum);
				break;
			}
			case 3://注册
			{
				register_in(&page);
				break;
			}
			case 4://菜单界面
			{
				menu_on(&page);
				break;
			}
			case 5://健康检测
			{
				healthmonitor(&page);
				break;

			}
			case  7://浇花
			{
				wateranime(&page);
				break;
			}
			case  8://扫地
			{
				brushanime(&page);
				break;
			}
			case  9://端茶倒水
			{
				teaanime(&page);
				break;
			}
			case  10://开窗关窗
			{
				winanime(&page);
				break;
			}
			case  11://炒菜做饭
			{
				cook_meal(&page);
				break;
			}
			case  12://家庭服务
			{
				Familyhelp(&page);
				break;
			}
			case  13://机器人日志界面
			{
				diarywin(&page);
				break;
			}
			case  14://点餐
			{
				orderfood(&page);
				break;
			}
			case  15://聊天功能
			{
				chat_robot(&page);
				break;
			}
			case  16://卧室
			{
				in_bedroom(&page);
				break;
			}
			case 17://平面图
			{
				gamei(&page);
				break;
			}
			case 100:
			{
				exit(0);
				break;
			}
			
		}
	}
	CloseSVGA();//关闭图形界面 
}