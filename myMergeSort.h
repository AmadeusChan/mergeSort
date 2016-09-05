#ifndef MY_MERGE_SORT_H
#define MY_MERGE_SORT_H

#include <QObject>
#include <QVector>
#include <QThread>
#include "dataNote.h"
#include "myMerge.h"
#include "globalVariable.h"

class myMergeSort:public QObject{

	Q_OBJECT

	public:
		myMergeSort(int num_,QObject *parent=0);
		~myMergeSort();

	private:
		QVector<int> *array;
		myMerge *merge;
		int num;

	signals:
        void workFinished(QVector<int>*);
		void initFinished();
	
	public slots:
		void init();
		void work(int begin_,int end_);

};

#endif
