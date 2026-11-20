#pragma once
#include "etl/optional.h"
#include "etl/vector.h"
#include "etl/atomic.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


template< class T >
class Mission {
private:
    friend class FREERTOSTest ;

    T taskHandle { nullptr };

    bool  taskRunning { false } ;



    void (*task)(void*) ;
    void * arg ;
    uint32_t stackSize ; 
    uint32_t priority ;



    static void _task( void * arg );

    union _event { 
        struct  {
            uint32_t : 29 ;
            uint32_t stop   : 1;
            uint32_t pause  : 1;
            uint32_t resume : 1;
        } flags ;
        uint32_t bits ;
    };

public:

    inline static _event event = {0, 0, 0 , 0 };    

    static  unsigned long MAX_DELAY ;

    ~Mission(){ 
        auto i{ 5 } ; 
        while( i--){ 
            if ( join()) break ; 
        }  
    }  
    
    Mission(  void (*p_task)(void*) , void * p_arg ,  uint32_t p_stackSize , uint32_t p_priority )
        : task( p_task ) , arg( p_arg ) , stackSize( p_stackSize ) , priority( p_priority ) {}
        

    static etl::optional< Mission > create( void (*task)(void*arg) , void * arg ,  uint32_t stackSize , uint32_t priority )  ;

    bool notify( const uint32_t message ) ;

    bool requestStop()  ;
    bool join();

    bool start() ;
    bool isRunning();

    static bool stopRequested();

    static uint32_t checkOnFlags();

    static bool waitForNotify( const uint32_t waitBitMask , const uint32_t p_delay );

    static void waitMS( const uint32_t ms ) ;

    static void yield() ;
};

#include "Mission.cpp"
