#ifndef PROJECTFOLDERREADER_H
#define PROJECTFOLDERREADER_H

#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QSemaphore>
#include <QDirIterator>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QFileInfo>

#include "projectfoldertype.h"

class ProjectFolderReadTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    void setOutput(ProjectFolderType *pf);
    void setProjectFolder(QString path);

    bool isBusy() {return m_isBusy;}

    void run() override;

Q_SIGNALS:
    void taskFinished();

private:
    ProjectFolderType *pf;
    QString path = "";
    bool m_isBusy = false;
};

#endif // PROJECTFOLDERREADER_H
