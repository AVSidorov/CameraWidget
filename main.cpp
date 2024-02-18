// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QVariant>
#include <QWidget>
//#include <QtQuickWidgets/QQuickWidget>
#include <QApplication>
#include <QMainWindow>
#include <QQuickWidget>
#include <QQmlContext>
#include <qqml.h>
#include "CamerViewImageProvider.h"
#include <QTimer>

class MyClass : public QObject
{
Q_OBJECT
public slots:
    void cppSlot(QQuickItem *item) {

        qDebug() << "Called the C++ slot with item:" << item;

        qDebug() << "Item dimensions:" << item->width()
                 << item->height();
    }

    void msgSlot(const QString &msg) {
        qDebug() << "Called the C++ slot with message:" << msg;
    }

    void mouseSlot(QQuickItem *item) {

        qDebug() << "x: " << item->x() << " y: " << item->y();
    }
};
#include "main.moc"
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(camera);
    QCoreApplication::setApplicationName("Camera Widget Test");

    QApplication app(argc, argv);

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view);
//    QWidget *container = QWidget::createWindowContainer(view, nullptr,Qt::Window | Qt::FramelessWindowHint);



    auto imageProvider = new CamerViewImageProvider;
    imageProvider->updatePixmap(QPixmap(":/camera/images/pr.png"));
    view->engine()->addImageProvider(QLatin1String("colors"), imageProvider);

    view->setSource(QUrl("qrc:/camera/camera.qml"));

    QObject *root= view->rootObject();

    MyClass myClass;

    QObject::connect(root, SIGNAL(qmlSignal(QQuickItem*)),
                     &myClass, SLOT(cppSlot(QQuickItem*)));
    QObject::connect(root, SIGNAL(msgSignal(QString)),
                     &myClass, SLOT(msgSlot(QString)));

    QObject::connect(root, SIGNAL(mouseMoveSignal(QQuickItem *)),
                     &myClass, SLOT(mouseSlot(QQuickItem*)));

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(container);
    auto timer1 = new QTimer(&mainWindow);
    auto timer2 = new QTimer(&mainWindow);
    QObject::connect(timer1, &QTimer::timeout, [&]{
        qDebug()<<"image 1";
        imageProvider->updatePixmap(QPixmap(":/camera/images/pr.png"));
    });
    QObject::connect(timer2, &QTimer::timeout, [&]{
        qDebug()<<"image 2";
        imageProvider->updatePixmap(QPixmap(":/camera/images/SWTestbild.png"));
    });

    int period = 10000;
    timer1->start(period);
    QTimer::singleShot(period/2,[&timer2, period] { timer2->start(period); });

    mainWindow.centralWidget()->setMinimumSize(QSize(500, 500));
    mainWindow.show();
    return app.exec();
}
