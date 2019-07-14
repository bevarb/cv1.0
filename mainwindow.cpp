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
   // connect(PasteAction,SIGNAL(triggered()),showWidget->text,SLOT(paste()));
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
void MainWindow::createStatusBars()
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
void MainWindow::showZoomOut()
{

}
void MainWindow::bluetooth()
{
    QDockWidget *dock1 = new QDockWidget(tr("DockWindow1"));
    dock1->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable); //窗口可移动
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

    addDockWidget(Qt::RightDockWidgetArea,dock1);

    BT_INFO = new QTableWidget(4,5,this);
    ConnectBtn = new QPushButton(tr("Connect"));
    BreakBtn = new QPushButton(tr("Break"));
    Stop1Btn = new QPushButton(tr("Stop"));
    dock1->setStyleSheet("QPushButton{color:white;background-color:black}");
    // QTextEdit *StatusOfBT = new QTextEdit;
    //进行布局
    QHBoxLayout *Dock1Layout1 = new QHBoxLayout();

    //Dock1Layout1->addWidget(BlueToothLabel,0,0);
    //Dock1Layout->addWidget(BlueToothPortComboBox,0,1);
    Dock1Layout1->addWidget(BT_INFO);
    QHBoxLayout *Dock1Layout2 = new QHBoxLayout();
    Dock1Layout2->addWidget(ConnectBtn);
    Dock1Layout2->addWidget(BreakBtn);
    Dock1Layout2->addWidget(Stop1Btn);
    //Dock1Layout->addWidget(StatusOfBT,3,0);
    QVBoxLayout *Dock1Layout = new QVBoxLayout();
    Dock1Layout->setAlignment(Qt::AlignCenter);
    Dock1Layout->addLayout(Dock1Layout1);
    Dock1Layout->addLayout(Dock1Layout2);
    QWidget *Dock1Widget = new QWidget();
    Dock1Widget->setLayout(Dock1Layout);
    dock1->setWidget(Dock1Widget);

    ConnectBtn->setMaximumWidth(50);
    BreakBtn->setMaximumWidth(50);
    Stop1Btn ->setMaximumWidth(50);
    //startDeviceDiscovery();
    BT_INFO->clearContents();
    BT_INFO->setRowCount(0);
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
    view->setMinimumSize(1000,800);
    setCentralWidget(view);
    resize(1000,800);
    setWindowTitle(tr("Graphics Items"));



    //停靠窗口3，显示图像各种参数
    QDockWidget *dock3 = new QDockWidget(tr("DockWindow3"));
    dock3->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable); //窗口可移动
    dock3->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea,dock3);
    dock3->setMinimumSize(1500,100);
    QTextEdit *StatusOfDock3 = new QTextEdit;
    dock3->setWidget(StatusOfDock3);
        
    //创建动作、菜单、工具栏的函数
    createActions();
    createMenus();
    createToolBars();
    createStatusBars();
    bluetooth();
    setvariables();


    //创建坐标轴


}

MainWindow::~MainWindow()
{

}
