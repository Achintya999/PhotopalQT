#include "logger.h"

#include <QFile>
#include <QTextStream>
#include <QDir>

void CreateLog(QString str, QString filename)
{
    if (str != NULL)
    {
        QFile file(LOG_FILE);
        if ( file.open(QIODevice::Append) )
        {
            QTextStream stream( &file );
            stream << __DATE__ << __TIME__ << " : "<< filename << " : " << str << '\n';
        }
        file.close();
    }
}
