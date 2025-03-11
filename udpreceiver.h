 #ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QVector>
#include <QDateTime>

class UdpReceiver : public QObject
{
    Q_OBJECT
public:
    explicit UdpReceiver(const QString &multicastAddress = "224.0.0.1",
                         int port = 50000,
                         QObject *parent = nullptr);
    ~UdpReceiver();
    bool start();
    void stop();
signals:
    // Emitted when new data is received
    void dataReceived(const QVector<double> &values, qint64 timestamp);
private slots:
    void processPendingDatagrams();
private:
    QUdpSocket m_socket;
    QHostAddress m_multicastAddress;
    int m_port;
    bool m_isRunning;
    // Unpack received data from binary format
    bool unpackData(const QByteArray &datagram, QVector<double> &values, qint64 &timestamp);
};
#endif // UDPRECEIVER_H
