#include "imageprovider.h"
#include <QDebug>

HomeHubModel* ImageProvider::source=NULL;

ImageProvider::ImageProvider(): QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

void ImageProvider::setSource(HomeHubModel* ptr)
{
    source = ptr;
}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug() << "requestPixmap: " << id << ", w=" <<requestedSize.width() << ", h=" << requestedSize.height();

    QPixmap ret_pixmap;
    int width;
    int height;

    if (id != "emptypic") {

        if (source != NULL)
        {
             ret_pixmap = source->getPhoto();
        }
        else
            qDebug()<<"NULL source";

        width = ret_pixmap.width();
        height = ret_pixmap.height();

    } else {
        width = requestedSize.width() > 0 ? requestedSize.width() : 100;
        height = requestedSize.height() > 0 ? requestedSize.height() : 100;

        QPixmap pixmap(width,height);
        pixmap.fill(QColor("transparent").rgba());
        ret_pixmap = pixmap;
    }

    if (size)
        *size = QSize(width, height);

    qDebug() << "ImageProvider: returning pixmap of width: " << ret_pixmap.width() << "and height:" << ret_pixmap.height();

    return ret_pixmap;
}

