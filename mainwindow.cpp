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

    ui->frameTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->frameTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    ui->frameTable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    ui->frameTable->sizePolicy().setVerticalStretch(0);

    frames.append(AnimationFrame());
    frames.append(AnimationFrame());
    painter->setFrame(&frames[1]);

    drawFrames();
    selectFrame(1);
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
    ui->frameTable->setColumnCount(frames.length());
    ui->frameTable->setVerticalHeaderItem(0, new QTableWidgetItem(""));

    for (int i = 0; i < frames.length(); i++)
    {
        ui->frameTable->setItem(0, i, &frames[i].tableWidget);
    }
}

int MainWindow::selectFrame(int which)
{
    if (which > 0 && which < frames.length())
        selectedFrame = which;

    //ui->frameTable->setCurrentCell(0, selectedFrame);
    painter->setFrame(&frames[which]);
    return selectedFrame;
}

void MainWindow::on_frameTable_cellClicked(int, int frameIndex)
{
    qDebug() << frameIndex << "clicked";
    selectFrame(frameIndex);
    //drawFrames();
}
