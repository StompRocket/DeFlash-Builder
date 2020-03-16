#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QString where, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , where(where)
{
    ui->setupUi(this);
    toolBar = new QToolBar();
    painter = new Painter(ui->painterScrollArea);
    toolBar->addAction(ui->actionPen);
    toolBar->addAction(ui->actionEraser);
    addToolBar(toolBar);
    ui->painterScrollArea->setWidget(painter);

    ui->strokeWidth->setValue(painter->penWidth);
    painter->setSize(imageWidth, imageHeight);

    ui->canvasSplitter->setChildrenCollapsible(false);
    ui->canvasSplitter->setStretchFactor(0, 3);
    ui->frameSplitter->setStretchFactor(0, 100);
    setCentralWidget(ui->frameSplitter);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete toolBar;
    delete painter;
}

void MainWindow::on_strokeWidth_valueChanged(int width)
{
    if (width > 0 && width < 128)
        painter->penWidth = width;
    else ui->strokeWidth->setValue(painter->penWidth);
}

void MainWindow::on_actionPen_triggered()
{
    painter->tool = Tool::pen;
}

void MainWindow::on_actionEraser_triggered()
{
    painter->tool = Tool::eraser;
}
