/*  anime.c
功能：
    根据控制台命令,外部调用播放相应动画
内容：
    1.winanime播放开关窗动画
    2.
    3.
*/

#include <anime.h>


void winanime(int *page);//开关窗全代码，执行开关窗动画
void openwin_anime(Robot *Rob);//开窗动画
void closewin_anime(Robot *Rob);//关窗动画
void draw_windowbase();//绘制开窗关窗共同元素：窗架子
void draw_openwin();//画开窗
void draw_closewin();//画关窗
void draw_winbackground(Robot *Rob);//画开窗关窗全背景



void brushanime(int *page);//扫地全代码，执行扫地动画
void cleaning_anime(Robot *Rob, Brush *brush);//播放扫地动画
void draw_cleaningbackground(Robot *Rob, Brush *brush);//绘制扫地界面背景，并存好baseimages
void draw_brush(Brush *brush);//绘制扫把
void draw_cleaningtip();//绘制“正在扫地”弹窗
void draw_cleanuptip();//绘制“完成清扫！”弹窗并于1秒后自动消失



void teaanime(int *page);//倒水全代码，执行倒水动画
void draw_livingroom(Robot *Rob, Kettle *kettle, Bottle *bottle);//绘制倒水界面背景，并存好baseimages
void boilwater_anime(Robot *Rob, Kettle *kettle, Bottle *bottle);//执行机器人烧水倒水动画
void draw_wbottle(Bottle *bottle);//画未装水的水杯
void draw_hbottle(Bottle *bottle);//画装半杯水的水杯
void draw_mbottle(Bottle *bottle);//画装满水的水杯
void draw_zkettle(Kettle *kettle);//正放的水壶
void draw_xkettle(Kettle *kettle);//斜放的水壶
void draw_boilingtip();//绘制“正在烧水”和“烧水完成”弹窗
void draw_bottlefulltip();//存背景，绘制“监测到水杯已装满！”弹窗
void draw_finishboilingtip();//存背景，绘制“完成烧水”和“和倒水！”弹窗
void draw_cleanningroom();//绘制完成扫地界面背景



void wateranime(int *page);//浇花全代码，执行浇花动画
void watering_anime(Robot *Rob, Sprinkler *sprinkler);//执行浇花动画
void draw_wateringbackground(Robot *Rob, Sprinkler *sprinkler);//绘制浇花界面背景，并存好baseimages
void draw_flower(int x,int y);//画花盆
void draw_balcony(void);//画阳台
void draw_xsprinkler(Sprinkler *sprinkler);//画斜着的花洒
void draw_zsprinkler(Sprinkler *sprinkler);//画正着的花洒
void draw_water(Sprinkler *sprinkler);//画洒出的水
void draw_fullsprinktip();//绘制“正在装水”和“已完成”弹窗
void draw_alreadywatertip();//存背景，绘制“已完成浇花！”弹窗
void draw_finishwatertip();//存背景，绘制“一次性浇太多水对植物不好哦！”弹窗






/**
 * @name:浇花部分
 * @description: 执行浇花动画页面
*/




void  wateranime(int *page)
{
    Robot Rob;
    Sprinkler sprinkler;

    struct tm eventtime;
    Incidentcode incidentcode;

    int waterflag = 0;//浇水完成标志，0-未完成，1-完成

    //机器人初始化
    Rob = init_robot();
    Rob.x = 60;
    Rob.y = 400;

    //花洒初始化
    sprinkler.width = 220;
    sprinkler.height = 160;


    mouse_off(&mouse);

    draw_wateringbackground(&Rob, &sprinkler);//画出洒水基本元素
    
    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);

        if(mouse_press(850,5,1020,80)==1)//退出
        {
            *page = 12;
            break;
        }

        /*控制动画部分*/
        if(mouse_press(850,85, 1020, 160)==1)//按下洒水按钮
        {
        	if(waterflag == 0)//未洒水
            {
                mouse_off(&mouse);

                incidentcode = plants;
                fstart_diary(&incidentcode, &eventtime);

                watering_anime(&Rob, &sprinkler);
                waterflag = 1;
                draw_finishwatertip();

                incidentcode = plants;
                fend_diary(&incidentcode, &eventtime);

                mouse_on(mouse);
            }
            else if(waterflag == 1)//已洒水
            {
                mouse_off(&mouse);

                draw_alreadywatertip();

                mouse_show(&mouse);	
            }

        }


    }


}


void watering_anime(Robot *Rob, Sprinkler *sprinkler)
{
    int i = 0;
    int n1 = 0;//机器人左右的移动次数
    int n2 = 0;//机器人上下的移动次数
    int step = 20;//每次移动的步长
    int x_end = sprinkler->x;//到达水壶边
    int water_x = 0;//洒出的水的坐标信息
    int water_y = 0;
    int water_width = 90;
    int water_height = 130;
    int Robsp_width = 0;//组合体宽度
    int Robsp_height = 0;//组合体高度

    n1 = (x_end - Rob->x) / step - 5;



    /*向右移动*/

    for( i = 0; i < n1; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
    }



    /*拿起花洒*/

    delay(1000);

    //擦掉robot
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");

    //擦除原来正花洒
    Load_image(sprinkler->x, sprinkler->y, sprinkler->x + sprinkler->width,
        sprinkler->y + sprinkler->height, "sprinkbg");

    //移动数据，创建组合体，以Rob->x, Rob->y为基准
    sprinkler->x = Rob->x + Rob->width - 30;
    sprinkler->y = Rob->y + Rob->height - 120;
    Robsp_width = sprinkler->x + sprinkler->width - Rob->x;
    Robsp_height = Rob->height + 80;

    //保存现在的背景
    Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");
        
    //画好现在的组合体
    draw_zsprinkler(sprinkler);
    robot_set(Rob);

    delay(1000);



    /*出去装水*/

    for( i = 0; i < n1 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
 
        //存储下一个背景
        Rob->x -= step;
        sprinkler->x -= step;
 
        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
         
        //绘制组合体到下一地方
        draw_zsprinkler(sprinkler);
        robot_set(Rob);
 
    }
    Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");//用组合体背景擦除，起到出去效果
 


    /*装水*/
    draw_fullsprinktip(); // 装水呢别急



    /*装水回来了*/

    //重新画出来组合体
    draw_zsprinkler(sprinkler);
    robot_set(Rob);

    //向右移动组合体
    for( i = 0; i < n1 - 3; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");

        //存储下一个背景
        Rob->x += step;
        sprinkler->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
        
        //绘制组合体到下一地方
        draw_zsprinkler(sprinkler);
        robot_set(Rob);
    }

    //向后移动组合体
    n2 = 7;
    for( i = 0; i < n2 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");

        //存储下一个背景
        Rob->y -= step;
        sprinkler->y -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
        
        //绘制组合体到下一地方
        draw_zsprinkler(sprinkler);
        robot_set(Rob);
    }


    /*洒水*/

    delay(1000);
    Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");

    //倾斜花洒
    draw_xsprinkler(sprinkler);
    robot_set(Rob);
    delay(500);

    //存背景，出水
    water_x = sprinkler->x + 230 - 20;
    water_y = sprinkler->y + 90 - 10;
    Save_image(water_x, water_y, water_x + water_width, 
        water_y + water_height, "waterbg");
    draw_water(sprinkler);
    delay(2000);

    //停止
    Load_image(water_x, water_y, water_x + water_width, 
        water_y + water_height, "waterbg");
    delay(500);

    //用现背景擦除原地方的组合体
    Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");

    //回正水壶
    robot_set(Rob);
    draw_zsprinkler(sprinkler);
    delay(1000);

    //向前移动组合体
    for( i = 0; i < n2 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");

        //存储下一个背景
        Rob->y += step;
        sprinkler->y += step;

        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
        
        //绘制组合体到下一地方
        draw_zsprinkler(sprinkler);
        robot_set(Rob);

    }

    //向右移动组合体，放回水壶
    for( i = 0; i < 3 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");

        //存储下一个背景
        Rob->x += step;
        sprinkler->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
        
        //绘制组合体到下一地方
        draw_zsprinkler(sprinkler);
        robot_set(Rob);

    }
    delay(1000);


    /*放回花洒*/

    //用现背景擦除原地方的组合体
    Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");

    //分割，移动数据，放回水壶
    sprinkler->x = 500;
    sprinkler->y = 480;

    //分别画好图像
    draw_zsprinkler(sprinkler);
    robot_set(Rob);
    
    delay(1000);


    /*向左回去*/
    for( i = 0; i < n1; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
    }

}


