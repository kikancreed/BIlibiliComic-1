#include "BIlibiliComic.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QMap>
#include <QDir>
#include <QMessageBox>

#include <windows.h>
#include "iostream"

#include "zip/zip.h"
#include "zip/unzip.h"

//��ȡ�����½���ϸ��Ϣ����¼�
void BIlibiliComic::requestDetailFinished(QNetworkReply* reply)
{

	connect(this, SIGNAL(onDetailFinished()),this, SLOT(parsePerEP()));

	// ��ȡhttp״̬��
	QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (statusCode.isValid())
		qDebug() << "status code=" << statusCode.toInt();

	QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
	if (reason.isValid())
		qDebug() << "reason=" << reason.toString();

	QNetworkReply::NetworkError err = reply->error();
	if (err != QNetworkReply::NoError) 
	{
		qDebug() << "Failed: " << reply->errorString();
	}
	else 
	{
		// ��ȡ��������
		QByteArray array = reply->readAll();

		QJsonParseError json_error;
		QJsonDocument jsonDoc(QJsonDocument::fromJson(array, &json_error));

		if (json_error.error != QJsonParseError::NoError)
		{
			qDebug() << "json error!";
			return;
		}

		m_detailJson = jsonDoc.object();
		QJsonObject data = m_detailJson.find("data")->toObject();
		
		if (data.contains("ep_list"))
		{
			m_comicName = data.value("title").toString();

			QJsonArray subArray = data.value("ep_list").toArray();
			for (int i = 0; i < subArray.size(); i++)
			{
				QJsonObject epJson = subArray.at(i).toObject();

				if (epJson.contains("short_title"))
				{
					QString strTitle = epJson.value("short_title").toString();
					int strID = epJson.value("id").toInt();

					m_epMap[strID] = strTitle;
				}
			}
		}

		emit onDetailFinished();
	}
}

//�������������½�
void BIlibiliComic::parsePerEP()
{
	QMap<int, QString>::iterator it = m_epMap.begin();

	for (it ; it != m_epMap.end(); ++it)
	{
		int nComicEpId = it.key();
		m_currentEP = m_epMap[nComicEpId];
		getIndexDataToken(QString::number(nComicEpId));
	}
}

//�ҵ���׿�����еĶ�Ӧindex.dat�ļ�
QByteArray BIlibiliComic::findIndexDataFromAndroid(QString qstrPath)
{
	QByteArray data;

	QDir dir(qstrPath);

	if (!dir.exists())
		return data;

	dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

	QFileInfoList fileList = dir.entryInfoList();

	int fileCount = fileList.count();
	for (int i = 0; i < fileCount; i++)
	{
		QFileInfo fileInfo = fileList[i];
		if (fileInfo.isFile())
		{
			QString suffix = fileInfo.suffix();
			if (QString::compare(suffix, QString(tr("dat")), Qt::CaseInsensitive) == 0)
			{
				/*��ȡ�ļ�����·����ȫ·��*/
				QString filePath = fileInfo.absoluteFilePath();

				QFile file(filePath);
				file.open(QIODevice::ReadOnly);
				data = file.readAll();
				file.close();
			}
		}
	}

	return data;
}

//�Ӱ�׿���صĻ�����ֱ�Ӷ�ȡ
QByteArray BIlibiliComic::getIndexDataFromAndroid(QString qstrEpID)
{
	QByteArray arrayIndexData;

	QDir dir(m_strIndexDataPath);

	if (!dir.exists())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����·��Ϊ��Ϊ�գ�"), QString::fromLocal8Bit("ȷ��"));
		return arrayIndexData;
	}

	dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

	QFileInfoList fileList = dir.entryInfoList();

	int fileCount = fileList.count();
	for (int i = 0; i < fileCount; i++)
	{
		QFileInfo fileInfo = fileList[i];

		if (fileInfo.isDir())
		{
			QString strAbsolutePath = fileInfo.filePath();

			if (strAbsolutePath.contains(qstrEpID))
			{
				arrayIndexData = findIndexDataFromAndroid(strAbsolutePath);
			}
		}
	}

	return arrayIndexData;
}

