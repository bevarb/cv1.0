#include "thread.h"
#include <QThread>
#include <QDebug>
Thread::Thread(QObject *parent) : QObject(parent)
{

}
//全局变量
int flag0 = 0;//用来确定用哪条线进行绘图
int flag1 = 0;//用来确定是否更新数据

double dataflag = -10;//用来判断是否重新画一条线,设为-10是因为要保证flag小于第一个x值
QString dataxy;
double datax = 0;
double datay = 0;
void Thread::on_restart_Clicked()
{
    qDebug() <<"还原数据";
    flag0 = 0;//
    flag1 = 0;//
    dataxy.clear();
    dataflag = -10;
}

void Thread::receive_Data(QString All)
{



    //先对数据进行预处理，去头去尾
    if (All.contains("START")&!All.contains("END"))
    {

        int id = All.indexOf("START");
        QString s = All.mid(id+5).trimmed();
        dataxy = s ;

    }
    else if (All.contains("START")&All.contains("END"))
    {
        int id1 = All.indexOf("START");
        QString s1 = All.mid(id1+5).trimmed();

        int id2 = All.indexOf("END");
        QString s2 = All.mid(0,id2).trimmed();

        dataxy = s2;

    }

   //再将每组数据拆分开

    QStringList X = dataxy.split("\r\n");
    int l = X.size();

    //再使用循环将每组数据的x,y整理处理
   for(int i=0 ; i<l ;i++)
    {
       if(X[i].contains("\r\n"))
       {
           QString str = X[i];
           str = str.trimmed();
           X[i] = str;
       }

       if(X[i].length() >= 17)
       {
           QStringList x1 = X[i].split(", ");
           datax = x1[0].toDouble();
           if (x1[1].contains("e-07"))
           {
               datay = x1[1].mid(0,5).toDouble();
           }
           else if (x1[1].contains("e-05"))
           {
               datay = x1[1].mid(0,5).toDouble();
               datay = datay*100;
           }
           else if (x1[1].contains("e-06"))
           {
               datay = x1[1].mid(0,5).toDouble();
               datay = datay*10;
           }
           else if (x1[1].contains("e-08"))
           {
               datay = x1[1].mid(0,5).toDouble();
               datay = datay/10;
           }
           else if (x1[1].contains("e-09"))
           {
               datay = x1[1].mid(0,5).toDouble();
               datay = datay/100;
           }

       }
       else
       {
           return;
       }


       if (datax >dataflag)//判断那个x开始减小的临界点
       {
           dataflag = datax;
           flag0 = 0;
       }
       else
       {
           flag0 = 1;
       }

       //将新数据进行更新，根据flag0就能判断好进哪个graph
       if (i >= flag1)
       {
           emit clean_Data(datax,datay,flag0);

           flag1++;
       }


   }

}
