#include "preferencedialog.h"
#include "ui_preferencedialog.h"

#include <QFile>
#include <QTextStream>

PreferenceDialog::PreferenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceDialog)
{
    ui->setupUi(this);
    QString dpi=readPreference();
    ui->dpiValue->setText(dpi);

}

void PreferenceDialog::accept()
{
    writePreference(ui->dpiValue->text());
    close();
}

QString PreferenceDialog::readPreference()
{
    QFile inputFile(PREF_FILE);
    QString line = "";
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          line = in.readLine();
       }
       inputFile.close();
    }
    if(line.compare("") == 0)
    {
        line = "72";
    }
    return line;
}

void PreferenceDialog::writePreference(QString dpiValue)
{
    QFile file(PREF_FILE);
    if ( file.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &file );
        stream << dpiValue;
    }
    file.close();
}

PreferenceDialog::~PreferenceDialog()
{
    delete ui;
}
