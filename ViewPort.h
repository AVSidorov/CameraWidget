//
// Created by sid on 2/18/24.
//

#ifndef CAMERATEST_VIEWPORT_H
#define CAMERATEST_VIEWPORT_H

#include <QWidget>
#include <qqml.h>
#include <QQuickWidget>
#include <QQuickView>
#include <QPointF>
#include <QDebug>
#include <QQuickItem>
#include <QGridLayout>

#include "ViewPortImageProvider.h"

class ViewPort: public QWidget{
    Q_OBJECT

public:
    ViewPort(QWidget* parent): QWidget(parent)
    , view(new QQuickView())
    , container(QWidget::createWindowContainer(view,this))
    , imageProvider(new ViewPortImageProvider){
        Q_INIT_RESOURCE(camera);
        auto layout = new QGridLayout(this);
        layout->addWidget(container);

        imageProvider->setParent(this);
        view->engine()->addImageProvider(QLatin1String("provider"), imageProvider);
        view->setSource(QUrl("qrc:/camera/ViewPort.qml"));

        QObject *root= view->rootObject();
        QObject::connect(root, SIGNAL(mouseMoveSignal(QQuickItem *)),
                         this, SLOT(cursorPositionSlot(QQuickItem*)));
    } ;
    ~ViewPort(){};
    void updatePixmap(std::shared_ptr<QPixmap> pixmap){
        if(pixmap == nullptr)
            return;
        m_pixmap = std::move(pixmap);
        imageProvider->updatePixmap(m_pixmap.get());
//        qDebug() << "New Pixmap size: " << m_pixmap->size();
        emit pixmapUpdated();
    };

    QSize pixmapSize(){return m_pixmap->size();};

private:
    QQuickView *view;
    QWidget *container;
    ViewPortImageProvider *imageProvider;
    std::shared_ptr<QPixmap> m_pixmap;

signals:
    void cursorPosition(QPointF);
    void pixmapUpdated();

private slots:
    void cursorPositionSlot(QQuickItem *item) {
        qDebug() << "x: " << item->x() << " y: " << item->y();
        emit cursorPosition(QPointF(item->x(), item->y()));
    }

};


#endif //CAMERATEST_VIEWPORT_H
