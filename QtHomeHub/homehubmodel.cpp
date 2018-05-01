#include "homehubmodel.h"
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QImageReader>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>

#include <imageprovider.h>

#define ZERO_KELVIN 273.15

WeatherData::WeatherData(QObject *parent) :
        QObject(parent)
{
}

WeatherData::WeatherData(const WeatherData &other) :
        QObject(0),
        m_dayOfWeek(other.m_dayOfWeek),
        m_weather(other.m_weather),
        m_weatherDescription(other.m_weatherDescription),
        m_temperature(other.m_temperature)
{
}

QString WeatherData::dayOfWeek() const
{
    return m_dayOfWeek;
}

/*!
 * The icon value is based on OpenWeatherMap.org icon set. For details
 * see http://bugs.openweathermap.org/projects/api/wiki/Weather_Condition_Codes
 *
 * e.g. 01d ->sunny day
 *
 * The icon string will be translated to
 * http://openweathermap.org/img/w/01d.png
 */
QString WeatherData::weatherIcon() const
{
    return m_weather;
}

QString WeatherData::weatherDescription() const
{
    return m_weatherDescription;
}

QString WeatherData::temperature() const
{
    return m_temperature;
}

void WeatherData::setDayOfWeek(const QString &value)
{
    m_dayOfWeek = value;
    emit dataChanged();
}

void WeatherData::setWeatherIcon(const QString &value)
{
    m_weather = value;
    emit dataChanged();
}

void WeatherData::setWeatherDescription(const QString &value)
{
    m_weatherDescription = value;
    emit dataChanged();
}

void WeatherData::setTemperature(const QString &value)
{
    m_temperature = value;
    emit dataChanged();
}

