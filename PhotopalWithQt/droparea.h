
#ifndef DROPAREA_H
#define DROPAREA_H

#include <QLabel>
#include <QProgressDialog>

QT_BEGIN_NAMESPACE
class QMimeData;
QT_END_NAMESPACE

class DropArea : public QLabel
{
    Q_OBJECT

public:
    QProgressDialog* progress1;
    DropArea(QWidget *parent = 0);

public slots:
    /*
    A function to restore the window when processing is completed
    */
    void clear();
    /*
    A function that is called when the thread exits
    */
    void threadExited();
    /*
    A function that handles the conversion of images by creating threads and creating a queue of images
    */
    void convertImage(QString filename);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    QLabel *label;
    /*
    A function that changes uri to absolute fil path
    */
    void normalizePath(QString& filename);
    /*
    A function to determine whether the given file is a n image or not
    */
    bool isImage(QString filename);
    /*
    A function to process the directory
    */
    void processDir(QString dirname);
};

#endif // DROPAREA_H