void draw_wateringbackground(Robot *Rob, Sprinkler *sprinkler)
{
    sprinkler->width = 230;
    sprinkler->height = 160;
    sprinkler->x = 500;
    sprinkler->y = 480;



    //画背景
    // bar1(0, 0, 1024, 768, 0x5686BF);
    // bar1(35, 32, 989, 744, 0xFFFFFF);
    // ThickDiagonalLine(35,32,989,32,2,0x003399);
    // ThickDiagonalLine(35,32,35,744,2,0x003399);
    // ThickDiagonalLine(35,744,989,744,2,0x003399);
    // ThickDiagonalLine(989,32,989,744,2,0x003399); 
    draw_balcony();


    //画退出按钮
    bar1(850,5,1020,80,0xF08080);
    bar1(855,10,1015,75,0xC0C0C0);
    prt_hz16_size(885,18, 3, 3, "返回", 0xffffff, "HZK\\HZK16s");

    //画浇花按钮
    bar1(850,85, 1020, 160,0x704214);
    bar1(855,90, 1015, 155,0x2A52BE);
    prt_hz16_size(885, 98, 3, 3, "浇花", 0xffffff, "HZK\\HZK16s");

    //画花盆
    draw_flower(757,577);

    //存背景，画花洒
    Save_image(sprinkler->x, sprinkler->y, sprinkler->x + sprinkler->width, 
        sprinkler->y + sprinkler->height, "sprinkbg");//存好背景
    draw_zsprinkler(sprinkler);

    //存背景，画机器人
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");//存为robot background
    robot_set(Rob);//画机器人
}


//存背景，绘制“正在装水”和“已完成”弹窗，共4秒
void draw_fullsprinktip()
{
    Save_image(300, 150, 720, 470, "fsptpbg");//存为full_sprinkler_tip background
    
    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "正在装水，", 0xffffff, "HZK\\HZK16s");//文字
    prt_hz16_size(350, 270, 3, 3, "请稍等", 0xffffff, "HZK\\HZK16s");
    delay(3000);

    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "完成装水！", 0xffffff, "HZK\\HZK16s");//文字
    delay(1000);

    Load_image(300, 150, 720, 470, "fsptpbg");//恢复背景
}


//存背景，绘制“已完成浇花！”弹窗，共2秒
void draw_finishwatertip()
{
    Save_image(300, 150, 720, 470, "fsptpbg");//存为full_sprinkler_tip background
    
    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "已完成浇花！", 0xffffff, "HZK\\HZK16s");//文字
    delay(2000);

    Load_image(300, 150, 720, 470, "fsptpbg");//恢复背景
}


//存背景，绘制“一次性浇太多水对植物不好哦！”弹窗，共2秒
void draw_alreadywatertip()
{
    Save_image(300, 150, 720, 470, "fsptpbg");//存为full_sprinkler_tip background
    
    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(330, 200, 3, 3, "一次性浇太多水", 0xffffff, "HZK\\HZK16s");//文字
    prt_hz16_size(330, 270, 3, 3, "对植物不好哦！", 0xffffff, "HZK\\HZK16s");
    delay(2000);

    Load_image(300, 150, 720, 470, "fsptpbg");//恢复背景
}


//画阳台
void draw_balcony()
{
    bar1(0, 0, 1024, 768, 0x5686BF);
    bar1(35, 32, 989, 768, 0xFFFFFF);
    Line3(35,32,35,768,2,0x00000000);
    Line3(989,32,989,768,2,0x000000);
    Line3(35,32,989,32,2,0x00000000);
    Line2(46,60,970,60,0x000000);
    Line2(46,75,970,75,0x000000);
    Line2(57,422,168,254,0x000000);
    Line2(168,254,862,254,0x000000);
    Line2(862,254,970,422,0x000000);
    Line2(66,435,174,276,0x000000);
    Line2(855,276,950,421,0x000000); 
    Line2(174,276,855,276,0x000000); 
    bar2(208,281,322,463,0x000000);
    bar2(332,281,446,463,0x000000);
    bar2(456,281,570,463,0x000000);
    bar2(580,281,694,463,0x000000);
    bar2(700,281,814,463,0x000000);
    Line2(81,599,185,482,0x000000);
    Line2(85,616,188,498,0x000000);
    Line2(845,485,975,595,0x000000);
    Line2(840,495,966,605,0x000000);
    Line2(185,482,845,485,0x000000);
    Line2(188,498,840,495,0x000000);

    Arc(781,75,21,180.0,320.0,0x000000);
    Line2(760,75,760,120,0x000000);
    DrawEllipse(760,140,60,20,0x000000);
    Line2(760,160,760,192,0x000000);
    Line2(740,145,740,177,0x000000);
    Line2(725,140,725,172,0x000000);
    Arc(760,197,5,0,360.0,0x000000);
    Arc(740,182,5,0.0,360.0,0x000000);
    Arc(725,177,5,0.0,360.0,0x000000);
    Line2(780,145,780,177,0x000000);
    Line2(795,140,795,172,0x000000);
    Arc(780,182,5,0.0,360.0,0x000000);
    Arc(795,177,5,0.0,360.0,0x000000);


    Arc(621,75,21,180.0,320.0,0x000000);
    Line2(600,75,600,120,0x000000);
    Line2(600,120,550,190,0x000000);
    Line2(600,120,670,140,0x000000);
    Line2(550,190,670,140,0x000000);


    
    Arc(471,75,21,180.0,320.0,0x000000);
    Line2(450,75,450,120,0x000000);
    Line2(450,120,400,190,0x000000);
    Line2(450,120,520,140,0x000000);
    Line2(400,190,520,140,0x000000);

    
    Arc(321,75,21,180.0,320.0,0x000000);
    Line2(300,75,300,120,0x000000);
    Line2(300,120,250,190,0x000000);
    Line2(300,120,370,140,0x000000);
    Line2(250,190,370,140,0x000000);

    Arc(171,75,21,180.0,320.0,0x000000);
    Line2(150,75,150,120,0x000000);
    Line2(150,120,100,190,0x000000);
    Line2(150,120,220,140,0x000000);
    Line2(100,190,220,140,0x000000);

}




void draw_flower(int x,int y)
{
    int base_x=x, base_y=y;//base_x=757, base_y=577;
    // 花盆
    Line2(base_x, base_y, base_x+62, base_y, 0x000000);
    Line2(base_x, base_y, base_x+3, base_y+6, 0x000000);
    Line2(base_x+62, base_y, base_x+61, base_y+6, 0x000000);
    Line2(base_x+3, base_y+6, base_x+61, base_y+6, 0x000000);
    Line2(base_x+6, base_y+6, base_x+12, base_y+47, 0x000000);
    Line2(base_x+58, base_y+6, base_x+54, base_y+47, 0x000000);
    Line2(base_x+12, base_y+48, base_x+54, base_y+47, 0x000000);
    
    // 花茎
    Line2(base_x+33, base_y-57, base_x+33, base_y, 0x000000);

    // 左侧花瓣
    Arc(base_x+3, base_y, 30, -75, 0, 0x000000);
    Line2(base_x+10, base_y-29, base_x+33, base_y, 0x000000);
    Arc(base_x+41, base_y-31, 30, 105, 175, 0x000000);

    // 右侧花瓣
    Arc(base_x+63, base_y, 30, 180, 255.0, 0x000000);
    Line2(base_x+56, base_y-29, base_x+33, base_y, 0x000000);
    Arc(base_x+27, base_y-29, 30, 3, 85, 0x000000);

    // 花蕊
    Arc(base_x+33, base_y-71, 2, 0, 360, 0x000000);
    Arc(base_x+33, base_y-71, 7, 0, 360, 0x000000);

    // 花瓣细节
    Arc(base_x+34, base_y-89, 9, -210, 30, 0x000000);
    Arc(base_x+21, base_y-77, 9, 90, 300, 0x000000);
    Arc(base_x+26, base_y-62, 9, 30, 240, 0x000000);
    Arc(base_x+40, base_y-62, 9, -60, 150, 0x000000);
    Arc(base_x+45, base_y-77, 9, -120, 90, 0x000000);
}


void draw_xsprinkler(Sprinkler *sprinkler)// x表示画的是斜的花洒
{
    int base_x = sprinkler->x + 60;
    int base_y = sprinkler->y - 10;

    // 瓶身轮廓
    Line2(base_x, base_y, base_x+85, base_y+23, 0x000000);
    Line2(base_x+85, base_y+23, base_x+40, base_y+153, 0x000000);
    Line2(base_x-45, base_y+130, base_x+40, base_y+153, 0x000000);
    Line2(base_x-45, base_y+130, base_x, base_y, 0x000000);
    
    Line2(base_x-7, base_y+19, base_x+77, base_y+41, 0x000000);
    Line2(base_x-37, base_y+107, base_x+47, base_y+132, 0x000000);

    // 瓶盖部分
    Line2(base_x+67, base_y+75, base_x+139, base_y+97, 0x000000);
    Line2(base_x+164, base_y+73, base_x+139, base_y+97, 0x000000);
    Line2(base_x+164, base_y+73, base_x+144, base_y+125, 0x000000);
    Line2(base_x+136, base_y+107, base_x+144, base_y+125, 0x000000);
    Line2(base_x+136, base_y+107, base_x+63, base_y+85, 0x000000);

    // 壶把
    Arc(base_x-23, base_y+57, 25, 103, 298, 0x000000);
    Arc(base_x-23, base_y+57, 35, 103, 296, 0x000000);
}






