#include "myController.h"
#include "dataNote.h"
#include "myMerge.h"
#include "globalVariable.h"
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <cstdio>
#include <QApplication>
#include <QDebug>

myController::myController(QObject *parent):QObject(parent){
	for (int i=0;i<4;++i){
		globalVariable::first[i]=NULL;
		threads[i]=new QThread(this);
		sorts[i]=new myMergeSort(i);
		sorts[i]->moveToThread(threads[i]);
		threads[i]->start();
		connect(this,SIGNAL(toStart()),
            sorts[i],SLOT(init()));
        connect(sorts[i],SIGNAL(workFinished(QVector<int>*)),
                this,SLOT(finishedAction(QVector<int>*)));
	}
	cnt=0;
	vectors=new QVector<QVector<int>>;
}

myController::~myController(){
	for (int i=0;i<4;++i){
		delete threads[i];
		delete sorts[i];
	}
	delete vectors;
}

void myController::start(){
    QFile file_("input.txt");
	file_.open(QFile::ReadOnly | QFile::Text);
	QTextStream stream_(&file_);
	
	emit toStart();
	int key_,val_;
	dataNote *pt;
    int cnt_=0;
    while (!stream_.atEnd()){
        ++cnt_;
		stream_>>key_>>val_;
		key_%=4;
		globalVariable::mutex[key_].lock();
		pt=new dataNote;
		pt->key=key_,pt->val=val_,pt->next=globalVariable::first[key_];
		globalVariable::first[key_]=pt;
		globalVariable::mutex[key_].unlock();
    }
    qDebug()<<"Total:"<<cnt_;
    cnt_=0;
    while (1){
        for (int i=0;i<4;++i){
            globalVariable::mutex[i].lock();
            if (globalVariable::first[i]==NULL){
                pt=new dataNote;
                pt->key=-1;
                globalVariable::first[i]=pt;
                globalVariable::mutex[i].unlock();
                ++cnt_;
            } else {
                globalVariable::mutex[i].unlock();
                QThread::sleep(1);
            }
        }
        if (cnt_==4) break;
    }

	file_.close();
}

void myController::finishedAction(QVector<int> *vector_){
	++cnt;
    vectors->append(*vector_);
	if (cnt<4) return ;
	QVector<int> *left_,*right_,*final_;
	left_=new QVector<int>;
	right_=new QVector<int>;
	final_=new QVector<int>;
	myMerge *merge_=new myMerge;
	merge_->merge((*vectors)[0],(*vectors)[1],*left_);
	merge_->merge((*vectors)[2],(*vectors)[3],*right_);
	merge_->merge(*left_,*right_,*final_);

    QFile file("output.txt");
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream stream(&file);
    bool flag=true;
    for (int i=0;i<final_->size();++i){
        if (i) if (final_->at(i)<final_->at(i-1)) flag=false;
        stream<<final_->at(i)<<"\n";
    }
    file.close();
    qDebug()<<"result:"<<flag;
	/*freopen("output.txt","w",stdout);
	for (int i=0;i<final_->size();++i){
		printf("%d\n",final_->at(i));
	}
	fclose(stdout);*/
	delete left_;
	delete right_;
	delete final_;
	delete merge_;
	qApp->quit();
}



