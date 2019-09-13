#include "BIlibiliComic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BIlibiliComic w;
	w.show();
	return a.exec();
}