void draw_zsprinkler(Sprinkler *sprinkler) //z表示画的是正的花洒
{
    
    int base_x = sprinkler->x + 50;
    int base_y = sprinkler->y + 5; // 基准点设为传入参数
    
    // 主体框架
    Line2(base_x, base_y, base_x+88, base_y, 0x000000);       // 顶部横线
    Line2(base_x, base_y, base_x, base_y+137, 0x000000);      // 左侧竖线
    Line2(base_x, base_y+137, base_x+88, base_y+137, 0x000000); // 底部横线
    Line2(base_x+88, base_y, base_x+88, base_y+137, 0x000000);  // 右侧竖线

    // 内部结构
    Line2(base_x, base_y+20, base_x+88, base_y+20, 0x000000); // 上部横线
    Line2(base_x, base_y+112, base_x+88, base_y+112, 0x000000); // 下部横线

    // 右侧箭头
    Line2(base_x+88, base_y+49, base_x+159, base_y+49, 0x000000); // 箭杆
    Line2(base_x+88, base_y+62, base_x+162, base_y+62, 0x000000); // 箭杆阴影
    Line2(base_x+159, base_y+49, base_x+178, base_y+21, 0x000000); // 箭头尖顶
    Line2(base_x+178, base_y+21, base_x+176, base_y+75, 0x000000); // 箭头右侧边
    Line2(base_x+176, base_y+75, base_x+162, base_y+62, 0x000000); // 箭头闭合

    // 左侧装饰弧线
    Arc(base_x, base_y+60, 25, 90, 270, 0x000000);  // 内弧
    Arc(base_x, base_y+60, 35, 90, 270, 0x000000);  // 外弧
}


void draw_water(Sprinkler *sprinkler) // 画出水流
{
    int base_x = sprinkler->x + 230;
    int base_y = sprinkler->y + 90;
    
    // 主水流线
    Line2(base_x, base_y, base_x+10, base_y+15, 0x00477D);
    Line2(base_x+20, base_y+23, base_x+29, base_y+40, 0x00477D);
    Line2(base_x+33, base_y+60, base_x+38, base_y+75, 0x00477D);
    Line2(base_x+48, base_y+89, base_x+49, base_y+105, 0x00477D);
    
    // 辅助水流线（左侧）
    Line2(base_x-4, base_y+20, base_x-2, base_y+28, 0x00477D);
    Line2(base_x+6, base_y+36, base_x+12, base_y+52, 0x00477D);
    Line2(base_x+29, base_y+92, base_x+27, base_y+71, 0x00477D);
    
    // 辅助水流线（右侧）
    Line2(base_x-9, base_y+42, base_x-4, base_y+59, 0x00477D);
    Line2(base_x-1, base_y+73, base_x+1, base_y+91, 0x00477D);
    Line2(base_x-20, base_y+49, base_x-17, base_y+60, 0x00477D);
    Line2(base_x-13, base_y+87, base_x-12, base_y+105, 0x00477D);
}









/**
 * @name:倒水部分
 * @description: 执行倒水动画页面
*/



void teaanime(int *page)
{
    Robot Rob;
    Bottle bottle;
    Kettle kettle;

    struct tm eventtime;
    Incidentcode incidentcode;

    int waterflag = 0; //记录水杯的状态,0为未装水，1为装半杯水，2为装满水

    int light=0; //记录灯的开关状态,0为管，1为开

    //水壶坐标初始化
    kettle.width = 80;
    kettle.height = 85;

    //水杯坐标初始化
    bottle.width=16;
    bottle.height=25;

    //机器人初始化
    Rob = init_robot();
    Rob.x = 20;
    Rob.y = 400;

    mouse_off(&mouse);

    draw_livingroom(&Rob, &kettle, &bottle);//画出客厅的基本元素

    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);

        if(mouse_press(850,5,1020,80)==1)//退出
        {
            *page=12;
            break;	
        }


        /*控制动画部分*/
        if (mouse_press(850, 85, 1020, 160)==1)//按下烧水倒水按钮
        {
            if(waterflag==0)//未装水
            {
            	mouse_off(&mouse);

                incidentcode = boilwater;
                fstart_diary(&incidentcode, &eventtime);

                boilwater_anime(&Rob, &kettle, &bottle);
                draw_finishboilingtip();
                waterflag = 2;

                incidentcode = boilwater;
                fend_diary(&incidentcode, &eventtime);

                mouse_show(&mouse);	
            }
            else if(waterflag==2)//装满水了
            {
            	mouse_off(&mouse);

                draw_bottlefulltip();

                mouse_show(&mouse);		
            }
            
        }
        

        if(mouse_press(539,527, 592, 554)==1&&light==0)//开灯
		{
            //记录日志
            incidentcode = light_on;
            fstart_diary(&incidentcode, &eventtime);

			mouse_off(&mouse);
            FillArc(636,229,19,-45.0,135.0,0x66FFE6);
            light=1;
            delay(500);
            mouse_on(mouse);

            //记录日志
            fend_diary(&incidentcode, &eventtime);
        }
        else  if(mouse_press(539,527, 592,554)==1&&light==1)//关灯
        {
            //记录日志
            incidentcode = light_off;
            fstart_diary(&incidentcode, &eventtime);

            mouse_off(&mouse);
            FillArc(636,229,19,-45.0,135.0,0xffffff);
            light=0;
            delay(500);
            mouse_on(mouse);

            //记录日志
            fend_diary(&incidentcode, &eventtime);
        }
    }
}





//执行机器人进场、拿水壶、出场动画
void boilwater_anime(Robot *Rob, Kettle *kettle, Bottle *bottle)
{
    int i = 0;
    int n1 = 0;//机器人从左边到中间的移动次数
    int n2 = 0;//机器人从中间到右边的移动次数
    int n3 = 0;//机器人从中间到后面的移动次数
    int step = 20;//每次移动的步长
    int x_end1 = kettle->x;//到达水壶边
    int x_end2 = 800;//到达右边
    int Robkt_width = 0;//组合体宽度
    int Robkt_height = 0;//组合体高度

    n1 = (x_end1 - Rob->x) / step;



	/*向右移动*/

    for( i = 0; i < n1; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
        //delay(50);//用于稳定动画？
    }




    /*拿起水壶*/

    delay(1000);

    //擦掉robot
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");

    //擦除原来正水壶
    Load_image(kettle->x, kettle->y, kettle->x + kettle->width,
        kettle->y + kettle->height, "zketbg");

    //移动数据，创建组合体，以kettle->x, Rob->y为基准
    kettle->x = Rob->x - 45;
    kettle->y = Rob->y + Rob->height - 80;
    Robkt_width = Rob->x + Rob->width - kettle->x;
    Robkt_height = kettle->y + kettle->height - Rob->y + 10;

    //保存现在的背景
    Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");
        
    //画好现在的组合体
    draw_zkettle(kettle);
    robot_set(Rob);

    // //存好现在的组合体
    // Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
    //     Rob->y + Robkt_height, "Robktim");

    delay(1000);


    

    /*出去装水*/

    n2 = (x_end2 - kettle->x) / step;

    for( i = 0; i < n2 - 3 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //存储下一个背景
        Rob->x += step;
        kettle->x += step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //绘制组合体到下一地方
        draw_zkettle(kettle);
        robot_set(Rob);

    }
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");//用组合体背景擦除，起到出去效果


    
    /*烧水*/
    draw_boilingtip(); // 烧水呢别急



    /*装水回来了*/

    //重新画出来组合体
    draw_zkettle(kettle);
    robot_set(Rob);

    //向左移动组合体
    for( i = 0; i < n2 + 5 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //存储下一个背景
        Rob->x -= step;
        kettle->x -= step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //绘制组合体到下一地方
        draw_zkettle(kettle);
        robot_set(Rob);

    }
    
    //向后移动组合体
    n3 = 3;
    for( i = 0; i < n3 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //存储下一个背景
        Rob->y -= step;
        kettle->y -= step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //绘制组合体到下一地方
        draw_zkettle(kettle);
        robot_set(Rob);

    }




    /*举起水壶，倒水*/

    delay(1000);

    //用现背景擦除原地方的组合体
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");
    
    //手臂举起来
    robot_uphand(Rob);
    
    //水壶举高高
    kettle->y -= 150;
    draw_zkettle(kettle);

    delay(1000);

    //倒水
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");
    draw_xkettle(kettle);
    robot_uphand(Rob);
    delay(1000);

    //水位上涨
    Load_image(bottle->x, bottle->y, bottle->x + bottle->width,
        bottle->y + bottle->height, "bottlbg");
    draw_hbottle(bottle);
    delay(1000);
    Load_image(bottle->x, bottle->y, bottle->x + bottle->width,
        bottle->y + bottle->height, "bottlbg");
    draw_mbottle(bottle);
    delay(1000);

    //倒水完毕
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");




    /*放下手，回去放水壶的位置*/

    //用现背景擦除原地方的组合体
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");

    //回正水壶
    robot_uphand(Rob);
    draw_zkettle(kettle);
    delay(1000);
    
    //手臂和水壶放下
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");
    robot_set(Rob);
    kettle->y += 150;
    draw_zkettle(kettle);
    delay(1000);

    //向前移动组合体
    for( i = 0; i < n3 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //存储下一个背景
        Rob->y += step;
        kettle->y += step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //绘制组合体到下一地方
        draw_zkettle(kettle);
        robot_set(Rob);

    }

    //向右移动组合体，放回水壶
    for( i = 0; i < 8 ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //存储下一个背景
        Rob->x += step;
        kettle->x += step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //绘制组合体到下一地方
        draw_zkettle(kettle);
        robot_set(Rob);

    }
    delay(1000);




    /*放回水壶*/

    //用现背景擦除原地方的组合体
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");

    //分割，移动数据，放回水壶
    kettle->x = 450;
    kettle->y = 470;

    //分别画好图像
    draw_zkettle(kettle);
    robot_set(Rob);
    
    delay(1000);




    /*向左回去*/

    for( i = 0; i < n1; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
        //delay(50);//用于稳定动画？
    }


}




