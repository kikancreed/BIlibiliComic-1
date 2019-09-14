#pragma once

#include <QNetworkReply>
#include <QJsonObject>
#include <QThread>
#include <QPointer>
#include <QNetworkAccessManager>

struct WorkInfo
{
	//index.dat文件目录，从安卓上下载下来的缓存
	QString m_strIndexDataPath;

	//漫画ID
	QString m_comicID;

	//保存目录
	QString m_saveRoot;

	//从安卓缓存中提取还是从web下载index.dat
	bool m_fromCache= false;

	//跳过多少章节
	int m_nJumpNum;

	//验证Cookie
	QString m_Cookie;
};

class WorkThread : public QThread
{
	Q_OBJECT

public:	
	
	virtual void run()
	{
		getComicDetail();
	}

	WorkThread(WorkInfo workInfo);
	virtual ~WorkThread() {};

	void getComicDetail();
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

	void requestDetailFinished(QNetworkReply* reply);
	void parsePerEP();

private:

	QPointer<QNetworkAccessManager> m_naManager;

	QJsonObject m_detailJson;
	QMap<int, QString> m_epMap;
	QString m_currentEP;

	QString m_comicName;

	WorkInfo m_workInfo;
};
