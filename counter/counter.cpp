#include "counter.h"

Counter::Counter():QObject(), number(0){
}

void Counter::slotInc(){
    emit showNumber(++number);
    if(number == 5)
        emit exit();
}