//画出倒水界面背景，并存好baseimages
void draw_livingroom(Robot *Rob, Kettle *kettle,Bottle *bottle)
{
    bar1(0,0,1024,768,0xffffff);

    bottle->x = 219;
    bottle->y = 430;
    kettle->x = 450;
    kettle->y = 470;


    //画退出按钮
    bar1(850,5,1020,80,0xF08080);
    bar1(855,10,1015,75,0xC0C0C0);
    prt_hz16_size(885,18, 3, 3, "返回", 0xffffff, "HZK\\HZK16s");

    //画倒水按钮
    bar1(850,85, 1020, 160,0x704214);
    bar1(855,90, 1015, 155,0x2A52BE);
    prt_hz16_size(873,105, 2, 2, "烧水倒水", 0xffffff, "HZK\\HZK16s");


    //画门
    Line3(38,73,38,560,2,0xFFB3E6);
    Line3(38,560,186,560,2,0xFFB3E6);
    Line3(186,73,186,560,2,0xFFB3E6);
    Line3(38,73,185,73,2,0xFFB3E6);
    Line3(55,95,55,560,2,0xFFB3E6);
    Line3(55,95,169,95,2,0xFFB3E6);
    Line3(169,95,169,560,2,0xFFB3E6);
    Line3(75,144,75,514,2,0xFFB3E6);
    Line3(75,514,153,514,2,0xFFB3E6);
    Line3(153,514,153,144,2,0xFFB3E6);
    Line3(75,144,153,144,2,0xFFB3E6);
    //画门把手
    Line3(160,282,166,282,2,0x000000);
    Line3(160,282,160,326,2,0x000000);
    Line3(160,326,166,326,2,0x000000);
    Line3(166,326,166,282,2,0x000000);   
    Line3(143,301,160,300,2,0x000000);
    Line3(143,301,143,309,2,0x000000);
    Line3(143,309,160,309,2,0x000000);

    //画柜子
    ThickDiagonalLine(199, 462,221,414,2, 0x003153);
    Line3(221,414,446,414,2,0x003153);
    Line3(446,414,446,463,2,0x003153);
    Line3(446,463,201,463,2,0x003153);
    Line3(201,463,201,561,2,0x003153);
    Line3(201,463,201,561,2,0x003153);
    Line3(435,464,435,508,2,0x003153);
    Line3(387,466,387,508,2,0x003153);
    Line3(201,472,276,472,2,0x003153);
    Line3(276,472,276,546,2,0x003153);
    Line3(276,546,201,546,2,0x003153);
    draw_botton(261,503,267,514,0x66FFE6,0x000000);
    draw_botton(408,517,417,524,0x66FFE6,0x000000);
    draw_botton(331,517,340,524,0x66FFE6,0x000000);
    Line3(296,508,449,508,2,0x003153);
    Line3(449,508,449,561,2,0x003153);
    Line3(449,508,449,561,2,0x003153);
    Line3(296,508,296,546,2,0x003153);
    Line3(296,546,449,546,2,0x003153);
    Line3(375,508,375,546,2,0x003153);
    Line3(201,561,449,561,2,0x003153);
    

    //画柜子上的物品
    Circle(257,392,20,0xCD5C5C);
    Line2(238,433,247,410,0xCD853F);
    Line2(267,410,274,433,0xCD853F);
    Line1(238,433,274,433,0xCD853F);
    bar2(299,400,306,435,0xEEE8AA);
    bar1(299,400,306,417,0xEEE8AA);
    bar2(314,388,320,435,0xEEE8AA);
    bar1(299,400,306,417,0xF5F5DC);
    bar2(331,420,344,435,0xF5F5DC);
    bar1(331,420,344,426,0xF5F5DC);
    Line1(377,375,423,375,0x66FF59);
    Line1(423,375,423,431,0x66FF59);
    Line1(377,431,423,431,0x66FF59);
    Line1(377,375,377,431,0x66FF59);
    Line1(384,385,417,385,0x66FF59);
    Line1(417,385,417,421,0x66FF59);
    Line1(383,421,417,421,0x66FF59);
    Line1(383,384,383,421,0x66FF59);
    Line2(395,390,390,399,0x000000);
    Line2(390,399,402,399,0x000000);
    Line2(395,390,402,399,0x000000);
    Line2(390,399,390,421,0x000000);
    Line2(402,399,402,421,0x000000);
    Line2(408,394,402,406,0x000000);
    Line2(402,406,411,406,0x000000);
    Line2(408,394,411,406,0x000000);
    Line2(411,406,411,421,0x000000);
    
    //画时钟
    Line3(298,11,379,11,2,0x000000);
    Line3(379,11,379,104,2,0x000000);
    Line3(379,104,298,104,2,0x000000);
    Line3(298,104,298,11,2,0x000000);
    Line3(308,22,370,22,2,0x000000);
    Line3(370,22,370,93,2,0x000000);
    Line3(370,93,308,93,2,0x000000);
    Line3(308,93,308,22,2,0x000000);
    prt_asc16(335,30,"12",0x000000);
    prt_asc16(360,57,"3",0x000000);
    prt_asc16(338,82,"6",0x000000);
    prt_asc16(310,57,"9",0x000000);
    Circlefill(340,59,3,0x000000);
    Line1(340,45,340,59,0x000000);
    Line1(340,59,340,71,0x000000);

    //画壁画
    Line3(440,18,705,18,2,0x008B8B);
    Line3(705,18,705,145,2,0x008B8B);
    Line3(440,145,705,145,2,0x008B8B);
    Line3(440,18,440,145,2,0x008B8B);
    Line3(449,34,449,127,2,0x008B8B);
    Line3(449,127,689,127,2,0x008B8B);
    Line3(689,34,689,127,2,0x008B8B);
    Line3(449,34,689,34,2,0x008B8B);
    prt_hz16_size(475,60, 3, 3, "蛇年大吉", 0xFFD9E6, "HZK\\HZK16s");
    
    //画沙发
    Line1(683,336,886,336,0xD2691E);
    Line1(886,336,886,400,0xD2691E);
    Line1(683,336,683,400,0xD2691E);
    Line1(693,426,880,456,0xD2691E);
    Arc(676, 415,15,180.0,360.0, 0xD2691E);
    Arc(894, 415,15,180.0,360.0, 0xD2691E);
    Line1(691,415,691,452,0xD2691E);
    Line1(879,415,879,452,0xD2691E);
    Line1(691,452,879,452,0xD2691E);
    Line1(661,415,661,502,0xD2691E);
    Line1(909,415,909,502,0xD2691E);
    Arc(894,502,15,0.0,90.0, 0xD2691E);
    Arc(676,502,15,90.0,180.0, 0xD2691E);
    Line1(676,517,894,517,0xD2691E);
    Circle(735,384,8,0xCD5C5C);
    Circle(827,384,8,0xCD5C5C);
    Line1(787,336,787,426,0xD2691E);
    Line1(676,517,676,561,0xD2691E);
    Line1(685,517,685,561,0xD2691E);
    Line1(894,517,894,561,0xD2691E);
    Line1(885,517,885,561,0xD2691E);
    Line1(685,537,885,537,0xD2691E);
    
    //绘制画框
    Line3(744,177,779,177,2,0x007FFF);
    Line3(779,177,779,219,2,0x007FFF);
    Line3(744,219,779,219,2,0x007FFF);
    Line3(744,177,744,219,2,0x007FFF);
    Line1(748,182,775,182,0x007FFF);
    Line1(775,182,775,214,0x007FFF);
    Line1(748,214,775,214,0x007FFF);
    Line1(748,182,748,214,0x007FFF);

    Line3(814,210,865,210,2,0x996B1F);
    Line3(865,210,865,266,2,0x996B1F);
    Line3(814,266,865,266,2,0x996B1F);
    Line3(814,210,814,266,2,0x996B1F);
    Line1(818,215,861,215,0x996B1F);
    Line1(861,215,861,262,0x996B1F);
    Line1(818,262,861,262,0x996B1F);
    Line1(818,215,818,262,0x996B1F);
    Line3(0,561,1024,561,2,0x000000);

    //画灯
    Arc(569,561,62,180.0,360.0,0xE6C35C);
    Line2(562,500,544,363,0xE6C35C);
    Line2(569,500,549,363,0xE6C35C);
    Circle(544,356,9,0xE6C35C);
    Line2(546,348,593,229,0xE6C35C);
    Line2(551,349,595,235,0xE6C35C);
    Arc(636,229,42,135.0,310.0,0xE6C35C);
    Arc(636,229,20,-45.0,135.0,0xE6C35C);
    Arc(603,203,15,123.0,315.0,0xE6C35C);
    Line2(605,260,663,197,0xE6C35C);
    Line2(567,530,567,542,0x4D1F00);
    Arc(567,535,10,45.0,135.0,0x4D1F00);



    //存背景，画空水杯
    Save_image(bottle->x, bottle->y, bottle->x + bottle->width,
        bottle->y + bottle->height, "bottlbg");//存为water bottle background
    draw_wbottle(bottle);


    //存背景，画水壶
    Save_image(kettle->x, kettle->y, kettle->x + kettle->width, 
        kettle->y + kettle->height, "zketbg");//存为zkettle background
    draw_zkettle(kettle);
    

    //存背景，画机器人
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");//存为robot background
    robot_set(Rob);//画机器人

}   



