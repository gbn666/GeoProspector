#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

#include "serialcomm.h"
#include <QImage>
#include <QByteArray>
#include <QObject>

class ImageUploader : public QObject {
    Q_OBJECT
public:
    ImageUploader(SerialComm *serial,
                  const QString &serverHost,
                  const QString &serverPort,
                  const QString &ssid,
                  const QString &password,
                  QObject *parent = nullptr);
    ~ImageUploader();

    void checkNetworkAndUpload(const QImage &image);

signals:
    void recognitionResult(const QString &label);
    void errorOccurred(const QString &errorMsg);

private:
    bool ensureConnection();
    bool uploadImage(const QImage &image);
    void connectSignals();

    SerialComm *m_serial;
    QString m_serverHost;
    QString m_serverPort;
    QString m_ssid;
    QString m_password;
    QByteArray *m_responseBuffer;
};

#endif // IMAGEUPLOADER_H
