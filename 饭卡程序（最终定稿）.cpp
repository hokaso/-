#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

/*û���ö���궨��򻯴��룬��������²�����*/
/*��ϲ����ϲ�����ⲻ���⣿*/
#define C card_imf
#define S struct
#define SIZE sizeof(S C)
#define T count
#define H head
#define I int
#define P printf
#define N scanf

S C
{
    long number;
    char name[20];
    double money;
    I lost;
    S C *next;
};

I user_choice;
FILE *fp;
S C *Creat_new();//�������г���ʱ�½�����
void Open_File(char *openmode);//���ļ�
void Close_File();//�ر��ļ�
void Build_File();//�������г���ʱ�½������ļ�
void Use_Card(S C *H,I T);//����
void Insert_Card(S C *H,I T);//�����·�����Ϣ
void Charge_Money(S C *H,I T);//��ֵ
void Delete_Card(S C *H,I T);//ע������
void Lost_Card(S C *H,I T);//��ʧ����
void Search_Card(S C *H,I T);//����ָ����������
void Start_Card(S C *H,I T);//�������г���ʱ����ĳ�ʼ����
void Sort_Card(S C *H,I T);//�Է������ݽ�������
void Print_Card(S C *H);//���������ļ�
I Input_Choice();//�����ѡ����
I Check_Card(S C *H,I T,I num);//���ĳ��ŵķ����Ƿ����

I main()
{
    long num;
    while((user_choice=Input_Choice())!=0)
    {
        I T=1;
        S C *H,*p;
        if(user_choice==1)
            Build_File();
        H=Creat_new();
        if(H==NULL)//���ڳ���ִ�г���ʱ�����Ⱥ�����׵Ĵ������԰ѡ���һ�ν������ݡ��͡���N�ν������ݡ��������ۣ���û�����˼���������ˣ�
        {
            switch(user_choice)
            {
            case 2:
            case 3:
            case 4:
                Start_Card(H,T);
                break;
            case 5:
            case 6:
            case 7:
                P("�����뷹����:");
                N("%d",&num);
                P("����������!\n");
                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                break;
            }
        }
        else
        {
            p=H;
            while(p->next!=NULL)
            {
                p=p->next;
                T++;
            }
            switch(user_choice)
            {
            case 2:
                Use_Card(H,T);
                break;
            case 3:
                Charge_Money(H,T);
                break;
            case 4:
                Insert_Card(H,T);
                break;
            case 5:
                Delete_Card(H,T);
                break;
            case 6:
                Lost_Card(H,T);
                break;
            case 7:
                Search_Card(H,T);
                break;
            case 8:
                Sort_Card(H,T);
                break;
            case 9:
                Print_Card(H);
                break;
            default:
                system("cls");
                break;
            }
        }
    }
    P("��лʹ�ñ�������������˳����������������\n");
    return 0;
}

I Input_Choice()
{

    I i,j,k;
    for(i=1; i<=14; i++)
    {
        for(j=1; j<=20; j++)
            P(" ");
        if(i==1||i==3||i==14)
        {
            for(k=1; k<=30; k++)
                P("-");
        }
        else if(i==2)
            P("��  ������ѡ���ţ�0-9��:  ��");
        else if(i==4)
            P("��    1--���������ļ�       ��");
        else if(i==5)
            P("��    2--����               ��");
        else if(i==6)
            P("��    3--��ֵ               ��");
        else if(i==7)
            P("��    4--����·���         ��");
        else if(i==8)
            P("��    5--ע���ɷ���         ��");
        else if(i==9)
            P("��    6--����������ʧ     ��");
        else if(i==10)
            P("��    7--��ѯ������Ϣ       ��");
        else if(i==11)
            P("��    8--���򷹿���Ϣ       ��");
        else if(i==12)
            P("��    9--����������Ϣ       ��");
        else if(i==13)
            P("��    0--�˳�ϵͳ           ��");
        P("\n");
    }
    P("\n������ѡ����:");
    N("%d",&user_choice);
    return user_choice;
}

void Close_File()
{
    if(fclose(fp))
    {
        P("Can not close the file!\n");
        exit(0);
    }
}

void Open_File(char *openmode)
{
    if((fp=fopen("card.dat",openmode))==NULL)
    {
        P("File open error!\n");
        exit(0);
    }
}

