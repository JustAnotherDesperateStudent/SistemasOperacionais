#define _GNU_SOURCE
#include <ucontext.h>
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
void threadFunction( void *arg)
{
    int i;
    for (i = 0; i < 10; i++) {
        if (from.saldo >= valor){ // 2
            from.saldo -= valor;
            to.saldo += valor;
        }
    }
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
    printf( "Child fiber yielding to parent\n" );
    swapcontext( &child, &parent );
    printf( "Child thread exiting\n" );
    swapcontext( &child, &parent );
    return 0;
}

int main()
{
    // Get the current execution context
    getcontext( &child );
    
    // Modify the context to a new stack
    child.uc_link = 0;
    child.uc_stack.ss_sp = malloc( FIBER_STACK );
    child.uc_stack.ss_size = FIBER_STACK;
    child.uc_stack.ss_flags = 0;        
    if ( child.uc_stack.ss_sp == 0 )
    {
         perror( "malloc: Could not allocate stack" );
         exit( 1 );
    }
    
    // Create the new context
    printf( "Creating child fiber\n" );
    makecontext( &child, &threadFunction, 0 );
    
    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
    printf( "Transferindo 10 para a conta c2\n" );
    valor = 10;
    // Execute the child context
    printf( "Switching to child fiber\n" );
    swapcontext( &parent, &child );
    printf( "Switching to child fiber again\n" );
    swapcontext( &parent, &child );
    
    // Free the stack
    free( child.uc_stack.ss_sp );
    
    printf( "Child fiber returned and stack freed\n" );
    
    return 0;
}
