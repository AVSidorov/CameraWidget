//
// Created by sid on 2/18/24.
//

#ifndef CAMERATEST_VIEWPORTIMAGEPROVIDER_H
#define CAMERATEST_VIEWPORTIMAGEPROVIDER_H
#include <QPixmap>
#include <QQuickImageProvider>

class ViewPortImageProvider: public QQuickImageProvider{

public:
    ViewPortImageProvider()
            : QQuickImageProvider(QQuickImageProvider::Pixmap)
            , m_pixmap(nullptr)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        if(m_pixmap){
            return *m_pixmap;
        }
        int width = 100;
        int height = 50;

        if (size)
            *size = QSize(width, height);
        QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                       requestedSize.height() > 0 ? requestedSize.height() : height);
        pixmap.fill(QColor(id).rgba());
        return pixmap;
    }
    void updatePixmap(QPixmap* pixmap){m_pixmap = pixmap;};
private:
    QPixmap* m_pixmap;
};


#endif //CAMERATEST_CAMERVIEWIMAGEPROVIDER_H