S C *Creat_new()
{
    Open_File("r");
    S C data;
    S C *H,*tail,*p;
    H=tail=NULL;
    while(fscanf(fp,"%ld%s%lf%d",&data.number,data.name,&data.money,&data.lost)!=EOF)
    {
        p=(S C *)malloc(SIZE);
        p->number=data.number;
        strcpy(p->name,data.name);
        p->money=data.money;
        p->lost=data.lost;
        p->next=NULL;
        if(H==NULL)
            H=p;
        else
            tail->next=p;
        tail=p;
    }
    Close_File();
    return H;
}

void fp_file(S C *H,I flag)//���ڴ������д�����ı�����д�ص��洢�����е��ļ�
{
    S C *p;
    Open_File("w");
    p=H;
    while(flag>0)
    {
        fprintf(fp,"%ld\t%s\t%f\t%d\n",p->number,p->name,p->money,p->lost);
        p=p->next;
        flag--;
    }
    Close_File();
}

void Build_File()
{
    Open_File("w");
    P("�ļ������ɹ���\n");
    Close_File();
    system("pause");
    system("cls");
}

void Use_Card(S C *H,I T)
{
    long num;
    I flag=T;
    double balance,charge;
    S C *p;
    p=H;
    P("�����뷹����:");
    N("%ld",&num);
    if(Check_Card(H,T,num)==-1)
        P("���������ڣ�\n");
    else
    {
        P("�����뷹��:");
        N("%lf",&charge);
        while(T>0)//�����������ҵ�ʹ���ߵĿ������п۷�
        {
            if(p->number==num)
            {
                if(p->money<5)
                    P("���㣬���ֵ��\n");
                else if(p->lost==1)
                    P("�����Ѷ��ᣡ\n");
                else
                {
                    balance=p->money-charge;
                    if(balance<0) P("���㣬���ֵ��\n");
                    else
                    {
                        P("��ǰ���:%.2f\n",p->money);
                        p->money=balance;
                        P("�򷹺����:%.2f\n",p->money);
                    }
                }
                break;
            }
            p=p->next;
            T--;
        }
        fp_file(H,flag);
    }
    system("pause");
    system("cls");
}

void Charge_Money(S C *H,I T)
{
    long num;
    I flag=T;
    double charge;
    S C *p;
    p=H;
    P("�����뷹����:");
    N("%ld",&num);
    if(Check_Card(H,T,num)==-1)   P("���������ڣ�\n");
    else
    {
        P("�������ֵ��:");
        N("%lf",&charge);
        while(T>0)
        {
            if(p->number==num)
            {
                if(p->lost==1)   P("�����Ѷ���!\n");
                else
                {
                    P("��ֵǰ���:%.2f\n",p->money);
                    p->money=p->money+charge;
                    P("��ֵ�����:%.2f\n",p->money);
                }
                break;
            }
            p=p->next;
            T--;
        }
        fp_file(H,flag);
    }
    system("pause");
    system("cls");
}

void Insert_Card(S C *H,I T)
{
    char a[5];
    S C *p1,*p2,new_data;
    p2=H;
    strcpy(a,"��");
    while(strcmp(a,"��")==0)
    {
        P("�����뷹���ţ�");
        N("%ld",&new_data.number);
        if(Check_Card(H,T,new_data.number)==1)
            P("�����Ѵ��ڣ�\n");
        else
        {
            P("������������");
            N("%s",new_data.name);
            P("�������");
            N("%lf",&new_data.money);
            new_data.lost=0;
            p1=(S C *)malloc(SIZE);
            p1->number=new_data.number;
            strcpy(p1->name,new_data.name);
            p1->money=new_data.money;
            p1->lost=new_data.lost;
            while(p2->next!=NULL)
                p2=p2->next;
            p2->next=p1;
            p2=p1;
            p2->next=NULL;
            T++;
            fp_file(H,T);
        }
        P("�Ƿ������ӷ����ţ�");
        getchar();
        gets(a);
    }
    system("pause");
    system("cls");
}

void Start_Card(S C *H,I T)
{
    S C *p;
    S C new_data;
    P("�����뷹���ţ�");
    N("%ld",&new_data.number);
    P("������������");
    N("%s",new_data.name);
    P("�������");
    N("%lf",&new_data.money);
    new_data.lost=0;
    p=(S C *)malloc(SIZE);
    p->number=new_data.number;
    strcpy(p->name,new_data.name);
    p->money=new_data.money;
    p->lost=new_data.lost;
    H=p;
    H->next==NULL;
    fp_file(H,T);
    system("pause");
    system("cls");
}

