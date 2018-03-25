#ifndef PHOTOPALMAINWINDOW_H
#define PHOTOPALMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PhotopalMainWindow;
}

class PhotopalMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PhotopalMainWindow(QWidget *parent = 0);
    ~PhotopalMainWindow();

public slots:
    /*
    A function to open the Log Dialog Box
    */
    void openLogDialog();
    /*
    A function to open the Prefernce Dialog Box
    */
    void openPrefDialog();

private:
    Ui::PhotopalMainWindow *ui;
    /*
    A function to create the menu and its options
    */
    void setupMenu();
};

#endif // PHOTOPALMAINWINDOW_H
