#include <pthread.h> 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


ucontext_t child, parent;
typedef struct c conta;
conta from, to;
int valor;

struct c {
 int saldo;
};

void transfer( void *arg)
{
    int i;
    for (i = 0; i < 10; i++) {
        if (from.saldo >= valor){ // 2
            printf( "Transferindo 10 para a conta c2\n" );
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
    valor = 10;
    pthread_create(&tid, NULL, transfer, NULL); 
    pthread_join(tid, NULL); 
    return 0;
}
