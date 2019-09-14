#include "BIlibiliComic.h"
#include "WorkThread.h"
#include <QFileDialog>

void BIlibiliComic::selectSavePath()
{
	QString qstrPath = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择保存文件夹"));
	if (qstrPath.isEmpty())
		return;

	ui.savePathLineEdit->setText(qstrPath);
}

void BIlibiliComic::starWork()
{
	QString qstrSavePath = ui.savePathLineEdit->text();
	QString qstrComicID = ui.comicIDLineEdit->text();
	int nJumpNum = ui.jumpCapLineEdit->text().toInt();
	QString qstrCookie = ui.cookieTextEdit->toPlainText();

	WorkInfo workInfo;
	workInfo.m_saveRoot = qstrSavePath;
	workInfo.m_comicID = qstrComicID;
	workInfo.m_nJumpNum = nJumpNum;
	workInfo.m_Cookie = qstrCookie;

	WorkThread * ptrWork = new WorkThread(workInfo);
	ptrWork->start();

}

BIlibiliComic::BIlibiliComic(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.mainToolBar->setVisible(false);
	ui.menuBar->setVisible(false);
	ui.statusBar->setVisible(false);

	connect(ui.chooseSavePathBtn, SIGNAL(clicked(bool)),this,SLOT(selectSavePath()));
	connect(ui.startWorkBtn, SIGNAL(clicked(bool)), this, SLOT(starWork()));

}
