

#include "settingsgui.h"

settingsgui::settingsgui(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
    	setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose,true);
	settings= new QSettings(QApplication::applicationDirPath()+"/application.ini",QSettings::IniFormat);

    	loadqss();
	styleCombo->addItems(QStyleFactory::keys());
	loadSettings();

	connect(ok_Button,     SIGNAL(clicked(bool) ),this,SLOT(saveSettings() ) );
	connect(cancel_Button, SIGNAL(clicked(bool) ),this,SLOT(close() ) );
	connect(cmd_openFile,  SIGNAL(clicked(bool) ),this,SLOT(on_cmd_openFile()));
	connect(cmd_openFile_2,SIGNAL(clicked(bool) ),this,SLOT(on_cmd_openFile2()));
	connect(cmd_openFile_3,SIGNAL(clicked(bool) ),this,SLOT(on_cmd_openFile3()));
	connect(cmd_openFile_4,SIGNAL(clicked(bool) ),this,SLOT(on_cmd_openFile4()));
	connect(cmd_openFile_5,SIGNAL(clicked(bool) ),this,SLOT(on_cmd_openFile5()));
	connect(cmd_openFile_6,SIGNAL(clicked(bool) ),this,SLOT(on_cmd_openFile6()));

}

settingsgui::~settingsgui()
{
	delete (settings);
}

void settingsgui::loadSettings()
{
	settings->beginGroup("General");
	
	  checkStartMinimized->setChecked(settings->value(QString::fromUtf8("StartMinimized"), false).toBool());
		

		if(settings->value("current_Style","").toString().isEmpty()==false)
			styleCombo->setCurrentIndex(styleCombo->findText(settings->value("current_Style","").toString()));
		else
		{
			//find default Style for this System
			QRegExp regExp("Q(.*)Style");
			QString defaultStyle = QApplication::style()->metaObject()->className();
			
			if (defaultStyle == QLatin1String("QMacStyle"))
				defaultStyle = QLatin1String("Macintosh (Aqua)");
			else if (regExp.exactMatch(defaultStyle))
				defaultStyle = regExp.cap(1);
			
			//styleCombo->addItems(QStyleFactory::keys());
			styleCombo->setCurrentIndex(styleCombo->findText(defaultStyle));

		}

		styleSheetCombo->setCurrentIndex(styleSheetCombo->findText(settings->value("current_Style_sheet","Default").toString()));
	settings->endGroup();

	settings->beginGroup("Network");

	settings->endGroup();


	settings->beginGroup("Sound");
		settings->beginGroup("SoundFilePath");
			txt_SoundFile->setText(settings->value("User_go_Online","").toString());
			txt_SoundFile2->setText(settings->value("User_go_Offline","").toString());
			txt_SoundFile3->setText(settings->value("FileSend_Finished","").toString());
			txt_SoundFile4->setText(settings->value("FileRecive_Incoming","").toString());
			txt_SoundFile5->setText(settings->value("FileRecive_Finished","").toString());
			txt_SoundFile6->setText(settings->value("NewChatMessage","").toString());

			if(!txt_SoundFile->text().isEmpty())checkBoxSound->setEnabled(true);
			if(!txt_SoundFile2->text().isEmpty())checkBoxSound_2->setEnabled(true);
			if(!txt_SoundFile3->text().isEmpty())checkBoxSound_3->setEnabled(true);
			if(!txt_SoundFile4->text().isEmpty())checkBoxSound_4->setEnabled(true);
			if(!txt_SoundFile5->text().isEmpty())checkBoxSound_5->setEnabled(true);
			if(!txt_SoundFile6->text().isEmpty())checkBoxSound_6->setEnabled(true);

		settings->endGroup();

		settings->beginGroup("Enable");
			checkBoxSound->setChecked(settings->value("User_go_Online",false).toBool());
			checkBoxSound_2->setChecked(settings->value("User_go_Offline",false).toBool());
			checkBoxSound_3->setChecked(settings->value("FileSend_Finished",false).toBool());
			checkBoxSound_4->setChecked(settings->value("FileRecive_Incoming",false).toBool());
			checkBoxSound_5->setChecked(settings->value("FileRecive_Finished",false).toBool());
			checkBoxSound_6->setChecked(settings->value("NewChatMessage",false).toBool());
		settings->endGroup();	
		
	settings->endGroup();

}
void settingsgui::saveSettings()
{	

	settings->beginGroup("General");
	
	  settings->setValue(QString::fromUtf8("StartMinimized"), startMinimized());

		settings->setValue("current_Style",styleCombo->currentText());
		settings->setValue("current_Style_sheet",styleSheetCombo->currentText());
		
	settings->endGroup();

	settings->beginGroup("Network");

	settings->endGroup();
	
	settings->beginGroup("Sound");
	
		settings->beginGroup("Enable");
			settings->setValue("User_go_Online",checkBoxSound->isChecked());
			settings->setValue("User_go_Offline",checkBoxSound_2->isChecked());
			settings->setValue("FileSend_Finished",checkBoxSound_3->isChecked());
			settings->setValue("FileRecive_Incoming",checkBoxSound_4->isChecked());
			settings->setValue("FileRecive_Finished",checkBoxSound_5->isChecked());
			settings->setValue("NewChatMessage",checkBoxSound_6->isChecked());
			settings->endGroup();
			
		settings->beginGroup("SoundFilePath");
			settings->setValue("User_go_Online",txt_SoundFile->text());
			settings->setValue("User_go_Offline",txt_SoundFile2->text());
			settings->setValue("FileSend_Finished",txt_SoundFile3->text());
			settings->setValue("FileRecive_Incoming",txt_SoundFile4->text());
			settings->setValue("FileRecive_Finished",txt_SoundFile5->text());
			settings->setValue("NewChatMessage",txt_SoundFile6->text());
		settings->endGroup();
		
	settings->endGroup();
	this->close();
}


