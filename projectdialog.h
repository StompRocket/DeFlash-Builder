#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class ProjectDialog;
}

class ProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectDialog(QWidget *parent = nullptr);
    ~ProjectDialog();

private slots:
    void on_newProjectButton_clicked();
    void on_openProjectButton_clicked();
    void onProjectCreated(QString where);

private:
    Ui::ProjectDialog *ui;
};

#endif // PROJECTDIALOG_H
