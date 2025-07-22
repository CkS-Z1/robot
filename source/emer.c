#include<allfunc.h>


// 突发状况检测函数
void emergency1();
void emergency2();
void emergency3();
void emergency4();
void emergency5();
void watchov(int *page);

// 成员摔倒突发状况处理
void emergency1()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // 白色背景
   Readbmp64k(500,400,"bmp\\dao.bmp");  
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // 红线标题分割线
   puthz(100, 200, "检测到成员摔倒", 48, 48, 0x000000); // 红色文字
   puthz(100, 300, "正在处理并回来", 48, 48, 0x000000);
   delay(5000); // 显示5秒
}

// 地上有水突发状况处理
void emergency2()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // 白色背景
   Readbmp64k(500,400,"bmp\\sa.bmp"); 
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // 红线标题分割线
   puthz(100, 200, "检测到地上有水", 48, 48, 0x000000); 
   puthz(100, 300, "正在处理并回来", 48, 48, 0x000000);
   delay(5000); // 显示5秒
}

// 煤气泄漏突发状况处理
void emergency3()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // 白色背景
   Readbmp64k(500,400,"bmp\\mei.bmp"); 
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // 红线标题分割线
   puthz(100, 200, "检测到煤气泄漏", 48, 48, 0x000000); // 红色文字
   puthz(100, 300, "正在处理并回来", 48, 48, 0x000000);
   delay(5000); // 显示5秒
}

void emergency4()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // 白色背景
   Readbmp64k(500,400,"bmp\\huo.bmp");
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // 红线标题分割线
   puthz(100, 200, "检测到火灾报警", 48, 48, 0x000000);
   puthz(100, 300, "正在处理并回来", 48, 48, 0x000000);
   delay(5000);
}


void emergency5()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // 白色背景
   Readbmp64k(500,400,"bmp\\gu.bmp");
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // 红线标题分割线
   puthz(100, 200, "检测到电源故障", 48, 48, 0x000000);
   puthz(100, 300, "正在处理并回来", 48, 48, 0x000000);
   delay(5000);
}



void watchov(int *page) 
{
   RoomID roomid = 0;
   Incidentcode incidentcode;
   struct tm eventtime;

   int a = rand() % 1000; 

   if( a>=0 && a<=4 )
   {
      Save_image(0, 0, 1024, 768, "floorim"); // 保存平面图
      mouse_off(&mouse); // 隐藏鼠标

      if (a == 0) 
      {
         incidentcode = falldown;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency1(); // 成员摔倒
      
      } 
      else if (a == 1) 
      {
         incidentcode = floorwet;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency2(); // 地上有水

      } 
      else if (a == 2) 
      {
         incidentcode = gasleak;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency3(); // 煤气泄漏
      
      } 
      else if (a == 3) 
      {
         incidentcode = firealarm;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency4(); // 火灾报警
      } 
      else if (a == 4) 
      {
         incidentcode = electricity;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency5(); // 电源故障   
      }

      Load_image(0, 0, 1024, 768, "floorim"); // 重新加载平面图
      mouse_show(&mouse); // 显示鼠标
   }
   
 
}