//存背景，绘制“正在烧水”和“已完成”弹窗，共4秒
void draw_boilingtip()
{
    Save_image(300, 150, 720, 470, "boitpbg");//存为boilingtip background
    
    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "正在烧水，", 0xffffff, "HZK\\HZK16s");//文字
    prt_hz16_size(350, 270, 3, 3, "请稍等", 0xffffff, "HZK\\HZK16s");
    delay(3000);

    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "完成烧水！", 0xffffff, "HZK\\HZK16s");//文字
    delay(1000);

    Load_image(300, 150, 720, 470, "boitpbg");//恢复背景
}



//存背景，绘制“完成烧水”和“和倒水！”弹窗
void draw_finishboilingtip()
{
    Save_image(300, 150, 720, 470, "boitpbg");//存为boilingtip background
    
    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "完成烧水", 0xffffff, "HZK\\HZK16s");//文字
    prt_hz16_size(350, 270, 3, 3, "和倒水！", 0xffffff, "HZK\\HZK16s");
    delay(2000);

    Load_image(300, 150, 720, 470, "boitpbg");//恢复背景
}



//存背景，绘制“监测到水杯已装满！”弹窗，共2秒
void draw_bottlefulltip()
{
    Save_image(300, 150, 720, 470, "boitpbg");//存为boilingtip background
    
    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "监测到水杯", 0xffffff, "HZK\\HZK16s");//文字
    prt_hz16_size(350, 270, 3, 3, "已装满！", 0xffffff, "HZK\\HZK16s");//文字
    delay(2000);

    Load_image(300, 150, 720, 470, "boitpbg");//恢复背景
}



void  draw_zkettle(Kettle *kettle)//正放的水壶
{
    int base_x = kettle->x + 10;
    int base_y = kettle->y + 5;     //初始x=457,y=470
    kettle->width = 80;
    kettle->height = 90;

    Line2(base_x, base_y, base_x+37, base_y,0x0000000);
    Line2(base_x+37, base_y, base_x+38, base_y+81,0x0000000);
    Line2(base_x, base_y, base_x-2, base_y+81,0x0000000);
    Arc(base_x+20, base_y+61,27,43.0,138.0,0x000000);
    Arc(base_x+20, base_y+61,20,32.0,159.0,0x000000);
    Line2(base_x-1, base_y+4, base_x+36, base_y+4,0x0000000);
    Line2(base_x+36, base_y+4, base_x+46, base_y+4,0x0000000);
    Line2(base_x+46, base_y+4, base_x+46, base_y+48,0x0000000);
    Line2(base_x+38, base_y+48, base_x+46, base_y+48,0x0000000);
    Line2(base_x+37, base_y, base_x+48, base_y,0x0000000);
    Line2(base_x+48, base_y, base_x+48, base_y+51,0x0000000);
    Line2(base_x+38, base_y+51, base_x+48, base_y+51,0x0000000);
    Line2(base_x-7, base_y+4, base_x+48, base_y+4,0x0000000);
    Line2(base_x-7, base_y+4, base_x-1, base_y+10,0x0000000);
    Line2(base_x+21, base_y+60, base_x+21, base_y+66,0x4D1F00);
    Arc(base_x+21, base_y+65,5,30.0,150.0,0x4D1F00);
}


void  draw_xkettle(Kettle *kettle)//x表示斜放的水壶
{
    int base_x = kettle->x + 5;
    int base_y = kettle->y + 25;
    kettle->width = 80;
    kettle->height = 90;

        Line2(base_x, base_y, base_x+34, base_y-24, 0x000000);   
        Line2(base_x+34, base_y-24, base_x+60, base_y+12, 0x000000); 
        Line2(base_x+60, base_y+12, base_x+54, base_y+17, 0x000000); 
        Line2(base_x-3, base_y+7, base_x+34, base_y-19, 0x000000); 
        Line2(base_x+56, base_y+11, base_x+34, base_y-19, 0x000000); 
        Line2(base_x+56, base_y+11, base_x+51, base_y+15, 0x000000); 
        Line2(base_x, base_y, base_x+39, base_y+57, 0x000000);    
        Line2(base_x+27, base_y-19, base_x+70, base_y+41, 0x000000); 
        Line2(base_x-3, base_y+7, base_x+4, base_y+7, 0x000000); 
        Arc(base_x+45, base_y+32, 27, 18, 102.0, 0x000000);      
        Arc(base_x+45, base_y+32, 20, 5, 130.0, 0x000000);       
        Line2(base_x+45, base_y+32, base_x+48, base_y+36, 0x4D1F00);
        Arc(base_x+45, base_y+32, 10, 15.0, 100.0, 0x4D1F00);     
}


void  draw_wbottle(Bottle *bottle)//画未装水的水杯
{
    int base_x = bottle->x;
    int base_y = bottle->y;     //初始x=219,y=430
    bottle->width=16;
    bottle->height=25;

    Line1(base_x,base_y,base_x,base_y+25,0x000000);
    Line1(base_x+16,base_y,base_x+16,base_y+25,0x000000);
    Line1(base_x,base_y+25,base_x+16,base_y+25,0x000000);
    DrawEllipse(base_x+8,base_y,8,4,0x000000);
}


void  draw_hbottle(Bottle *bottle)//画装半杯水的水杯
{
    int base_x = bottle->x;
    int base_y = bottle->y;     //初始x=219,y=430
    bottle->width=16;
    bottle->height=25;

    Line1(base_x,base_y,base_x,base_y+25,0x000000);
    Line1(base_x+16,base_y,base_x+16,base_y+25,0x000000);
    Line1(base_x,base_y+25,base_x+16,base_y+25,0x000000);
    DrawEllipse(base_x+8,base_y,8,4,0x000000);
    bar1(base_x+2,base_y+12,base_x+14,base_y+23,0x00477D);

}


void  draw_mbottle(Bottle *bottle)//画装一杯水的水杯
{
    int base_x = bottle->x;
    int base_y = bottle->y;     //初始x=219,y=430
    bottle->width=16;
    bottle->height=25;

    Line1(base_x,base_y,base_x,base_y+25,0x000000);
    Line1(base_x+16,base_y,base_x+16,base_y+25,0x000000);
    Line1(base_x,base_y+25,base_x+16,base_y+25,0x000000);
    DrawEllipse(base_x+8,base_y,8,4,0x000000);
    bar1(base_x+2,base_y+4,base_x+14,base_y+23,0x00477D);

}










