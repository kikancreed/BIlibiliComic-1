#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BIlibiliComic.h"
#include <QNetworkReply>
#include <QJsonObject>

class BIlibiliComic : public QMainWindow
{
	Q_OBJECT

public:
	BIlibiliComic(QWidget *parent = Q_NULLPTR);
	void getComicDetail(QUrl url);
	void getIndexDataToken(QString qstrEpID);

	int* generateHashKey(int nComicID,int nEpID);
	void unhashContent(int* hashKey, unsigned char* indexData, int nDataSize);
	void unZip();

	void parseAllImage(QByteArray& realData);
	QByteArray getImageToken(QString imageinfo);
	QByteArray getImageData(QByteArray& imageToken);

	void saveTo(QByteArray imageData,int name);

	QByteArray getIndexDataFromAndroid(QString qstrEpID);
	QByteArray getIndexDataFromWeb(QString qstrEpID);
	QByteArray findIndexDataFromAndroid(QString qstrPath);

public slots:
	void requestDetailFinished(QNetworkReply* reply);
	void parsePerEP();

signals:
	void onDetailFinished();
	void onTokenFinished();

private:

	Ui::BIlibiliComicClass ui;
	QJsonObject m_detailJson;
	QMap<int, QString> m_epMap;
	QString m_currentEP;

	QString m_strIndexDataPath;

	QString m_comicName;
	QString m_comicID;

	QString m_saveRoot;

	bool m_fromCache;
};
