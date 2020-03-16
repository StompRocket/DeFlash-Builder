#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include "filepicker.h"

#include <QWidget>
#include <QWizard>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>

class NewProjectWizard : public QWizard
{
    Q_OBJECT

signals:
    void projectCreated(QString path);

public:
    NewProjectWizard(QWidget *parent = nullptr);
    void accept() override;
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = nullptr);

private:
    QLabel *label;
};

class ProjectPage : public QWizardPage
{
    Q_OBJECT

public:
    ProjectPage(QWidget *parent = nullptr);

private:
    QFormLayout *form;
    QLineEdit *projectName;
    FilePicker *filePicker;
};

#endif // NEWPROJECTWIZARD_H
