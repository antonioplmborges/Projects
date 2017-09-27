#include "ProducerConsumer.h"

//TODO: add BoundedBuffer, locks and any global variables here
pthread_mutex_t locker;
BoundedBuffer *buff;
pthread_t *pThreads;
pthread_t *cThreads;
int produced,consumed,pSleep,cSleep,item;
time_t t;
FILE *f;

void InitProducerConsumer(int p, int c, int psleep, int csleep, int items){
	//TODO: constructor to initialize variables declared
	//also see instruction for implementation

  if(p < 1 || c < 1){
		printf("producer and consumer have to at least 1\n");
		return;
	}
  else{


  	pthread_mutex_init(&locker, NULL);
  	//pthread_mutex_init(&lock2, NULL);
  	produced= 0;
  	consumed = 0;
  	item = items;
  	pSleep = psleep;
  	cSleep = csleep;
  	pThreads = new pthread_t[p];
  	cThreads =  new pthread_t[c];
  	buff = new BoundedBuffer(items);

    f = fopen("output.txt", "w+");


    for(int i=0; i < p; i++){
      pthread_create(&pThreads[i], NULL, producer, NULL);
    }

    for(int i=0; i < c; i++){
      pthread_create(&cThreads[i], NULL, consumer, NULL);
    }

    for(int i=0; i < c; i++){
      pthread_join(cThreads[i], NULL);
    }

    for(int i=0; i < p; i++){
      pthread_join(pThreads[i], NULL);
    }

    fclose(f);

  }


  }

void* producer(void* threadID){
	//TODO: producer thread, see instruction for implementation
	while(1){
		if(produced >= item){ break; }
		else{
			usleep(pSleep*1000);
      produced++;
			int data = rand();
      pthread_mutex_unlock(&locker);
			buff->append(data);
      pthread_mutex_lock(&locker);
      t = time(0);
			fprintf(f, "Producer #%d, time = %ld, producing data item #%d, item value = %d\n", pthread_self(), (long)t, produced, data);
		}
	}
  pthread_mutex_unlock(&locker);
	pthread_exit(NULL);
}

void* consumer(void* threadID){
	//TODO: consumer thread, see instruction for implementation
  while(1){
		if(consumed>= item){break;}
		else{
			usleep(pSleep*1000);
			consumed++;
			pthread_mutex_unlock(&locker);
			int data = buff->remove();
			pthread_mutex_lock(&locker);
			t = time(0);
			fprintf(f, "Consumer #%ld, time = %ld, producing data item with value= %ld\n", pthread_self(), (long)t, data);
		}
	}
	pthread_mutex_unlock(&locker);
	pthread_exit(0);


}
