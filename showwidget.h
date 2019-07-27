#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

#include <QPen>
#include <QPainter>
#include <QtSvg/QSvgWidget>
#include <QtSvg/QSvgRenderer>
#include <QMouseEvent>
#include <QtCharts>

#include "qcustomplot.h"

extern int flag0 ;
extern int flag1 ;
extern QString dataxy ;
extern double datax;
extern double datay;
extern double dataflag;



class ShowWidget : public QWidget

{
    Q_OBJECT

public:
    explicit ShowWidget(QWidget *parent = 0);
    QImage img;

    QChartView *ChartView;
    QChart *Chart;
    QLineSeries *series;
    QValueAxis *axisx;
    QValueAxis *axisy;
    //一些函数
    void update_Data(double x,double y);
    void set_Chart();
    QCustomPlot *Plot;




signals:


public slots:

    void receive_Data(QString All);

    void on_restart_clicked();

    void myMoveEvent(QMouseEvent *event);

private:

  QRubberBand *rubberBand;
  QPoint rubberOrigin;


};

#endif // SHOWWIDGET_H
