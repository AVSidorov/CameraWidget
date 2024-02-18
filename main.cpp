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

class MyClass : public QObject
{
Q_OBJECT
public slots:
    void cppSlot(QQuickItem *item) {

        qDebug() << "Called the C++ slot with item:" << item;

        qDebug() << "Item dimensions:" << item->width()
                 << item->height();
    }
//    void cppSlot(const QQuickItem& item) {
//
//        qDebug() << "Called the C++ slot with item:" << &item;
//
//        qDebug() << "Item dimensions:" << item.width()
//                 << item.height();
//    }
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
    QCoreApplication::setApplicationName("Camera Widget Test");

//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);


    //QQuickView view;
    //QQuickWidget *view = new QQuickWidget;
    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view);
//    QWidget *container = QWidget::createWindowContainer(view, nullptr,Qt::Window | Qt::FramelessWindowHint);

//    view->setSource(QUrl::fromLocalFile("camera.qml"));
    view->setSource(QUrl("qrc:/camera/camera.qml"));
//    if (view.status() == QQuickView::Error)
//        return -1;

    QObject *root= view->rootObject();
//    qDebug() << root;
//    qDebug() << dynamic_cast<QQuickItem*>(root);
//    QQmlContext* const context = qmlContext(root);
//    QString id = context->nameForObject(root);
//    qDebug() << id;
//    QObject *rect = root->findChild<QObject*>("rect");
    MyClass myClass;

    QObject::connect(root, SIGNAL(qmlSignal(QQuickItem*)),
                     &myClass, SLOT(cppSlot(QQuickItem*)));
    QObject::connect(root, SIGNAL(msgSignal(QString)),
                     &myClass, SLOT(msgSlot(QString)));

    QObject::connect(root, SIGNAL(mouseMoveSignal(QQuickItem *)),
                     &myClass, SLOT(mouseSlot(QQuickItem*)));
    //   container->show();

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(container);
//    mainWindow.setWindowFlag(Qt::FramelessWindowHint);
//    mainWindow.setWindowFlag(Qt::SplashScreen);
    mainWindow.show();
    return app.exec();
}
