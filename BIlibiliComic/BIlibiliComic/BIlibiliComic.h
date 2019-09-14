#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BIlibiliComic.h"
#include <QNetworkReply>
#include <QJsonObject>
#include <QThread>

class BIlibiliComic : public QMainWindow
{
	Q_OBJECT

public:
	BIlibiliComic(QWidget *parent = Q_NULLPTR);

public slots:	
	void selectSavePath();
	void starWork();

private:

	Ui::BIlibiliComicClass ui;
};