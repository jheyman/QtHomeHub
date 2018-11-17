#include "graphbackend.h"

DataPoint::DataPoint(QObject *parent): QObject(parent)
{
}

DataPoint::DataPoint(long timestamp, float value)
{
    m_timestamp = timestamp;
    m_datapointvalue = value;
}

long DataPoint::timestamp() const
{
    return m_timestamp;
}

void DataPoint::setTimestamp(const long &value)
{
    m_timestamp = value;
}

float DataPoint::dataPointValue() const
{
    return m_datapointvalue;
}

void DataPoint::setDataPointValue(const float &value)
{
    m_datapointvalue = value;
}

GraphBackEnd::GraphBackEnd(QObject *parent) : QObject(parent)
{
    m_dataPoints.append(DataPoint(0, 1.0));
    m_dataPoints.append(DataPoint(1, 2.0));
    m_dataPoints.append(DataPoint(2, 3.0));
    m_dataPoints.append(DataPoint(3, 4.0));
}

QList<DataPoint> GraphBackEnd::graphData() const
{
    return m_dataPoints;
}







