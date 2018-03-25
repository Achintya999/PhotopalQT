#include "photopalmainwindow.h"
#include "ui_photopalmainwindow.h"
#include "logger.h"
#include "logdialog.h"
#include "preferencedialog.h"

PhotopalMainWindow::PhotopalMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::PhotopalMainWindow)
{
    ui->setupUi(this);
    setupMenu();
    LOG("Main Window Created");
}

void PhotopalMainWindow::openLogDialog()
{
    LogDialog* logDialog = new LogDialog(this);
    logDialog->setModal(true);
    logDialog->show();
}

void PhotopalMainWindow::openPrefDialog()
{
    PreferenceDialog* prefDialog = new PreferenceDialog(this);
    prefDialog->setModal(true);
    prefDialog->show();
}

void PhotopalMainWindow::setupMenu()
{
    QAction* openLog = new QAction(tr("&Logs"),this);
    connect(openLog,&QAction::triggered,this,&PhotopalMainWindow::openLogDialog);
    QAction* openPref = new QAction(tr("&Preferences"),this);
    connect(openPref,&QAction::triggered,this,&PhotopalMainWindow::openPrefDialog);

    QMenu* fileMenu = ui->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openLog);
    fileMenu->addAction(openPref);
}

PhotopalMainWindow::~PhotopalMainWindow()
{
    delete ui;
}


