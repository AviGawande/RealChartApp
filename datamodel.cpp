#include "datamodel.h"
#include <QDebug>

DataModel::DataModel(QObject *parent)
    : QObject(parent)
{
    // Connect UDP receiver signals
    connect(&m_udpReceiver, &UdpReceiver::dataReceived,
            this, &DataModel::handleUdpData);
}

DataModel::~DataModel()
{
    stopUdpReceiver();
}

void DataModel::startUdpReceiver()
{
    if (m_udpReceiver.start()) {
        qDebug() << "Started receiving data from UDP";
    } else {
        qWarning() << "Failed to start UDP receiver";
    }
}

void DataModel::stopUdpReceiver()
{
    m_udpReceiver.stop();
    qDebug() << "Stopped receiving data from UDP";
}

void DataModel::handleUdpData(const QVector<double> &values, qint64 timestamp)
{
    for (const double &value : values) {
        emit newDataPoint(static_cast<float>(value));
        qDebug() << "Received data point:" << value << "at timestamp:" << timestamp;
    }
}
