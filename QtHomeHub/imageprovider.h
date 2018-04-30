#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <homehubmodel.h>

class ImageProvider:  public QQuickImageProvider
{
public:
    ImageProvider();
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    static void setSource(HomeHubModel* ptr);
private:
    static HomeHubModel* source;
};

#endif // IMAGEPROVIDER_H
