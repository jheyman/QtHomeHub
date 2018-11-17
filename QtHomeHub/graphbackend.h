#ifndef GRAPHBACKEND_H
#define GRAPHBACKEND_H

#include <QObject>
#include <QQmlListProperty>
#include <QList>


class DataPoint : public QObject {
    Q_OBJECT
    Q_PROPERTY(long timestamp
               READ timestamp WRITE setTimestamp
               NOTIFY timeStampChanged)
    Q_PROPERTY(float dataPointValue
               READ dataPointValue WRITE setDataPointValue
               NOTIFY dataPointValueChanged)
public:
    explicit DataPoint(QObject *parent = 0);
    DataPoint(long timestamp, float value);

    long timestamp() const;
    void setTimestamp(const long &value);

    float dataPointValue() const;
    void setDataPointValue(const float &value);

signals:
    void timeStampChanged();
    void dataPointValueChanged();

private:
    long m_timestamp;
    long m_datapointvalue;
};

Q_DECLARE_METATYPE(DataPoint)


class GraphBackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<DataPoint> graphData
               READ graphData
               NOTIFY graphDataChanged)
public:
    explicit GraphBackEnd(QObject *parent = nullptr);

    QList<DataPoint> graphData() const;

signals:

public slots:

private:
    QList<DataPoint> m_dataPoints;
};

#endif // GRAPHBACKEND_H
