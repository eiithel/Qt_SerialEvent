#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QWebSocket>
#include <QByteArray>
#include <QList>
#include <QObject>


class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~Socket();

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

#endif // WEBSOCKET_H

