/*  anime.c
���ܣ�
    ���ݿ���̨����,�ⲿ���ò�����Ӧ����
���ݣ�
    1.winanime���ſ��ش�����
    2.
    3.
*/

#include <anime.h>


void winanime(int *page);//���ش�ȫ���룬ִ�п��ش�����
void openwin_anime(Robot *Rob);//��������
void closewin_anime(Robot *Rob);//�ش�����
void draw_windowbase();//���ƿ����ش���ͬԪ�أ�������
void draw_openwin();//������
void draw_closewin();//���ش�
void draw_winbackground(Robot *Rob);//�������ش�ȫ����



void brushanime(int *page);//ɨ��ȫ���룬ִ��ɨ�ض���
void cleaning_anime(Robot *Rob, Brush *brush);//����ɨ�ض���
void draw_cleaningbackground(Robot *Rob, Brush *brush);//����ɨ�ؽ��汳���������baseimages
void draw_brush(Brush *brush);//����ɨ��
void draw_cleaningtip();//���ơ�����ɨ�ء�����
void draw_cleanuptip();//���ơ������ɨ������������1����Զ���ʧ



void teaanime(int *page);//��ˮȫ���룬ִ�е�ˮ����
void draw_livingroom(Robot *Rob, Kettle *kettle, Bottle *bottle);//���Ƶ�ˮ���汳���������baseimages
void boilwater_anime(Robot *Rob, Kettle *kettle, Bottle *bottle);//ִ�л�������ˮ��ˮ����
void draw_wbottle(Bottle *bottle);//��δװˮ��ˮ��
void draw_hbottle(Bottle *bottle);//��װ�뱭ˮ��ˮ��
void draw_mbottle(Bottle *bottle);//��װ��ˮ��ˮ��
void draw_zkettle(Kettle *kettle);//���ŵ�ˮ��
void draw_xkettle(Kettle *kettle);//б�ŵ�ˮ��
void draw_boilingtip();//���ơ�������ˮ���͡���ˮ��ɡ�����
void draw_bottlefulltip();//�汳�������ơ���⵽ˮ����װ����������
void draw_finishboilingtip();//�汳�������ơ������ˮ���͡��͵�ˮ��������
void draw_cleanningroom();//�������ɨ�ؽ��汳��



void wateranime(int *page);//����ȫ���룬ִ�н�������
void watering_anime(Robot *Rob, Sprinkler *sprinkler);//ִ�н�������
void draw_wateringbackground(Robot *Rob, Sprinkler *sprinkler);//���ƽ������汳���������baseimages
void draw_flower(int x,int y);//������
void draw_balcony(void);//����̨
void draw_xsprinkler(Sprinkler *sprinkler);//��б�ŵĻ���
void draw_zsprinkler(Sprinkler *sprinkler);//�����ŵĻ���
void draw_water(Sprinkler *sprinkler);//��������ˮ
void draw_fullsprinktip();//���ơ�����װˮ���͡�����ɡ�����
void draw_alreadywatertip();//�汳�������ơ�����ɽ�����������
void draw_finishwatertip();//�汳�������ơ�һ���Խ�̫��ˮ��ֲ�ﲻ��Ŷ��������






/**
 * @name:��������
 * @description: ִ�н�������ҳ��
*/




void  wateranime(int *page)
{
    Robot Rob;
    Sprinkler sprinkler;

    struct tm eventtime;
    Incidentcode incidentcode;

    int waterflag = 0;//��ˮ��ɱ�־��0-δ��ɣ�1-���

    //�����˳�ʼ��
    Rob = init_robot();
    Rob.x = 60;
    Rob.y = 400;

    //������ʼ��
    sprinkler.width = 220;
    sprinkler.height = 160;


    mouse_off(&mouse);

    draw_wateringbackground(&Rob, &sprinkler);//������ˮ����Ԫ��
    
    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);

        if(mouse_press(850,5,1020,80)==1)//�˳�
        {
            *page = 12;
            break;
        }

        /*���ƶ�������*/
        if(mouse_press(850,85, 1020, 160)==1)//������ˮ��ť
        {
        	if(waterflag == 0)//δ��ˮ
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
            else if(waterflag == 1)//����ˮ
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
    int n1 = 0;//���������ҵ��ƶ�����
    int n2 = 0;//���������µ��ƶ�����
    int step = 20;//ÿ���ƶ��Ĳ���
    int x_end = sprinkler->x;//����ˮ����
    int water_x = 0;//������ˮ��������Ϣ
    int water_y = 0;
    int water_width = 90;
    int water_height = 130;
    int Robsp_width = 0;//�������
    int Robsp_height = 0;//�����߶�

    n1 = (x_end - Rob->x) / step - 5;



    /*�����ƶ�*/

    for( i = 0; i < n1; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
    }



    /*������*/

    delay(1000);

    //����robot
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");

    //����ԭ��������
    Load_image(sprinkler->x, sprinkler->y, sprinkler->x + sprinkler->width,
        sprinkler->y + sprinkler->height, "sprinkbg");

    //�ƶ����ݣ���������壬��Rob->x, Rob->yΪ��׼
    sprinkler->x = Rob->x + Rob->width - 30;
    sprinkler->y = Rob->y + Rob->height - 120;
    Robsp_width = sprinkler->x + sprinkler->width - Rob->x;
    Robsp_height = Rob->height + 80;

    //�������ڵı���
    Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");
        
    //�������ڵ������
    draw_zsprinkler(sprinkler);
    robot_set(Rob);

    delay(1000);



    /*��ȥװˮ*/

    for( i = 0; i < n1 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
 
        //�洢��һ������
        Rob->x -= step;
        sprinkler->x -= step;
 
        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
         
        //��������嵽��һ�ط�
        draw_zsprinkler(sprinkler);
        robot_set(Rob);
 
    }
    Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");//������屳���������𵽳�ȥЧ��
 


    /*װˮ*/
    draw_fullsprinktip(); // װˮ�ر�



    /*װˮ������*/

    //���»����������
    draw_zsprinkler(sprinkler);
    robot_set(Rob);

    //�����ƶ������
    for( i = 0; i < n1 - 3; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");

        //�洢��һ������
        Rob->x += step;
        sprinkler->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
        
        //��������嵽��һ�ط�
        draw_zsprinkler(sprinkler);
        robot_set(Rob);
    }

    //����ƶ������
    n2 = 7;
    for( i = 0; i < n2 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");

        //�洢��һ������
        Rob->y -= step;
        sprinkler->y -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
        
        //��������嵽��һ�ط�
        draw_zsprinkler(sprinkler);
        robot_set(Rob);
    }


    /*��ˮ*/

    delay(1000);
    Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");

    //��б����
    draw_xsprinkler(sprinkler);
    robot_set(Rob);
    delay(500);

    //�汳������ˮ
    water_x = sprinkler->x + 230 - 20;
    water_y = sprinkler->y + 90 - 10;
    Save_image(water_x, water_y, water_x + water_width, 
        water_y + water_height, "waterbg");
    draw_water(sprinkler);
    delay(2000);

    //ֹͣ
    Load_image(water_x, water_y, water_x + water_width, 
        water_y + water_height, "waterbg");
    delay(500);

    //���ֱ�������ԭ�ط��������
    Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");

    //����ˮ��
    robot_set(Rob);
    draw_zsprinkler(sprinkler);
    delay(1000);

    //��ǰ�ƶ������
    for( i = 0; i < n2 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");

        //�洢��һ������
        Rob->y += step;
        sprinkler->y += step;

        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
        
        //��������嵽��һ�ط�
        draw_zsprinkler(sprinkler);
        robot_set(Rob);

    }

    //�����ƶ�����壬�Ż�ˮ��
    for( i = 0; i < 3 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");

        //�洢��һ������
        Rob->x += step;
        sprinkler->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Robsp_width,
            Rob->y + Robsp_height, "Robspbg");
        
        //��������嵽��һ�ط�
        draw_zsprinkler(sprinkler);
        robot_set(Rob);

    }
    delay(1000);


    /*�Żػ���*/

    //���ֱ�������ԭ�ط��������
    Load_image(Rob->x, Rob->y, Rob->x + Robsp_width,
        Rob->y + Robsp_height, "Robspbg");

    //�ָ�ƶ����ݣ��Ż�ˮ��
    sprinkler->x = 500;
    sprinkler->y = 480;

    //�ֱ𻭺�ͼ��
    draw_zsprinkler(sprinkler);
    robot_set(Rob);
    
    delay(1000);


    /*�����ȥ*/
    for( i = 0; i < n1; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
    }

}


