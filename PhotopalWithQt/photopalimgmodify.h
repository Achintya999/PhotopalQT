#ifndef PHOTOPALIMGMODIFY_H
#define PHOTOPALIMGMODIFY_H

#include "QImage"
#include "droparea.h"
#include "QUrl"

#define DPM_VALUE 39.3701

class PhotopalImgModify
{
public:
    /*
    A function that converts a given image to the dpi mentioned in the prefernce and save it as filename-low.jpeg
    */
    void convertImage(QString filename);
    /*
    A function to remove the extension from the filename
    */
    void removeExtension(QString& filename);
    /*
    A function that converts the dpi value to dpm value
    */
    double convertToDpm(QString dpiValue);
};

#endif // PHOTOPALIMGMODIFY_H
