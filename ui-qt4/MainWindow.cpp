
#include "settingsgui.h"
#include "aboutgui.h"
#include "addpeer.h"
#include "MainWindow.h"

#include <QtGui>
#include <QMessageBox>
#include <QSystemTrayIcon>

#define IMAGE_MINIMIZE          ":/images/window_nofullscreen.png"
#define IMAGE_MAXIMIZE          ":/images/window_fullscreen.png"
#define IMAGE_N2NICON           ":/images/network_workgroup.png"
#define IMAGE_QUIT              ":/images/exit.png"

/** Constructor */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Startup ui
    setupUi(this);

    // Connections
    connect(actionAdd_Peer, SIGNAL(triggered()), this, SLOT(showAddPeer()));
    connect(actionSettings, SIGNAL(triggered()), this, SLOT(showSettingsGui()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(doQuit()));
   
    // Tray icon Menu
    menu = new QMenu(this);
    QObject::connect(menu, SIGNAL(aboutToShow()), this, SLOT(updateMenu()));
    toggleVisibilityAction = 
            menu->addAction(QIcon(IMAGE_N2NICON), tr("Show/Hide"), this, SLOT(toggleVisibilitycontextmenu()));
    menu->addSeparator();
    menu->addAction(QIcon(IMAGE_MINIMIZE), tr("Minimize"), this, SLOT(showMinimized()));
    menu->addAction(QIcon(IMAGE_MAXIMIZE), tr("Maximize"), this, SLOT(showMaximized()));
    menu->addSeparator();
    menu->addAction(QIcon(IMAGE_QUIT), tr("&Quit"), this, SLOT(doQuit()));
    // End of Icon Menu
    
    // Create the tray icon
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip(tr("ceofhack"));
    trayIcon->setContextMenu(menu);
    trayIcon->setIcon(QIcon(IMAGE_N2NICON));
    
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, 
            SLOT(toggleVisibility(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
    
    initStyle();
}

MainWindow::~MainWindow()
{
    //delete ui;
}


void MainWindow::closeEvent(QCloseEvent *e)
{
    static bool firstTime = true;

    if (trayIcon->isVisible()) {
        if (firstTime)
        {
/*****
            QMessageBox::information(this, tr("ceofhack gui System tray"),
            tr("Application will continue running. Quit using context menu in the system tray"));
*****/
            firstTime = false;
        }
        hide();
        e->ignore();
    }

}


void MainWindow::updateMenu()
{
    toggleVisibilityAction->setText(isVisible() ? tr("Hide") : tr("Show"));
}

void MainWindow::toggleVisibility(QSystemTrayIcon::ActivationReason e)
{
    if(e == QSystemTrayIcon::Trigger || e == QSystemTrayIcon::DoubleClick){
        if(isHidden()){
            show();
            if(isMinimized()){
                if(isMaximized()){
                    showMaximized();
                }else{
                    showNormal();
                }
            }
            raise();
            activateWindow();
        }else{
            hide();
        }
    }
}

void MainWindow::toggleVisibilitycontextmenu()
{
    if (isVisible())
        hide();
    else
        show();
}

void MainWindow::doQuit()
{  
    QString queryWrn;
	  queryWrn.clear();
	  queryWrn.append(tr("Do you really want to exit ceofhack ?"));

		if ((QMessageBox::question(this, tr("Really quit ? "),queryWrn,QMessageBox::Ok|QMessageBox::No, QMessageBox::Ok))== QMessageBox::Ok)
		{
      qApp->quit();
		}
		else
		return;
}

void MainWindow::initStyle()
{
    QSettings * settings=new QSettings(QApplication::applicationDirPath()+"/application.ini",QSettings::IniFormat);
    settings->beginGroup("General");
	//Load Style
		QString Style=(settings->value("current_Style","")).toString();
		if(Style.isEmpty()==true)
		{
			//find default Style for this System
			QRegExp regExp("Q(.*)Style");
			Style = QApplication::style()->metaObject()->className();
			
			if (Style == QLatin1String("QMacStyle"))
				Style = QLatin1String("Macintosh (Aqua)");
			else if (regExp.exactMatch(Style))
				Style = regExp.cap(1);
			
			//styleCombo->addItems(QStyleFactory::keys());
		}
		
		qApp->setStyle(Style);
	 //Load Style end

	 //Load Stylesheet	
		QFile file(QApplication::applicationDirPath() + "/qss/" + 
			settings->value("current_Style_sheet","Default").toString() + ".qss");
		
		file.open(QFile::ReadOnly);
		QString styleSheet = QLatin1String(file.readAll());
		qApp->setStyleSheet(styleSheet);
	//load Stylesheet end
	settings->endGroup();

    delete settings;
}

/** Shows Settings */
void MainWindow::showSettingsGui()
{
    settingsgui *sgui = new settingsgui();
    sgui->show();
}

/** Shows About Dialog */
void MainWindow::showAbout()
{
    aboutgui *showAbout = new aboutgui();
    showAbout->show();
}

/** Shows Add Peer Dialog */
void MainWindow::showAddPeer()
{
    AddPeer *addpeerdlg = new AddPeer();
    addpeerdlg->show();
}