//�ӷ������ϻ�ȡindex.dat
QByteArray BIlibiliComic::getIndexDataFromWeb(QString qstrEpID)
{
	QByteArray array;

	QString qstrRequset = "{\"ep_id\":" + qstrEpID + "}";

	QByteArray arrayPara(qstrRequset.toUtf8());
	QUrl url("https://manga.bilibili.com/twirp/comic.v1.Comic/GetImageIndex?device=pc&platform=web");
	QNetworkRequest request(url);
	//request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

	QNetworkAccessManager* naManager = new QNetworkAccessManager(this);

	//ͬ��post���indexdata��token��Ϣ
	QNetworkReply* reply = naManager->post(request, arrayPara);
	QEventLoop eventLoop;
	connect(naManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	eventLoop.exec();       //block until finish

	QByteArray toKenArray = reply->readAll();

	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(toKenArray, &json_error));

	if (json_error.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!";
		return array;
	}

	QJsonObject json = jsonDoc.object();
	QJsonObject data = json.find("data")->toObject();

	if (data.contains("path"))
	{
		QString qstrDataIndexToken = data.value("path").toString();
		QString qstrHost = data.value("host").toString();

		QString qstrRequest = qstrHost + qstrDataIndexToken;
		QUrl url(qstrRequest);
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
		//QNetworkAccessManager* naManager = new QNetworkAccessManager(this);

		QNetworkReply* indexReply = naManager->get(request);

		//QEventLoop eventLoop;
		connect(naManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
		eventLoop.exec();       //block until finish

		array = indexReply->readAll();
	}
	
	return array;
}

//���ڻ��index.dat,���������ȡ�����Ǵӻ��ڰ�׿���صĵĻ����ж�ȡ��
void BIlibiliComic::getIndexDataToken(QString qstrEpID)
{
	QByteArray array;

	if (m_fromCache)
	{
		array = getIndexDataFromAndroid(qstrEpID);
	}
	else
	{
		array = getIndexDataFromWeb(qstrEpID);
	}

	int nTotal = array.size();

	//��9���ֽ�
	unsigned char* indexData = (uchar*)array.data();
	indexData += 9;
	int nBufferSize = nTotal - 9;

	int nComicID = m_comicID.toInt();
	int nEpID = qstrEpID.toInt();

	int* hashKey = generateHashKey(nComicID, nEpID);

	unhashContent(hashKey, indexData, nBufferSize);

	QByteArray indexDataJson = QByteArray((char*)indexData, nTotal - 9);

	QFile writeFile("./index.temp");

	if (writeFile.exists())
		writeFile.remove();

	writeFile.open(QIODevice::WriteOnly);
	writeFile.write(indexDataJson);
	writeFile.close();

	//��ѹ
	unZip();

	QFile readFile("./index.dat");

	readFile.open(QIODevice::ReadOnly);
	QByteArray realData = readFile.readAll();
	readFile.close();
	parseAllImage(realData);

}

//������������ͼƬ
void BIlibiliComic::parseAllImage(QByteArray& realData)
{
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(realData, &json_error));

	if (json_error.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!";
		return;
	}

	QJsonObject imageJson = jsonDoc.object();

	QStringList list;

	if (imageJson.contains("pics"))
	{
		QJsonArray jsonArray = imageJson.value("pics").toArray();

		for (int i = 0; i < jsonArray.size(); i++)
		{
			QString image = jsonArray.at(i).toString();
			list.push_back(image);
		}
	}

	for (int i = 0;i < list.size();++i)
	{
		//����Token
		QByteArray imageToken = getImageToken(list[i]);

		//��Token����ͼƬ
		QByteArray realImageData = getImageData(imageToken);

		saveTo(realImageData,i);
	}
}

//�����༶Ŀ¼
QString mkMutiDir(const QString path) 
{
	QDir dir(path);
	if (dir.exists(path))
	{
		return path;
	}
	QString parentDir = mkMutiDir(path.mid(0, path.lastIndexOf('/')));
	QString dirname = path.mid(path.lastIndexOf('/') + 1);
	QDir parentPath(parentDir);
	if (!dirname.isEmpty())
		parentPath.mkpath(dirname);
	return parentDir + "/" + dirname;
}

//���浽�ļ�
void BIlibiliComic::saveTo(QByteArray imageData,int name)
{
	QString strPath = m_saveRoot+ m_comicName + "/" + m_currentEP;
	QDir dir(strPath);
	if (!dir.exists())
		mkMutiDir(strPath);

	QString imageName = QString::number(name);
	QString imagePath = strPath + "/" + imageName + ".jpg";
	QFile writeFile(imagePath);

	if (writeFile.exists())
		return;

	std::cout << "���棺" << imagePath.toLocal8Bit().data() << std::endl;

	writeFile.open(QIODevice::WriteOnly);
	writeFile.write(imageData);
	writeFile.close();
}

//����ͼƬ����
QByteArray BIlibiliComic::getImageData(QByteArray& imageToken)
{
	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(imageToken, &json_error));

	if (json_error.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!";
		return QByteArray();
	}

	QJsonObject imageJson = jsonDoc.object();

	QJsonObject imageTokenJson;
	if (imageJson.contains("data"))
	{
		QJsonArray subArray = imageJson.value("data").toArray();
		for (int i = 0; i < subArray.size(); i++)
		{
			imageTokenJson = subArray.at(i).toObject();
		}
	}

	if (imageTokenJson.contains("url"))
	{
		QString strUrl = imageTokenJson.value("url").toString();
		QString strToken = imageTokenJson.value("token").toString();


		QString qstrRequest = strUrl + "?token=" + strToken;
		QUrl url(qstrRequest);
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

		QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
		QNetworkReply* indexReply = naManager->get(request);

		QEventLoop eventLoop;
		connect(naManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
		eventLoop.exec();       //block until finish

		QByteArray array = indexReply->readAll();

		return array;
	}

	return QByteArray();
}