void draw_wateringbackground(Robot *Rob, Sprinkler *sprinkler)
{
    sprinkler->width = 230;
    sprinkler->height = 160;
    sprinkler->x = 500;
    sprinkler->y = 480;



    //������
    // bar1(0, 0, 1024, 768, 0x5686BF);
    // bar1(35, 32, 989, 744, 0xFFFFFF);
    // ThickDiagonalLine(35,32,989,32,2,0x003399);
    // ThickDiagonalLine(35,32,35,744,2,0x003399);
    // ThickDiagonalLine(35,744,989,744,2,0x003399);
    // ThickDiagonalLine(989,32,989,744,2,0x003399); 
    draw_balcony();


    //���˳���ť
    bar1(850,5,1020,80,0xF08080);
    bar1(855,10,1015,75,0xC0C0C0);
    prt_hz16_size(885,18, 3, 3, "����", 0xffffff, "HZK\\HZK16s");

    //��������ť
    bar1(850,85, 1020, 160,0x704214);
    bar1(855,90, 1015, 155,0x2A52BE);
    prt_hz16_size(885, 98, 3, 3, "����", 0xffffff, "HZK\\HZK16s");

    //������
    draw_flower(757,577);

    //�汳����������
    Save_image(sprinkler->x, sprinkler->y, sprinkler->x + sprinkler->width, 
        sprinkler->y + sprinkler->height, "sprinkbg");//��ñ���
    draw_zsprinkler(sprinkler);

    //�汳������������
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");//��Ϊrobot background
    robot_set(Rob);//��������
}


//�汳�������ơ�����װˮ���͡�����ɡ���������4��
void draw_fullsprinktip()
{
    Save_image(300, 150, 720, 470, "fsptpbg");//��Ϊfull_sprinkler_tip background
    
    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "����װˮ��", 0xffffff, "HZK\\HZK16s");//����
    prt_hz16_size(350, 270, 3, 3, "���Ե�", 0xffffff, "HZK\\HZK16s");
    delay(3000);

    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "���װˮ��", 0xffffff, "HZK\\HZK16s");//����
    delay(1000);

    Load_image(300, 150, 720, 470, "fsptpbg");//�ָ�����
}


//�汳�������ơ�����ɽ���������������2��
void draw_finishwatertip()
{
    Save_image(300, 150, 720, 470, "fsptpbg");//��Ϊfull_sprinkler_tip background
    
    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "����ɽ�����", 0xffffff, "HZK\\HZK16s");//����
    delay(2000);

    Load_image(300, 150, 720, 470, "fsptpbg");//�ָ�����
}


//�汳�������ơ�һ���Խ�̫��ˮ��ֲ�ﲻ��Ŷ������������2��
void draw_alreadywatertip()
{
    Save_image(300, 150, 720, 470, "fsptpbg");//��Ϊfull_sprinkler_tip background
    
    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(330, 200, 3, 3, "һ���Խ�̫��ˮ", 0xffffff, "HZK\\HZK16s");//����
    prt_hz16_size(330, 270, 3, 3, "��ֲ�ﲻ��Ŷ��", 0xffffff, "HZK\\HZK16s");
    delay(2000);

    Load_image(300, 150, 720, 470, "fsptpbg");//�ָ�����
}


//����̨
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
    // ����
    Line2(base_x, base_y, base_x+62, base_y, 0x000000);
    Line2(base_x, base_y, base_x+3, base_y+6, 0x000000);
    Line2(base_x+62, base_y, base_x+61, base_y+6, 0x000000);
    Line2(base_x+3, base_y+6, base_x+61, base_y+6, 0x000000);
    Line2(base_x+6, base_y+6, base_x+12, base_y+47, 0x000000);
    Line2(base_x+58, base_y+6, base_x+54, base_y+47, 0x000000);
    Line2(base_x+12, base_y+48, base_x+54, base_y+47, 0x000000);
    
    // ����
    Line2(base_x+33, base_y-57, base_x+33, base_y, 0x000000);

    // ��໨��
    Arc(base_x+3, base_y, 30, -75, 0, 0x000000);
    Line2(base_x+10, base_y-29, base_x+33, base_y, 0x000000);
    Arc(base_x+41, base_y-31, 30, 105, 175, 0x000000);

    // �Ҳ໨��
    Arc(base_x+63, base_y, 30, 180, 255.0, 0x000000);
    Line2(base_x+56, base_y-29, base_x+33, base_y, 0x000000);
    Arc(base_x+27, base_y-29, 30, 3, 85, 0x000000);

    // ����
    Arc(base_x+33, base_y-71, 2, 0, 360, 0x000000);
    Arc(base_x+33, base_y-71, 7, 0, 360, 0x000000);

    // ����ϸ��
    Arc(base_x+34, base_y-89, 9, -210, 30, 0x000000);
    Arc(base_x+21, base_y-77, 9, 90, 300, 0x000000);
    Arc(base_x+26, base_y-62, 9, 30, 240, 0x000000);
    Arc(base_x+40, base_y-62, 9, -60, 150, 0x000000);
    Arc(base_x+45, base_y-77, 9, -120, 90, 0x000000);
}


