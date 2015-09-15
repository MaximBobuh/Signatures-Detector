#include <QCoreApplication>
#include "server.h"

const QString DICT_FILE_NAME = "D:\\file.txt";
QString fileName;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc < 2)
        fileName = DICT_FILE_NAME;
    else
        fileName = argv[1];

    Server serv(2323);

    return a.exec();
}
