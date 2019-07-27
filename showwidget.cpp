#include "showwidget.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QChart>

//全局变量
int flag0 = 0;//这个暂时没什么用
int flag1 = 0;//这个暂时没什么用
QString dataxy;
double datax = 0;
double datay = 0;
double dataflag = -10;//用来判断是否重新画一条线,设为-10是因为要保证flag小于第一个x值

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
//主界面图窗口显示
    Plot = new QCustomPlot;
    Plot->addGraph();
    Plot->addGraph();
//设置x,y坐标轴
    Plot->xAxis->setLabel("Potential/v");
    Plot->yAxis->setLabel("Current/1e-6A");
    Plot->xAxis->setRange(-2,2);//设置范围
    Plot->yAxis->setRange(-1,3);
    Plot->xAxis->setLabelColor(QColor(40,80,65));//设置x,y轴名称颜色
    Plot->yAxis->setLabelColor(QColor(40,80,65));
    Plot->xAxis->setLabelFont(QFont("Times", 15,QFont::Bold));//设置x,y轴名称字体
    Plot->yAxis->setLabelFont(QFont("Times", 15,QFont::Bold));
    Plot->xAxis->setTickLength(10);
    Plot->yAxis->setTickLength(10);
    Plot->xAxis->setTickPen(QColor(40,80,65));
    Plot->yAxis->setTickPen(QColor(40,80,65));
    Plot->xAxis->setBasePen(QColor(40,80,65));
    Plot->yAxis->setBasePen(QColor(40,80,65));

    Plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    Plot->graph(0)->setPen(QPen(QColor(70,0,70)));//设置画笔颜色
    Plot->graph(1)->setLineStyle(QCPGraph::lsLine);
    Plot->graph(1)->setPen(QPen(QColor(70,0,70)));//设置画笔颜色

    //设置可拖拽 滚轮放大缩小 图像可选择
    Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    connect(Plot,&QCustomPlot::mouseMove,this,&ShowWidget::myMoveEvent);
    QGridLayout *MainW = new QGridLayout(this);//为什么这里必须加this
    MainW->addWidget(Plot);
    set_Chart();

}
void ShowWidget::set_Chart()
{


}
void ShowWidget::on_restart_clicked()//当按下重新开始按钮时，应该将坐标轴设置为原来的样子
{
//各个全局变量得清空
    flag0 = 0;//这个暂时没什么用
    flag1 = 0;//这个暂时没什么用
    dataxy.clear();
    dataflag = -10;
    Plot->graph(0)->data().data()->clear();
    Plot->graph(1)->data().data()->clear();
    Plot->replot();

}




void ShowWidget::update_Data(double x,double y)
{
   if (flag0 ==  0)
   {
         Plot->graph(0)->addData(x,y);
   }
   else if(flag0 == 1)
   {
         Plot->graph(1)->addData(x,y);
   }
   Plot->replot();
}




void ShowWidget::receive_Data(QString All)
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
       if(X[i].length() == 17)
       {
           QStringList x1 = X[i].split(", ");
           datax = x1[0].toDouble();
           if (x1[1].contains("e-06"))
           {
               datay = x1[1].mid(0,5).toDouble();
           }
           else if (x1[1].contains("e-05"))
           {
               datay = x1[1].mid(0,5).toDouble();
               datay = datay*10;
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
           qDebug("0");
       }
       else
       {
           flag0 = 1;
           qDebug("1");
       }

       //将新数据进行更新，根据flag0就能判断好进哪个graph
       if (i >= flag1)
       {
           update_Data(datax,datay);
           flag1++;
       }


   }

}
void ShowWidget::myMoveEvent(QMouseEvent *event)
{

    double x = event->pos().x();
    double y = event->pos().y();

    double x_ = Plot->xAxis->pixelToCoord(x);
    double y_ = Plot->yAxis->pixelToCoord(y);



    QString str = QString("x:%1,y:%2\n"
                          "滚轮滚动放大缩小\n"
                          "鼠标拖拽移动位置").arg(QString::number(x_,10,3))
            .arg(QString::number(y_,10,3));

/*
 *  获取当前图像线上的数据点
    for(int i = 0;i<m_plot->xAxis->graphs().count();i++)
    {
        double _x = m_plot->graph(0)->data().data()->at(i)->key;
        double _y = m_plot->graph(0)->data().data()->at(i)->value;
    }
*/


    QToolTip::showText(cursor().pos(),str,Plot);



}
