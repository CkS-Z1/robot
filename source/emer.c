#include<allfunc.h>


// ͻ��״����⺯��
void emergency1();
void emergency2();
void emergency3();
void emergency4();
void emergency5();
void watchov(int *page);

// ��Աˤ��ͻ��״������
void emergency1()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // ��ɫ����
   Readbmp64k(500,400,"bmp\\dao.bmp");  
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // ���߱���ָ���
   puthz(100, 200, "��⵽��Աˤ��", 48, 48, 0x000000); // ��ɫ����
   puthz(100, 300, "���ڴ�������", 48, 48, 0x000000);
   delay(5000); // ��ʾ5��
}

// ������ˮͻ��״������
void emergency2()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // ��ɫ����
   Readbmp64k(500,400,"bmp\\sa.bmp"); 
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // ���߱���ָ���
   puthz(100, 200, "��⵽������ˮ", 48, 48, 0x000000); 
   puthz(100, 300, "���ڴ�������", 48, 48, 0x000000);
   delay(5000); // ��ʾ5��
}

// ú��й©ͻ��״������
void emergency3()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // ��ɫ����
   Readbmp64k(500,400,"bmp\\mei.bmp"); 
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // ���߱���ָ���
   puthz(100, 200, "��⵽ú��й©", 48, 48, 0x000000); // ��ɫ����
   puthz(100, 300, "���ڴ�������", 48, 48, 0x000000);
   delay(5000); // ��ʾ5��
}

void emergency4()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // ��ɫ����
   Readbmp64k(500,400,"bmp\\huo.bmp");
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // ���߱���ָ���
   puthz(100, 200, "��⵽���ֱ���", 48, 48, 0x000000);
   puthz(100, 300, "���ڴ�������", 48, 48, 0x000000);
   delay(5000);
}


void emergency5()
{
   bar1(0, 0, 1024, 768, 0xFFFFFF); // ��ɫ����
   Readbmp64k(500,400,"bmp\\gu.bmp");
   ThickDiagonalLine(100, 100, 924, 100,2, 0xC0C0C0); // ���߱���ָ���
   puthz(100, 200, "��⵽��Դ����", 48, 48, 0x000000);
   puthz(100, 300, "���ڴ�������", 48, 48, 0x000000);
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
      Save_image(0, 0, 1024, 768, "floorim"); // ����ƽ��ͼ
      mouse_off(&mouse); // �������

      if (a == 0) 
      {
         incidentcode = falldown;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency1(); // ��Աˤ��
      
      } 
      else if (a == 1) 
      {
         incidentcode = floorwet;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency2(); // ������ˮ

      } 
      else if (a == 2) 
      {
         incidentcode = gasleak;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency3(); // ú��й©
      
      } 
      else if (a == 3) 
      {
         incidentcode = firealarm;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency4(); // ���ֱ���
      } 
      else if (a == 4) 
      {
         incidentcode = electricity;
         fstart_diary(&incidentcode, &eventtime);
         fend_diary(&incidentcode, &eventtime);
         emergency5(); // ��Դ����   
      }

      Load_image(0, 0, 1024, 768, "floorim"); // ���¼���ƽ��ͼ
      mouse_show(&mouse); // ��ʾ���
   }
   
 
}