#ifndef HOMEHUBMODEL_H
#define HOMEHUBMODEL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QPixmap>
#include <QTimer>

class WeatherData : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString dayOfWeek
               READ dayOfWeek WRITE setDayOfWeek
               NOTIFY dataChanged)
    Q_PROPERTY(QString weatherIcon
               READ weatherIcon WRITE setWeatherIcon
               NOTIFY dataChanged)
    Q_PROPERTY(QString weatherDescription
               READ weatherDescription WRITE setWeatherDescription
               NOTIFY dataChanged)
    Q_PROPERTY(QString temperature
               READ temperature WRITE setTemperature
               NOTIFY dataChanged)

public:
    explicit WeatherData(QObject *parent = 0);
    WeatherData(const WeatherData &other);

    QString dayOfWeek() const;
    QString weatherIcon() const;
    QString weatherDescription() const;
    QString temperature() const;

    void setDayOfWeek(const QString &value);
    void setWeatherIcon(const QString &value);
    void setWeatherDescription(const QString &value);
    void setTemperature(const QString &value);

signals:
    void dataChanged();

private:
    QString m_dayOfWeek;
    QString m_weather;
    QString m_weatherDescription;
    QString m_temperature;
};

Q_DECLARE_METATYPE(WeatherData)

class HomeHubModel : public QObject
{
    Q_OBJECT
    // GENERAL data
    Q_PROPERTY(QString homeHubStatus
               READ homeHubStatus
               NOTIFY homeHubStatusChanged)

    // PHOTOFRAME data
    Q_PROPERTY(QString homeHubPhotoSource
               READ homeHubPhotoSource
               NOTIFY homeHubPhotoSourceChanged)

    // WEATHER data
    Q_PROPERTY(bool hasValidWeather
               READ hasValidWeather
               NOTIFY weatherChanged)
    Q_PROPERTY(WeatherData *currentWeather
               READ currentWeather
               NOTIFY weatherChanged)
    Q_PROPERTY(WeatherData *forecast1Weather
               READ forecast1Weather
               NOTIFY weatherChanged)
    Q_PROPERTY(WeatherData *forecast2Weather
               READ forecast2Weather
               NOTIFY weatherChanged)
    Q_PROPERTY(WeatherData *forecast3Weather
               READ forecast3Weather
               NOTIFY weatherChanged)
    Q_PROPERTY(WeatherData *forecast4Weather
               READ forecast4Weather
               NOTIFY weatherChanged)

public:
    explicit HomeHubModel(QObject *parent = nullptr);

    // GENERAL
    QString homeHubStatus() const;
    void setHomeHubStatus(const QString &status);

    // PHOTOFRAME
    QString homeHubPhotoSource() const;
    QPixmap getPhoto() { return m_photo;}

    // WEATHER
    bool hasValidWeather() const;
    WeatherData *currentWeather();
    WeatherData *forecast1Weather();
    WeatherData *forecast2Weather();
    WeatherData *forecast3Weather();
    WeatherData *forecast4Weather();

private:
    // GENERAL
    QString m_homeHubStatus="uninitializedStatus";
    QNetworkAccessManager m_networkAccessManager;

    // PHOTOFRAME
    QString m_homeHubPhotoSource="image://imageProvider/emptypic";
    QPixmap m_photo;
    QString m_photoPath;
    int m_photoWidth;
    int m_photoHeigth;
    int m_photoOrientation;

    void requestRandomImagePath();
    void requestSelectedImage(QString pathname);

    // WEATHER
    static const int m_baseMsBeforeNewRequest = 5 * 1000; // 5 s, increased after each missing answer up to 10x
    QString m_city = "Paris,FR";
    WeatherData m_now;
    WeatherData m_forecast1;
    WeatherData m_forecast2;
    WeatherData m_forecast3;
    WeatherData m_forecast4;
    int m_nErrors;
    int m_minMsBeforeNewRequest;
    QTimer m_requestNewWeatherTimer;
    QString m_app_ident = QStringLiteral("2dee82fd5d7326c51ceb0d4b8a42e2b5");
    //QString m_app_ident = QStringLiteral("2dee82fd5d7326c51ceb0d4b8a42e2ff"); // FAKE to test ERROR

signals:
    // PHOTOFRAME
    void homeHubStatusChanged();
    void homeHubPhotoSourceChanged();

    // WEATHER
    void weatherChanged();

public slots:

    // PHOTOFRAME
    void refreshPicture();

    // WEATHER
    Q_INVOKABLE void refreshWeather();

private slots:

    // PHOTOFRAME
    void handleRandomImagePathReception(QNetworkReply *networkReply);
    void handleSelectedImageReception(QNetworkReply *networkReply);

    // WEATHER
    void handleWeatherNetworkData(QNetworkReply *networkReply);
    void handleForecastNetworkData(QNetworkReply *networkReply);
};

#endif // HOMEHUBMODEL_H
