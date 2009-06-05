

#include "aboutgui.h"

#include <iostream>
#include <sstream>

#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <QContextMenuEvent>
#include <QMenu>
#include <QCursor>
#include <QPoint>
#include <QMouseEvent>
#include <QPixmap>


aboutgui::aboutgui(QWidget *parent)
:QDialog(parent)
{
  
  ui.setupUi(this);
 

  QFile aboutFile(QString(QApplication::applicationDirPath()+"/about.html"));
   if (aboutFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&aboutFile);
        ui.about->setText(in.readAll());
   }
/*
  QFile licenseFile(QLatin1String(":/licence.html"));
   if (licenseFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&licenseFile);
        ui.license->setText(in.readAll());
   }
  QFile authorsFile(QLatin1String(":/authors.html"));
   if (authorsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&authorsFile);
        ui.authors->setText(in.readAll());
   }
  QFile thanksFile(QLatin1String(":/thanks.html"));
   if (thanksFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&thanksFile);
        ui.thanks->setText(in.readAll());
   }
  */
	//ui.authors->setText
	
 
   	ui.label_2->setMinimumWidth(20);
}


