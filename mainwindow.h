#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// DEPRECATED:
// #include "projectfile.h"
#include "config.h"
#include "animationframe.h"

#include <QMainWindow>
#include <QToolBar>
#include <QTableWidgetItem>
#include <QDir>
#include <painter.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString where, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_strokeWidth_valueChanged(int arg1);
    void on_actionPen_triggered();
    void on_actionEraser_triggered();
    void on_frameTable_cellClicked(int, int frameIndex);
    void on_actionNextFrame_triggered();

    void on_actionSave_triggered();

    void on_actionExport_triggered();

private:
    Ui::MainWindow *ui;
    QToolBar *toolBar;
    Painter *painter;
    QDir where;
    int imageWidth = 640;
    int imageHeight = 480;
    Config proj;
    QDir frameDir;
    QList<AnimationFrame> frames;
    int selectedFrame = 0;
    void saveFrames();

    int selectFrame(int which);
    void drawFrames();
};
#endif // MAINWINDOW_H