/**
 * @name:扫地动画部分
 * @description: 执行扫地动画页面
*/



//扫地动画总代码
void brushanime(int *page)
{
    Robot Rob;
    Brush brush;
    struct tm eventtime;
    Incidentcode incidentcode;

    Rob = init_robot();//初始化机器人

    draw_cleaningbackground(&Rob, &brush);//画扫地背景

    //进行扫地命令的判断，执行动画
    mouse_on(mouse);
    while(1)
    {
       mouse_show(&mouse);
       
       if(mouse_press(5, 5, 105, 75)==1) // 按下返回按钮
       {
           mouse_off(&mouse);
           *page = 12;
           break;
       }

       if(mouse_press(5, 80, 105, 150)==1) // 按下开始扫地按钮
       {
           mouse_off(&mouse); // 不允许中断

           /*记录日志*/
           incidentcode = cleanup;
           fstart_diary(&incidentcode, &eventtime); 


           cleaning_anime(&Rob, &brush); // 执行扫地动画

           
           /*记录日志*/
           fend_diary(&incidentcode, &eventtime);

           //恢复鼠标
           mouse_on(mouse);

       }



    }

}





//播放扫地动画
void cleaning_anime(Robot *Rob, Brush *brush)
{
    int i = 0;
    int n = 0;//机器人移动次数
    int step = 20;//每次移动的步长
    int x_end = brush->x - 4*step;//到达扫把边
    int brush_midx = 0;
    int brush_midy = 0;//这个是扫把中间移动的临时数据信息
    int Robcl_width = 0;//组合体宽度
    int Robcl_height = 0;//组合体高度

    n = (x_end - Rob->x) / step;


    /*向右移动*/

    for( i = 0; i < n; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
        //delay(50);//用于稳定动画？
    }


    /*拿起扫把*/

    delay(1000);

    //擦掉robot
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");

    Save_image(brush->x, brush->y, brush->x + brush->width,
        brush->y + brush->height, "brushbim");//保存此时扫把

    Load_image(brush->x, brush->y, brush->x + brush->width,
        brush->y + brush->height, "brushbg");//擦除原来扫把
    
    //创建组合体，以Rob的x、y为基准
    Robcl_width = brush->x + brush->width - Rob->x + 20;
    Robcl_height = brush->y + brush->height - Rob->y;
    brush_midx = brush->x;
    brush_midy = brush->y;//临时存好扫把的位置
    brush->x += 20;
    brush->y -= 20;

    Save_image(Rob->x, Rob->y, Rob->x + Robcl_width,
        Rob->y + Robcl_height, "Robclbg");//保存组合体Robclbg


    draw_brush(brush);//绘制扫把
    robot_set(Rob);//重新画好机器人

    delay(1000);

    


    /*出去扫地*/
    for( i = 0; i < n ; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(Rob->x, Rob->y, Rob->x + Robcl_width,
            Rob->y + Robcl_height, "Robclbg");

        //存储下一个背景
        Rob->x -= step;
        brush->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Robcl_width,
            Rob->y + Robcl_height, "Robclbg");
        
        //绘制组合体到下一地方
        draw_brush(brush);//绘制扫把
        robot_set(Rob);//重新画好机器人

    }
    Load_image(Rob->x, Rob->y, Rob->x + Robcl_width,
        Rob->y + Robcl_height, "Robclbg");//用组合体背景擦除，起到出去效果


    /*跳出弹窗*/
    draw_cleaningtip();//绘制“正在清扫”弹窗并delay5000
    draw_cleanuptip();//绘制“完成清扫！”弹窗并消失



    /*还回扫把*/

    draw_brush(brush);//绘制扫把
    robot_set(Rob);//重新画好机器人

    for( i = 0; i < n; i++)
    {
        //用现背景擦除原地方的组合体
        Load_image(Rob->x, Rob->y, Rob->x + Robcl_width,
            Rob->y + Robcl_height, "Robclbg");

        //存储下一个背景
        Rob->x += step;
        brush->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Robcl_width,
            Rob->y + Robcl_height, "Robclbg");
        
        //绘制组合体到下一地方
        draw_brush(brush);//绘制扫把
        robot_set(Rob);//重新画好机器人

    }

    //分离组合体，放下扫把
    delay(1000);
    Load_image(Rob->x, Rob->y, Rob->x + Robcl_width,
        Rob->y + Robcl_height, "Robclbg"); // 擦除组合体

    brush->x = brush_midx;
    brush->y = brush_midy;

    Load_image(brush->x, brush->y, brush->x + brush->width,
        brush->y + brush->height, "brushim"); // 放回扫把
    robot_set(Rob);//重新画好机器人
    delay(1000);



    /*机器人回去*/
    for( i = 0; i < n; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
        //delay(50);//用于稳定动画？
    }


}



//绘制扫地界面背景，并存好baseimages
void draw_cleaningbackground(Robot *Rob, Brush *brush)
{
    brush->x = 700;
    brush->y = 380;//扫把初始位置
    brush->width = 160;
    brush->height = 350;//包含完整扫把图形

    Rob->x = 20;
    Rob->y = 370;//机器人初始位置

    //初始化界面
    bar1(0, 0, 1024, 768, 0xffffff);

    draw_cleanningroom();//修饰房间

    //存好扫把的背景为brushbg
    Save_image(brush->x, brush->y, brush->x + brush->width, 
        brush->y + brush->height, "brushbg");

    //绘制扫把并保存为brushim
    draw_brush(brush);
    Save_image(brush->x, brush->y, brush->x + brush->width, 
        brush->y + brush->height, "brushim");

    //存好机器人的背景Robbg
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height,"Robbg");
    

    //画出最初机器人
    robot_set(Rob);

    
    //绘制“返回”按钮
    bar1(5, 5, 105, 75, 0xFF9900);
    bar1(10, 10, 100, 70, 0xFAF0E6);
    prt_hz16_size(23, 24, 2, 2, "返回", 0xffffff, "HZK\\HZK16s");

    //绘制“开始扫地”按钮
    bar1(5, 80, 105, 150, 0x996B1F);
    bar1(10, 85, 100, 145, 0x0D33FF);
    prt_hz16_size(23, 99, 2, 2, "清扫", 0xffffff, "HZK\\HZK16s");
}



//绘制“正在扫地”弹窗
void draw_cleaningtip()
{
    Save_image(300, 150, 720, 470, "cletpbg");//保存当前背景

    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "正在清扫中", 0xffffff, "HZK\\HZK16s");//文字

    delay(5000);//弹窗5秒后消失
}



//绘制“完成清扫！”弹窗并于1秒后自动消失
void draw_cleanuptip()
{
    bar1(310, 160, 710, 460, 0xB87333);//阴影
    bar1(300, 150, 700, 450, 0x704214);//深蓝主框
    bar2(310, 160, 690, 440, 0xffffff);//tip白边框
    prt_hz16_size(350, 200, 3, 3, "完成清扫！", 0xffffff, "HZK\\HZK16s");//文字
    delay(1000);
    
    Load_image(300, 150, 720, 470, "cletpbg");//保存当前背景
}



//绘制扫把
void draw_brush(Brush *brush)
{
    int base_x = brush->x + 120;
    int base_y = brush->y + 20; // 基准点坐标
    // 使用相对坐标绘制扫把
    ThickDiagonalLine(base_x, base_y, base_x+9, base_y+4, 2, 0x000000);
    ThickDiagonalLine(base_x, base_y, base_x-38, base_y+215, 2, 0x000000);
    ThickDiagonalLine(base_x+9, base_y+4, base_x-28, base_y+222, 2, 0x000000);
    ThickDiagonalLine(base_x-64, base_y+209, base_x-1, base_y+231, 2, 0x000000);
    ThickDiagonalLine(base_x-1, base_y+231, base_x-6, base_y+241, 2, 0x000000);
    ThickDiagonalLine(base_x-67, base_y+220, base_x-6, base_y+241, 2, 0x000000);
    ThickDiagonalLine(base_x-64, base_y+209, base_x-69, base_y+223, 2, 0x000000);
    ThickDiagonalLine(base_x-69, base_y+223, base_x-111, base_y+274, 2, 0x000000);
    ThickDiagonalLine(base_x-6, base_y+241, base_x-2, base_y+314, 2, 0x000000);
    ThickDiagonalLine(base_x-111, base_y+272, base_x-2, base_y+314, 2, 0x000000);
    ThickDiagonalLine(base_x-59, base_y+228, base_x-93, base_y+275, 2, 0x000000);
    ThickDiagonalLine(base_x-48, base_y+229, base_x-73, base_y+285, 2, 0x000000);
    ThickDiagonalLine(base_x-25, base_y+239, base_x-39, base_y+300, 2, 0x000000);
    ThickDiagonalLine(base_x-13, base_y+239, base_x-20, base_y+307, 2, 0x000000);
    ThickDiagonalLine(base_x-38, base_y+234, base_x-57, base_y+293, 2, 0x000000);
}