//pos����ͼƬToken
QByteArray BIlibiliComic::getImageToken(QString imageinfo)
{
	QString qstrRequset = "{\"urls\":\"[\\\"" + imageinfo + "\\\"]\"}";

	QByteArray array(qstrRequset.toUtf8());
	QUrl url("https://manga.bilibili.com/twirp/comic.v1.Comic/ImageToken?device=pc&platform=web");
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

	QNetworkAccessManager* naManager = new QNetworkAccessManager(this);

	QNetworkReply* indexReply = naManager->post(request, array);

	QEventLoop eventLoop;
	connect(naManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	eventLoop.exec();       //block until finish

	QByteArray imageToken = indexReply->readAll();

	return imageToken;
}

//��ѹ
void BIlibiliComic::unZip()
{
	unz_file_info64 FileInfo;
	unzFile zFile = unzOpen64("./index.temp");
	if (NULL == zFile)
		qDebug() << "zero!";
	else
		qDebug() << "haha";

	unz_global_info64 gi;

	if (unzGetGlobalInfo64(zFile, &gi) != UNZ_OK)
	{
		qDebug() << "ho no";
	}

	int result;
	for (int i = 0; i < gi.number_entry; ++i)
	{
		char file[256] = { 0 };
		char ext[256] = { 0 };

		char com[1024] = { 0 };
		if (unzGetCurrentFileInfo64(zFile, &FileInfo, file, sizeof(file), ext, 256, com, 1024) != UNZ_OK)
			qDebug() << "error";
		qDebug() << file << ":" << ext << ":" << com;

		if (!(FileInfo.external_fa & FILE_ATTRIBUTE_DIRECTORY)) //�ļ�������ΪĿ¼

		//���ļ�
		result = unzOpenCurrentFile(zFile);/* ������ */
		//result = unzOpenCurrentFilePassword(zFile, "szPassword"); /* ������ */

		char data[1024] = { 0 };
		int size;
		//��ȡ����

		QString path = QString("./") + file;
		QFile f(path);

		if (f.exists())
			f.remove();

		f.open(QFile::WriteOnly);
		while (true) 
		{
			size = unzReadCurrentFile(zFile, data, sizeof(data));

			if (size <= 0)
				break;

			//QString str;
			//str = QString::fromLocal8Bit(data, size);
			f.write(data, size);
		}

		f.close();

		//�رյ�ǰ�ļ�
		unzCloseCurrentFile(zFile);

		//����
		if (i < gi.number_entry - 1 && unzGoToNextFile(zFile) != UNZ_OK)
			qDebug() << "error2";
	}
	unzClose(zFile);

}

//��hash
void BIlibiliComic::unhashContent(int* hashKey, unsigned char* indexData,int nDataSize)
{
	for (int i = 0; i < nDataSize; ++i)
	{
		indexData[i] ^= hashKey[i % 8];
	}
}

//����hashkey
int* BIlibiliComic::generateHashKey(int nComicID, int nEpID)
{
	int* n = new int[8];
	int e = nComicID;
	int	t = nEpID;
	n[0] = t;
	n[1] = t >> 8;
	n[2] = t >> 16;
	n[3] = t >> 24;
	n[4] = e;
	n[5] = e >> 8;
	n[6] = e >> 16;
	n[7] = e >> 24;

	for (int i = 0;i < 8;i++)
	{
		n[i] = n[i] % 256;
	}

	return n;
}

//pos������������ϸ��Ϣ
void BIlibiliComic::getComicDetail(QUrl url)
{
	QString qtrRequest = "{\"comic_id\":" + m_comicID + "}";
	QByteArray array(qtrRequest.toUtf8());
	QNetworkRequest request(url);
	//request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

	QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
	QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestDetailFinished(QNetworkReply*)));

	naManager->post(request, array);
}

BIlibiliComic::BIlibiliComic(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QUrl url("https://manga.bilibili.com/twirp/comic.v2.Comic/ComicDetail?device=pc&platform=web");

	//����Ŀ¼
	m_saveRoot = "G:/";

	//index.dat�ļ�Ŀ¼���Ӱ�׿�����������Ļ���
	m_strIndexDataPath = "G:/25971";

	//����ID
	m_comicID = "25523";

	//�Ӱ�׿��������ȡ���Ǵ�web����index.dat
	m_fromCache = false;

	//��ȡ����������½���Ϣ
	getComicDetail(url);
}
