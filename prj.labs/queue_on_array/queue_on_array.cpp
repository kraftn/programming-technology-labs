#include "queue_on_array.h"

int32_t QueueOnArray::GetSizeQueue() const {
	if (i_first > i_last) { 
		return(i_first - i_last + 1);
	}
	if (i_first == i_last) {
		return 0;
	}
	if (i_first<i_last)
	{
		return(size_ - (i_last - i_first - 1));
	}
}

QueueOnArray::QueueOnArray() {
	data_ = new int32_t[10]{ 0 };
	size_ = 10;
}

QueueOnArray::QueueOnArray(const QueueOnArray& obj) {
	if (obj.i_first>)
}

void QueueOnArray::Push(const int obj) {
	data_[i_first] = obj;
	++i_first;
}