//绘制房间
void draw_cleanningroom()
{
    bar1(0,0,1024,555,0xF5F5F5);
    bar1(0,555,1024,768,0xFFE5B4);
    bar1(95,75,449,373,0xFFE4E1);
    Line3(0,555,1024,555,2,0x0000000);//上边框
    Line3(95,75,449,75,2,0xFFB366);//上边框
    Line3(95,75,95,373,2,0xFFB366);//左边框
    Line3(449,75,449,373,2,0xFFB366);//右边框
    Line3(95,373,449,373,2,0xFFB366);//下边框
    Line3(118,105,422,105,2,0xFFB366);
    Line3(118,105,118,346,2,0xFFB366);//左边框
    Line3(422,105,422,346,2,0xFFB366);//右边框
    Line3(118,346,422,346,2,0xFFB366);//下边框
    Line3(247,105,247,346,2,0xFFB366);//中间分割线
    Line3(296,105,296,346,2,0xFFB366);//中间分割线
    Line3(270,105,270,346,2,0xFFB366);
    Line3(118,212,247,212,2,0xFFB366);//中间分割线
    Line3(118,240,247,240,2,0xFFB366);//中间分割线
    Line3(296,212,422,212,2,0xFFB366);//中间分割线
    Line3(296,240,422,240,2,0xFFB366);//中间分割线
    bar1(118,105,247,212,0xffffff);//上面左边小框
    bar1(296,105,422,212,0xffffff);//上面右边小框
    bar1(118,240,247,346,0xffffff);//下面左边小框
    bar1(296,240,422,346,0xffffff);//下面右边小框

    bar1(510,160,594,228,0xFFE4E1);
    bar1(520,168,584,220,0xCD5C5C);//上面小框
    Line3(510,160,594,160,2,0xFFB366);//上边框
    Line3(510,160,510,228,2,0xFFB366);//左边框
    Line3(594,160,594,228,2,0xFFB366);//右边框
    Line3(510,228,594,228,2,0xFFB366);//下边框
    Line1(519,167,587,167,0xFFB366);//上边框
    Line1(519,167,519,221,0xFFB366);//左边框
    Line1(584,167,584,221,0xFFB366);//右边框
    Line1(519,221,587,221,0xFFB366);//下边框
    Line2(510,160,519,167,0xFFB366);//上边框
    Line2(594,160,587,167,0xFFB366);//上边框
    Line2(510,228,519,221,0xFFB366);//下边框
    Line2(594,228,587,221,0xFFB366);//下边框

    bar1(637,96,735,228,0xFFE4E1);
    bar1(646,106,724,220,0xE6C35C);//上面小框
    Line3(637,96,735,95,2,0xFFB366);//上边框
    Line3(637,96,637,228,2,0xFFB366);//左边框
    Line3(735,96,735,228,2,0xFFB366);//右边框
    Line3(637,228,735,228,2,0xFFB366);//下边框
    Line1(646,106,724,106,0xFFB366);//上边框
    Line1(646,106,646,220,0xFFB366);//左边框   
    Line1(724,106,724,220,0xFFB366);//右边框
    Line1(646,220,724,220,0xFFB366);//下边框
    Line2(637,96,646,106,0xFFB366);//上边框
    Line2(735,96,724,106,0xFFB366);//上边框
    Line2(637,228,646,220,0xFFB366);//下边框
    Line2(735,228,724,220,0xFFB366);//下边框

    bar1(785,125,905,231,0xFFE4E1);
    Line3(785,125,905,125,2,0xFFB366);
    Line3(905,125,905,231,2,0xFFB366);
    Line3(785,125,785,231,2,0xFFB366);
    Line3(785,231,905,231,2,0xFFB366);
    bar1(793,136,898,216,0xCD853F);
    Line2(793,136,898,136,0xFFB366);
    Line2(898,136,898,216,0xFFB366);
    Line2(793,136,793,216,0xFFB366);
    Line2(793,216,898,216,0xFFB366);

    Line2(785,125,793,136,0xFFB366);
    Line2(905,125,898,136,0xFFB366);
    Line2(785,231,793,216,0xFFB366);
    Line2(905,231,898,216,0xFFB366);

    bar1(482,277,727,422,0xCD5C5C);//电视机
    Line3(482,277,727,277,2,0x625B57);
    Line3(482,277,482,422,2,0x625B57);//左边框
    Line3(727,277,727,422,2,0x625B57);//右边框
    Line3(482,422,727,422,2,0x625B57);//下边框
    bar1(794,289,718,413,0x704214);//电视机屏幕
    Line3(494,289,718,289,2,0x625B57);//上边框
    Line3(494,289,494,413,2,0x625B57);//左边框
    Line3(718,289,718,413,2,0x625B57);//右边框
    Line3(494,413,718,413,2,0x625B57);//下边框
    ThickDiagonalLine(520,422,507,435,2,0x625B57);//斜线
    ThickDiagonalLine(689,422,700,435,2,0x625B57);//斜线
    ThickDiagonalLine(507,435,700,435,2,0x625B57);//斜线
    Line3(455,436,821,437,2,0x625B57);
    Line3(455,436,455,568,2,0x625B57);
    Line3(821,436,821,568,2,0x625B57);//右边框
    Line3(455,568,821,568,2,0x625B57);//下边框
    Line3(455,462,821,462,2,0x625B57);//上边框
    Line3(641,463,641,568,2,0x625B57);//左边框
    ThickDiagonalLine(458,568,460,580,2,0x625B57);
    ThickDiagonalLine(460,580,484,580,2,0x625B57);
    ThickDiagonalLine(484,580,486,568,2,0x625B57);
    ThickDiagonalLine(788,568,790,580,2,0x625B57);
    ThickDiagonalLine(790,580,814,580,2,0x625B57);
    ThickDiagonalLine(814,580,816,568,2,0x625B57);
    
    Line3(745,387,813,387,2,0xFAF0E6);
    Line3(745,387,745,420,2,0xFAF0E6);//左边框
    Line3(813,387,813,420,2,0xFAF0E6);//右边框
    Line3(745,420,813,420,2,0xFAF0E6);//下边框
    Line3(760,394,800,394,2,0xCC7722);
    Line3(760,394,760,413,2,0xCC7722);//左边框
    Line3(800,394,800,413,2,0xCC7722);//右边框
    Line3(760,413,800,413,2,0xCC7722);//下边框

    FillEllipse(422,659,352,60,0xCD853F);
    DrawEllipse(422,659,352,60,0x000000);

}










/**
 * @name:开关窗动画部分
 * @description: 执行开关窗动画页面
*/



