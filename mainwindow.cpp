#include "mainwindow.h"
#include <QTextEdit>
#include <QDockWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QGridLayout>
#include <QtGui>
#include <QLabel>
#include <QFileDialog>
#include <QAction>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>

#include <synchapi.h>

void MainWindow::createActions()
{
    OpenFileAction = new QAction(QIcon("Open.png"),tr("Open"),this);
    OpenFileAction->setShortcut(tr("Ctrl+O"));
    OpenFileAction->setStatusTip(tr("Open one file"));
    connect(OpenFileAction,&QAction::triggered,[=] ()
    {
          QString path = QFileDialog::getOpenFileName(
                      this,"open","../",
                      "souce(*.cpp *.h);;Text(*.txt);;All(*.*)");
    }
            );
    NewFileAction = new QAction(QIcon("Open.png"),tr("New"),this);
    NewFileAction->setShortcut(tr("Ctrl+N"));
    NewFileAction->setStatusTip(tr("Build one new file"));
    connect(NewFileAction,SIGNAL(triggered()),this,SLOT(showNewFile()));
    ExitAction = new QAction(QIcon("Open.png"),tr("Exit"),this);
    ExitAction->setShortcut(tr("Ctrl+N"));
    ExitAction->setStatusTip(tr("Exit"));
    CopyAction = new QAction(QIcon("Open.png"),tr("Copy"),this);
    CopyAction->setShortcut(tr("Ctrl+Q"));
    CopyAction->setStatusTip(tr("Exit"));
    //connect(CopyAction,SIGNAL(triggered()),showWidget->text,SLOT(copy()));
    CutAction = new QAction(QIcon("Open.png"),tr("Cut"),this);
    CutAction->setShortcut(tr("Crtl+C"));
    //connect(CutAction,SIGNAL(triggered()),showWidget->text,SLOT(cut()));
    PasteAction = new QAction(QIcon("Open.png"),tr("Paste"),this);
    PasteAction->setShortcut(tr("Ctrl+V"));
    //connect(PasteAction,SIGNAL(triggered()),showWidget->text,SLOT(paste()));
    ZoomInAction = new QAction(QIcon("Open.png"),tr("ZoomIn"),this);
    connect(ZoomInAction,SIGNAL(triggered()),this,SLOT(showZoomIn()));
    ZoomOutAction = new QAction(QIcon("Open.png"),tr("ZoomOut"),this);
    connect(ZoomOutAction,SIGNAL(triggered()),this,SLOT(showZoomOut()));//图标未设置，均采用open.png

}
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(OpenFileAction);
    fileMenu->addAction(NewFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(ExitAction);

}
void MainWindow::createToolBars()
{
    Tool = addToolBar("Tool");
    Tool->addAction(CopyAction);
    Tool->addAction(CutAction);
    Tool->addAction(PasteAction);
    Tool->addAction(ZoomInAction);
    Tool->addAction(ZoomOutAction);
    Tool->setAllowedAreas(Qt::TopToolBarArea);

}


