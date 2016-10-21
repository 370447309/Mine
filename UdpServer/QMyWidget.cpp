#include "QMyWidget.h"
#include <QHBoxLayout>  
#include <QMessageBox>  
#include <QList>  

QMyWidget::QMyWidget( QWidget *parent )
: QWidget( parent )
{
	udpsocket = new QUdpSocket( this );
	setWindowTitle( tr( "udp聊天" ) );
	label1 = new QLabel;
	label1->setText( "请输入bind端口号" );
	label2 = new QLabel;
	label2->setText( "请输入目的IP地址" );
	label3 = new QLabel;
	label3->setText( "请输入目的端口号" );
	label4 = new QLabel;
	label4->setText( "请输入发送的消息" );

	edit1 = new QLineEdit;
	edit2 = new QLineEdit;
	edit3 = new QLineEdit;
	edit4 = new QLineEdit;

	btn1 = new QPushButton;
	btn1->setText( tr( "bind" ) );
	btn2 = new QPushButton;
	btn2->setText( tr( "发送" ) );

	QGridLayout *layout1 = new QGridLayout( this );
	layout1->addWidget( label1, 0, 0 );
	layout1->addWidget( edit1, 0, 1 );
	layout1->addWidget( btn1, 1, 0 );
	layout1->addWidget( label2, 2, 0 );
	layout1->addWidget( edit2, 2, 1 );
	layout1->addWidget( label3, 3, 0 );
	layout1->addWidget( edit3, 3, 1 );
	layout1->addWidget( label4, 4, 0 );
	layout1->addWidget( edit4, 4, 1 );
	layout1->addWidget( btn2, 5, 0 );

	connect( btn1, SIGNAL( clicked() ), this, SLOT( on_clicked1() ) );
	connect( btn2, SIGNAL( clicked() ), this, SLOT( on_clicked2() ) );
	connect( udpsocket, SIGNAL( readyRead() ), this, SLOT( dataReceived() ) );
}

QMyWidget::~QMyWidget()
{

}


void QMyWidget::on_clicked1()
{
	udpsocket->close();
	udpsocket->bind( edit1->text().toInt() );
}

void QMyWidget::on_clicked2()
{
	QHostAddress addr;
	addr.setAddress( edit2->text() );
	int port = edit3->text().toInt();
	udpsocket->writeDatagram( edit4->text().toUtf8(), addr, port );
}

void QMyWidget::dataReceived()
{
	QHostAddress addr;
	char buf[1024];
	while( udpsocket->hasPendingDatagrams() )
	{
		memset( buf, 0, sizeof( buf ) );
		udpsocket->readDatagram( buf, sizeof( buf ), &addr );
		QMessageBox::information( this, tr( "消息" ), tr( "来自" ) + addr.toString() + tr( "的消息：\n" ) + buf );
	}
}