void draw_xsprinkler(Sprinkler *sprinkler)// x��ʾ������б�Ļ���
{
    int base_x = sprinkler->x + 60;
    int base_y = sprinkler->y - 10;

    // ƿ������
    Line2(base_x, base_y, base_x+85, base_y+23, 0x000000);
    Line2(base_x+85, base_y+23, base_x+40, base_y+153, 0x000000);
    Line2(base_x-45, base_y+130, base_x+40, base_y+153, 0x000000);
    Line2(base_x-45, base_y+130, base_x, base_y, 0x000000);
    
    Line2(base_x-7, base_y+19, base_x+77, base_y+41, 0x000000);
    Line2(base_x-37, base_y+107, base_x+47, base_y+132, 0x000000);

    // ƿ�ǲ���
    Line2(base_x+67, base_y+75, base_x+139, base_y+97, 0x000000);
    Line2(base_x+164, base_y+73, base_x+139, base_y+97, 0x000000);
    Line2(base_x+164, base_y+73, base_x+144, base_y+125, 0x000000);
    Line2(base_x+136, base_y+107, base_x+144, base_y+125, 0x000000);
    Line2(base_x+136, base_y+107, base_x+63, base_y+85, 0x000000);

    // ����
    Arc(base_x-23, base_y+57, 25, 103, 298, 0x000000);
    Arc(base_x-23, base_y+57, 35, 103, 296, 0x000000);
}






void draw_zsprinkler(Sprinkler *sprinkler) //z��ʾ���������Ļ���
{
    
    int base_x = sprinkler->x + 50;
    int base_y = sprinkler->y + 5; // ��׼����Ϊ�������
    
    // ������
    Line2(base_x, base_y, base_x+88, base_y, 0x000000);       // ��������
    Line2(base_x, base_y, base_x, base_y+137, 0x000000);      // �������
    Line2(base_x, base_y+137, base_x+88, base_y+137, 0x000000); // �ײ�����
    Line2(base_x+88, base_y, base_x+88, base_y+137, 0x000000);  // �Ҳ�����

    // �ڲ��ṹ
    Line2(base_x, base_y+20, base_x+88, base_y+20, 0x000000); // �ϲ�����
    Line2(base_x, base_y+112, base_x+88, base_y+112, 0x000000); // �²�����

    // �Ҳ��ͷ
    Line2(base_x+88, base_y+49, base_x+159, base_y+49, 0x000000); // ����
    Line2(base_x+88, base_y+62, base_x+162, base_y+62, 0x000000); // ������Ӱ
    Line2(base_x+159, base_y+49, base_x+178, base_y+21, 0x000000); // ��ͷ�ⶥ
    Line2(base_x+178, base_y+21, base_x+176, base_y+75, 0x000000); // ��ͷ�Ҳ��
    Line2(base_x+176, base_y+75, base_x+162, base_y+62, 0x000000); // ��ͷ�պ�

    // ���װ�λ���
    Arc(base_x, base_y+60, 25, 90, 270, 0x000000);  // �ڻ�
    Arc(base_x, base_y+60, 35, 90, 270, 0x000000);  // �⻡
}


void draw_water(Sprinkler *sprinkler) // ����ˮ��
{
    int base_x = sprinkler->x + 230;
    int base_y = sprinkler->y + 90;
    
    // ��ˮ����
    Line2(base_x, base_y, base_x+10, base_y+15, 0x00477D);
    Line2(base_x+20, base_y+23, base_x+29, base_y+40, 0x00477D);
    Line2(base_x+33, base_y+60, base_x+38, base_y+75, 0x00477D);
    Line2(base_x+48, base_y+89, base_x+49, base_y+105, 0x00477D);
    
    // ����ˮ���ߣ���ࣩ
    Line2(base_x-4, base_y+20, base_x-2, base_y+28, 0x00477D);
    Line2(base_x+6, base_y+36, base_x+12, base_y+52, 0x00477D);
    Line2(base_x+29, base_y+92, base_x+27, base_y+71, 0x00477D);
    
    // ����ˮ���ߣ��Ҳࣩ
    Line2(base_x-9, base_y+42, base_x-4, base_y+59, 0x00477D);
    Line2(base_x-1, base_y+73, base_x+1, base_y+91, 0x00477D);
    Line2(base_x-20, base_y+49, base_x-17, base_y+60, 0x00477D);
    Line2(base_x-13, base_y+87, base_x-12, base_y+105, 0x00477D);
}









/**
 * @name:��ˮ����
 * @description: ִ�е�ˮ����ҳ��
*/



void teaanime(int *page)
{
    Robot Rob;
    Bottle bottle;
    Kettle kettle;

    struct tm eventtime;
    Incidentcode incidentcode;

    int waterflag = 0; //��¼ˮ����״̬,0Ϊδװˮ��1Ϊװ�뱭ˮ��2Ϊװ��ˮ

    int light=0; //��¼�ƵĿ���״̬,0Ϊ�ܣ�1Ϊ��

    //ˮ�������ʼ��
    kettle.width = 80;
    kettle.height = 85;

    //ˮ�������ʼ��
    bottle.width=16;
    bottle.height=25;

    //�����˳�ʼ��
    Rob = init_robot();
    Rob.x = 20;
    Rob.y = 400;

    mouse_off(&mouse);

    draw_livingroom(&Rob, &kettle, &bottle);//���������Ļ���Ԫ��

    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);

        if(mouse_press(850,5,1020,80)==1)//�˳�
        {
            *page=12;
            break;	
        }


        /*���ƶ�������*/
        if (mouse_press(850, 85, 1020, 160)==1)//������ˮ��ˮ��ť
        {
            if(waterflag==0)//δװˮ
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
            else if(waterflag==2)//װ��ˮ��
            {
            	mouse_off(&mouse);

                draw_bottlefulltip();

                mouse_show(&mouse);		
            }
            
        }
        

        if(mouse_press(539,527, 592, 554)==1&&light==0)//����
		{
            //��¼��־
            incidentcode = light_on;
            fstart_diary(&incidentcode, &eventtime);

			mouse_off(&mouse);
            FillArc(636,229,19,-45.0,135.0,0x66FFE6);
            light=1;
            delay(500);
            mouse_on(mouse);

            //��¼��־
            fend_diary(&incidentcode, &eventtime);
        }
        else  if(mouse_press(539,527, 592,554)==1&&light==1)//�ص�
        {
            //��¼��־
            incidentcode = light_off;
            fstart_diary(&incidentcode, &eventtime);

            mouse_off(&mouse);
            FillArc(636,229,19,-45.0,135.0,0xffffff);
            light=0;
            delay(500);
            mouse_on(mouse);

            //��¼��־
            fend_diary(&incidentcode, &eventtime);
        }
    }
}





