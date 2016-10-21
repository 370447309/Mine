#include "udpserver.h"
#include <QString>
#include <QFile>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>

#define UDP_PORT 45454
UdpServer::UdpServer(QWidget *parent)
	: QWidget( parent )
{
	m_nIndex = 0;
	m_pUdpSocket = new QUdpSocket();
	QHostAddress addr;
	addr.setAddress( "192.168.1.95" );//ip改成你的ip
	m_pUdpSocket->bind( addr, UDP_PORT, QAbstractSocket::ShareAddress );

	QLabel* pLabel = new QLabel( QString( "port:%1" ).arg( UDP_PORT ) );
	QLabel* pLabel2 = new QLabel( tr( "Info:" ) );
	m_pBtnSend = new QPushButton( tr( "send" ) );
	m_pTextEdit = new QTextEdit();

	QGridLayout* playout = new QGridLayout;
	playout->addWidget( m_pBtnSend, 0, 0 );
	playout->addWidget( pLabel, 0, 1 );
	playout->addWidget( pLabel2, 1, 0, Qt::AlignTop | Qt::AlignRight );
	playout->addWidget( m_pTextEdit, 1, 1 );

	resize( 500, 200 );
	setLayout( playout );
	connect( m_pUdpSocket, SIGNAL( readyRead() ), this, SLOT( readPendingDatagrams() ) );
	connect( m_pBtnSend, SIGNAL( clicked() ), this, SLOT( slotSendMsg() ) );

	QString strFilePath = "D:\\svn\\test_B3.DEB";
	GetDataFromFile( strFilePath );
}

UdpServer::~UdpServer()
{

}

void UdpServer::slotSendMsg()
{
	m_nIndex = 0;
	QByteArray dataTemp( "readySend" );
	QHostAddress addr;
	addr.setAddress( "192.168.1.254" );
	int size = m_pUdpSocket->writeDatagram( dataTemp.data(), dataTemp.size(), addr, UDP_PORT );//给服务器发送命令
	m_pBtnSend->setDisabled( true );
}

void UdpServer::readPendingDatagrams()
{
	while( m_pUdpSocket->hasPendingDatagrams() )
	{
		QByteArray datagram;
		datagram.resize( m_pUdpSocket->pendingDatagramSize() );
		m_pSenderIP = new QHostAddress;
		m_pSendPort = new quint16;

		m_pUdpSocket->readDatagram( datagram.data(), datagram.size(), m_pSenderIP, m_pSendPort );

		processTheDatagram( datagram );
	}
}

void UdpServer::processTheDatagram( QByteArray& datagram )
{
	////判断是否可以发送,测试
	if( datagram == "readySend" )
	{
		QTimer *timer = new QTimer( this );
		connect( timer, SIGNAL( timeout() ), this, SLOT( sendData() ) ); //定时发送
		timer->start( 1000 );
	}
	else if( datagram == "Send complete" )
	{
		m_pBtnSend->setDisabled( false );
	}
	else
	{
		//处理得到的数据包
		m_pTextEdit->setText( static_cast< char* >( datagram.data() ) );//test
	}
}

//test
void UdpServer::GetDataFromFile( QString& strFilePath )
{
	//从文件中读取8k字节数据
	if( !QFile::exists( strFilePath ) )
	{
		return;
	}

	QFile file( strFilePath );
	file.open( QIODevice::ReadOnly );
	quint16 senderPort = UDP_PORT;
	int nSize = 0;

	//while( !file.atEnd() )
	for( int i = 0; i < 10; i++ )
	{
		QByteArray dataTemp;
		dataTemp.resize( 8000 );
		nSize = file.read( dataTemp.data(), 8000 );
		if( nSize == 8000 )
		{
			QByteArray head;
			head.resize( 8 );
			head[0] = 0xFE;
			head[1] = 0xED;
			head[2] = 0xBE;
			head[3] = 0xEF;
			head[4] = ( 0x3E8 & 0xFF00 ) >> 8;
			head[5] = 0x3E8 & 0xFF;
			head[6] = 0xD0;
			head[7] = 0xD0;
			dataTemp.insert( 0, head );
			m_vecData.push_back( dataTemp );
		}
	}
	file.close();
}

void UdpServer::sendData()
{
	if( m_nIndex < m_vecData.size() )
	{
		int size = m_pUdpSocket->writeDatagram( ( m_vecData[m_nIndex] ).data(), ( m_vecData[m_nIndex] ).size(), *m_pSenderIP, *m_pSendPort );//给客户端发送数据
 		if( size == 8008 )
 		{
 			m_nIndex++;
 			return;
 		}
	}
	else
	{
		QByteArray dataTemp("Send complete");
		m_pUdpSocket->writeDatagram( dataTemp.data(), dataTemp.size(), *m_pSenderIP, *m_pSendPort );//给客户端发送数据
	}
}
