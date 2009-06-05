

#ifndef SETTINGSGUI_H
#define SETTINGSGUI_H

#include "ui_settingsgui.h"
#include <QtGui>
#include <QSettings>


class settingsgui : public QDialog, private Ui::settingsgui
{
    	Q_OBJECT

public:
	settingsgui(QWidget *parent = 0, Qt::WFlags flags = 0);
	~settingsgui();
	
	 bool startMinimized() const;

private slots:
	void loadSettings();
	void saveSettings();
	void on_styleCombo_activated(const QString &styleName);
	void on_styleSheetCombo_activated(const QString &styleSheetName);
	
	void on_cmd_openFile();
	void on_cmd_openFile2();
	void on_cmd_openFile3();
	void on_cmd_openFile4();
	void on_cmd_openFile5();
	void on_cmd_openFile6();

private:
	QSettings* settings;
	void loadStyleSheet(const QString &sheetName);
  void loadqss();

};


#endif

