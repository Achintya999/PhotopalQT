#include "logger.h"
#include "logdialog.h"
#include "ui_logdialog.h"

#include <QFile>
#include <QScrollBar>
#include <QTextStream>

LogDialog::LogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);

    ui->textLog->setText(readLogs());
}

QString LogDialog::readLogs()
{
    QFile inputFile(LOG_FILE);
    QString line="";
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          line = line + '\n' +in.readLine();
       }
       inputFile.close();
    }
    return line;
}

LogDialog::~LogDialog()
{
    delete ui;
}