//ִ�л����˽�������ˮ������������
void boilwater_anime(Robot *Rob, Kettle *kettle, Bottle *bottle)
{
    int i = 0;
    int n1 = 0;//�����˴���ߵ��м���ƶ�����
    int n2 = 0;//�����˴��м䵽�ұߵ��ƶ�����
    int n3 = 0;//�����˴��м䵽������ƶ�����
    int step = 20;//ÿ���ƶ��Ĳ���
    int x_end1 = kettle->x;//����ˮ����
    int x_end2 = 800;//�����ұ�
    int Robkt_width = 0;//�������
    int Robkt_height = 0;//�����߶�

    n1 = (x_end1 - Rob->x) / step;



	/*�����ƶ�*/

    for( i = 0; i < n1; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
        //delay(50);//�����ȶ�������
    }




    /*����ˮ��*/

    delay(1000);

    //����robot
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");

    //����ԭ����ˮ��
    Load_image(kettle->x, kettle->y, kettle->x + kettle->width,
        kettle->y + kettle->height, "zketbg");

    //�ƶ����ݣ���������壬��kettle->x, Rob->yΪ��׼
    kettle->x = Rob->x - 45;
    kettle->y = Rob->y + Rob->height - 80;
    Robkt_width = Rob->x + Rob->width - kettle->x;
    Robkt_height = kettle->y + kettle->height - Rob->y + 10;

    //�������ڵı���
    Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");
        
    //�������ڵ������
    draw_zkettle(kettle);
    robot_set(Rob);

    // //������ڵ������
    // Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
    //     Rob->y + Robkt_height, "Robktim");

    delay(1000);


    

    /*��ȥװˮ*/

    n2 = (x_end2 - kettle->x) / step;

    for( i = 0; i < n2 - 3 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //�洢��һ������
        Rob->x += step;
        kettle->x += step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //��������嵽��һ�ط�
        draw_zkettle(kettle);
        robot_set(Rob);

    }
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");//������屳���������𵽳�ȥЧ��


    
    /*��ˮ*/
    draw_boilingtip(); // ��ˮ�ر�



    /*װˮ������*/

    //���»����������
    draw_zkettle(kettle);
    robot_set(Rob);

    //�����ƶ������
    for( i = 0; i < n2 + 5 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //�洢��һ������
        Rob->x -= step;
        kettle->x -= step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //��������嵽��һ�ط�
        draw_zkettle(kettle);
        robot_set(Rob);

    }
    
    //����ƶ������
    n3 = 3;
    for( i = 0; i < n3 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //�洢��һ������
        Rob->y -= step;
        kettle->y -= step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //��������嵽��һ�ط�
        draw_zkettle(kettle);
        robot_set(Rob);

    }




    /*����ˮ������ˮ*/

    delay(1000);

    //���ֱ�������ԭ�ط��������
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");
    
    //�ֱ۾�����
    robot_uphand(Rob);
    
    //ˮ���ٸ߸�
    kettle->y -= 150;
    draw_zkettle(kettle);

    delay(1000);

    //��ˮ
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");
    draw_xkettle(kettle);
    robot_uphand(Rob);
    delay(1000);

    //ˮλ����
    Load_image(bottle->x, bottle->y, bottle->x + bottle->width,
        bottle->y + bottle->height, "bottlbg");
    draw_hbottle(bottle);
    delay(1000);
    Load_image(bottle->x, bottle->y, bottle->x + bottle->width,
        bottle->y + bottle->height, "bottlbg");
    draw_mbottle(bottle);
    delay(1000);

    //��ˮ���
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");




    /*�����֣���ȥ��ˮ����λ��*/

    //���ֱ�������ԭ�ط��������
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");

    //����ˮ��
    robot_uphand(Rob);
    draw_zkettle(kettle);
    delay(1000);
    
    //�ֱۺ�ˮ������
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");
    robot_set(Rob);
    kettle->y += 150;
    draw_zkettle(kettle);
    delay(1000);

    //��ǰ�ƶ������
    for( i = 0; i < n3 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //�洢��һ������
        Rob->y += step;
        kettle->y += step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //��������嵽��һ�ط�
        draw_zkettle(kettle);
        robot_set(Rob);

    }

    //�����ƶ�����壬�Ż�ˮ��
    for( i = 0; i < 8 ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");

        //�洢��һ������
        Rob->x += step;
        kettle->x += step;

        Save_image(kettle->x, Rob->y, kettle->x + Robkt_width,
            Rob->y + Robkt_height, "Robktbg");
        
        //��������嵽��һ�ط�
        draw_zkettle(kettle);
        robot_set(Rob);

    }
    delay(1000);




    /*�Ż�ˮ��*/

    //���ֱ�������ԭ�ط��������
    Load_image(kettle->x, Rob->y, kettle->x + Robkt_width,
        Rob->y + Robkt_height, "Robktbg");

    //�ָ�ƶ����ݣ��Ż�ˮ��
    kettle->x = 450;
    kettle->y = 470;

    //�ֱ𻭺�ͼ��
    draw_zkettle(kettle);
    robot_set(Rob);
    
    delay(1000);




    /*�����ȥ*/

    for( i = 0; i < n1; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
        //delay(50);//�����ȶ�������
    }


}




//������ˮ���汳���������baseimages
void draw_livingroom(Robot *Rob, Kettle *kettle,Bottle *bottle)
{
    bar1(0,0,1024,768,0xffffff);

    bottle->x = 219;
    bottle->y = 430;
    kettle->x = 450;
    kettle->y = 470;


    //���˳���ť
    bar1(850,5,1020,80,0xF08080);
    bar1(855,10,1015,75,0xC0C0C0);
    prt_hz16_size(885,18, 3, 3, "����", 0xffffff, "HZK\\HZK16s");

    //����ˮ��ť
    bar1(850,85, 1020, 160,0x704214);
    bar1(855,90, 1015, 155,0x2A52BE);
    prt_hz16_size(873,105, 2, 2, "��ˮ��ˮ", 0xffffff, "HZK\\HZK16s");


    //����
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
    //���Ű���
    Line3(160,282,166,282,2,0x000000);
    Line3(160,282,160,326,2,0x000000);
    Line3(160,326,166,326,2,0x000000);
    Line3(166,326,166,282,2,0x000000);   
    Line3(143,301,160,300,2,0x000000);
    Line3(143,301,143,309,2,0x000000);
    Line3(143,309,160,309,2,0x000000);

    //������
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
    

    //�������ϵ���Ʒ
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
    
    //��ʱ��
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

    //���ڻ�
    Line3(440,18,705,18,2,0x008B8B);
    Line3(705,18,705,145,2,0x008B8B);
    Line3(440,145,705,145,2,0x008B8B);
    Line3(440,18,440,145,2,0x008B8B);
    Line3(449,34,449,127,2,0x008B8B);
    Line3(449,127,689,127,2,0x008B8B);
    Line3(689,34,689,127,2,0x008B8B);
    Line3(449,34,689,34,2,0x008B8B);
    prt_hz16_size(475,60, 3, 3, "�����", 0xFFD9E6, "HZK\\HZK16s");
    
    //��ɳ��
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
    
    //���ƻ���
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

    //����
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



    //�汳��������ˮ��
    Save_image(bottle->x, bottle->y, bottle->x + bottle->width,
        bottle->y + bottle->height, "bottlbg");//��Ϊwater bottle background
    draw_wbottle(bottle);


    //�汳������ˮ��
    Save_image(kettle->x, kettle->y, kettle->x + kettle->width, 
        kettle->y + kettle->height, "zketbg");//��Ϊzkettle background
    draw_zkettle(kettle);
    

    //�汳������������
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");//��Ϊrobot background
    robot_set(Rob);//��������

}   