void MainWindow::showNewFile()//新建文件，这里需要修改
{
    MainWindow *newFile = new MainWindow;
    newFile->show();
}
void MainWindow::showZoomIn()//下面这两个要修改，能够将实时图像放大或者缩小
{

}
void MainWindow::showZoomOut()//
{

}
void MainWindow::bluetooth()//蓝牙模块
{
    QDockWidget *dock1 = new QDockWidget(tr("DockWindow1"));
    dock1->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable); //窗口可移动
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

    addDockWidget(Qt::RightDockWidgetArea,dock1);
    dock1->setStyleSheet("QPushButton{color:white;background-color:black}");//按钮样式设置
    BlueToothLabel = new QLabel(tr("Port name: "));
    ConnectBtn = new QPushButton("Connect");
    BreakBtn = new QPushButton(tr("Break"));
    Stop1Btn = new QPushButton(tr("Stop"));
    BlueToothPortComboBox = new QComboBox;

    BaudRateLabel = new QLabel(tr("BaudRate: "));
    BaudRateComBox = new QComboBox;
    BaudRateComBox->addItem(tr("9600"));
    BaudRateComBox->addItem(tr("11520"));

    DateRateLabel = new QLabel(tr("DateRate: "));
    DateRateComBox = new QComboBox;
    DateRateComBox->addItem("5");
    DateRateComBox->addItem("6");
    DateRateComBox->addItem("7");
    DateRateComBox->addItem("8");
    DateRateComBox->setCurrentIndex(3);//设置下拉选择默认为第4个
    ParityLabel = new QLabel("Parity");
    ParityComBox = new QComboBox;
    ParityComBox->addItem("On");
    ParityComBox->addItem("Off");
    ParityComBox->setCurrentIndex(1);
    StopBitsLabel = new QLabel("StopBits: ");
    StopBitsComBox = new QComboBox;
    StopBitsComBox->addItem("1");
    StopBitsComBox->addItem("2");


    // QTextEdit *StatusOfBT = new QTextEdit;

    //进行布局，先横向再纵向
    QHBoxLayout *Dock1Layout1 = new QHBoxLayout();
    Dock1Layout1->addWidget(BlueToothLabel);
    Dock1Layout1->addWidget(BlueToothPortComboBox);

    QHBoxLayout *Dock1Layout2 = new QHBoxLayout();
    Dock1Layout2->addWidget(BaudRateLabel);
    Dock1Layout2->addWidget(BaudRateComBox);

    QHBoxLayout *Dock1Layout3 = new QHBoxLayout();
    Dock1Layout3->addWidget(DateRateLabel);
    Dock1Layout3->addWidget(DateRateComBox);

    QHBoxLayout *Dock1Layout4 = new QHBoxLayout();
    Dock1Layout4->addWidget(ParityLabel);
    Dock1Layout4->addWidget(ParityComBox);

    QHBoxLayout *Dock1Layout5 = new QHBoxLayout();
    Dock1Layout5->addWidget(StopBitsLabel);
    Dock1Layout5->addWidget(StopBitsComBox);

    QHBoxLayout *Dock1Layout6 = new QHBoxLayout();
    Dock1Layout6->addWidget(ConnectBtn);//点击后就开始寻找设备进行连接
    Dock1Layout6->addWidget(BreakBtn);//点击后断开串口连接
 //   Dock1Layout6->addWidget(Stop1Btn);//暂时未用到

    QVBoxLayout *Dock1Layout = new QVBoxLayout();
    Dock1Layout->setAlignment(Qt::AlignCenter);
    Dock1Layout->addLayout(Dock1Layout1);
    Dock1Layout->addLayout(Dock1Layout2);
    Dock1Layout->addLayout(Dock1Layout3);
    Dock1Layout->addLayout(Dock1Layout4);
    Dock1Layout->addLayout(Dock1Layout5);
    Dock1Layout->addLayout(Dock1Layout6);


    QWidget *Dock1Widget = new QWidget();
    Dock1Widget->setLayout(Dock1Layout);
    dock1->setWidget(Dock1Widget);

    ConnectBtn->setMinimumWidth(70);
    BreakBtn->setMaximumWidth(50);
    Stop1Btn ->setMaximumWidth(50);

    //搜索串口，并添加到选项上供使用者选择
    foreach(const QSerialPortInfo &Info,QSerialPortInfo ::availablePorts())
    {
        QSerialPort CurrentPort;
        CurrentPort.setPort(Info);
        if(CurrentPort.open(QIODevice::ReadWrite))
        {
          BlueToothPortComboBox->addItem(CurrentPort.portName());//插入串口的名字
          CurrentPort.close();   //先开再关，把串口名称先导入
        }

    }
    connect(ConnectBtn, SIGNAL(clicked()),this,SLOT(on_connectButton_clicked()));
    connect(BreakBtn, SIGNAL(clicked()),this,SLOT(on_breakButton_clicked()));

}

