#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include <QStringList>
#include <QApplication>

#include "client.h"

Client::Client(QWidget *par) : QWidget(par), connection("localhost", 2323), count(0)
{
    dir.setText("D:/");
    butScan.setText("Scan");

    progress.setaMaximum(1);
    progress.setValue(0);
    connect(&connection,  SIGNAL(signalReply(QString)), SLOT(slotReply(QString)));

    QLabel* lbl = new QLabel("Directory");
    QPushButton*  butDir = new QPushButton("Open");    

    connect(butDir, SIGNAL(clicked()), SLOT(slotBrowse()));
    connect(&butScan, SIGNAL(clicked()), SLOT(slotScan()));

    QGridLayout* grid = new QGridLayout;
    grid->addWidget(lbl, 0, 0);
    grid->addWidget(&dir, 0, 1);
    grid->addWidget(butDir, 0, 2);
    grid->addWidget(&butScan, 1, 0, 1, 3);
    grid->addWidget(&progress, 2, 0, 1, 3);
    grid->addWidget(&fileStatus, 3, 0, 1, 3);

    setLayout(grid);
}

//----------------------------------------------

void Client::slotBrowse()
{
    QString str = QFileDialog::getExistingDirectory(0, "Select a Directory",
                                                    dir.text() );
    if (!str.isEmpty())
        dir.setText(str);
}

//----------------------------------------------

void Client::slotScan()
{
    fileStatus.setText("");
    butScan.setEnabled(false);
    progress.setMaximum(1);
    progress.setValue(0);

    start(QDir(dir.text()));
}

//----------------------------------------------

void Client::slotReply(const QString& str)
{    
    if(str != "-1")
        fileStatus.append(str);

    progress.setValue(progress.value() + 1);

    if(progress.maximum() == progress.value())
    {
        butScan.setEnabled(true);
        count = 0;
    }
}

//----------------------------------------------

void Client::start(const QDir& curDir)
{
    QApplication::processEvents();

    QStringList listFiles = curDir.entryList(QDir::Files);
    count += listFiles.size();   // Подсчет файлов в текущем каталоге
    progress.setMaximum(count);

    QStringList listDir = curDir.entryList(QDir::Dirs);
    foreach (QString subdir, listDir)
    {
        if (subdir == "." || subdir == "..")
            continue;

        start(QDir(curDir.absoluteFilePath(subdir)));
    }

    foreach (QString file, listFiles)
    {
        connection.SendToServer(curDir.absoluteFilePath(file));
    }
}

//-----------------------------------------------