//�汳�������ơ�������ˮ���͡�����ɡ���������4��
void draw_boilingtip()
{
    Save_image(300, 150, 720, 470, "boitpbg");//��Ϊboilingtip background
    
    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "������ˮ��", 0xffffff, "HZK\\HZK16s");//����
    prt_hz16_size(350, 270, 3, 3, "���Ե�", 0xffffff, "HZK\\HZK16s");
    delay(3000);

    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "�����ˮ��", 0xffffff, "HZK\\HZK16s");//����
    delay(1000);

    Load_image(300, 150, 720, 470, "boitpbg");//�ָ�����
}



//�汳�������ơ������ˮ���͡��͵�ˮ��������
void draw_finishboilingtip()
{
    Save_image(300, 150, 720, 470, "boitpbg");//��Ϊboilingtip background
    
    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "�����ˮ", 0xffffff, "HZK\\HZK16s");//����
    prt_hz16_size(350, 270, 3, 3, "�͵�ˮ��", 0xffffff, "HZK\\HZK16s");
    delay(2000);

    Load_image(300, 150, 720, 470, "boitpbg");//�ָ�����
}



//�汳�������ơ���⵽ˮ����װ��������������2��
void draw_bottlefulltip()
{
    Save_image(300, 150, 720, 470, "boitpbg");//��Ϊboilingtip background
    
    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "��⵽ˮ��", 0xffffff, "HZK\\HZK16s");//����
    prt_hz16_size(350, 270, 3, 3, "��װ����", 0xffffff, "HZK\\HZK16s");//����
    delay(2000);

    Load_image(300, 150, 720, 470, "boitpbg");//�ָ�����
}



void  draw_zkettle(Kettle *kettle)//���ŵ�ˮ��
{
    int base_x = kettle->x + 10;
    int base_y = kettle->y + 5;     //��ʼx=457,y=470
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


void  draw_xkettle(Kettle *kettle)//x��ʾб�ŵ�ˮ��
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


void  draw_wbottle(Bottle *bottle)//��δװˮ��ˮ��
{
    int base_x = bottle->x;
    int base_y = bottle->y;     //��ʼx=219,y=430
    bottle->width=16;
    bottle->height=25;

    Line1(base_x,base_y,base_x,base_y+25,0x000000);
    Line1(base_x+16,base_y,base_x+16,base_y+25,0x000000);
    Line1(base_x,base_y+25,base_x+16,base_y+25,0x000000);
    DrawEllipse(base_x+8,base_y,8,4,0x000000);
}


void  draw_hbottle(Bottle *bottle)//��װ�뱭ˮ��ˮ��
{
    int base_x = bottle->x;
    int base_y = bottle->y;     //��ʼx=219,y=430
    bottle->width=16;
    bottle->height=25;

    Line1(base_x,base_y,base_x,base_y+25,0x000000);
    Line1(base_x+16,base_y,base_x+16,base_y+25,0x000000);
    Line1(base_x,base_y+25,base_x+16,base_y+25,0x000000);
    DrawEllipse(base_x+8,base_y,8,4,0x000000);
    bar1(base_x+2,base_y+12,base_x+14,base_y+23,0x00477D);

}


void  draw_mbottle(Bottle *bottle)//��װһ��ˮ��ˮ��
{
    int base_x = bottle->x;
    int base_y = bottle->y;     //��ʼx=219,y=430
    bottle->width=16;
    bottle->height=25;

    Line1(base_x,base_y,base_x,base_y+25,0x000000);
    Line1(base_x+16,base_y,base_x+16,base_y+25,0x000000);
    Line1(base_x,base_y+25,base_x+16,base_y+25,0x000000);
    DrawEllipse(base_x+8,base_y,8,4,0x000000);
    bar1(base_x+2,base_y+4,base_x+14,base_y+23,0x00477D);

}










/**
 * @name:ɨ�ض�������
 * @description: ִ��ɨ�ض���ҳ��
*/



//ɨ�ض����ܴ���
void brushanime(int *page)
{
    Robot Rob;
    Brush brush;
    struct tm eventtime;
    Incidentcode incidentcode;

    Rob = init_robot();//��ʼ��������

    draw_cleaningbackground(&Rob, &brush);//��ɨ�ر���

    //����ɨ��������жϣ�ִ�ж���
    mouse_on(mouse);
    while(1)
    {
       mouse_show(&mouse);
       
       if(mouse_press(5, 5, 105, 75)==1) // ���·��ذ�ť
       {
           mouse_off(&mouse);
           *page = 12;
           break;
       }

       if(mouse_press(5, 80, 105, 150)==1) // ���¿�ʼɨ�ذ�ť
       {
           mouse_off(&mouse); // �������ж�

           /*��¼��־*/
           incidentcode = cleanup;
           fstart_diary(&incidentcode, &eventtime); 


           cleaning_anime(&Rob, &brush); // ִ��ɨ�ض���

           
           /*��¼��־*/
           fend_diary(&incidentcode, &eventtime);

           //�ָ����
           mouse_on(mouse);

       }



    }

}





//����ɨ�ض���
void cleaning_anime(Robot *Rob, Brush *brush)
{
    int i = 0;
    int n = 0;//�������ƶ�����
    int step = 20;//ÿ���ƶ��Ĳ���
    int x_end = brush->x - 4*step;//����ɨ�ѱ�
    int brush_midx = 0;
    int brush_midy = 0;//�����ɨ���м��ƶ�����ʱ������Ϣ
    int Robcl_width = 0;//�������
    int Robcl_height = 0;//�����߶�

    n = (x_end - Rob->x) / step;


    /*�����ƶ�*/

    for( i = 0; i < n; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
        //delay(50);//�����ȶ�������
    }


    /*����ɨ��*/

    delay(1000);

    //����robot
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");

    Save_image(brush->x, brush->y, brush->x + brush->width,
        brush->y + brush->height, "brushbim");//�����ʱɨ��

    Load_image(brush->x, brush->y, brush->x + brush->width,
        brush->y + brush->height, "brushbg");//����ԭ��ɨ��
    
    //��������壬��Rob��x��yΪ��׼
    Robcl_width = brush->x + brush->width - Rob->x + 20;
    Robcl_height = brush->y + brush->height - Rob->y;
    brush_midx = brush->x;
    brush_midy = brush->y;//��ʱ���ɨ�ѵ�λ��
    brush->x += 20;
    brush->y -= 20;

    Save_image(Rob->x, Rob->y, Rob->x + Robcl_width,
        Rob->y + Robcl_height, "Robclbg");//���������Robclbg


    draw_brush(brush);//����ɨ��
    robot_set(Rob);//���»��û�����

    delay(1000);

    


    /*��ȥɨ��*/
    for( i = 0; i < n ; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(Rob->x, Rob->y, Rob->x + Robcl_width,
            Rob->y + Robcl_height, "Robclbg");

        //�洢��һ������
        Rob->x -= step;
        brush->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Robcl_width,
            Rob->y + Robcl_height, "Robclbg");
        
        //��������嵽��һ�ط�
        draw_brush(brush);//����ɨ��
        robot_set(Rob);//���»��û�����

    }
    Load_image(Rob->x, Rob->y, Rob->x + Robcl_width,
        Rob->y + Robcl_height, "Robclbg");//������屳���������𵽳�ȥЧ��


    /*��������*/
    draw_cleaningtip();//���ơ�������ɨ��������delay5000
    draw_cleanuptip();//���ơ������ɨ������������ʧ



    /*����ɨ��*/

    draw_brush(brush);//����ɨ��
    robot_set(Rob);//���»��û�����

    for( i = 0; i < n; i++)
    {
        //���ֱ�������ԭ�ط��������
        Load_image(Rob->x, Rob->y, Rob->x + Robcl_width,
            Rob->y + Robcl_height, "Robclbg");

        //�洢��һ������
        Rob->x += step;
        brush->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Robcl_width,
            Rob->y + Robcl_height, "Robclbg");
        
        //��������嵽��һ�ط�
        draw_brush(brush);//����ɨ��
        robot_set(Rob);//���»��û�����

    }

    //��������壬����ɨ��
    delay(1000);
    Load_image(Rob->x, Rob->y, Rob->x + Robcl_width,
        Rob->y + Robcl_height, "Robclbg"); // ���������

    brush->x = brush_midx;
    brush->y = brush_midy;

    Load_image(brush->x, brush->y, brush->x + brush->width,
        brush->y + brush->height, "brushim"); // �Ż�ɨ��
    robot_set(Rob);//���»��û�����
    delay(1000);



    /*�����˻�ȥ*/
    for( i = 0; i < n; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
        //delay(50);//�����ȶ�������
    }


}



