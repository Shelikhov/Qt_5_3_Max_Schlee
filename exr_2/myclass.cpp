#include "myclass.h"

MyClass::MyClass(): QObject(), lbl("standart name"){
    lbl.show();
}

void MyClass::changeText(const QString &str){
    lbl.setText(str);
    lbl.show();
}
