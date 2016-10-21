#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_udpserver.h"
#include <QUdpSocket>
#include <QTextEdit>
#include <QPushButton>
#include <QHostAddress>


class UdpServer : public QWidget
{
	Q_OBJECT

public:
	UdpServer(QWidget *parent = 0);
	~UdpServer();

	void processTheDatagram( QByteArray& datagram );

public slots:
	void readPendingDatagrams();
	void GetDataFromFile( QString& strFilePath );
	void sendData();
	void slotSendMsg();

private:
	Ui::UdpServerClass ui;
	QUdpSocket* m_pUdpSocket;
	QVector<QByteArray> m_vecData;
	int m_nIndex;
	QTextEdit* m_pTextEdit;
	QPushButton* m_pBtnSend;
	QHostAddress* m_pSenderIP;
	quint16* m_pSendPort;
};

#endif // UDPSERVER_H
