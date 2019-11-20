#include <pthread.h> 
#include <stdlib.h>
#include <stdio.h>

typedef struct c conta;
conta from, to;
int valor;

struct c {
 int saldo;
};

void transfer( void *arg)
{
    if (from.saldo >= valor){ 
            printf( "Transferindo para a conta c2\n" );
            from.saldo -= valor;
            to.saldo += valor;
            printf("Transferência concluída com sucesso!\n");
            printf("Saldo de c1: %d\n", from.saldo);
            printf("Saldo de c2: %d\n", to.saldo);
    }
    else
    {
        printf("Saldo insuficiente da conta origem");
    }
    return;
}

int main()
{
    pthread_t tid[100];
    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
    valor = 1;
    for(int i = 0; i < 100; i++)
    {
        pthread_create(&tid[i], NULL, (void *)transfer, NULL);
    }
    for(int i = 0; i < 100; i++)
    {
    pthread_join(tid[i], NULL);
    return 0;
    }
        
}
