//
//  callSwiftCallBacks.c
//  CallingSwiftFromC
//
//  Created by ing.conti on 19/01/2020.
//  Copyright © 2020 ing.conti. All rights reserved.
//

#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


#include "callSwiftCallBacks.h"


// thread ideas from:
// https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/


// protos for function, it may match @_cdecl("CallBackModule")
intptr_t CallBackModule(intptr_t);

intptr_t invoke_C_Callback(intptr_t x) {
    long result = CallBackModule(x);
    return result;
}



void *inc_x(void *x_void_ptr)
{
    long *x_ptr = (long *)x_void_ptr;
    while(*x_ptr < 10)
    {
        printf("x: %ld\n", *x_ptr);
        *x_ptr = invoke_C_Callback( *x_ptr);
        usleep(2000000);
    }
    
    /* the function must return something - NULL will do */
    return NULL;
    
}



int C_ThreadLoop(void)
{
    long x = 0;
    
    printf("started\n");
    
    // this variable is our reference to the thread
    pthread_t inc_x_thread;
    
    // create thread which executes inc_x(&x)
    if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
        
        fprintf(stderr, "Error creating thread\n");
        return 1;
        
    }
    
    // wait for the thread to finish:
    if(pthread_join(inc_x_thread, NULL)) {
        
        fprintf(stderr, "Error joining thread\n");
        return 2;
        
    }

    
    
    return 0;
    
}
