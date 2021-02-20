#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMessageBox>
#include <QThreadPool>
#include <QLabel>

#include "macro.h"
#include "projectfoldertype.h"
#include "projectfolderreadtask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef enum
{
    NOT_LEAVING = 0,
    FORCED,
    DESERVED
} AppExitType;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readSettings();
    void saveSettings();
    void hideToTray();
    void restoreFromTray();

    // Events
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent* event);

public slots:
    void pfrCallback();

private slots:
    void dudeIReallyHaveToExit();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QMessageBox *mbQuit;
    ProjectFolderReadTask *pfrTask;
    ProjectFolderType *pf;

    AppExitType appExit = NOT_LEAVING;

    // Settings
    bool param_hiddenToTray;
    QString param_projectsFolder;
    uint param_timesLostToTheirOwnProcrastination;
    uint param_discardWinOverProcrastinationIn;
    uint param_latestChange;

    bool isFinishedScanning = true;

    uint stats_unfinishedProjects = 0;
    uint stats_abandonedProjects = 0;
    uint stats_finishedProjects = 0;

    void readProjectFolder();
    void renderTable();
};
#endif // MAINWINDOW_H
