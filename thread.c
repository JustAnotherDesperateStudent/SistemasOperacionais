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
        printf("Saldo insuficiente da conta origem\n");
        pthread_exit(0);
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
    for(int i = 0; i < 102; i++)
    {
        pthread_create(&tid[i], NULL, (void *)transfer, NULL);
        if(i != 0)
        {
          pthread_join(tid[i], NULL);
        }
    }
        
}
