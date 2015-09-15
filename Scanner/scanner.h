#ifndef SCANNER_H
#define SCANNER_H

#include <QByteArray>
#include <QVector>
#include <QPair>


class QString;

class Scanner
{
    typedef QPair<QByteArray, QString> Pair;   // <hexString, GUID>
    typedef QVector<Pair> Vector;
    typedef Vector::const_iterator Const_It;    

    QPair<int, int> minMaxLen();      // Min and max length hexStrings in dictionary.

public:
    Scanner(const QString& fileName) { loadDictionary(fileName); }

    QString scanFile (const QString&);
    QString scanArray(const QByteArray&);

    void loadDictionary(const QString&);

private:
    Vector dictionary;
};

#endif // SCANNER_H


