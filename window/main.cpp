#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget myWin;

    //size and location
    myWin.setWindowFlags(Qt::Window);
    myWin.setWindowTitle("My window");
    myWin.move(100, 100);
    myWin.resize(300, 300);

    //color
    QWidget *wdg = new QWidget;
    QPixmap pix("picture.jpg");

    QPalette color;
    color.setBrush(wdg->backgroundRole(), QBrush(pix));
    myWin.setPalette(color);
    myWin.setAutoFillBackground(true);
    myWin.setFixedSize(pix.width(), pix.height());

    //scroll
    QScrollArea sa;
    sa.setWidget(&myWin);
    sa.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    sa.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //frame
    sa.setFrameStyle(QFrame::Panel | QFrame::Raised);
    sa.setLineWidth(3);

    sa.show();

    return app.exec();
}
