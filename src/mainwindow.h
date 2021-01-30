#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMessageBox>
#include <QThreadPool>
#include <QSemaphore>

#include "macro.h"
#include "projectfoldertype.h"
#include "projectfolderreadtask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

    bool forceExit = false;

    // Settings
    bool param_hiddenToTray;
    QString param_projectsFolder;
    unsigned int param_timesLostToTheirOwnProcrastination;

    void readProjectFolder();
};
#endif // MAINWINDOW_H
