#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "version.h"
#include "videoexporter.h"

#include <QDir>
#include <QDateTime>
#include <QDebug>

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
    toolBar->addSeparator();
    toolBar->addAction(ui->actionNextFrame);
    addToolBar(toolBar);
    ui->painterScrollArea->setWidget(painter);

    ui->strokeWidth->setValue(painter->getPenWidth());
    painter->setSize(imageWidth, imageHeight);

    ui->canvasSplitter->setChildrenCollapsible(false);
    ui->canvasSplitter->setStretchFactor(0, 3);
    ui->frameSplitter->setStretchFactor(0, 100);
    setCentralWidget(ui->frameSplitter);

    setWindowTitle(QString("%1 - %2").arg(fullName).arg(where.path()));

    double projectVersion = proj.getOrSet("meta.version", appVersion).toDouble();

    frameDir = QDir(where);
    QString frameSubDir = proj.getOrSet("frames.location", "rames").toString();
    qDebug() << "creating" << frameSubDir << frameDir.mkdir(frameSubDir);
    frameDir.cd(frameSubDir);

    if (projectVersion > appVersion)
    {
        qDebug() << "Warning: Project created in a newer version of Create, it might not work.";
    }

    ui->frameTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->frameTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    ui->frameTable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    ui->frameTable->sizePolicy().setVerticalStretch(0);

    frames.append(AnimationFrame());
    painter->setFrame(&frames[0]);

    drawFrames();
    selectFrame(0);
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
        painter->setPenWidth(width);
    else ui->strokeWidth->setValue(painter->getPenWidth());
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
    ui->frameTable->selectionModel()->select(
                ui->frameTable->model()->index(0, selectedFrame),
                QItemSelectionModel::Deselect);

    if (which >= 0 && which < frames.length())
        selectedFrame = which;

    ui->frameTable->selectionModel()->select(
                ui->frameTable->model()->index(0, selectedFrame),
                QItemSelectionModel::Select);

    //ui->frameTable->setCurrentCell(0, selectedFrame);
    painter->setFrame(&frames[which]);
    proj.set("frames.current-selected", selectedFrame);
    proj.set("frames.count", frames.length());
    return selectedFrame;
}

void MainWindow::on_frameTable_cellClicked(int, int frameIndex)
{
    qDebug() << frameIndex << "clicked";
    selectFrame(frameIndex);
    //drawFrames();
}

void MainWindow::on_actionNextFrame_triggered()
{
    qDebug() << "Deselecting current frame";
    ui->frameTable->selectionModel()->select(
                ui->frameTable->model()->index(0, selectedFrame),
                QItemSelectionModel::Deselect);
    qDebug() << "Currently selected" << selectedFrame << "of" << frames.length();
    if (selectedFrame == frames.length() - 1)
    {
        qDebug() << "Already on the last frame, will make a new one";
        // Create another frame
        frames.append(AnimationFrame());
        ui->frameTable->setColumnCount(frames.length());
        // this is slow, fix it:
        drawFrames();
        selectFrame(frames.length() - 1);
    }
    else
        selectFrame(selectedFrame + 1);
    ui->frameTable->selectionModel()->select(
                ui->frameTable->model()->index(0, selectedFrame),
                QItemSelectionModel::Select);
}

void MainWindow::saveFrames()
{
    for (int i = 0; i < frames.length(); i++)
    {
        frames[i].saveTo(frameDir.filePath(QString("frame%1.png").arg(i)), "png");
    }
}

void MainWindow::on_actionSave_triggered()
{
    qDebug() << "saving frames to" << frameDir;
    saveFrames();
}

void MainWindow::on_actionExport_triggered()
{
    VideoExporter x;
    x.setFps(12);
    qDebug() << "Rendering..." << x.render(frameDir, frameDir.filePath("output.mp4"));
}
