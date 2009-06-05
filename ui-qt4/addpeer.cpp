
#include "addpeer.h"

AddPeer::AddPeer(QDialog *parent)
{
	setupUi(this);	
	this->setAttribute(Qt::WA_DeleteOnClose,true);

	connect(buttonBox,SIGNAL(accepted()),this,SLOT(addnewUser()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	
	setFixedSize(QSize(408, 184));

}
void AddPeer::addnewUser()
{
	QString Name=nickline->text();
	//QString I2PDestination=textEdit->toPlainText();

	if(Name.isEmpty())
	{
		QMessageBox* msgBox= new QMessageBox(this);
			msgBox->setIcon(QMessageBox::Warning);
			msgBox->setText("Adding Peer");
			msgBox->setInformativeText("You must add a nick for the User\nadding abborted");
			msgBox->setStandardButtons(QMessageBox::Ok);
			msgBox->setDefaultButton(QMessageBox::Ok);
			msgBox->setWindowModality(Qt::NonModal);
			msgBox->show();
		return;
	}

	this->close();


}

