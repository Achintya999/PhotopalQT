#include "droparea.h"
#include "photopalimgmodify.h"
#include "logger.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QDir>
#include <QQueue>
#include <QThread>
#include <QThreadPool>

QQueue<QString> fileQueue;
QMutex mutex,mutex_done;
int doneSize,noOfFiles;

// Thread class to process image
class ImageModifyThread : public QThread
{
public:
    void run()
    {
        PhotopalImgModify photopalImgModify;

        while(!isQueueEmpty())
        {

            LOG(QString("Thread started running ") + QString::number((int)currentThreadId()));
            QString filename = fileQueue.dequeue();
            mutex.unlock();

            LOG("Caling Conversion" + QString::number((int)currentThreadId()));
            photopalImgModify.convertImage(filename);

            mutex_done.lock();
            doneSize--;
            mutex_done.unlock();
            LOG("Thread ended running " + QString::number((int)currentThreadId()));
            msleep(20);
        }
        mutex.unlock();
    }

    bool isQueueEmpty()
    {
        mutex.lock();
        if(fileQueue.empty())
        {
            return true;
        }
        return false;
    }
};

DropArea::DropArea(QWidget *parent)
    : QLabel(parent)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    setFont(QFont("Arial",20));
    LOG("DropArea Initialized");
    clear();
}

void DropArea::dragEnterEvent(QDragEnterEvent *event)
{
    setText(tr("<drop content>"));
    setBackgroundRole(QPalette::Highlight);

    event->acceptProposedAction();
}

void DropArea::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void DropArea::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (!mimeData->hasText())
    {
         setText(tr("Cannot display data"));
         return;
    }
    setBackgroundRole(QPalette::Dark);

    convertImage(mimeData->text());
    event->acceptProposedAction();
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void DropArea::clear()
{
    setText(tr("<drop content>"));
    setBackgroundRole(QPalette::Dark);
}

void DropArea::convertImage(QString filename)
{
    setText("Processing");
    QStringList filenames = filename.split('\n');
    foreach(QString filename,filenames)
    {
        QDir dir;
        normalizePath(filename);
        if(isImage(filename))
        {
            fileQueue.enqueue(filename);
        }
        else if(dir.exists(filename))
        {
            processDir(filename);
        }
        else
        {
            setText("Some files are not valid image files");
        }

    }
    noOfFiles = fileQueue.size();

    if(noOfFiles == 0)
    {
        setText("No valid image files were found");
        return;
    }

    progress1 =new QProgressDialog("Converting files...", "Cancel" ,0, noOfFiles, this);
    progress1->setWindowModality(Qt::WindowModal);

    doneSize = noOfFiles;

    for(int i = 0; i < 50 && i< noOfFiles; i++)
    {
        ImageModifyThread* imgModifyThread = new ImageModifyThread;
        imgModifyThread->start();
        connect(imgModifyThread,SIGNAL(finished()),this,SLOT(threadExited()));
        LOG("Thread Created!");
    }
    QThread::yieldCurrentThread();
}

void DropArea::threadExited()
{
    progress1->setValue(noOfFiles - doneSize);
    if(doneSize == 0)
    {
        LOG("All Threads Exiting");
        clear();
    }
}

void DropArea::processDir(QString dirname)
{
    QDir dir(dirname);
    QStringList fileList = dir.entryList();

    foreach(QString filename,fileList)
    {
        if(isImage(filename))
        {
            QString fullPath = dirname + "/" + filename;
            fileQueue.enqueue(fullPath);
        }
        else
        {
            setText("Some files are not valid image files");
        }
    }
}

bool DropArea::isImage(QString filename)
{
    int pos=filename.lastIndexOf('.');
    QString extension=filename.mid(pos + 1);
    if(extension.compare("png",Qt::CaseInsensitive) == 0 || extension.compare("jpeg",Qt::CaseInsensitive) == 0 || extension.compare("jpg",Qt::CaseInsensitive) == 0 || extension.compare("tiff",Qt::CaseInsensitive) == 0 || extension.compare("gif",Qt::CaseInsensitive) == 0 || extension.compare("tif",Qt::CaseInsensitive) == 0)
    {
        LOG(filename + " is a image");
        return true;
    }
    LOG(filename + "is not an image");
    return false;
}

void DropArea::normalizePath(QString& filename)
{
    QUrl qUrl(filename);
    filename=qUrl.toLocalFile();
}




