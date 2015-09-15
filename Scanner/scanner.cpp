#include <QString>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <algorithm>

#include "scanner.h"

const int MAX_SIZE = 2000000;


//--------------------------------------------------

void Scanner::loadDictionary(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    if(!dictionary.isEmpty())
        dictionary.clear();

    QTextStream text(&file);
    while(!text.atEnd())
    {
        QString line = text.readLine();
        if(!line.isEmpty())
        {
            QRegularExpression reg("(\\w{2,}).+({.+})");
            QRegularExpressionMatch match = reg.match(line);

            dictionary.push_back(qMakePair(QByteArray::fromHex(match.captured(1).toLatin1() ),
                                           match.captured(2)));
        }
    }
}

//--------------------------------------------------

QString Scanner::scanFile (const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly ))
        return fileName +" file isn't opened";

    auto minMax = minMaxLen();
    int  minLen = minMax.first;
    int  maxLen = minMax.second;

    int size   = file.size();
    int offset = 0;

    QString result = "";
    uchar* text;

    while(offset < size - minLen + 1)
    {
        int tlen = MAX_SIZE > size - offset ? size - offset : MAX_SIZE;

        text = file.map(offset, tlen);
        if(!text)
            break;

        QByteArray buffer = QByteArray::fromRawData(reinterpret_cast<char*>(text), tlen);
        if((result = scanArray(buffer)) != "-1")
            return fileName + " - " + result;

        file.unmap(text);

        if(tlen >= maxLen)
            offset += tlen - maxLen + 1;
        else
            offset += tlen - minLen + 1;
    }
    return "-1";
}

//---------------------------------------------------

QString Scanner::scanArray(const QByteArray& array)
{
    Const_It pos = dictionary.constBegin();

    for(; pos != dictionary.constEnd(); ++pos)
    {
        if(array.contains(pos->first))
            return pos->second;
    }
    return "-1";
}

//----------------------------------------------------

// Min and max length hexStrings in dictionary.
QPair<int, int> Scanner::minMaxLen()
{
    const auto lambda = [](const Pair& a, const Pair& b){return a.first.size() < b.first.size();};    
    auto tmp = std::minmax_element(dictionary.begin(), dictionary.end(), lambda);

    return qMakePair(tmp.first->first.size(), tmp.second->first.size());
}


