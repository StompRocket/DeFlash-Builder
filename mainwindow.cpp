#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDir>
#include <QDateTime>
#include <QDebug>

const static double createVersion = 0.1;

MainWindow::MainWindow(QString w, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , where(w)
    , proj(QDir(where).filePath("create.cfg"), true, this)
    , emptyWidget(new QTableWidgetItem(""))
    , fullWidget(new QTableWidgetItem("•"))
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

    setWindowTitle(QString("StompRocket Create - %1").arg(where.path()));

    double projectVersion = proj.getOrSet("meta.create-version", createVersion).toDouble();
    if (!proj.exists("frames.location"))
    {
        frameDir = QDir(where);
        frameDir.cd(proj.getOrSet("frames.location", "assets/frames").toString());
    }
    if (projectVersion > createVersion)
    {
        qDebug() << "Warning: Project created in a newer version of Create, it might not work.";
    }

    fullWidget->setBackgroundColor(QColor(88, 237, 162));

    ui->frameTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    drawFrames();
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

void MainWindow::drawFrames()
{
    qDebug() << "Setting Frames";
    ui->frameTable->setRowCount(1);
    ui->frameTable->setColumnCount(5);
    ui->frameTable->setVerticalHeaderItem(0, new QTableWidgetItem(""));
    ui->frameTable->setItem(0, 0, new QTableWidgetItem("Hello!"));
}