HomeHubModel::HomeHubModel(QObject *parent) : QObject(parent)
{  
    // PHOTOFRAME
    ImageProvider::setSource(this);
    refreshPicture();
    setHomeHubStatus("Initialized");

    // WEATHER
    refreshWeather();
    connect(&m_requestNewWeatherTimer, SIGNAL(timeout()), this, SLOT(refreshWeather()));
    m_requestNewWeatherTimer.setSingleShot(false);
    m_requestNewWeatherTimer.setInterval(30*60*1000); // 30 minutes
    m_requestNewWeatherTimer.start();
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

void HomeHubModel::refreshWeather()
{
    qDebug()<<"refreshWeather";

    QUrl url("http://api.openweathermap.org/data/2.5/weather");
    QUrlQuery query;

    query.addQueryItem("q", m_city);
    query.addQueryItem("mode", "json");
    query.addQueryItem("lang", "fr"); // French text
    query.addQueryItem("APPID", m_app_ident);
    url.setQuery(query);

    QNetworkReply *rep = m_networkAccessManager.get(QNetworkRequest(url));
    connect(rep, &QNetworkReply::finished, this, [this, rep]() { handleWeatherNetworkData(rep); });
}

static QString niceTemperatureString(double t)
{
    return QString::number(qRound(t-ZERO_KELVIN)) + QChar(0xB0);
}

void HomeHubModel::handleWeatherNetworkData(QNetworkReply *networkReply)
{
    qDebug()<< "handleWeatherNetworkData";

    if (!networkReply)
        return;

    if (!networkReply->error()) {

        m_now.setWeatherDescription("??");
        m_now.setWeatherIcon("00");
        m_now.setTemperature("??");

        QJsonDocument document = QJsonDocument::fromJson(networkReply->readAll());

        if (document.isObject()) {
            QJsonObject obj = document.object();
            QJsonObject tempObject;
            QJsonValue val;

            if (obj.contains(QStringLiteral("weather"))) {
                val = obj.value(QStringLiteral("weather"));
                QJsonArray weatherArray = val.toArray();
                val = weatherArray.at(0);
                tempObject = val.toObject();
                m_now.setWeatherDescription(tempObject.value(QStringLiteral("description")).toString());
                qDebug()<<"current weather: "<<"desc="<<tempObject.value(QStringLiteral("description")).toString();
                m_now.setWeatherIcon(tempObject.value("icon").toString());
                qDebug()<<"current weather: "<<"icon="<<tempObject.value("icon").toString();

            }
            if (obj.contains(QStringLiteral("main"))) {
                val = obj.value(QStringLiteral("main"));
                tempObject = val.toObject();
                val = tempObject.value(QStringLiteral("temp"));
                m_now.setTemperature(niceTemperatureString(val.toDouble()));
                qDebug()<<"current weather: "<<"temp="<<niceTemperatureString(val.toDouble());

            }
        }
    }
    networkReply->deleteLater();

    //retrieve the forecast
    QUrl url("http://api.openweathermap.org/data/2.5/forecast/daily");
    QUrlQuery query;

    query.addQueryItem("q", m_city);
    query.addQueryItem("mode", "json");
    query.addQueryItem("cnt", "5");
    query.addQueryItem("lang", "fr"); // French text
    query.addQueryItem("APPID", m_app_ident);
    url.setQuery(query);

    QNetworkReply *rep = m_networkAccessManager.get(QNetworkRequest(url));
    connect(rep, &QNetworkReply::finished, this, [this, rep]() { handleForecastNetworkData(rep); });
}

void HomeHubModel::handleForecastNetworkData(QNetworkReply *networkReply)
{
    if (!networkReply)
        return;

    if (!networkReply->error()) {
        QJsonDocument document = QJsonDocument::fromJson(networkReply->readAll());

        QJsonObject jo;
        QJsonValue jv;
        QJsonObject root = document.object();
        jv = root.value(QStringLiteral("list"));
        if (!jv.isArray())
            qWarning() << "Invalid forecast object";
        QJsonArray ja = jv.toArray();
        //we need 4 days of forecast -> first entry is today
        if (ja.count() != 5)
            qWarning() << "Invalid forecast object";

        QString data;

        for (int i = 1; i<ja.count(); i++) {
            WeatherData *forecastEntry=NULL;
            switch (i){
                case 1:
                    forecastEntry = &m_forecast1;
                    break;
                case 2:
                    forecastEntry = &m_forecast2;
                    break;
                case 3:
                    forecastEntry = &m_forecast3;
                    break;
                case 4:
                    forecastEntry = &m_forecast4;
                    break;
                default:
                    qWarning()<<"invalid index";
                    break;
            }

            //min/max temperature
            QJsonObject subtree = ja.at(i).toObject();
            jo = subtree.value(QStringLiteral("temp")).toObject();
            jv = jo.value(QStringLiteral("min"));
            data.clear();
            data += niceTemperatureString(jv.toDouble());
            data += QChar('/');
            jv = jo.value(QStringLiteral("max"));
            data += niceTemperatureString(jv.toDouble());
            forecastEntry->setTemperature(data);

            qDebug()<<"forecast "<<i<<", temp="<<data;

            //get date
            jv = subtree.value(QStringLiteral("dt"));
            QDateTime dt = QDateTime::fromMSecsSinceEpoch((qint64)jv.toDouble()*1000);

            QDate date = dt.date();
            QLocale locale  = QLocale(QLocale::French, QLocale::France);
            QString frenchDate = locale.toString(date, "ddd");
            forecastEntry->setDayOfWeek(frenchDate);

            qDebug()<<"forecast "<<i<<", day="<<frenchDate;

            //get icon
            QJsonArray weatherArray = subtree.value(QStringLiteral("weather")).toArray();
            jo = weatherArray.at(0).toObject();
            forecastEntry->setWeatherIcon(jo.value(QStringLiteral("icon")).toString());

            qDebug()<<"forecast "<<i<<", icon="<<jo.value(QStringLiteral("icon")).toString();

            //get description
            forecastEntry->setWeatherDescription(jo.value(QStringLiteral("description")).toString());
        }

        emit weatherChanged();
    }
    networkReply->deleteLater();
}

bool HomeHubModel::hasValidWeather() const
{
    return (!(m_now.weatherIcon().isEmpty()) &&
           (m_now.weatherIcon().size() > 1) &&
            m_now.weatherIcon() != "");
}

WeatherData *HomeHubModel::currentWeather()
{
    return &m_now;
}

WeatherData *HomeHubModel::forecast1Weather()
{
    return &m_forecast1;
}
WeatherData *HomeHubModel::forecast2Weather()
{
    return &m_forecast2;
}
WeatherData *HomeHubModel::forecast3Weather()
{
    return &m_forecast3;
}
WeatherData *HomeHubModel::forecast4Weather()
{
    return &m_forecast4;
}



