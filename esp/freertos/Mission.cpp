#include "Mission.hpp"


template< class T >
unsigned long Mission<T>::MAX_DELAY = portMAX_DELAY;

template< class T >
etl::optional< Mission<T> > Mission<T>::create( void (*task)(void*arg) , void * arg ,  uint32_t stackSize , uint32_t priority )  {
    Mission<T> tmp{ task ,arg , stackSize , priority } ;
    
    return tmp;
}

template< class T >
 void Mission<T>::_task( void * arg ){
        auto &instance=  *static_cast<Mission<T>*>( arg ) ;
        instance.taskRunning = true ;
        instance.task( arg  ) ;

        vTaskDelete( instance.taskHandle ) ;
        instance.taskRunning = false ;

    }

template< class T >
uint32_t Mission<T><checkOnFlags(){
        uin32_t result{ 0 } ;
        xTaskNotifyWait( 0 , ~(uint32_t)0 , &result , 0 );
        return result ;
}

template< class T >
bool Mission<T>::notify( const uint32_t message )   {
    auto result = xTaskNotify( taskHandle , message , eSetBits ) ;
    if ( result != pdPASS) return false ; 
    return true ;
}

template< class T >
bool Mission<T>::requestStop()  {
    auto result = xTaskNotify( taskHandle , stopBit , eSetBits  ) ;
    if ( result != pdPASS) return false ; 
    return true ;
}

template< class T >
bool Mission<T>::join(){
    if ( !taskRunning ) return true ;
    if ( !requestStop() ) return false ;
    while ( taskRunning ){ Mission<T>::yield(); }
    return true  ;
}

template< class T >
bool Mission<T>::start() {
    if ( taskRunning) return true ;
    auto result  = xTaskCreate( _task , "task" , stackSize , arg  , priority , &taskHandle ) ;
    if ( result != pdPASS ) return false ; 
    return true; 
} 


template< class T >
bool Mission<T>::stopRequested(   ){
    uint32_t result { 0 } ;
    if ( !xTaskNotifyWait( 0 , stopBit ,  &result , 0  )) return false ;
    if ( result & stopBit ) return true ;
    return false ;
}

template< class T >
bool Mission<T>::waitForNotify( const uint32_t waitBitMask , const uint32_t p_delay ){
    uint32_t result { 0 } ;
    auto delay = ( p_delay == MAX_DELAY ) ? (  portMAX_DELAY ) : pdMS_TO_TICKS( p_delay ) ;
    if ( !xTaskNotifyWait( 0 ,  waitBitMask , &result , delay )) return false ;

    if ( result & waitBitMask )  return true ;

    return false  ;

}

template< class T >
void Mission<T>::waitMS( const uint32_t ms ) {
    vTaskDelay( pdMS_TO_TICKS( ms ) ) ;
}


template< class T >
void Mission<T>::yield(){
    taskYIELD() ;
}

template< class T >
bool Mission<T>::isRunning(){ return taskRunning ; }

