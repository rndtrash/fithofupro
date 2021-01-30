#ifndef PROJECTFOLDERTYPE_H
#define PROJECTFOLDERTYPE_H

#include <QString>
#include <string>
#include <unordered_map>

typedef enum {
    UNDEFINED = 0,
    FORGOTTEN,
    IN_PROGRESS,
    FINISHED
} ProjectStatusType;

class ProjectType
{
public:
    ProjectStatusType pst;
    uint lastChange;

    ProjectType(ProjectStatusType pst, uint lastChange)
        :pst(pst), lastChange(lastChange)
    {}
};

typedef std::unordered_map<std::string, ProjectType*> ProjectFolderType;

#endif // PROJECTFOLDERTYPE_H
