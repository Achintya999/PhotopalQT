#include "photopalimgmodify.h"
#include "preferencedialog.h"
#include "logger.h"

#include <QThread>

void PhotopalImgModify::convertImage(QString filename)
{

    QImage qImage(filename);
    double dpi = convertToDpm(PreferenceDialog::readPreference());
    qImage.setDotsPerMeterX(dpi);
    qImage.setDotsPerMeterY(dpi);

    removeExtension(filename);

    qImage.save(filename.append("-low.jpg"));
    LOG(filename + QString::number((int)QThread::currentThreadId()));
}

double PhotopalImgModify::convertToDpm(QString dpiValue)
{
    double dpi = dpiValue.toDouble();
    return dpi * DPM_VALUE;
}

void PhotopalImgModify::removeExtension(QString& filename)
{
    int pos=filename.lastIndexOf('.');
    filename=filename.left(pos);
}
