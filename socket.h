#ifndef SOCKET
#define SOCKET


#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

class EchoServer : public QObject
{
    Q_OBJECT
public:
    explicit EchoServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~EchoServer();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
};


#endif // SOCKET