void settingsgui::on_styleCombo_activated(const QString &styleName)
{
	qApp->setStyle(styleName);

}

void settingsgui::on_styleSheetCombo_activated(const QString &sheetName)
{
	loadStyleSheet(sheetName);
}

void settingsgui::loadStyleSheet(const QString &sheetName)
{
	// external Stylesheets
	QFile file(QApplication::applicationDirPath() + "/qss/" + sheetName.toLower() + ".qss");
	
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	
	
	qApp->setStyleSheet(styleSheet); 
}

void settingsgui::loadqss()
{

	QFileInfoList slist = QDir(QApplication::applicationDirPath() + "/qss/").entryInfoList();
	foreach(QFileInfo st, slist)
	{
	if(st.fileName() != "." && st.fileName() != ".." && st.isFile())
	styleSheetCombo->addItem(st.fileName().remove(".qss"));
	}
}
////FilePath=QFileDialog::getOpenFileName(this,"Open File", ".", "all Files (*.*)");
void settingsgui::on_cmd_openFile()
{

	txt_SoundFile->setText(QFileDialog::getOpenFileName(this,"Open File", ".", "wav (*.wav)"));
	if(txt_SoundFile->text().isEmpty()){
		checkBoxSound->setChecked(false);
		checkBoxSound->setEnabled(false);
	}
	else
		checkBoxSound->setEnabled(true);
}

void settingsgui::on_cmd_openFile2()
{
	txt_SoundFile2->setText(QFileDialog::getOpenFileName(this,"Open File", ".", "wav (*.wav)"));
	if(txt_SoundFile2->text().isEmpty()){	
		checkBoxSound_2->setChecked(false);
		checkBoxSound_2->setEnabled(false);
	}	
	else
		checkBoxSound_2->setEnabled(true);

}
void settingsgui::on_cmd_openFile3()
{
	txt_SoundFile3->setText(QFileDialog::getOpenFileName(this,"Open File", ".", "wav (*.wav)"));
	if(txt_SoundFile3->text().isEmpty()){
		checkBoxSound_3->setChecked(false);
		checkBoxSound_3->setEnabled(false);
	}
	else
		checkBoxSound_3->setEnabled(true);
}
void settingsgui::on_cmd_openFile4()
{
	txt_SoundFile4->setText(QFileDialog::getOpenFileName(this,"Open File", ".", "wav (*.wav)"));
	if(txt_SoundFile4->text().isEmpty()){
		checkBoxSound_4->setChecked(false);
		checkBoxSound_4->setEnabled(false);
	}
	else
		checkBoxSound_4->setEnabled(true);
}
void settingsgui::on_cmd_openFile5()
{
	txt_SoundFile5->setText(QFileDialog::getOpenFileName(this,"Open File", ".", "wav (*.wav)"));
	if(txt_SoundFile5->text().isEmpty()){
		checkBoxSound_5->setChecked(false);
		checkBoxSound_5->setEnabled(false);
	}
	else
		checkBoxSound_5->setEnabled(true);
}
void settingsgui::on_cmd_openFile6()
{
	txt_SoundFile6->setText(QFileDialog::getOpenFileName(this,"Open File", ".", "wav (*.wav)"));
	if(txt_SoundFile6->text().isEmpty()){
		checkBoxSound_6->setChecked(false);
		checkBoxSound_6->setEnabled(false);
	}
	else
		checkBoxSound_6->setEnabled(true);
	
}

bool settingsgui::startMinimized() const {
  if(checkStartMinimized->isChecked()) return true;
  return checkStartMinimized->isChecked();
}