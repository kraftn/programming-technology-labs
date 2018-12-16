#ifndef QUEUE_ON_ARRAY
#define QUEUE_ON_ARRAY

#include <cstdint>

class QueueOnArray {
public:
	QueueOnArray();
	QueueOnArray(const QueueOnArray& obj);
	~QueueOnArray();
	QueueOnArray& operator=(const QueueOnArray&);
	void Push(const int32_t obj);
	void Pop();
	int Top()const;
	bool IsEmpty()const;
private:
	int32_t* data_{nullptr};
	int32_t size_{ 0 };
	int32_t i_first{ 0 };
	int32_t i_last{ 0 };
	int32_t GetSizeQueue()const;
};

#endif