//����ɨ�ؽ��汳���������baseimages
void draw_cleaningbackground(Robot *Rob, Brush *brush)
{
    brush->x = 700;
    brush->y = 380;//ɨ�ѳ�ʼλ��
    brush->width = 160;
    brush->height = 350;//��������ɨ��ͼ��

    Rob->x = 20;
    Rob->y = 370;//�����˳�ʼλ��

    //��ʼ������
    bar1(0, 0, 1024, 768, 0xffffff);

    draw_cleanningroom();//���η���

    //���ɨ�ѵı���Ϊbrushbg
    Save_image(brush->x, brush->y, brush->x + brush->width, 
        brush->y + brush->height, "brushbg");

    //����ɨ�Ѳ�����Ϊbrushim
    draw_brush(brush);
    Save_image(brush->x, brush->y, brush->x + brush->width, 
        brush->y + brush->height, "brushim");

    //��û����˵ı���Robbg
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height,"Robbg");
    

    //�������������
    robot_set(Rob);

    
    //���ơ����ء���ť
    bar1(5, 5, 105, 75, 0xFF9900);
    bar1(10, 10, 100, 70, 0xFAF0E6);
    prt_hz16_size(23, 24, 2, 2, "����", 0xffffff, "HZK\\HZK16s");

    //���ơ���ʼɨ�ء���ť
    bar1(5, 80, 105, 150, 0x996B1F);
    bar1(10, 85, 100, 145, 0x0D33FF);
    prt_hz16_size(23, 99, 2, 2, "��ɨ", 0xffffff, "HZK\\HZK16s");
}



//���ơ�����ɨ�ء�����
void draw_cleaningtip()
{
    Save_image(300, 150, 720, 470, "cletpbg");//���浱ǰ����

    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "������ɨ��", 0xffffff, "HZK\\HZK16s");//����

    delay(5000);//����5�����ʧ
}



//���ơ������ɨ������������1����Զ���ʧ
void draw_cleanuptip()
{
    bar1(310, 160, 710, 460, 0xB87333);//��Ӱ
    bar1(300, 150, 700, 450, 0x704214);//��������
    bar2(310, 160, 690, 440, 0xffffff);//tip�ױ߿�
    prt_hz16_size(350, 200, 3, 3, "�����ɨ��", 0xffffff, "HZK\\HZK16s");//����
    delay(1000);
    
    Load_image(300, 150, 720, 470, "cletpbg");//���浱ǰ����
}



