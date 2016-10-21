#include "QMyWidget.h"
#include <QHBoxLayout>  
#include <QMessageBox>  
#include <QList>  

QMyWidget::QMyWidget( QWidget *parent )
: QWidget( parent )
{
	udpsocket = new QUdpSocket( this );
	setWindowTitle( tr( "udp����" ) );
	label1 = new QLabel;
	label1->setText( "������bind�˿ں�" );
	label2 = new QLabel;
	label2->setText( "������Ŀ��IP��ַ" );
	label3 = new QLabel;
	label3->setText( "������Ŀ�Ķ˿ں�" );
	label4 = new QLabel;
	label4->setText( "�����뷢�͵���Ϣ" );

	edit1 = new QLineEdit;
	edit2 = new QLineEdit;
	edit3 = new QLineEdit;
	edit4 = new QLineEdit;

	btn1 = new QPushButton;
	btn1->setText( tr( "bind" ) );
	btn2 = new QPushButton;
	btn2->setText( tr( "����" ) );

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
		QMessageBox::information( this, tr( "��Ϣ" ), tr( "����" ) + addr.toString() + tr( "����Ϣ��\n" ) + buf );
	}
}