#ifndef FILEPICKER_H
#define FILEPICKER_H

#include <QWidget>
#include <QLineEdit>
#include <QFileDialog>

namespace Ui {
class FilePicker;
}

class FilePicker : public QWidget
{
    Q_OBJECT

public:
    enum
    {
        File,
        NewFile,
        Directory,
    };

    explicit FilePicker(QString filter, int what = File, QWidget *parent = nullptr);
    ~FilePicker();
    QString path{};
    QLineEdit *getPathTextField();

private slots:
    void on_pathEdit_textChanged(const QString &arg1);
    void on_chooseButton_clicked();

private:
    Ui::FilePicker *ui;
    QFileDialog *dlg;
    QString home;
    QString filter;
    int what;
};

#endif // FILEPICKER_H