//����ɨ��
void draw_brush(Brush *brush)
{
    int base_x = brush->x + 120;
    int base_y = brush->y + 20; // ��׼������
    // ʹ������������ɨ��
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



//���Ʒ���
void draw_cleanningroom()
{
    bar1(0,0,1024,555,0xF5F5F5);
    bar1(0,555,1024,768,0xFFE5B4);
    bar1(95,75,449,373,0xFFE4E1);
    Line3(0,555,1024,555,2,0x0000000);//�ϱ߿�
    Line3(95,75,449,75,2,0xFFB366);//�ϱ߿�
    Line3(95,75,95,373,2,0xFFB366);//��߿�
    Line3(449,75,449,373,2,0xFFB366);//�ұ߿�
    Line3(95,373,449,373,2,0xFFB366);//�±߿�
    Line3(118,105,422,105,2,0xFFB366);
    Line3(118,105,118,346,2,0xFFB366);//��߿�
    Line3(422,105,422,346,2,0xFFB366);//�ұ߿�
    Line3(118,346,422,346,2,0xFFB366);//�±߿�
    Line3(247,105,247,346,2,0xFFB366);//�м�ָ���
    Line3(296,105,296,346,2,0xFFB366);//�м�ָ���
    Line3(270,105,270,346,2,0xFFB366);
    Line3(118,212,247,212,2,0xFFB366);//�м�ָ���
    Line3(118,240,247,240,2,0xFFB366);//�м�ָ���
    Line3(296,212,422,212,2,0xFFB366);//�м�ָ���
    Line3(296,240,422,240,2,0xFFB366);//�м�ָ���
    bar1(118,105,247,212,0xffffff);//�������С��
    bar1(296,105,422,212,0xffffff);//�����ұ�С��
    bar1(118,240,247,346,0xffffff);//�������С��
    bar1(296,240,422,346,0xffffff);//�����ұ�С��

    bar1(510,160,594,228,0xFFE4E1);
    bar1(520,168,584,220,0xCD5C5C);//����С��
    Line3(510,160,594,160,2,0xFFB366);//�ϱ߿�
    Line3(510,160,510,228,2,0xFFB366);//��߿�
    Line3(594,160,594,228,2,0xFFB366);//�ұ߿�
    Line3(510,228,594,228,2,0xFFB366);//�±߿�
    Line1(519,167,587,167,0xFFB366);//�ϱ߿�
    Line1(519,167,519,221,0xFFB366);//��߿�
    Line1(584,167,584,221,0xFFB366);//�ұ߿�
    Line1(519,221,587,221,0xFFB366);//�±߿�
    Line2(510,160,519,167,0xFFB366);//�ϱ߿�
    Line2(594,160,587,167,0xFFB366);//�ϱ߿�
    Line2(510,228,519,221,0xFFB366);//�±߿�
    Line2(594,228,587,221,0xFFB366);//�±߿�

    bar1(637,96,735,228,0xFFE4E1);
    bar1(646,106,724,220,0xE6C35C);//����С��
    Line3(637,96,735,95,2,0xFFB366);//�ϱ߿�
    Line3(637,96,637,228,2,0xFFB366);//��߿�
    Line3(735,96,735,228,2,0xFFB366);//�ұ߿�
    Line3(637,228,735,228,2,0xFFB366);//�±߿�
    Line1(646,106,724,106,0xFFB366);//�ϱ߿�
    Line1(646,106,646,220,0xFFB366);//��߿�   
    Line1(724,106,724,220,0xFFB366);//�ұ߿�
    Line1(646,220,724,220,0xFFB366);//�±߿�
    Line2(637,96,646,106,0xFFB366);//�ϱ߿�
    Line2(735,96,724,106,0xFFB366);//�ϱ߿�
    Line2(637,228,646,220,0xFFB366);//�±߿�
    Line2(735,228,724,220,0xFFB366);//�±߿�

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

    bar1(482,277,727,422,0xCD5C5C);//���ӻ�
    Line3(482,277,727,277,2,0x625B57);
    Line3(482,277,482,422,2,0x625B57);//��߿�
    Line3(727,277,727,422,2,0x625B57);//�ұ߿�
    Line3(482,422,727,422,2,0x625B57);//�±߿�
    bar1(794,289,718,413,0x704214);//���ӻ���Ļ
    Line3(494,289,718,289,2,0x625B57);//�ϱ߿�
    Line3(494,289,494,413,2,0x625B57);//��߿�
    Line3(718,289,718,413,2,0x625B57);//�ұ߿�
    Line3(494,413,718,413,2,0x625B57);//�±߿�
    ThickDiagonalLine(520,422,507,435,2,0x625B57);//б��
    ThickDiagonalLine(689,422,700,435,2,0x625B57);//б��
    ThickDiagonalLine(507,435,700,435,2,0x625B57);//б��
    Line3(455,436,821,437,2,0x625B57);
    Line3(455,436,455,568,2,0x625B57);
    Line3(821,436,821,568,2,0x625B57);//�ұ߿�
    Line3(455,568,821,568,2,0x625B57);//�±߿�
    Line3(455,462,821,462,2,0x625B57);//�ϱ߿�
    Line3(641,463,641,568,2,0x625B57);//��߿�
    ThickDiagonalLine(458,568,460,580,2,0x625B57);
    ThickDiagonalLine(460,580,484,580,2,0x625B57);
    ThickDiagonalLine(484,580,486,568,2,0x625B57);
    ThickDiagonalLine(788,568,790,580,2,0x625B57);
    ThickDiagonalLine(790,580,814,580,2,0x625B57);
    ThickDiagonalLine(814,580,816,568,2,0x625B57);
    
    Line3(745,387,813,387,2,0xFAF0E6);
    Line3(745,387,745,420,2,0xFAF0E6);//��߿�
    Line3(813,387,813,420,2,0xFAF0E6);//�ұ߿�
    Line3(745,420,813,420,2,0xFAF0E6);//�±߿�
    Line3(760,394,800,394,2,0xCC7722);
    Line3(760,394,760,413,2,0xCC7722);//��߿�
    Line3(800,394,800,413,2,0xCC7722);//�ұ߿�
    Line3(760,413,800,413,2,0xCC7722);//�±߿�

    FillEllipse(422,659,352,60,0xCD853F);
    DrawEllipse(422,659,352,60,0x000000);

}










/**
 * @name:���ش���������
 * @description: ִ�п��ش�����ҳ��
*/



void winanime(int *page)//���ش�����
{
    FILE *fp = NULL;
    Robot Rob;
    Windowstate winstate;
    struct tm eventtime;
    Incidentcode incidentcode;


    Rob = init_robot();//��ʼ��������
    
    draw_winbackground(&Rob);//�������ش�ȫ����


    //��ȡWindowstate���жϵ�ǰ����״̬
    fp = fopen("Data\\winstate.dat", "rb");
    if (fp == NULL) 
    {
        perror("�޷��� winstate.dat �ļ�");
        exit(1);
    }

    if (fread(&winstate, sizeof(Windowstate), 1, fp) != 1) 
    {
        perror("��ȡ winstate.dat �ļ�ʱ����");
        fclose(fp);
        exit(1);
    }

    fclose(fp);

    

    //���ݵ�ǰ����״̬���������߹ش�
    if(winstate == WindowClose)
    {
        draw_closewin();//���ش�
    }
    else if(winstate == WindowOpen)
    {
        draw_openwin();//������
    }



    //���п��ش�������Windowstate���жϣ�ִ����Ӧ����
    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);

        if(mouse_press(5, 5, 105, 75)==1) //���·��ذ�ť
        {
            mouse_off(&mouse);
            *page = 12;//���ؼ�ͥ����
            break;
        }

        if(mouse_press(5, 80, 105, 150)==1) //���¿�����ť
        {
            if(winstate == WindowClose) //�����ǹصģ�ȷʵҪ��
            {
                mouse_off(&mouse);//�������ж�

                //tip
                prt_hz16_size(120, 100, 2, 2, "���ڿ�����", 0xFFFAFA, "HZK\\HZK16s");

                /*��¼��־*/
                incidentcode = window_on;
                fstart_diary(&incidentcode, &eventtime);


                openwin_anime(&Rob);//���Ŷ���


               /*����winstate.dat�����windowstate����*/
               winstate = WindowOpen;

               fp = fopen("Data\\winstate.dat", "wb");
               if (fp == NULL) 
               {
                   perror("�޷��� winstate.dat �ļ�");
                   exit(1);
               }
               if (fwrite(&winstate, sizeof(Windowstate), 1, fp) != 1) 
               {
                   perror("д�� winstate.dat �ļ�ʱ����");
                   fclose(fp);
                   exit(1);
               }

               fclose(fp);


               /*��¼��־*/
               incidentcode = window_on;
               fend_diary(&incidentcode, &eventtime);

               //close tip
               bar1(120,100,400,200,0xffffff);
               prt_hz16_size(120, 100, 2, 2, "�����ɹ���", 0xFFFAFA, "HZK\\HZK16s");
               delay(2000);
               bar1(120,100,400,200,0xffffff);

               //�ָ����
               mouse_on(mouse);
            }
            else if(winstate == WindowOpen) //�����������ǿ��ģ�����Ҫ��
            {
                mouse_off(&mouse);
                prt_hz16_size(120, 100, 2, 2, "�����Ѿ����ˣ�", 0xFFFAFA, "HZK\\HZK16s");
                delay(2000);
                bar1(120,100,400,200,0xffffff);
                mouse_show(&mouse);
            }
            

        }
        if(mouse_press(5, 155, 105, 225)==1) //���¹ش���ť
        {
            if(winstate == WindowOpen) //�����ǿ��ģ�ȷʵҪ��
            {
                mouse_off(&mouse);//�������ж�

                //tip
                prt_hz16_size(120, 100, 2, 2, "���ڹش���", 0xFFFAFA, "HZK\\HZK16s");


                /*��¼��־*/
                incidentcode = window_off;
                fstart_diary(&incidentcode, &eventtime);
    
    
                closewin_anime(&Rob);//���Ŷ���  
    
    
                /*����winstate.dat�����windowstate����*/
                winstate = WindowClose;
    
                fp = fopen("Data\\winstate.dat", "wb");
                if (fp == NULL) 
                {
                    perror("�޷��� winstate.dat �ļ�");
                    exit(1);
                }
                if (fwrite(&winstate, sizeof(Windowstate), 1, fp) != 1) 
                {
                    perror("д�� winstate.dat �ļ�ʱ����");
                    fclose(fp);
                    exit(1);
                }
    
                fclose(fp);
    
    
                /*��¼��־*/
                incidentcode = window_off;
                fend_diary(&incidentcode, &eventtime);
    
    
                //close tip
                bar1(120,100,400,200,0xffffff);
                prt_hz16_size(120, 100, 2, 2, "�ش��ɹ���", 0xFFFAFA, "HZK\\HZK16s");
                delay(2000);
                bar1(120,100,400,200,0xffffff);


                //�ָ����
                mouse_on(mouse);
            }
            else if(winstate == WindowClose) //�����������ǹصģ����ù�
            {
                mouse_off(&mouse);
                prt_hz16_size(120, 100, 2, 2, "�����Ѿ����ˣ�", 0xFFFAFA, "HZK\\HZK16s");
                delay(2000);
                bar1(120,100,400,200,0xffffff);
                mouse_show(&mouse);
            }
            
        }


    }


}





