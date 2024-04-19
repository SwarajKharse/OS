#include <bits/stdc++.h>

#define NUM_READERS 2
#define NUM_WRITERS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_reader = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;

int readers_count = 0;
int writers_count = 0;
int resource = 0;
bool synchronized = true;

void *reader(void *arg) {

  int reader_id = *((int *)arg);

  if (synchronized) {
    pthread_mutex_lock(&mutex);
    while (writers_count > 0) {
      printf("Reader %d is waiting because a writer is writing\n", reader_id);
      pthread_cond_wait(&cond_reader, &mutex);
    }
    readers_count++;
    pthread_mutex_unlock(&mutex);

    printf("Reader %d reading shared resource\n", reader_id);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readers_count--;
    if (readers_count == 0) {
      pthread_cond_signal(&cond_writer);
    }
    pthread_mutex_unlock(&mutex);

  } else {
    printf("Reader %d reads resource: %d\n", reader_id, resource);
    sleep(1);
  }

  printf("Reader %d completed with reading, CS is free\n", reader_id);
  return NULL;
}

void *writer(void *arg) {
  int writer_id = *((int *)arg);

  if (synchronized) {
    pthread_mutex_lock(&mutex);
    writers_count++;
    while (readers_count > 0 || writers_count > 1) {
      printf("Writer %d wants to write but not allowed\n", writer_id);
      pthread_cond_wait(&cond_writer, &mutex);
    }

    pthread_mutex_unlock(&mutex);
    resource = writer_id;

    printf("Writer %d writing shared resource\n", writer_id);
    sleep(1);

    pthread_mutex_lock(&mutex);
    writers_count--;

    pthread_cond_signal(&cond_writer);
    pthread_cond_broadcast(&cond_reader);
    pthread_mutex_unlock(&mutex);
  } else {
    resource = writer_id;
    printf("Writer %d writes resource: %d\n", writer_id, resource);
    sleep(1);
  }

  printf("Writer %d completed with writing, CS is free\n", writer_id);
  return NULL;
}

int main() {

  pthread_t readers[NUM_READERS];
  pthread_t writers[NUM_WRITERS];

  int i, reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

  for (i = 0; i < NUM_READERS; i++) {
    reader_ids[i] = i + 1;
    writer_ids[i] = i + 1;
  }

  synchronized = true;
  printf("Reader-Reader (RR) case:\n");
  for (i = 0; i < NUM_READERS; i++) {
    pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
  }
  for (i = 0; i < NUM_READERS; i++) {
    pthread_join(readers[i], NULL);
  }

  synchronized = true;
  printf("\nReader-Writer (RW) case:\n");
  pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
  pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
  pthread_join(readers[0], NULL);
  pthread_join(writers[0], NULL);

  synchronized = true;
  printf("\nWriter-Writer (WW) case:\n");
  for (i = 0; i < NUM_WRITERS; i++) {
    pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
  }
  for (i = 0; i < NUM_WRITERS; i++) {
    pthread_join(writers[i], NULL);
  }

  synchronized = true;
  printf("\nWriter-Reader (WR) case:\n");
  pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
  pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
  pthread_join(readers[0], NULL);
  pthread_join(writers[0], NULL);

  synchronized = false;
  printf("\nReader-Reader (RR) case without synchronization:\n");
  for (i = 0; i < NUM_READERS; i++) {
    pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
  }
  for (i = 0; i < NUM_READERS; i++) {
    pthread_join(readers[i], NULL);
  }

  synchronized = false;
  printf("\nReader-Writer (RW) case without synchronization:\n");
  pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
  pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
  pthread_join(readers[0], NULL);
  pthread_join(writers[0], NULL);

  synchronized = false;
  printf("\nWriter-Writer (WW) case without synchronization:\n");
  for (i = 0; i < NUM_WRITERS; i++) {
    pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
  }
  for (i = 0; i < NUM_WRITERS; i++) {
    pthread_join(writers[i], NULL);
  }

  synchronized = false;
  printf("\nWriter-Reader (WR) case without synchronization:\n");
  pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
  pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
  pthread_join(readers[0], NULL);
  pthread_join(writers[0], NULL);
  return 0;
}
