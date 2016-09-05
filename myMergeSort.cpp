#include "myMergeSort.h"
#include <QThread>
#include <QDebug>

myMergeSort::myMergeSort(int num_,QObject *parent):num(num_),QObject(parent){
	array=new QVector<int>;
	merge=new myMerge;
}

myMergeSort::~myMergeSort(){
	delete array;
	delete merge;
}

void myMergeSort::init(){
	while (1){
		globalVariable::mutex[num].lock();
		if (globalVariable::first[num]==NULL){
			globalVariable::mutex[num].unlock();
			QThread::sleep(1);
		} else {
			if (globalVariable::first[num]->key==-1){
				globalVariable::mutex[num].unlock();
				break;
			}
			array->append(globalVariable::first[num]->val);
			globalVariable::first[num]=globalVariable::first[num]->next;
			globalVariable::mutex[num].unlock();
		}
	}
	emit initFinished();
    qDebug()<<"Finished Init"<<num;
    qDebug()<<array->size();
    work(0,array->size()-1);
}

void myMergeSort::work(int begin_,int end_){
	if (begin_==end_) return ;
    if (begin_>end_) return ;
	int mid_=(begin_+end_)/2;
	work(begin_,mid_), work(mid_+1,end_);
	QVector<int> *left_,*right_,*output_;
	left_=new QVector<int>;
	right_=new QVector<int>;
	output_=new QVector<int>;
	left_->clear(), right_->clear(), output_->clear();
	for (int i=begin_;i<=mid_;++i) left_->append(array->at(i));
	for (int i=mid_+1;i<=end_;++i) right_->append(array->at(i));
	merge->merge(*left_,*right_,*output_);
	for (int i=0;i<output_->size();++i){
		(*array)[begin_+i]=output_->at(i);
	}
	delete left_;
	delete right_;
	delete output_;
    if (begin_==0 && end_==array->size()-1) emit workFinished(array);
}
