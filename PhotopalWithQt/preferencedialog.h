#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>

#define PREF_FILE "prefs.txt"
#define GET_RESOLUTION(x) x + "x" + x

namespace Ui {
class PreferenceDialog;
}

class PreferenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenceDialog(QWidget *parent = 0);
    static QString readPreference();
    ~PreferenceDialog();

public slots:
    void accept();

private:
    Ui::PreferenceDialog *ui;
    void writePreference(QString dpiValue);
};

#endif // PREFERENCEDIALOG_H
