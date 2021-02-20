#ifndef PROJECTFOLDERMODEL_H
#define PROJECTFOLDERMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class ProjectFolderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ProjectFolderModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // PROJECTFOLDERMODEL_H
