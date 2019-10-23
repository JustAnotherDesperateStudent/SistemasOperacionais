#define _GNU_SOURCE
#include <pthread.h> 
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
// 64kB stack
#define FIBER_STACK 1024*64

ucontext_t child, parent;
typedef struct c conta;
conta from, to;
int valor;

struct c {
 int saldo;
};

// The child thread will execute this function
void transfer( void *arg)
{
    int i;
    for (i = 0; i < 10; i++) {
        if (from.saldo >= valor){ // 2
            from.saldo -= valor;
            to.saldo += valor;
            printf("Transferência concluída com sucesso!\n");
            printf("Saldo de c1: %d\n", from.saldo);
            printf("Saldo de c2: %d\n", to.saldo);
        }
    }
    return;
}

int main()
{
    pthread_t tid;
    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
    printf( "Transferindo 10 para a conta c2\n" );
    valor = 10;
    pthread_create(&tid, NULL, transfer, NULL); 
    pthread_join(tid, NULL); 
    return 0;
}
