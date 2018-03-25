#ifndef LOGGER_H
#define LOGGER_H
#define LOG(x) CreateLog( x , __FILE__)
#define LOG_FILE "log.txt"

#include <QString>

void CreateLog(QString str,QString filename);

#endif // LOGGER_H
