
#ifndef _MainWindow_H
#define _MainWindow_H

#include <QtGui>
#include <QMainWindow>
#include <QSystemTrayIcon>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    /** Default Constructor */
    MainWindow(QWidget *parent = 0);
    /** Destructor. */
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

public slots:

    

    
private slots:

    void updateMenu();
    
    void toggleVisibility(QSystemTrayIcon::ActivationReason e);
    void toggleVisibilitycontextmenu();
    
    void doQuit();
    
    void initStyle();
    
    void showSettingsGui();
    void showAbout();
    void showAddPeer();

private:
    
    QSystemTrayIcon *trayIcon;
    QAction *toggleVisibilityAction;
    QMenu *menu;
    
};

#endif 
