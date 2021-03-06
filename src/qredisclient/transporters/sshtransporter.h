#pragma once
#include <QEventLoop>
#include <QTimer>
#include <qsshclient/qxtsshclient.h>

#include "abstracttransporter.h"

class QxtSshTcpSocket;

namespace RedisClient {

/**
 * @brief The SshTransporter class
 * Provides execution of redis commands through SSH tunnel.
 */
class SshTransporter : public AbstractTransporter
{
public:
    SshTransporter(Connection *);

public slots:
    void disconnectFromHost();

protected:
    bool isInitialized() const override;
    bool isSocketReconnectRequired() const override;
    bool canReadFromSocket() override;
    QByteArray readFromSocket() override;
    void initSocket() override;
    bool connectToHost() override;
    void sendCommand(const QByteArray& cmd) override;

protected slots:
    void reconnect() override;

private slots:
    void OnSshConnectionError(QxtSshClient::Error);
    void OnSshSocketDestroyed();

private:
    QxtSshTcpSocket * m_socket; // owner of this object is sshClient
    QSharedPointer<QxtSshClient> m_sshClient;

    bool m_isHostKeyAlreadyAdded;
};
}
