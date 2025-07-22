#include <allfunc.h>
void  Familyhelp(int *page);
void  Familyhelp(int *page)
{
    mouse_off(&mouse);
    bar1(0, 0, 1024, 768, 0x5686BF);
    bar1(35, 32, 989, 744, 0xFFFFFF);
    ThickDiagonalLine(35,32,989,32,2,0x003399);
    ThickDiagonalLine(35,32,35,744,2,0x003399);
    ThickDiagonalLine(35,744,989,744,2,0x003399);
    ThickDiagonalLine(989,32,989,744,2,0x003399); 

  
   //浇花按钮
   Readbmp64k(323,75, "bmp\\pen.bmp");
   draw_botton(290,188,490,258,0x002FA7,0xDDDD);  
   prt_hz16_size(331,194, 3, 3, "浇花", 0xFFFFFF, "HZK\\HZK16s"); 
   
   //扫地按钮
   Readbmp64k(624,75, "bmp\\sao.bmp");
   draw_botton(599,188,799,258,0x002FA7,0xDDDD);  
   prt_hz16_size(650,194, 3, 3, "扫地", 0xFFFFFF, "HZK\\HZK16s");
   //端茶倒水按钮
   Readbmp64k(160,300, "bmp\\shui.bmp");
   draw_botton(147,408,347,478,0x002FA7,0xDDDD);  
   prt_hz16_size(160,414, 3, 3, "端茶倒水", 0xFFFFFF, "HZK\\HZK16s"); 
   //开窗关窗按钮
    Readbmp64k(463,300, "bmp\\chuang.bmp");
   draw_botton(436,408,636,478,0x002FA7,0xDDDD);  
   prt_hz16_size(442,414, 3, 3, "开窗关窗", 0xFFFFFF, "HZK\\HZK16s");
   //炒菜做饭按钮
    Readbmp64k(748,300, "bmp\\fan.bmp");
   draw_botton(742,408,902,478,0x002FA7,0xDDDD);  
   prt_hz16_size(730,414, 3, 3, "炒菜做饭", 0xFFFFFF, "HZK\\HZK16s"); 
   //返回按钮
   draw_botton(866,686,958,734,0x002FA7,0xDDDD);  
   prt_hz16_size(880,695, 2, 2, "返回", 0xFFFFFF, "HZK\\HZK16s"); 

   mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(290,188,490,258)==1)//浇花按钮
        {
            *page=7;
            wateranime(page);
            break;
        }
        else  if(mouse_press(599,188,799,258)==1)//扫地按钮
        {
            *page=8;
            brushanime(page);
            break;
        }
        else  if(mouse_press(147,408,347,478)==1)//端茶倒水按钮
        {
            *page=9;
            teaanime(page);
            break;
        }
        else  if(mouse_press(436,408,636,478)==1)//开窗关窗
        {
            *page=10;
            winanime(page);
            break;
        }
        else  if(mouse_press(742,408,902,478)==1)//炒菜做饭按钮
        {
            *page=11;
            cook_meal(page);
            break;
        }
        else  if(mouse_press(866,686,958,734)==1)//返回按钮
        {
            *page=4;
            break;
        }


    }
}







