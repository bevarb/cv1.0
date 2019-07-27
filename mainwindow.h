#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QStatusBar>
#include <QTextCharFormat>
#include <QDockWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QtSerialPort/QSerialPort>
#include "showwidget.h"


extern QString alldata;

extern int Flag_isOpen;       //标记：判断是否打开或创建了一个文件
extern int Flag_IsNew;        //标记：如果新建了文件就为1，初始值为0
extern QString Last_FileName;     //最后一次保存的文件的名字
extern QString Last_FileContent;  //最后一次保存文件的内容

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();    //创建动作
    void createMenus();      //创建菜单
    void createToolBars();   //创建工具栏
    void createStatusBars();  //创建状态栏
    void loadFile(QString filename);   //??
    void mergeFormat(QTextCharFormat);  //??
    void setvariables();  //设置调试参数
    void startDeviceDiscovery();
    void deviceDiscovered();
    void bluetooth();
    void statusOfAll();

private:
    //基本布局
    QGraphicsScene *scene;
    QStackedWidget *Stack1;
    QMenu *fileMenu;
    QMenu *zoomMenu;
    QImage img;
    QString filename;


    ShowWidget *showWidget;

    QPushButton *SendBtn;
    //文件菜单栏
    QAction *OpenFileAction; //打开文件
    QAction *NewFileAction; //新建文件
    QAction *ExitAction;
    QAction *SaveAction; //保存文件
    QAction *SaveAsAction; //另存为文件
    //编辑菜单栏

    QAction *CutAction;
    QAction *PasteAction;
    QAction *AboutAction;
    QAction *ZoomInAction;
    QAction *ZoomOutAction;
    QAction *UndoAction;
    QAction *RedoAction;
    //工具栏
    QToolBar *Tool;
    QToolBar *DoToolBar;
    //状态栏
    QStatusBar *Status;

    //停靠窗口1，显示蓝牙连接状态
    QLabel *BlueToothLabel;
    QComboBox *BlueToothPortComboBox;
    QPushButton *ConnectBtn;
    QPushButton *BreakBtn;
    QPushButton *serchBtn;


    QSerialPort *CurrentPort;
    QLabel *BaudRateLabel;
    QComboBox *BaudRateComBox;
    QLabel *DateRateLabel;
    QComboBox *DateRateComBox;
    QLabel *ParityLabel;
    QComboBox *ParityComBox;
    QLabel *StopBitsLabel;
    QComboBox *StopBitsComBox;


    //停靠窗口2，各种参数调整模块
    QLabel *MeasureLabel;
    QLabel *InitELabel;
    QLabel *FinalELabel;
    QLabel *ScanRateLabel;
    QLabel *ScanningDirectionLabel;
    QLabel *GainLabel;
    QLabel *SampleIntervalLabel;
    QLabel *QuietTimeLabel;
    QLabel *CorrectLabel;
    QLineEdit *InitELineEdit;
    QLineEdit *FinalELineEdit;
    QLineEdit *ScanRateLineEdit;
    QLineEdit *SampleIntervalLineEdit;
    QComboBox *MeasureComboBox;
    QComboBox *ScanningDirectionComboBox;
    QComboBox *GainComboBox;
    QComboBox *CorrectComboBox;
    QComboBox *QuietTimeComboBox;

    QPushButton *ReStartBtn;
    QPushButton *PauseBtn;
    QPushButton *Stop2Btn;
    QButtonGroup *Dock2Group;
    QTextEdit *StatusOfBT;

    //停靠窗口3，3个显示窗口，状态/接受/发送
    QTextEdit *StatusOfDock3;
    QTextEdit *SendInfo;
    QTextEdit *ReceiveInfo;

    QLabel *StatusOfDate;
   // void buf_Signal(QString allData);

signals:
    void send_Signal(QString Send);
    void send_Axis(double x,double y);
    void send_Restart();

protected slots:
    void showNewFile();   //打开新文件，其实就清空各项内容，发送restart信号，保存文件还是用Save
    void showOpenFile();  //***__实现了打开文件的功能，并读取数据到状态栏上   还没有实现： 将数据添加到plot上
    void showSaveFile();  //√ 能够保存文本信息到txt文件上
    void showSaveFileAs(); //
    void axis_Signal();

private slots:
 //   void on_clearButton_clicked();
    void on_sendButtton_clicked();
    void on_restartButton_clicked();
    void on_connectButton_clicked();
    void on_breakButton_clicked();
    void on_serchButton_clicked();
    void Read_Data();
    void Delay_MSec(int msec);

};

#endif // MAINWINDOW_H
