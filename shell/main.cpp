//#include"myclass.h"
#include <QtWidgets>
#include"shell.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    Shell sh;
    sh.show();

    return app.exec();
}
