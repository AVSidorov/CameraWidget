// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QVariant>


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
    QCoreApplication::setApplicationName("Camera Widget Test");

    QGuiApplication app(argc, argv);

    QQuickView view;
    view.connect(view.engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit);
    view.setSource(QUrl("qrc:/camera/camera.qml"));
    if (view.status() == QQuickView::Error)
        return -1;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QObject *item = view.rootObject();
    MyClass myClass;

    QObject::connect(item, SIGNAL(qmlSignal(QQuickItem*)),
                     &myClass, SLOT(cppSlot(QQuickItem*)));
    QObject::connect(item, SIGNAL(msgSignal(QString)),
                     &myClass, SLOT(msgSlot(QString)));

    QObject::connect(item, SIGNAL(mouseMoveSignal(QQuickItem*)),
                     &myClass, SLOT(mouseSlot(QQuickItem*)));


    view.show();
    return app.exec();
}
