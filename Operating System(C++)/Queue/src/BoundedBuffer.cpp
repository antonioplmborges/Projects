#include "BoundedBuffer.h"

BoundedBuffer::BoundedBuffer(int N){
	//TODO: constructor to initiliaze all the varibales declared in BoundedBuffer.h
	buffer_size = N;
	buffer_cnt = 0;
	buffer_last = 0;
	buffer = new int[buffer_size];
	pthread_mutex_init(&buffer_lock, NULL);
	pthread_cond_init(&buffer_full, NULL);
	pthread_cond_init(&buffer_empty, NULL);
}


void BoundedBuffer::append(int data){
	//TODO: append a data item to the circular buffer
	pthread_mutex_lock(&buffer_lock);
	while (buffer_cnt == buffer_size)
		pthread_cond_wait(&buffer_empty, &buffer_lock);
	buffer[buffer_last] = data;
	buffer_last = (buffer_last + 1) % buffer_size;
	buffer_cnt += 1;
	pthread_cond_signal(&buffer_full);
	pthread_mutex_unlock(&buffer_lock);
}

int BoundedBuffer::remove(){
	//TODO: remove and return a data item from the circular buffer
	pthread_mutex_lock(&buffer_lock);
while(buffer_cnt == 0){
	pthread_cond_wait(&buffer_empty, &buffer_lock);
}
int output;
if((buffer_last - buffer_cnt)%buffer_size < 0){
	output = buffer[(buffer_last - buffer_cnt)%buffer_size + buffer_size];
}
else{
	output = buffer[(buffer_last - buffer_cnt)%buffer_size];
}
buffer_cnt--;
pthread_cond_signal(&buffer_empty);
pthread_mutex_unlock(&buffer_lock);
return output;


}

bool BoundedBuffer::isEmpty(){
	//TODO: check is the buffer is empty
	if (buffer_cnt == 0){ return true; }
	else { return false; }
}