void MainWindow::on_restartButton_clicked()//清空各个窗口信息，重新开始
{
    StatusOfDock3->clear();
    ReceiveInfo->clear();
    MeasureComboBox->setEnabled(true);
    InitELineEdit->setEnabled(true);
    FinalELineEdit->setEnabled(true);
    ScanRateLineEdit->setEnabled(true);
    ScanningDirectionComboBox->setEnabled(true);
    GainComboBox->setEnabled(true);
    CorrectComboBox->setEnabled(true);
    SampleIntervalLineEdit->setEnabled(true);
    QuietTimeComboBox->setEnabled(true);
    SendBtn->setText("Paste");
    SendBtn->setEnabled(true);
}


void MainWindow::on_sendButtton_clicked()//发送数据
{
    if(SendBtn->text() == QString("Paste"))
    {
        MeasureComboBox->setEnabled(false);
        InitELineEdit->setEnabled(false);
        FinalELineEdit->setEnabled(false);
        ScanRateLineEdit->setEnabled(false);
        ScanningDirectionComboBox->setEnabled(false);
        GainComboBox->setEnabled(false);
        CorrectComboBox->setEnabled(false);
        SampleIntervalLineEdit->setEnabled(false);
        QuietTimeComboBox->setEnabled(false);
        SendBtn->setText("Send");

    }
    else
    {
        SendBtn->setEnabled(false);
        //发送 1 过去启动程序
        QByteArray SendMethods = "1";
        StatusOfDock3->append("Send message: ");
        CurrentPort->write(SendMethods);SendMethods.clear();
        Delay_MSec(1000);
        //发送测量方式
        if (MeasureComboBox->currentIndex() == 1)
        {
            QByteArray SendMethods = "0";//循环伏安法
            StatusOfDock3->append(SendMethods);
            CurrentPort->write(SendMethods);SendMethods.clear();
        }
        else
        {
            QByteArray SendMethods = "1";//参数测量
            StatusOfDock3->append(SendMethods);
            CurrentPort->write(SendMethods);SendMethods.clear();
        }
        Delay_MSec(1000);
        //发送InitE
        QByteArray SendBytesIL = InitELineEdit->text().toLatin1();
        StatusOfDock3->append(SendBytesIL);
        CurrentPort->write(SendBytesIL);SendBytesIL.clear();
        Delay_MSec(1000);
        //发送FinalE
        QByteArray SendBytesFL = FinalELineEdit->text().toLatin1();
        StatusOfDock3->append(SendBytesFL);
        CurrentPort->write(SendBytesFL);SendBytesFL.clear();
        Delay_MSec(1000);
        //发送ScanRate
        QByteArray SendBytesSL = ScanRateLineEdit->text().toLatin1();
        StatusOfDock3->append(SendBytesSL);
        CurrentPort->write(SendBytesSL);SendBytesSL.clear();
        Delay_MSec(1000);
        //发送ScanningDirection
        if(ScanningDirectionComboBox->currentIndex() == 0)
        {
            QByteArray SendBytesDP = "1";    //发送Positive
            StatusOfDock3->append(SendBytesDP);
            CurrentPort->write(SendBytesDP);SendBytesDP.clear();
        }
        else
        {
            QByteArray SendBytesDP = "0";    //发送Negative
            StatusOfDock3->append(SendBytesDP);
            CurrentPort->write(SendBytesDP);SendBytesDP.clear();
        }
        Delay_MSec(1000);
        //发送Gain
        QByteArray SendBytesGL = GainComboBox->currentText().toLatin1();
        StatusOfDock3->append(SendBytesGL);
        CurrentPort->write(SendBytesGL);SendBytesGL.clear();
        Delay_MSec(1000);
        //发送是否纠正
        if (CorrectComboBox->currentIndex() == 0)
        {
            QByteArray SendBytesCP = "1";    //发送On
            StatusOfDock3->append(SendBytesCP);
            CurrentPort->write(SendBytesCP);SendBytesCP.clear();
        }
        else
        {
            QByteArray SendBytesCP = "0";    //发送Off
            StatusOfDock3->append(SendBytesCP);
            CurrentPort->write(SendBytesCP);SendBytesCP.clear();
        }
        Delay_MSec(1000);
        //发送SampleInterval
        QByteArray SendBytesSIL = SampleIntervalLineEdit->text().toLatin1();
        StatusOfDock3->append(SendBytesSIL);
        CurrentPort->write(SendBytesSIL);SendBytesSIL.clear();
        Delay_MSec(1000);
        //发送QuietTime--这里需要设置延迟时间，当静息时间结束再开始接受数据
        QByteArray SendBytesQTL = QuietTimeComboBox->currentText().toLatin1();
        StatusOfDock3->append(SendBytesQTL);
        CurrentPort->write(SendBytesQTL);
        SendBytesQTL.clear();
       // switch (QuietTimeComboBox->currentIndex())
        //{
        //case 0 :Delay_MSec(2);break;
        //case 1 :Delay_MSec(3);break;
       // case 2 :Delay_MSec(4);break;
       // }
    }

   // if(SendBytes.isEmpty())//判断发送数据是否为空
    // {
   //         StatusOfDock3->append("No message can be sent, Please write something");
  //   }


}





