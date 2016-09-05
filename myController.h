#ifndef MY_CONTROLLER_H
#define MY_CONTROLLER_H

#include <QObject>
#include <QThread>
#include "globalVariable.h"
#include "myMergeSort.h"

class myController:public QObject{

	Q_OBJECT

	public:
		myController(QObject *parent=0);
		~myController();
		void start();
	private:
		QThread *threads[4];
		myMergeSort *sorts[4];
		QVector<QVector<int>> *vectors;
		int cnt;

	private slots:
        void finishedAction(QVector<int>* vector_);

	signals:
		void toStart();

};

#endif
