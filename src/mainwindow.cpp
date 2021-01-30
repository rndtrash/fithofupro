#include "mainwindow.h"
#include "./ui_mainwindow.h"

// https://www.youtube.com/watch?v=gLYg1Pe2_K8

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pfrTask(new ProjectFolderReadTask())
    , pf(new ProjectFolderType(0))
{
    // Init classes
    pfrTask->setAutoDelete(false);
    pfrTask->setOutput(pf);
    connect(pfrTask, &ProjectFolderReadTask::taskFinished,
            this, &MainWindow::pfrCallback);

    QIcon fithofuproIcon = QICON_SYSTEM("fithofupro");

    trayMenu = new QMenu(this);
    {
        QAction *a = new QAction(tr("Восстановить из трея"), trayMenu);
        connect(a, &QAction::triggered,
                this, &MainWindow::restoreFromTray);
        trayMenu->addAction(a);
    }

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(fithofuproIcon);
    trayIcon->setContextMenu(trayMenu);

    mbQuit = new QMessageBox(QMessageBox::Icon::Question, tr("Выход из FiThoFuPro"),
                             tr("Внимание! Вы ещё не сделали ни одного изменения в один из своих проектов. " \
                                "Данная выходка будет учтена, вы будете чувствовать явный проигрыш своей прокрастинации, вам будет стыдно, вы совершите судоку (осуждаем)." \
                                "\nВсё ещё хотите выйти?"),
                             QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No, this);

    // Init UI
    ui->setupUi(this);

    this->setWindowIcon(fithofuproIcon);

    connect(ui->m_hide_to_tray, &QAction::triggered,
            this, &MainWindow::hideToTray);
    connect(ui->m_dude_i_really_have_to_exit, &QAction::triggered,
            this, &MainWindow::dudeIReallyHaveToExit);

    ui->tableWidget->horizontalHeader()->resizeSections(QHeaderView::ResizeMode::ResizeToContents);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("Название проекта") << tr("Статус") << tr("Последнее изменение"));

    ui->statusBar->showMessage(tr("Готово."));

    // Read settings
    readSettings();

    if (param_hiddenToTray)
        hideToTray();

    readProjectFolder();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pfrTask;

    for(auto itr = pf->begin(); itr != pf->end(); itr++)
    {
        delete (itr->second);
    }
    pf->clear();
    delete pf;
}

void MainWindow::hideToTray()
{
    trayIcon->show();
    this->hide();
}

void MainWindow::restoreFromTray()
{
    trayIcon->hide();
    this->show();
}

void MainWindow::readSettings()
{
    QSETTINGS_FITHOFUPRO();

    settings.beginGroup("App");
    QSETTINGS_READ_PROPERTY(hiddenToTray, false, toBool)
    QSETTINGS_READ_PROPERTY(projectsFolder, "", toString)
    QSETTINGS_READ_PROPERTY(timesLostToTheirOwnProcrastination, 0, toUInt)
    settings.endGroup();

    pfrTask->setProjectFolder(param_projectsFolder);
}

void MainWindow::saveSettings()
{
    QSETTINGS_FITHOFUPRO();

    settings.beginGroup("App");
    QSETTINGS_SAVE_PROPERTY(hiddenToTray)
    QSETTINGS_SAVE_PROPERTY(projectsFolder)
    QSETTINGS_SAVE_PROPERTY(timesLostToTheirOwnProcrastination)
    settings.endGroup();

    settings.beginGroup("Projects");
    for (const auto &entry : *pf)
    {
        settings.setValue(QString::fromUtf8(entry.first.c_str()), entry.second->pst);
    }
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (forceExit)
    {
        // TODO: mock user for exiting
        QThreadPool::globalInstance()->waitForDone();
        saveSettings();
        event->accept();
    }
    else
    {
        event->ignore();
        hideToTray();
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        event->accept();
        break;
    }

    QMainWindow::changeEvent(event);
}

void MainWindow::pfrCallback()
{
#ifdef QT_DEBUG
    qDebug() << "PFR:" << "Поток для рекурсивного поиска по папкам завершил свою работу.";
#endif

    QSETTINGS_FITHOFUPRO();
    settings.beginGroup("Projects");
    for (const auto &entry : *pf)
    {
        if (entry.second->pst == ProjectStatusType::UNDEFINED)
        {
            entry.second->pst = (ProjectStatusType) settings.value(QString::fromUtf8(entry.first.c_str()), ProjectStatusType::IN_PROGRESS).toUInt();
        }
#ifdef QT_DEBUG
        qDebug() << "PFR:" << "Содержимое элемента:"
                 << QString::fromUtf8(entry.first.c_str()) << ":"
                 << entry.second->pst << "," << QDateTime::fromTime_t(entry.second->lastChange);
#endif
    }
    settings.endGroup();
}

void MainWindow::dudeIReallyHaveToExit()
{
    int dc = this->mbQuit->exec();
    if (dc == QMessageBox::Yes)
    {
        param_timesLostToTheirOwnProcrastination++;
        forceExit = true;
        this->close();
    }
}

void MainWindow::readProjectFolder()
{
    if (pfrTask->isBusy())
    {
#ifdef QT_DEBUG
        qDebug() << "PFR:" << "Поиск уже запущен!";
#endif
        return;
    }

    this->statusBar()->clearMessage();
    QThreadPool::globalInstance()->start(pfrTask);
}