void MainWindow::Read_Data()//读取接收到的数据
{

    QByteArray buf;
    buf = CurrentPort->readAll();//Qbytearray类提供一个字节数组

    if (buf == "START")
    {
        StatusOfDate->setText("START");
        StatusOfDock3->append(buf);
        buf.clear();
    }
    else if (buf == "END")
    {
        StatusOfDate->setText("END");//在绘图函数可以加一个if,当绘完图以后设置为"Ready"
        StatusOfDock3->append(buf);
        MeasureComboBox->setEnabled(true);
        InitELineEdit->setEnabled(true);
        FinalELineEdit->setEnabled(true);
        ScanRateLineEdit->setEnabled(true);
        ScanningDirectionComboBox->setEnabled(true);
        GainComboBox->setEnabled(true);
        CorrectComboBox->setEnabled(true);
        SampleIntervalLineEdit->setEnabled(true);
        QuietTimeComboBox->setEnabled(true);
        SendBtn->setText("Paste");
        SendBtn->setEnabled(true);
        buf.clear();
    }
    if (!buf.isEmpty())
    {
        if(StatusOfDate->text() == "START")
        {
            QString str = this->ReceiveInfo->toPlainText().toUtf8();
            str += tr(buf);
            ReceiveInfo->clear();
            ReceiveInfo->append(str);//buf.clear();
        }
        else
        {
            QString str = this->StatusOfDock3->toPlainText().toUtf8();
            str += tr(buf);
            StatusOfDock3->clear();
            StatusOfDock3->append(str);//buf.clear();
        }
    }
    //buf.clear();

    //if(!buf.isEmpty())
   // {
    //    QString str = this->ReceiveInfo->toPlainText().toUtf8();
    //    str += tr(buf);//???
    //    ReceiveInfo->clear();

    //    ReceiveInfo->append(str);

    //}
    //buf.clear();
}


