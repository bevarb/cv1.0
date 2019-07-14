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
#include <QtBluetooth/QtBluetooth>
#include <QTableWidget>
//#include <QtCharts/QXYSeries>

#include "showwidget.h"
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
private:
    //基本布局

    QGraphicsScene *scene;
  //  QDockWidget *Dock1;
  //  QDockWidget *Dock2;
    QStackedWidget *Stack1;
    QMenu *fileMenu;
    QMenu *zoomMenu;
    QImage img;
    QString filename;
    ShowWidget *showWidget;

    QAction *OpenFileAction;    //文件菜单栏
    QAction *NewFileAction;
    QAction *ExitAction;
    QAction *CopyAction;        //编辑菜单栏
    QAction *CutAction;
    QAction *PasteAction;
    QAction *AboutAction;
    QAction *ZoomInAction;
    QAction *ZoomOutAction;
    QAction *UndoAction;
    QAction *RedoAction;

    QToolBar *Tool;       //工具栏

    QToolBar *DoToolBar;
    //状态栏
    QStatusBar *Status;
    //停靠窗口1，显示蓝牙连接状态
    QLabel *BlueToothLabel;
    QComboBox *BlueToothPortComboBox;
    QPushButton *ConnectBtn;
    QPushButton *BreakBtn;
    QTableWidget *BT_INFO;
    QPushButton *Stop1Btn;

    //停靠窗口2，各种参数调整模块
    QLabel *InitELabel;
    QLabel *FinalELabel;
    QLabel *ScanRateLabel;
    QLabel *ScanningDirectionLabel;
    QLabel *GainLabel;
    QLabel *SampleIntervalLabel;
    QLabel *QuietTimeLabel;
    QLineEdit *InitELineEdit;
    QLineEdit *FinalELineEdit;
    QLineEdit *ScanRateLineEdit;
    QComboBox *ScanningDirectionComboBox;
    QLineEdit *GainLineEdit;
    QLineEdit *SampleIntervalLineEdit;
    QLineEdit *QuietTimeLineEdit;
    QPushButton *StartBtn;
    QPushButton *PauseBtn;
    QPushButton *Stop2Btn;
    QButtonGroup *Dock2Group;
    QTextEdit *StatusOfBT;

protected slots:
    void showNewFile();
    void showZoomIn();
    void showZoomOut();

};

#endif // MAINWINDOW_H
