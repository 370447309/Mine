#ifndef QMYWIDGET_H  
#define QMYWIDGET_H  

#include <QWidget>  
#include <QLabel>  
#include <QPushButton>  
#include <QLineEdit>  
#include <QUdpSocket>  

class QMyWidget : public QWidget
{
	Q_OBJECT

public:
	QMyWidget( QWidget *parent = 0 );
	~QMyWidget();
private:
	QLabel *label1, *label2, *label3, *label4;
	QLineEdit *edit1, *edit2, *edit3, *edit4;
	QPushButton *btn1, *btn2;
	QUdpSocket *udpsocket;
	private slots:
	void on_clicked1();
	void on_clicked2();
	void dataReceived();
};

#endif // QMYWIDGET_H  