void MainWindow::on_connectButton_clicked()
{
        CurrentPort = new QSerialPort;
        CurrentPort->setPortName(BlueToothPortComboBox->currentText());//设置串口名
        //设置波特率
        switch (BaudRateComBox->currentIndex())
        {
         case 0: StatusOfDock3->append("Baud:9600");
            CurrentPort->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections); break;
         case 1: StatusOfDock3->append("Baud:115200");
            CurrentPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections); break;
        default: break;
        }

        //设置数据位数
        switch(DateRateComBox->currentIndex())
        {
        case 0: StatusOfDock3->append("Data:5");
            CurrentPort->setDataBits(QSerialPort::Data5); break;
        case 1: StatusOfDock3->append("Data:6");
            CurrentPort->setDataBits(QSerialPort::Data6); break;
        case 2: StatusOfDock3->append("Data:7");
            CurrentPort->setDataBits(QSerialPort::Data7); break;
        case 3: StatusOfDock3->append("Data:8");
            CurrentPort->setDataBits(QSerialPort::Data8); break;
        default: break;
        }
        //设置奇偶校验
        switch(ParityComBox->currentIndex())
        {
        case 1:StatusOfDock3->append("Parity: off");
            CurrentPort->setParity(QSerialPort::NoParity); break;
        default: break;
        }
        switch(StopBitsComBox->currentIndex())   //设置停止位
        {
        case 0: StatusOfDock3->append("StopBits:1");
            CurrentPort->setStopBits(QSerialPort::OneStop); break;
        case 1: StatusOfDock3->append("StopBits:2");
            CurrentPort->setStopBits(QSerialPort::TwoStop); break;
        default: break;
        }
        CurrentPort->setFlowControl(QSerialPort::NoFlowControl);  //设置流控制

        CurrentPort->open(QIODevice::ReadWrite);//打开串口

        if(CurrentPort->isOpen())
        {
           StatusOfDock3->append("Succeesfully open the Port ");
           //关闭设置菜单使能
           BlueToothPortComboBox->setEnabled(false);
           BaudRateComBox->setEnabled(false);
           DateRateComBox->setEnabled(false);
           ParityComBox->setEnabled(false);
           StopBitsComBox->setEnabled(false);
           ConnectBtn->setEnabled(false);
           BreakBtn->setEnabled(true);
           SendBtn->setEnabled(true);
        }
        else
        {
           StatusOfDock3->append("Defeatly open the port");
        }

        //连接信号槽
        QObject::connect(CurrentPort, &QSerialPort::readyRead, this, &MainWindow::Read_Data);

}
void MainWindow::on_breakButton_clicked()
{
    //关闭串口
    CurrentPort->clear();
    CurrentPort->close();
    CurrentPort->deleteLater();
    StatusOfDock3->append("Serial connection has been disconnected");
    //恢复设置使能
    BlueToothPortComboBox->setEnabled(true);
    BaudRateComBox->setEnabled(true);
    DateRateComBox->setEnabled(true);
    ParityComBox->setEnabled(true);
    StopBitsComBox->setEnabled(true);
    ConnectBtn->setEnabled(true);
    BreakBtn->setEnabled(false);
    SendBtn->setEnabled(false);
}
void MainWindow::startPainting()
{

}
void MainWindow::stopPainting()
{

}
void MainWindow::setvariables()
{
    //停靠窗口2，调整各种变量
    QDockWidget *dock2 = new QDockWidget(tr("DockWindow2"));
    dock2->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable); //窗口可移动
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    //dock2->setStyleSheet("QPushButtonl{color:white;background-color:black}");//设置按钮/标签等颜色   color\background-color
                                                                             //空白margain/边框border/填充padding/内容content
    addDockWidget(Qt::RightDockWidgetArea,dock2);
                  //设置各个Widget，进行填充
    MeasureLabel = new QLabel(tr("Measure Methods: "));
    MeasureComboBox = new QComboBox;
    MeasureComboBox->addItem("Parameter Measurement");
    MeasureComboBox->addItem("Cyclic Voltammetry");
    InitELabel = new QLabel(tr("Init E(V): "));
    InitELineEdit = new QLineEdit;

    //QRegExp rx1("^-?(5|[0-0][\\.][0-9]{1,2})$");
    //QRegExpValidator *pReg = new QRegExpValidator(rx1, this);
    //InitELineEdit->setValidator(pReg);


    //InitELineEdit->setValidator()
    FinalELabel = new QLabel(tr("Final E(V): "));FinalELineEdit = new QLineEdit("0.6");
    ScanRateLabel = new QLabel(tr("Scan Rate (mV/s): "));ScanRateLineEdit = new QLineEdit("50");
    ScanningDirectionLabel = new QLabel(tr("Scanning direction: "));
    ScanningDirectionComboBox = new QComboBox;
    ScanningDirectionComboBox->addItem(tr("Positive"));
    ScanningDirectionComboBox->addItem(tr("Negative"));
    GainLabel = new QLabel(tr("Gain : "));
    GainComboBox = new QComboBox;
    GainComboBox->addItem("1000");
    GainComboBox->addItem("5000");
    GainComboBox->addItem("10000");
    GainComboBox->addItem("50000");
    GainComboBox->addItem("100000");
    GainComboBox->addItem("500000");
    GainComboBox->addItem("1000000");
    GainComboBox->setCurrentIndex(2);
    CorrectLabel = new QLabel("Correct");
    CorrectComboBox = new QComboBox;
    CorrectComboBox->addItem("On");
    CorrectComboBox->addItem("Off");
    CorrectComboBox->setCurrentIndex(1);

    SampleIntervalLabel = new QLabel(tr("Sample Interval (mv): "));
    SampleIntervalLineEdit = new QLineEdit("1");
    QRegExp rx("^?(20|[0-1]?\\d(\\.\\d{2})?)$");
    SampleIntervalLineEdit->setValidator(new QRegExpValidator(rx, this));

    QuietTimeLabel = new QLabel(tr("Quiet Time: "));
    QuietTimeComboBox = new QComboBox;
    QuietTimeComboBox->addItem("2");
    QuietTimeComboBox->addItem("3");
    QuietTimeComboBox->addItem("4");
    SendBtn = new QPushButton(tr("Paste"));
    SendBtn->setMaximumWidth(70);
    ReStartBtn = new QPushButton(tr("ReStart"));
    PauseBtn = new QPushButton(tr("Pause"));
    Stop2Btn = new QPushButton(tr("Stop"));
    dock2->setStyleSheet("QPushButton{color:white;background-color:black}");//设置按钮样式
    ReStartBtn->setMaximumWidth(70);
    PauseBtn->setMaximumWidth(50);
    Stop2Btn ->setMaximumWidth(50);
    //设置完各个控件进行布局，先水平布局再垂直布局
    QHBoxLayout *Dock2Layout1 = new QHBoxLayout();
    Dock2Layout1->addWidget(MeasureLabel);
    Dock2Layout1->addWidget(MeasureComboBox);



    QHBoxLayout *Dock2Layout2 = new QHBoxLayout();
    Dock2Layout2->addWidget(InitELabel);
    Dock2Layout2->addWidget(InitELineEdit);

    QHBoxLayout *Dock2Layout3 = new QHBoxLayout();
    Dock2Layout3->addWidget(FinalELabel);
    Dock2Layout3->addWidget(FinalELineEdit);

    QHBoxLayout *Dock2Layout4 = new QHBoxLayout();
    Dock2Layout4->addWidget(ScanRateLabel);
    Dock2Layout4->addWidget(ScanRateLineEdit);

    QHBoxLayout *Dock2Layout5 = new QHBoxLayout();
    Dock2Layout5->addWidget(ScanningDirectionLabel);
    Dock2Layout5->addWidget(ScanningDirectionComboBox);

    QHBoxLayout *Dock2Layout6 = new QHBoxLayout();
    Dock2Layout6->addWidget(GainLabel);
    Dock2Layout6->addWidget(GainComboBox);

    QHBoxLayout *Dock2Layout7 = new QHBoxLayout();
    Dock2Layout7->addWidget(CorrectLabel);
    Dock2Layout7->addWidget(CorrectComboBox);

    QHBoxLayout *Dock2Layout8 = new QHBoxLayout();
    Dock2Layout8->addWidget(SampleIntervalLabel);
    Dock2Layout8->addWidget(SampleIntervalLineEdit);

    QHBoxLayout *Dock2Layout9 = new QHBoxLayout();
    Dock2Layout9->addWidget(QuietTimeLabel);
    Dock2Layout9->addWidget(QuietTimeComboBox);

    QHBoxLayout *Dock2Layout10 = new QHBoxLayout();
    Dock2Layout10->addWidget(SendBtn);
    Dock2Layout10->addWidget(ReStartBtn);
   // Dock2Layout8->addWidget(PauseBtn);
   // Dock2Layout8->addWidget(Stop2Btn);

    QVBoxLayout *Dock2Layout = new QVBoxLayout;
    Dock2Layout->setAlignment(Qt::AlignCenter);
    Dock2Layout->addLayout(Dock2Layout1);
    Dock2Layout->addLayout(Dock2Layout2);
    Dock2Layout->addLayout(Dock2Layout3);
    Dock2Layout->addLayout(Dock2Layout4);
    Dock2Layout->addLayout(Dock2Layout5);
    Dock2Layout->addLayout(Dock2Layout6);
    Dock2Layout->addLayout(Dock2Layout7);
    Dock2Layout->addLayout(Dock2Layout8);
    Dock2Layout->addLayout(Dock2Layout9);
    Dock2Layout->addLayout(Dock2Layout10);

    Dock2Layout->setSpacing(20);//设置间隙
    QWidget *Dock2Widget = new QWidget();
    Dock2Widget->setLayout(Dock2Layout);
    dock2->setWidget(Dock2Widget);

    connect(SendBtn,SIGNAL(clicked()),this,SLOT(on_sendButtton_clicked()));
    connect(ReStartBtn,SIGNAL(clicked()),this,SLOT(on_restartButton_clicked()));
    connect(GainComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](){ CorrectComboBox->setCurrentIndex(0); });//增益改变就将校准设置为On
}
void MainWindow::statusOfAll()//最下面的窗口，显示图像的各个数据；暂时让收发数据显示在这里，到后面可隐藏掉
{
    //停靠窗口3，显示图像各种参数
    QDockWidget *dock3 = new QDockWidget(tr("DockWindow3"));
    dock3->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable); //窗口可移动
    dock3->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea,dock3);
    dock3->setMinimumSize(1500,100);
    QHBoxLayout *Dock3Layout = new QHBoxLayout;
    StatusOfDock3 = new QTextEdit;
    StatusOfDock3->setMinimumSize(300,200);
    SendInfo = new QTextEdit;
    ReceiveInfo = new QTextEdit;
