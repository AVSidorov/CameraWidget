//
// Created by sid on 2/18/24.
//

#ifndef CAMERATEST_CAMERVIEWIMAGEPROVIDER_H
#define CAMERATEST_CAMERVIEWIMAGEPROVIDER_H
#include <QPixmap>
#include <QQuickImageProvider>

class CamerViewImageProvider: public QQuickImageProvider{

public:
    CamerViewImageProvider()
            : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        if(id.contains("LiveFrame",Qt::CaseInsensitive)){
            return m_pixmap;
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
    void updatePixmap(QPixmap pixmap){m_pixmap = pixmap;};
private:
    QPixmap m_pixmap;
};


#endif //CAMERATEST_CAMERVIEWIMAGEPROVIDER_H
