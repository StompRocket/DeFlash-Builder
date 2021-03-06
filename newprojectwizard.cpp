#include "newprojectwizard.h"
#include "config.h"
#include "version.h"

#include <QVBoxLayout>
#include <QLayoutItem>
#include <QDebug>
#include <QDir>
#include <QDialog>

NewProjectWizard::NewProjectWizard(QWidget *parent) : QWizard(parent)
{
    setWindowTitle(QString("New %1 Project").arg(shortName));

    addPage(new IntroPage);
    addPage(new ProjectPage);
}

void NewProjectWizard::accept()
{
    QString projectName = field("projectName").toString();
    QString projectPath = field("projectPath").toString();

    QDir project(projectPath);
    QDialog::accept();

    if (!project.mkdir(projectName))
    {
        qDebug() << "Could not create project directory, exiting";
        return;
    }
    project.cd(projectName);

    Config cfg{project.filePath("create.cfg")};
    cfg.set("meta.version", appVersion);
    cfg.set("frames.location", "frames");
    cfg.save();

    emit projectCreated(project.path());
}

IntroPage::IntroPage(QWidget *parent) : QWizardPage(parent)
{
    setTitle("Introduction");

    label = new QLabel(QString("Welcome to %1. This wizard will help "
                       "you create a new project.").arg(fullName), this);
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

ProjectPage::ProjectPage(QWidget *parent) : QWizardPage(parent)
{
    projectName = new QLineEdit(this);
    filePicker = new FilePicker("", FilePicker::Directory, this);

    form = new QFormLayout;
    form->addRow("Project Name", projectName);
    form->addRow("Project Location", filePicker);

    registerField("projectName", projectName);
    registerField("projectPath", filePicker->getPathTextField());

    setLayout(form);
}
