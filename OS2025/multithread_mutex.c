#include <pthread.h> // phread.h -> pthread.h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // usleep 함수를 위한 헤더 추가

#define MAX_COUNT 100
#define MAX_THREADS 10 // MAX_THREDS -> MAX_THREADS

pthread_mutex_t mutex;
int sum = 0;

void *counter(void *arg) { // i값을 1부터 MAX_COUNT까지 증가시키면서 누적합산
    int i;

    for (int i = 1; i <= MAX_COUNT; i++) {
        pthread_mutex_lock(&mutex); // 뮤텍스 잠금 down 연산
        sum += i;
        pthread_mutex_unlock(&mutex); // 뮤텍스 잠금 해제 up 연산
        usleep(1000); // 1000마이크로초 간격으로 실행 ->초 간격을 바꿔가면서 실행해보기
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) { // argvp[] -> argv[] (일반적인 표기)
    pthread_t tids[MAX_THREADS];   // MAX_TRHEADS -> MAX_THREADS
    pthread_mutex_init(&mutex, NULL); // 뮤텍스 초기화

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&tids[i], NULL, counter, &i); // 스레드 생성 counter로 스레드
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }
    
    printf("Sum: %d\n", sum);  //스레드가 10개 이므로 5050 x 10 = 50500
    pthread_exit(0);
}

//gcc -o sum_test sum_test.c -lpthread 
