#include "projectdialog.h"
#include "ui_projectdialog.h"
#include "mainwindow.h"
#include "newprojectwizard.h"
#include "version.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

ProjectDialog::ProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);
    setContentsMargins(10, 10, 10, 10);
    setWindowTitle(fullName);
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

void ProjectDialog::onProjectCreated(QString where)
{
    auto *mw = new MainWindow(where);
    mw->show();
    close();
}

void ProjectDialog::on_newProjectButton_clicked()
{
    auto *wizard = new NewProjectWizard();
    connect(wizard, &NewProjectWizard::projectCreated, this, &ProjectDialog::onProjectCreated);
    wizard->open();
}

void ProjectDialog::on_openProjectButton_clicked()
{
    auto home = QStandardPaths::locate(QStandardPaths::HomeLocation, "",
                                       QStandardPaths::LocateOption::LocateDirectory);
    qDebug() << home;

    onProjectCreated(QFileDialog::getExistingDirectory(this, "StompRocket Create Project"));
}
