#include <allfunc.h>

void main()
{      
	/*
	********************
	func��Ӧҳ��ֵ

	2-��ʼ�˵�����¼���棻
	3-ע����棻
	4-�˵�����
	5-������⣻
	6-ƽ��ͼ��
	7-������
	8-ɨ�أ�
	9-�˲赹ˮ��
	10-�����ش���
	11-����������
	12-��ͥ����
	13-��������־���棻
	14-��ͣ�
	15-���칦�ܣ�
	16-����
	17-ƽ��ͼ
	100-�˳�
	
	********************
	*/
	int page=2;
    int unum=0;
    FILE *file = NULL;


	//����roomid�ļ�
    file = fopen("Data\\roomid.dat", "wb");
    if (file == NULL) {
        perror("Failed to create roomid.dat file");
        return;
    }
    fclose(file);
	

    SetSVGA64k();//����SVGA��ͼ����
	bar1(0, 0,1024,768, 0xffffff);
	Readbmp64k(0,0,"bmp\\logo4.bmp");
    mouse_init();


	finitialize_diary();//��ʼ����־��д��<struct Todaydata>
	initialize_fundation();//��ʼ���������ݣ�����ֻ�д���״̬��д��<winstate.dat>

	

    
	while(1)   
	{
		mouse_show(&mouse);
		switch (page)
		{
		
			case 2://��½
			{
				log_in(&page,&unum);
				break;
			}
			case 3://ע��
			{
				register_in(&page);
				break;
			}
			case 4://�˵�����
			{
				menu_on(&page);
				break;
			}
			case 5://�������
			{
				healthmonitor(&page);
				break;

			}
			case  7://����
			{
				wateranime(&page);
				break;
			}
			case  8://ɨ��
			{
				brushanime(&page);
				break;
			}
			case  9://�˲赹ˮ
			{
				teaanime(&page);
				break;
			}
			case  10://�����ش�
			{
				winanime(&page);
				break;
			}
			case  11://��������
			{
				cook_meal(&page);
				break;
			}
			case  12://��ͥ����
			{
				Familyhelp(&page);
				break;
			}
			case  13://��������־����
			{
				diarywin(&page);
				break;
			}
			case  14://���
			{
				orderfood(&page);
				break;
			}
			case  15://���칦��
			{
				chat_robot(&page);
				break;
			}
			case  16://����
			{
				in_bedroom(&page);
				break;
			}
			case 17://ƽ��ͼ
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
	CloseSVGA();//�ر�ͼ�ν��� 
}