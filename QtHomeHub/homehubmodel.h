#ifndef HOMEHUBMODEL_H
#define HOMEHUBMODEL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QPixmap>

class HomeHubModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString homeHubStatus
               READ homeHubStatus
               NOTIFY homeHubStatusChanged)
    Q_PROPERTY(QString homeHubPhotoSource
               READ homeHubPhotoSource
               NOTIFY homeHubPhotoSourceChanged)
public:
    explicit HomeHubModel(QObject *parent = nullptr);

    QString homeHubStatus() const;
    void setHomeHubStatus(const QString &status);

    QString homeHubPhotoSource() const;
    QPixmap getPhoto() { return m_photo;}

private:
    QString m_homeHubStatus="uninitializedStatus";
    QString m_homeHubPhotoSource="image://imageProvider/emptypic";

    QNetworkAccessManager m_networkAccessManager;

    QPixmap m_photo;
    QString m_photoPath;
    int m_photoWidth;
    int m_photoHeigth;
    int m_photoOrientation;

    void requestRandomImagePath();
    void requestSelectedImage(QString pathname);

signals:
    void homeHubStatusChanged();
    void homeHubPhotoSourceChanged();

public slots:
    void refreshPicture();

private slots:
    void handleRandomImagePathReception(QNetworkReply *networkReply);
    void handleSelectedImageReception(QNetworkReply *networkReply);

};

#endif // HOMEHUBMODEL_H
