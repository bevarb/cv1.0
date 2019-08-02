#ifndef THREAD_H
#define THREAD_H

#include <QObject>


extern QString dataxy ;
extern double datax;
extern double datay;

extern int flag0 ;
extern int flag1 ;

extern double dataflag;



class Thread : public QObject
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = nullptr);

    void close_Thread();

signals:

    void clean_Data(double,double,int);

public slots:


    void receive_Data(QString All);

    void on_restart_Clicked();
};

#endif // THREAD_H
