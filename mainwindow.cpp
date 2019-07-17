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
void MainWindow::createStatusBars()//状态栏，最下面一行，显示状态
{
    Status = statusBar();
    Status->addWidget(new QLabel("2",this));

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
    BaudRateComBox->addItem(tr("11520"));
    BaudRateComBox->addItem(tr("9600"));

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
          CurrentPort.close();
        }

    }
    connect(ConnectBtn, SIGNAL(clicked()),this,SLOT(on_connectButton_clicked()));
    connect(BreakBtn, SIGNAL(clicked()),this,SLOT(on_breakButton_clicked()));

}

void MainWindow::on_clearButton_clicked()//清空发送与接收窗口信息
{
    SendInfo->clear();
    ReceiveInfo->clear();
}


void MainWindow::on_sendButtton_clicked()//发送数据
{


    QByteArray SendBytes = SendInfo->toPlainText().toLatin1();//toPlainText(将文本编辑的文本转换为纯文本)


    if(SendBytes.isEmpty())//判断发送数据是否为空
     {
            StatusOfDock3->append("No message can be sent, Please write something");
     }

    //StatusOfDock3->append(SendBytes);



    CurrentPort->write(SendBytes);


     // QByteArray bufCeShi = CurrentPort->readAll();//Qbytearray类提供一个字节数组  ？？？？？？？这里出错了，读取不了数据(测试时加到这里的)

    //StatusOfDock3->append(bufCeShi);
}


void MainWindow::Read_Data()//读取接收到的数据
{
    QByteArray buf = CurrentPort->readAll();//Qbytearray类提供一个字节数组,buf这里应该是缓冲数据的功能


    if(!buf.isEmpty())
    {
         //QString str = QString::fromLocal8Bit(buf);
        QString str = ReceiveInfo->toPlainText().toUtf8();
        str += QString(buf);//???
        ReceiveInfo->clear();
        ReceiveInfo->append(str);

    }
    buf.clear();
}


void MainWindow::on_connectButton_clicked()
{
        CurrentPort = new QSerialPort;
        CurrentPort->setPortName(BlueToothPortComboBox->currentText());//设置串口名
        //设置波特率
        switch (BaudRateComBox->currentIndex())
        {
         case 0: StatusOfDock3->append("Baud:115200");
            CurrentPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections); break;
         case 1: StatusOfDock3->append("Baud:9600");
            CurrentPort->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections); break;
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
        }
        else
        {
           StatusOfDock3->append("Defeatly open the port");
        }


        //关闭设置菜单使能
        BlueToothPortComboBox->setEnabled(false);
        BaudRateComBox->setEnabled(false);
        DateRateComBox->setEnabled(false);
        ParityComBox->setEnabled(false);
        StopBitsComBox->setEnabled(false);
        ConnectBtn->setEnabled(false);
        BreakBtn->setEnabled(true);
        SendBtn->setEnabled(true);
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
    InitELabel = new QLabel(tr("Init E(V): "));
    InitELineEdit = new QLineEdit;
    FinalELabel = new QLabel(tr("Final E(V): "));
    FinalELineEdit = new QLineEdit;
    ScanRateLabel = new QLabel(tr("Scan Rate (mV/s): "));
    ScanRateLineEdit = new QLineEdit;
    ScanningDirectionLabel = new QLabel(tr("Scanning direction: "));
    ScanningDirectionComboBox = new QComboBox;
    ScanningDirectionComboBox->addItem(tr("Positive"));
    ScanningDirectionComboBox->addItem(tr("Negative"));
    GainLabel = new QLabel(tr("Gain : "));
    GainLineEdit = new QLineEdit;
    SampleIntervalLabel = new QLabel(tr("Sample Interval (mv): "));
    SampleIntervalLineEdit = new QLineEdit;
    QuietTimeLabel = new QLabel(tr("Quiet Time: "));
    QuietTimeLineEdit = new QLineEdit;
    SendBtn = new QPushButton(tr("Send"));
    StartBtn = new QPushButton(tr("Start"));
    PauseBtn = new QPushButton(tr("Pause"));
    Stop2Btn = new QPushButton(tr("Stop"));
    dock2->setStyleSheet("QPushButton{color:white;background-color:black}");//设置按钮样式
    StartBtn->setMaximumWidth(50);
    PauseBtn->setMaximumWidth(50);
    Stop2Btn ->setMaximumWidth(50);
    //设置完各个控件进行布局，先水平布局再垂直布局
    QHBoxLayout *Dock2Layout1 = new QHBoxLayout();
    Dock2Layout1->addWidget(InitELabel);
    Dock2Layout1->addWidget(InitELineEdit);

    QHBoxLayout *Dock2Layout2 = new QHBoxLayout();
    Dock2Layout2->addWidget(FinalELabel);
    Dock2Layout2->addWidget(FinalELineEdit);

    QHBoxLayout *Dock2Layout3 = new QHBoxLayout();
    Dock2Layout3->addWidget(ScanRateLabel);
    Dock2Layout3->addWidget(ScanRateLineEdit);

    QHBoxLayout *Dock2Layout4 = new QHBoxLayout();
    Dock2Layout4->addWidget(ScanningDirectionLabel);
    Dock2Layout4->addWidget(ScanningDirectionComboBox);

    QHBoxLayout *Dock2Layout5 = new QHBoxLayout();
    Dock2Layout5->addWidget(GainLabel);
    Dock2Layout5->addWidget(GainLineEdit);

    QHBoxLayout *Dock2Layout6 = new QHBoxLayout();
    Dock2Layout6->addWidget(SampleIntervalLabel);
    Dock2Layout6->addWidget(SampleIntervalLineEdit);

    QHBoxLayout *Dock2Layout7 = new QHBoxLayout();
    Dock2Layout7->addWidget(QuietTimeLabel);
    Dock2Layout7->addWidget(QuietTimeLineEdit);

    QHBoxLayout *Dock2Layout8 = new QHBoxLayout();
    Dock2Layout8->addWidget(SendBtn);
    Dock2Layout8->addWidget(StartBtn);
    Dock2Layout8->addWidget(PauseBtn);
    Dock2Layout8->addWidget(Stop2Btn);

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

    Dock2Layout->setSpacing(20);//设置间隙
    QWidget *Dock2Widget = new QWidget();
    Dock2Widget->setLayout(Dock2Layout);
    dock2->setWidget(Dock2Widget);

    connect(SendBtn,SIGNAL(clicked()),this,SLOT(on_sendButtton_clicked()));

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

    Dock3Layout->addWidget(StatusOfDock3);
    Dock3Layout->addWidget(SendInfo);
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
