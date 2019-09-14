#pragma once

#include <QNetworkReply>
#include <QJsonObject>
#include <QThread>
#include <QPointer>
#include <QNetworkAccessManager>

struct WorkInfo
{
	//index.dat�ļ�Ŀ¼���Ӱ�׿�����������Ļ���
	QString m_strIndexDataPath;

	//����ID
	QString m_comicID;

	//����Ŀ¼
	QString m_saveRoot;

	//�Ӱ�׿��������ȡ���Ǵ�web����index.dat
	bool m_fromCache= false;

	//���������½�
	int m_nJumpNum;

	//��֤Cookie
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