void winanime(int *page)//开关窗动画
{
    FILE *fp = NULL;
    Robot Rob;
    Windowstate winstate;
    struct tm eventtime;
    Incidentcode incidentcode;


    Rob = init_robot();//初始化机器人
    
    draw_winbackground(&Rob);//画开窗关窗全背景


    //读取Windowstate，判断当前窗的状态
    fp = fopen("Data\\winstate.dat", "rb");
    if (fp == NULL) 
    {
        perror("无法打开 winstate.dat 文件");
        exit(1);
    }

    if (fread(&winstate, sizeof(Windowstate), 1, fp) != 1) 
    {
        perror("读取 winstate.dat 文件时出错");
        fclose(fp);
        exit(1);
    }

    fclose(fp);

    

    //根据当前窗的状态画出开或者关窗
    if(winstate == WindowClose)
    {
        draw_closewin();//画关窗
    }
    else if(winstate == WindowOpen)
    {
        draw_openwin();//画开窗
    }



    //进行开关窗命令与Windowstate的判断，执行相应动画
    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);

        if(mouse_press(5, 5, 105, 75)==1) //按下返回按钮
        {
            mouse_off(&mouse);
            *page = 12;//返回家庭服务
            break;
        }

        if(mouse_press(5, 80, 105, 150)==1) //按下开窗按钮
        {
            if(winstate == WindowClose) //窗户是关的，确实要开
            {
                mouse_off(&mouse);//不允许中断

                //tip
                prt_hz16_size(120, 100, 2, 2, "正在开窗中", 0xFFFAFA, "HZK\\HZK16s");

                /*记录日志*/
                incidentcode = window_on;
                fstart_diary(&incidentcode, &eventtime);


                openwin_anime(&Rob);//播放动画


               /*更新winstate.dat里面的windowstate数据*/
               winstate = WindowOpen;

               fp = fopen("Data\\winstate.dat", "wb");
               if (fp == NULL) 
               {
                   perror("无法打开 winstate.dat 文件");
                   exit(1);
               }
               if (fwrite(&winstate, sizeof(Windowstate), 1, fp) != 1) 
               {
                   perror("写入 winstate.dat 文件时出错");
                   fclose(fp);
                   exit(1);
               }

               fclose(fp);


               /*记录日志*/
               incidentcode = window_on;
               fend_diary(&incidentcode, &eventtime);

               //close tip
               bar1(120,100,400,200,0xffffff);
               prt_hz16_size(120, 100, 2, 2, "开窗成功！", 0xFFFAFA, "HZK\\HZK16s");
               delay(2000);
               bar1(120,100,400,200,0xffffff);

               //恢复鼠标
               mouse_on(mouse);
            }
            else if(winstate == WindowOpen) //本来窗户就是开的，不需要开
            {
                mouse_off(&mouse);
                prt_hz16_size(120, 100, 2, 2, "窗户已经开了！", 0xFFFAFA, "HZK\\HZK16s");
                delay(2000);
                bar1(120,100,400,200,0xffffff);
                mouse_show(&mouse);
            }
            

        }
        if(mouse_press(5, 155, 105, 225)==1) //按下关窗按钮
        {
            if(winstate == WindowOpen) //窗户是开的，确实要关
            {
                mouse_off(&mouse);//不允许中断

                //tip
                prt_hz16_size(120, 100, 2, 2, "正在关窗中", 0xFFFAFA, "HZK\\HZK16s");


                /*记录日志*/
                incidentcode = window_off;
                fstart_diary(&incidentcode, &eventtime);
    
    
                closewin_anime(&Rob);//播放动画  
    
    
                /*更新winstate.dat里面的windowstate数据*/
                winstate = WindowClose;
    
                fp = fopen("Data\\winstate.dat", "wb");
                if (fp == NULL) 
                {
                    perror("无法打开 winstate.dat 文件");
                    exit(1);
                }
                if (fwrite(&winstate, sizeof(Windowstate), 1, fp) != 1) 
                {
                    perror("写入 winstate.dat 文件时出错");
                    fclose(fp);
                    exit(1);
                }
    
                fclose(fp);
    
    
                /*记录日志*/
                incidentcode = window_off;
                fend_diary(&incidentcode, &eventtime);
    
    
                //close tip
                bar1(120,100,400,200,0xffffff);
                prt_hz16_size(120, 100, 2, 2, "关窗成功！", 0xFFFAFA, "HZK\\HZK16s");
                delay(2000);
                bar1(120,100,400,200,0xffffff);


                //恢复鼠标
                mouse_on(mouse);
            }
            else if(winstate == WindowClose) //窗户本来就是关的，不用关
            {
                mouse_off(&mouse);
                prt_hz16_size(120, 100, 2, 2, "窗户已经关了！", 0xFFFAFA, "HZK\\HZK16s");
                delay(2000);
                bar1(120,100,400,200,0xffffff);
                mouse_show(&mouse);
            }
            
        }


    }


}





//绘制开窗关窗共同元素：窗架子
void draw_windowbase()
{
    //画窗子框架
    Line3(544,8,940,8,2,0x000000);
    Line3(940,8,940,537,2,0x000000);
    Line3(544,537,940,537,2,0x000000);
    Line3(544,8,544,537,2,0x000000);
    Line3(559,25,923,25,2,0x000000);
    Line3(923,25,923,92,2,0x000000);
    Line3(559,92,923,92,2,0x000000);
    Line3(559,25,559,92,2,0x000000);
    Line3(560,109,730,109,2,0x000000);
    Line3(730,109,730,518,2,0x000000);
    Line3(560,518,730,518,2,0x000000);
    Line3(560,109,560,518,2,0x000000);
    Line3(750,109,920,109,2,0x000000);
    Line3(920,109,920,518,2,0x000000);
    Line3(750,518,920,518,2,0x000000);
    Line3(750,109,750,518,2,0x000000);   
    //画窗台
    Line3(516,554,1000,554,2,0x000000);
    ThickDiagonalLine(516,554,505,569,2,0x0000000);
    ThickDiagonalLine(1000,554,989,569,2,0x0000000);
    Line3(505,569,989,569,2,0x000000);
}


//开窗
void draw_openwin()
{
    ThickDiagonalLine(573,109,682,152,2,0x000000);
    Line3(573,109,573,518,2,0x000000);
    ThickDiagonalLine(573,518,682,503,2,0x000000);
    Line3(682,152,682,503,2,0x000000);
    ThickDiagonalLine(584,140,666,170,2,0x000000);
    Line3(584,140,584,492,2,0x000000);
    ThickDiagonalLine(584,492,666,477,2,0x000000);
    Line3(666,170,666,477,2,0x000000);
    bar2(671,297,676,350,0x000000);
    ThickDiagonalLine(910,109,812,159,2,0x000000);
    ThickDiagonalLine(812,499,910,518,2,0x000000);
    Line3(812,159,812,499,2,0x000000);
    Line3(910,109,910,518,2,0x000000);
    ThickDiagonalLine(899,140,828,175,2,0x000000);
    ThickDiagonalLine(899,486,828,476,2,0x000000);
    Line3(899,140,899,484,2,0x000000);
    Line3(828,175,828,476,2,0x000000);
    bar2(819,302,824,357,0x000000);

}


void draw_closewin()//关窗
{
    Line3(569,119,709,119,2,0x000000);
    Line3(709,119,709,510,2,0x000000);
    Line3(569,510,709,510,2,0x000000);
    Line3(569,119,569,510,2,0x000000);
    bar2(713,259,724,321,0x000000);

    Line3(771,119,911,119,2,0x0000000);
    Line3(771,119,771,510,2,0x000000);
    Line3(771,510,911,510,2,0x000000);
    Line3(911,119,911,510,2,0x000000);
    bar2(756,259,767,321,0x000000);

}



//绘制窗户界面背景，并存好baseimages
void draw_winbackground(Robot *Rob)
{
    
    Rob->x = 20;
    Rob->y = 370;//机器人初始位置

    //初始化界面
    bar1(0, 0, 1024, 768, 0xffffff);

    //绘制窗台并保存为winbg
    draw_windowbase();
    Save_image(480, 0, 950, 600, "winbg");
    
    //存好机器人的背景Robbg
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height,"Robbg");
    

    //画出最初机器人
    robot_set(Rob);

    
    //绘制“返回”按钮
    bar1(5, 5, 105, 75, 0xFF9900);
    bar1(10, 10, 100, 70, 0xFAF0E6);
    prt_hz16_size(23, 24, 2, 2, "返回", 0xffffff, "HZK\\HZK16s");

    //绘制“开窗”、“关窗”按钮
    bar1(5, 80, 105, 150, 0x996B1F);//开窗按钮
    bar1(10, 85, 100, 145, 0x0D33FF);
    prt_hz16_size(23, 99, 2, 2, "开窗", 0xffffff, "HZK\\HZK16s");
    bar1(5, 155, 105, 225, 0x996B1F);//关窗按钮
    bar1(10, 160, 100, 220, 0x0D33FF);
    prt_hz16_size(23, 174, 2, 2, "关窗", 0xffffff, "HZK\\HZK16s");

}


//播放机器人开窗的动画
void openwin_anime(Robot *Rob)
{
    int i = 0;
    int n = 0;//机器人移动次数
    int step = 20;//每次移动的步长
    int x_end = 500;//到达窗边

    n = (x_end - Rob->x) / step;

    //移动
    for( i = 0; i < n; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
        //delay(50);//用于稳定动画？
    }


    //开窗
    delay(1000);
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");//开窗前先擦掉机器人，避免Robbg含有它
    Load_image(480, 0, 950, 600, "winbg");//重新画好窗台
    draw_openwin();//开窗
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height,"Robbg");//更新背景
    robot_set(Rob);//重新绘制机器人
    delay(1000);
    


    //回去
    for( i = 0; i < n; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
        //delay(50);//用于稳定动画？
    }
    
}


//播放机器人关窗的动画
void closewin_anime(Robot *Rob)
{
    int i = 0;
    int n = 0;//机器人移动次数
    int step = 20;//每次移动的步长
    int x_end = 500;//到达窗边

    n = (x_end - Rob->x) / step;

    //移动
    for( i = 0; i < n; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
        //delay(50);//用于稳定动画？
    }


    //关窗
    delay(1000);
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");//开窗前先擦掉机器人，避免Robbg含有它
    Load_image(480, 0, 950, 600, "winbg");//重新画好窗台
    draw_closewin();//关窗
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height,"Robbg");//更新背景
    robot_set(Rob);//重新绘制机器人
    delay(1000);


    //回去
    for( i = 0; i < n; i++)
    {
        //用现背景擦除原地方的机器人
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //存储下一个背景
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //绘制机器人到下一地方
        robot_set(Rob);
        //delay(50);//用于稳定动画？
    }



    
}



