#include "homehubmodel.h"
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QImageReader>
#include <imageprovider.h>

HomeHubModel::HomeHubModel(QObject *parent) : QObject(parent)
{
    ImageProvider::setSource(this);
    refreshPicture();
    setHomeHubStatus("Initialized");
}

void HomeHubModel::refreshPicture()
{
    qDebug() << "refreshPicture requested";
    requestRandomImagePath();
}

void HomeHubModel::requestRandomImagePath()
{
    QUrl url("http://192.168.0.13:8081/getRandomImagePath.php");
    QUrlQuery query;
    query.addQueryItem("basepath", "/mnt/photo");
    url.setQuery(query);

    QNetworkReply *rep = m_networkAccessManager.get(QNetworkRequest(url));
    connect(rep, &QNetworkReply::finished, this, [this, rep]() { handleRandomImagePathReception(rep); });
}

void HomeHubModel::requestSelectedImage(QString pathname)
{
    qDebug()<<"requestSelectedImage: "<<pathname;
    QUrl url("http://192.168.0.13:8081/getImage.php");
    QUrlQuery query;
    query.addQueryItem("path", pathname);
    url.setQuery(query);

    QNetworkReply *rep = m_networkAccessManager.get(QNetworkRequest(url));
    connect(rep, &QNetworkReply::finished, this, [this, rep]() { handleSelectedImageReception(rep); });
}

QString HomeHubModel::homeHubStatus() const
{
    return m_homeHubStatus;
}

void HomeHubModel::setHomeHubStatus(const QString &status)
{
    m_homeHubStatus = status;
    emit homeHubStatusChanged();
}

QString HomeHubModel::homeHubPhotoSource() const
{
    return m_homeHubPhotoSource;
}

void HomeHubModel::handleRandomImagePathReception(QNetworkReply *networkReply)
{
    if (!networkReply) {
        qDebug()<<"ERROR in handleRandomImagePathReception : null reply";
        return;
    }

    if (!networkReply->error()) {

        // format of the returned info is :
        // [file path];[width in pixels];[height in pixels];[orientation]
        QByteArray tmp = networkReply->readAll();
        QStringList parts = QString(tmp).split(";");

        m_photoPath = parts.at(0);

        if (parts.length() > 2) {
            m_photoWidth = parts.at(1).toInt();
            m_photoHeigth = parts.at(2).toInt();
            if (parts.length() > 3) {
                m_photoOrientation = parts.at(3).toInt();
            }
        }

        qDebug() << "updated photo info: photopath= " << m_photoPath <<", W=" << m_photoWidth << ", H=" << m_photoHeigth << "Orient=" << m_photoOrientation;

        requestSelectedImage(m_photoPath);

    } else {
        qDebug()<<"ERROR in handleRandomImagePathReception : reply error";
    }
    networkReply->deleteLater();
}


void HomeHubModel::handleSelectedImageReception(QNetworkReply *networkReply)
{
    if (!networkReply) {
        qDebug()<<"ERROR in handleSelectedImageReception : null reply";
        return;
    }

    if (!networkReply->error()) {

        // read image data from HTTP datastream
        // QImageReader will figure out the image type automatically
        QImageReader imageReader(networkReply);

        // store retrieved picture locally
        QImage pic = imageReader.read();

        // Rotate image depending on the orientation setting gathered from the image EXIF data

        int rotationAngle = 0;
        switch (m_photoOrientation) {
            case 1:
                rotationAngle = 0;
                break;
            case 3:
                rotationAngle = 180;
                break;
            case 6:
                rotationAngle = 90;
                break;
            case 8:
                rotationAngle = 270;
                break;
            default:
                qWarning()<< "Unknown image orientation value: " << m_photoOrientation;
                break;
        }
        pic = pic.transformed(QMatrix().rotate(rotationAngle));
        m_photo = QPixmap::fromImage(pic);

        // update & notify the image source property (with the path and name of the image, but this is arbitrary)
        // This will trig a reload of the Image in the QML engine.
        m_homeHubPhotoSource = "image://imageProvider"+m_photoPath;
        emit homeHubPhotoSourceChanged();

    } else {
        qDebug()<<"ERROR in handleSelectedImageReception : reply error";
    }
    networkReply->deleteLater();
}


