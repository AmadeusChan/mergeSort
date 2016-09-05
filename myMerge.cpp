#include "myMerge.h"

void myMerge::merge(const QVector<int> &left_, const QVector<int> &right_, QVector<int> &output_){
	output_.clear();
	int left_index_=0;
	int right_index_=0;
	while (left_index_<left_.size() && right_index_<right_.size()){
		if (left_.at(left_index_) < right_.at(right_index_)){
			output_.append(left_.at(left_index_++));
		} else {
			output_.append(right_.at(right_index_++));
		}
	}
	while (left_index_ < left_.size()){
		output_.append(left_.at(left_index_++));
	}
	while (right_index_ < right_.size()){
		output_.append(right_.at(right_index_++));
	}
}