void Delete_Card(S C *H,I T)
{
    long num;
    I flag=T;
    P("�����뷹����:");
    N("%ld",&num);
    S C *p1,*p2,*p;
    p2=p1=H;
    if(Check_Card(H,T,num)==-1)
        P("���������ڣ�\n");
    else
    {
        Open_File("w");
        while(T>0)
        {
            if(p1->number==num)
            {
                if(p1==H)
                {
                    H=p1->next;
                }
                else
                {
                    p2->next=p1->next;
                }
                free(p1);
                goto loop;
            }
            p2=p1;
            p1=p1->next;
            T--;
        }
        loop:p=H;
        while(flag>1)
        {
            fprintf(fp,"%ld\t%s\t%f\t%d\n",p->number,p->name,p->money,p->lost);
            p=p->next;
            flag--;
        }
        Close_File();
        P("�ɷ���ע���ɹ���\n");
    }
    system("pause");
    system("cls");
}

void Lost_Card(S C *H,I T)
{
    I flag=T;
    char a[5];
    long num;
    S C *p;
    p=H;
    P("�����뷹����:");
    N("%ld",&num);
    if(Check_Card(H,T,num)==-1)
        P("���������ڣ�\n");
    else
    {
        while(T>0)
        {
            if(p->number==num)
            {
                if(p->lost==0)
                {
                    P("��ǰ����δ��ʧ���Ƿ��ʧ:");
                    N("%s",a);
                    if(strcmp(a,"��")==0)
                        p->lost=1;
                }
                else if(p->lost==1)
                {
                    P("��ǰ�����ѹ�ʧ���Ƿ�����ʧ:");
                    N("%s",a);
                    if(strcmp(a,"��")==0)
                        p->lost=0;
                }
            }
            p=p->next;
            T--;
        }
        fp_file(H,flag);
        P("�����ɹ���\n");
    }
    system("pause");
    system("cls");
}

void Search_Card(S C *H,I T)
{
    long num;
    S C *p;
    p=H;
    P("�����뷹����:");
    N("%ld",&num);
    if(Check_Card(H,T,num)==-1)
        P("���������ڣ�\n");
    else
    {
        P("������\t����\t���\t�Ƿ��ʧ\n");
        while(T>0)
        {
            if(p->number==num)
            {
                if(p->lost==0)
                    P("%ld\t%s\t%.2f\t%s\n",p->number,p->name,p->money,"��");
                else
                    P("%ld\t%s\t%.2f\t%s\n",p->number,p->name,p->money,"��");
                break;
            }
            p=p->next;
            T--;
        }
    }
    system("pause");
    system("cls");
}

I Check_Card(S C *H,I T,I num)
{
    S C *p;
    p=H;
    while(T>0)
    {
        if(p->number==num)
            break;
        T--;
        p=p->next;
    }
    if(T==0)
        return -1;
    else
        return 1;
}

void Sort_Card(S C *H,I T)//ͨ������ָ�����ʵ�������ð������
{
    S C *p1,*p2,temp;
    I i,j,k;
    p1=p2=H;

    P("1.�ɴ�С����\n2.��С�������� \n��ѡ�����з�ʽ��\n");
    while(i!=1&&i!=2)
    {
        N("%d",&i);
        if(i==1)
        {
            for(j=1; j<T; j++)
            {
                p2=p2->next;
                for(k=0; k<(T-j); k++)
                {
                    if((p1->number)<(p2->number))
                    {
                        temp=*p1;
                        temp.next=p2->next;
                        *p1=*p2;
                        *p2=temp;
                        p1->next=p2;
                    }
                    p2=p2->next;
                    p1=p1->next;
                }
                p2=p1=H;
            }
        }
        else if(i==2)
        {
            for(j=1; j<T; j++)
            {
                p2=p2->next;
                for(k=0; k<(T-j); k++)
                {
                    if((p1->number)>(p2->number))
                    {
                        temp=*p1;
                        temp.next=p2->next;
                        *p1=*p2;
                        *p2=temp;
                        p1->next=p2;
                    }
                    p2=p2->next;
                    p1=p1->next;
                }
                p2=p1=H;
            }
        }
        else
            P("��������ȷ��ѡ���ţ�\n");
    }
    P("�Ѱ�������ѡ��������У�\n");
    fp_file(H,T);
    system("pause");
    system("cls");
}

void Print_Card(S C *H)
{
    S C *p;
    P("ѧ��������Ϣ���£�\n");
    P("������\t����\t���\t�Ƿ��ʧ\n");
    for(p=H;p!=NULL;p=p->next)
    {
        if(p->lost==0)
            P("%ld\t%s\t%.2f\t%s\n",p->number,p->name,p->money,"��");
        else
            P("%ld\t%s\t%.2f\t%s\n",p->number,p->name,p->money,"��");
    }
    system("pause");
    system("cls");
}
