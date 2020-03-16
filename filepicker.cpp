#include "filepicker.h"
#include "ui_filepicker.h"

#include <QStandardPaths>
#include <QFileDialog>

FilePicker::FilePicker(QString filter, int what, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilePicker),
    dlg(new QFileDialog),
    filter(filter),
    what(what)
{
    ui->setupUi(this);

    home = QStandardPaths::locate(QStandardPaths::HomeLocation, "",
                                  QStandardPaths::LocateOption::LocateDirectory);
    ui->pathEdit->setText(home);

    dlg->setNameFilter(filter);
    switch (what)
    {
    case File:
        dlg->setFileMode(QFileDialog::FileMode::ExistingFile);
        break;
    case NewFile:
        dlg->setFileMode(QFileDialog::FileMode::AnyFile);
        break;
    case Directory:
        dlg->setFileMode(QFileDialog::FileMode::Directory);
        break;
    }

    connect(dlg, &QFileDialog::currentChanged, this, [this](const QString &p)
    {
        ui->pathEdit->setText(p);
        path = p;
    });

    setLayout(ui->horizontalLayout);
}

FilePicker::~FilePicker()
{
    delete ui;
}

void FilePicker::on_pathEdit_textChanged(const QString &p)
{
    path = p;
}

void FilePicker::on_chooseButton_clicked()
{
    dlg->open();
}

QLineEdit *FilePicker::getPathTextField()
{
    return ui->pathEdit;
}