//���ƿ����ش���ͬԪ�أ�������
void draw_windowbase()
{
    //�����ӿ��
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
    //����̨
    Line3(516,554,1000,554,2,0x000000);
    ThickDiagonalLine(516,554,505,569,2,0x0000000);
    ThickDiagonalLine(1000,554,989,569,2,0x0000000);
    Line3(505,569,989,569,2,0x000000);
}


//����
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


void draw_closewin()//�ش�
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



//���ƴ������汳���������baseimages
void draw_winbackground(Robot *Rob)
{
    
    Rob->x = 20;
    Rob->y = 370;//�����˳�ʼλ��

    //��ʼ������
    bar1(0, 0, 1024, 768, 0xffffff);

    //���ƴ�̨������Ϊwinbg
    draw_windowbase();
    Save_image(480, 0, 950, 600, "winbg");
    
    //��û����˵ı���Robbg
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height,"Robbg");
    

    //�������������
    robot_set(Rob);

    
    //���ơ����ء���ť
    bar1(5, 5, 105, 75, 0xFF9900);
    bar1(10, 10, 100, 70, 0xFAF0E6);
    prt_hz16_size(23, 24, 2, 2, "����", 0xffffff, "HZK\\HZK16s");

    //���ơ������������ش�����ť
    bar1(5, 80, 105, 150, 0x996B1F);//������ť
    bar1(10, 85, 100, 145, 0x0D33FF);
    prt_hz16_size(23, 99, 2, 2, "����", 0xffffff, "HZK\\HZK16s");
    bar1(5, 155, 105, 225, 0x996B1F);//�ش���ť
    bar1(10, 160, 100, 220, 0x0D33FF);
    prt_hz16_size(23, 174, 2, 2, "�ش�", 0xffffff, "HZK\\HZK16s");

}


//���Ż����˿����Ķ���
void openwin_anime(Robot *Rob)
{
    int i = 0;
    int n = 0;//�������ƶ�����
    int step = 20;//ÿ���ƶ��Ĳ���
    int x_end = 500;//���ﴰ��

    n = (x_end - Rob->x) / step;

    //�ƶ�
    for( i = 0; i < n; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
        //delay(50);//�����ȶ�������
    }


    //����
    delay(1000);
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");//����ǰ�Ȳ��������ˣ�����Robbg������
    Load_image(480, 0, 950, 600, "winbg");//���»��ô�̨
    draw_openwin();//����
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height,"Robbg");//���±���
    robot_set(Rob);//���»��ƻ�����
    delay(1000);
    


    //��ȥ
    for( i = 0; i < n; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
        //delay(50);//�����ȶ�������
    }
    
}


//���Ż����˹ش��Ķ���
void closewin_anime(Robot *Rob)
{
    int i = 0;
    int n = 0;//�������ƶ�����
    int step = 20;//ÿ���ƶ��Ĳ���
    int x_end = 500;//���ﴰ��

    n = (x_end - Rob->x) / step;

    //�ƶ�
    for( i = 0; i < n; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x += step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
        //delay(50);//�����ȶ�������
    }


    //�ش�
    delay(1000);
    Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height, "Robbg");//����ǰ�Ȳ��������ˣ�����Robbg������
    Load_image(480, 0, 950, 600, "winbg");//���»��ô�̨
    draw_closewin();//�ش�
    Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
        Rob->y + Rob->height,"Robbg");//���±���
    robot_set(Rob);//���»��ƻ�����
    delay(1000);


    //��ȥ
    for( i = 0; i < n; i++)
    {
        //���ֱ�������ԭ�ط��Ļ�����
        Load_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height, "Robbg");

        //�洢��һ������
        Rob->x -= step;

        Save_image(Rob->x, Rob->y, Rob->x + Rob->width, 
            Rob->y + Rob->height,"Robbg");
        
        //���ƻ����˵���һ�ط�
        robot_set(Rob);
        //delay(50);//�����ȶ�������
    }



    
}



