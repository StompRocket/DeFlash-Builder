#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
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

private:
    Ui::MainWindow *ui;
    QToolBar *toolBar;
    Painter *painter;
    QString where;
    int imageWidth = 640;
    int imageHeight = 480;
};
#endif // MAINWINDOW_H