SendInfo->document()->lineCount();
    Dock3Layout->addWidget(StatusOfDock3);
   // Dock3Layout->addWidget(SendInfo);
    Dock3Layout->addWidget(ReceiveInfo);
    QWidget *Dock3Widget = new QWidget();
    Dock3Widget->setLayout(Dock3Layout);
    dock3->setWidget(Dock3Widget);

}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("V1.0"));//窗体标题
    //主窗口设计
    scene = new QGraphicsScene;
    scene->setSceneRect(-200,-200,400,400);
    //initScene();
    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->setMinimumSize(800,600);
    setCentralWidget(view);
    resize(1000,800);
    //创建动作、菜单、工具栏的函数
    createActions();
    createMenus();
    createToolBars();
    createStatusBars();
    //蓝牙、参数设置、状态显示
    bluetooth();
    setvariables();
    statusOfAll();
    //创建坐标轴


}

MainWindow::~MainWindow()
{

}
//一些固定的槽函数
void MainWindow::Delay_MSec(int msec)//非阻塞延迟，采用事件循环的方法
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}
void MainWindow::createStatusBars()//状态栏，最下面一行，显示状态
{
    Status = statusBar();
    StatusOfDate = new QLabel("Ready");
    Status->addWidget(StatusOfDate);

}
