#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

/*没错，用多个宏定义简化代码，这可是最新操作！*/
/*惊喜不惊喜，意外不意外？*/
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
S C *Creat_new();//初次运行程序时新建链表
void Open_File(char *openmode);//打开文件
void Close_File();//关闭文件
void Build_File();//初次运行程序时新建数据文件
void Use_Card(S C *H,I T);//消费
void Insert_Card(S C *H,I T);//插入新饭卡信息
void Charge_Money(S C *H,I T);//充值
void Delete_Card(S C *H,I T);//注销饭卡
void Lost_Card(S C *H,I T);//挂失饭卡
void Search_Card(S C *H,I T);//查找指定饭卡数据
void Start_Card(S C *H,I T);//初次运行程序时输入的初始数据
void Sort_Card(S C *H,I T);//对饭卡数据进行排序
void Print_Card(S C *H);//遍历饭卡文件
I Input_Choice();//输入的选项编号
I Check_Card(S C *H,I T,I num);//检查某编号的饭卡是否存在

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
        if(H==NULL)//由于初次执行程序时会出现群龙无首的错误，所以把「第一次接收数据」和「第N次接收数据」分类讨论（我没别的意思，别想歪了）
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
                P("请输入饭卡号:");
                N("%d",&num);
                P("饭卡不存在!\n");
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
    P("感谢使用本软件。已正常退出，按任意键结束。\n");
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
            P("☆  请输入选项编号（0-9）:  ☆");
        else if(i==4)
            P("★    1--建立饭卡文件       ★");
        else if(i==5)
            P("★    2--消费               ★");
        else if(i==6)
            P("★    3--充值               ★");
        else if(i==7)
            P("★    4--添加新饭卡         ★");
        else if(i==8)
            P("★    5--注销旧饭卡         ★");
        else if(i==9)
            P("★    6--设置与解除挂失     ★");
        else if(i==10)
            P("★    7--查询饭卡信息       ★");
        else if(i==11)
            P("★    8--排序饭卡信息       ★");
        else if(i==12)
            P("★    9--遍历饭卡信息       ★");
        else if(i==13)
            P("★    0--退出系统           ★");
        P("\n");
    }
    P("\n请输入选项编号:");
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

void fp_file(S C *H,I flag)//把内存链表中储存的文本内容写回到存储介质中的文件
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
    P("文件建立成功！\n");
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
    P("请输入饭卡号:");
    N("%ld",&num);
    if(Check_Card(H,T,num)==-1)
        P("饭卡不存在！\n");
    else
    {
        P("请输入饭费:");
        N("%lf",&charge);
        while(T>0)//遍历饭卡，找到使用者的卡并进行扣费
        {
            if(p->number==num)
            {
                if(p->money<5)
                    P("余额不足，请充值！\n");
                else if(p->lost==1)
                    P("本卡已冻结！\n");
                else
                {
                    balance=p->money-charge;
                    if(balance<0) P("余额不足，请充值！\n");
                    else
                    {
                        P("买饭前余额:%.2f\n",p->money);
                        p->money=balance;
                        P("买饭后余额:%.2f\n",p->money);
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
    P("请输入饭卡号:");
    N("%ld",&num);
    if(Check_Card(H,T,num)==-1)   P("饭卡不存在！\n");
    else
    {
        P("请输入充值额:");
        N("%lf",&charge);
        while(T>0)
        {
            if(p->number==num)
            {
                if(p->lost==1)   P("本卡已冻结!\n");
                else
                {
                    P("充值前余额:%.2f\n",p->money);
                    p->money=p->money+charge;
                    P("充值后余额:%.2f\n",p->money);
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
    strcpy(a,"是");
    while(strcmp(a,"是")==0)
    {
        P("请输入饭卡号：");
        N("%ld",&new_data.number);
        if(Check_Card(H,T,new_data.number)==1)
            P("饭卡已存在！\n");
        else
        {
            P("请输入姓名：");
            N("%s",new_data.name);
            P("请输入金额：");
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
        P("是否继续添加饭卡号：");
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
    P("请输入饭卡号：");
    N("%ld",&new_data.number);
    P("请输入姓名：");
    N("%s",new_data.name);
    P("请输入金额：");
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
    P("请输入饭卡号:");
    N("%ld",&num);
    S C *p1,*p2,*p;
    p2=p1=H;
    if(Check_Card(H,T,num)==-1)
        P("饭卡不存在！\n");
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
        P("旧饭卡注销成功！\n");
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
    P("请输入饭卡号:");
    N("%ld",&num);
    if(Check_Card(H,T,num)==-1)
        P("饭卡不存在！\n");
    else
    {
        while(T>0)
        {
            if(p->number==num)
            {
                if(p->lost==0)
                {
                    P("当前饭卡未挂失！是否挂失:");
                    N("%s",a);
                    if(strcmp(a,"是")==0)
                        p->lost=1;
                }
                else if(p->lost==1)
                {
                    P("当前饭卡已挂失！是否解除挂失:");
                    N("%s",a);
                    if(strcmp(a,"是")==0)
                        p->lost=0;
                }
            }
            p=p->next;
            T--;
        }
        fp_file(H,flag);
        P("操作成功！\n");
    }
    system("pause");
    system("cls");
}

void Search_Card(S C *H,I T)
{
    long num;
    S C *p;
    p=H;
    P("请输入饭卡号:");
    N("%ld",&num);
    if(Check_Card(H,T,num)==-1)
        P("饭卡不存在！\n");
    else
    {
        P("饭卡号\t姓名\t金额\t是否挂失\n");
        while(T>0)
        {
            if(p->number==num)
            {
                if(p->lost==0)
                    P("%ld\t%s\t%.2f\t%s\n",p->number,p->name,p->money,"否");
                else
                    P("%ld\t%s\t%.2f\t%s\n",p->number,p->name,p->money,"是");
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

void Sort_Card(S C *H,I T)//通过两个指针就能实现链表的冒泡排序
{
    S C *p1,*p2,temp;
    I i,j,k;
    p1=p2=H;

    P("1.由大到小排列\n2.由小到大排列 \n请选择排列方式：\n");
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
            P("请输入正确的选项编号！\n");
    }
    P("已按照您的选项进行排列！\n");
    fp_file(H,T);
    system("pause");
    system("cls");
}

void Print_Card(S C *H)
{
    S C *p;
    P("学生饭卡信息如下：\n");
    P("饭卡号\t姓名\t金额\t是否挂失\n");
    for(p=H;p!=NULL;p=p->next)
    {
        if(p->lost==0)
            P("%ld\t%s\t%.2f\t%s\n",p->number,p->name,p->money,"否");
        else
            P("%ld\t%s\t%.2f\t%s\n",p->number,p->name,p->money,"是");
    }
    system("pause");
    system("cls");
}
