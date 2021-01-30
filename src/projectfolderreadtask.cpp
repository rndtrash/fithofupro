#include "projectfolderreadtask.h"

void ProjectFolderReadTask::setOutput(ProjectFolderType *pf)
{
    this->pf = pf;
}

void ProjectFolderReadTask::setProjectFolder(QString path)
{
    this->path = path;
}

void ProjectFolderReadTask::run()
{
    m_isBusy = true;

    assert(path != "");
    assert(pf != nullptr);

#ifdef QT_DEBUG
    qDebug() << "PFR:" << "Запускаем итератор для корневых папок...";
#endif

    QDirIterator pfRoot(path, QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot);
    while (pfRoot.hasNext())
    {
        QDir project(pfRoot.next());
        std::string projectName = project.dirName().toStdString();
#ifdef QT_DEBUG
        qDebug() << "PFR: Смотрим папку" << project.dirName();
#endif
        uint lastMod = 0;
        QDirIterator pfInside(project.absolutePath(), QDir::Filter::Files | QDir::Filter::NoDotAndDotDot, QDirIterator::IteratorFlag::Subdirectories);
        while (pfInside.hasNext())
        {
            QFileInfo fi(pfInside.next());
            lastMod = qMax(lastMod, fi.lastModified().toTime_t());
        }

        auto it = pf->find(projectName);
        if (it != pf->end())
        {
            it->second->lastChange = lastMod;
        } else {
            pf->insert(std::make_pair(projectName, new ProjectType(UNDEFINED, lastMod)));
        }
    }

    m_isBusy = false;
    emit taskFinished();
}
