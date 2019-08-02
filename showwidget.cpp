#include "showwidget.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QChart>

#include <QThread>
#include <QDebug>
#include <QMutexLocker>
#include <QElapsedTimer>
#include <limits>




ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
//主界面图窗口显示
    Plot = new QCustomPlot;
    Plot->addGraph();
    Plot->addGraph();
//设置x,y坐标轴
    Plot->xAxis->setLabel("Potential/v");
    Plot->yAxis->setLabel("Current/1e-7A");
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
    QPen pen(QColor(70,100,70), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    Plot->graph(0)->setPen(pen);//设置画笔颜色
    Plot->graph(1)->setLineStyle(QCPGraph::lsLine);
    Plot->graph(1)->setPen(pen);//设置画笔颜色

    //设置可拖拽 滚轮放大缩小 图像可选择
    Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    connect(Plot,&QCustomPlot::mouseMove,this,&ShowWidget::myMoveEvent);
    QGridLayout *MainW = new QGridLayout(this);//为什么这里必须加this
    MainW->addWidget(Plot);
  //  set_Chart();

}
void ShowWidget::set_Chart()
{


}
void ShowWidget::on_restart_clicked()//当按下重新开始按钮时，应该将坐标轴设置为原来的样子
{
//各个全局变量得清空

    Plot->graph(0)->data().data()->clear();
    Plot->graph(1)->data().data()->clear();
    Plot->replot();

}




void ShowWidget::update_Data(double x,double y,int flag)
{

    qDebug() << x  << y << flag;
    if (flag ==  0)
   {
         Plot->graph(0)->addData(x,y);
   }
   else if(flag == 1)
   {
         Plot->graph(1)->addData(x,y);
   }
   Plot->replot();
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


    QToolTip::showText(cursor().pos(),str,Plot);



}
