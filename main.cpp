#include <QFile>
#include <QApplication>
#include <QThread>
#include "myController.h"

int main(int argc, char *argv[]){
	QApplication *app=new QApplication(argc,argv);

	myController *controller=new myController;
	controller->start();

	return app->exec();
}
