#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QPixmap>


#include "ViewPort.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(camera);
    QCoreApplication::setApplicationName("Camera Widget Test");

    QApplication app(argc, argv);

    ViewPort *viewPort = new ViewPort(nullptr);
    viewPort->updatePixmap(std::make_shared<QPixmap>(":/camera/images/pr.png"));

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(viewPort);

    auto timer1 = new QTimer(&mainWindow);
    auto timer2 = new QTimer(&mainWindow);

    QObject::connect(timer1, &QTimer::timeout, [&]{
        qDebug()<<"image 1";
        viewPort->updatePixmap(std::make_shared<QPixmap>(":/camera/images/pr.png"));
    });
    QObject::connect(timer2, &QTimer::timeout, [&]{
        qDebug()<<"image 2";
        viewPort->updatePixmap(std::make_shared<QPixmap>(":/camera/images/SWTestbild.png"));
    });

    int period = 10000;
    timer1->start(period);
    QTimer::singleShot(period/2,[&timer2, period] { timer2->start(period); });






    mainWindow.show();
    return app.exec();
}
