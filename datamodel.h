#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QVector>
#include "udpreceiver.h"

class DataModel : public QObject
{
    Q_OBJECT

public:
    explicit DataModel(QObject *parent = nullptr);  //initialize the data model

    ~DataModel(); // destructor to clean-up when obj. is deleted

    // Methods for UDP data receiving
    Q_INVOKABLE void startUdpReceiver();  //this func.will be called directly from qml
    Q_INVOKABLE void stopUdpReceiver();   // this func.will be called directly from qml

signals:
    void newDataPoint(float value);  //qml ui listening this new data point

private slots:
    void handleUdpData(const QVector<double> &values, qint64 timestamp);
    // listens incoming data

private:
    UdpReceiver m_udpReceiver;
};

#endif // DATAMODEL_H
