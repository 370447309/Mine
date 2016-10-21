#include "udpserver.h"
#include <QtWidgets/QApplication>
#include "QMyWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UdpServer w;
	//QMyWidget w;
	w.show();
	return a.exec();
}
