#include "udpreceiver.h"
#include <QNetworkInterface>
#include <QDataStream>
#include <QDebug>


UdpReceiver::UdpReceiver(const QString &multicastAddress, int port, QObject *parent)
    : QObject(parent)
    , m_multicastAddress(multicastAddress)
    , m_port(port)
    , m_isRunning(false)
{
    connect(&m_socket, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
}

UdpReceiver::~UdpReceiver()
{
    stop();
}

bool UdpReceiver::start()
{
    if (m_isRunning) {
        return true;
    }
    // Bind to the port
    if (!m_socket.bind(QHostAddress::AnyIPv4, m_port, QUdpSocket::ShareAddress)) {
        qWarning() << "Failed to bind UDP socket:" << m_socket.error();
        return false;
    }
    // Join the multicast group
    if (!m_socket.joinMulticastGroup(m_multicastAddress)) {
        qWarning() << "Failed to join multicast group:" << m_socket.error();
        m_socket.close();
        return false;
    }
    m_isRunning = true;
    qDebug() << "UDP Receiver started on multicast group" << m_multicastAddress.toString()
             << "port" << m_port;
    return true;
}

void UdpReceiver::stop()
{
    if (!m_isRunning) {
        return;
    }
    // Leave the multicast group
    m_socket.leaveMulticastGroup(m_multicastAddress);
    m_socket.close();
    m_isRunning = false;
    qDebug() << "UDP Receiver stopped";
}

void UdpReceiver::processPendingDatagrams()
{
    while (m_socket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_socket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QVector<double> values;
        qint64 timestamp;
        if (unpackData(datagram, values, timestamp)) {
            emit dataReceived(values, timestamp);
            qDebug() << "Received" << values.size() << "data points from"
                     << sender.toString() << ":" << senderPort
                     << "at" << QDateTime::fromMSecsSinceEpoch(timestamp).toString("hh:mm:ss.zzz");
        }
    }
}

bool UdpReceiver::unpackData(const QByteArray &datagram, QVector<double> &values, qint64 &timestamp)
{
    QDataStream stream(datagram);
    stream.setVersion(QDataStream::Qt_6_5);
    // Read timestamp
    stream >> timestamp;
    // Read number of values
    int count;
    stream >> count;
    if (stream.status() != QDataStream::Ok || count < 0 || count > 500) {
        qWarning() << "Invalid data received: bad format or count";
        return false;
    }
    // Read each value
    values.clear();
    values.reserve(count);
    for (int i = 0; i < count; ++i) {
        double value;
        stream >> value;
        if (stream.status() != QDataStream::Ok) {
            qWarning() << "Failed to read data point" << i;
            return false;
        }
        values.append(value);
    }
    return true;
}
