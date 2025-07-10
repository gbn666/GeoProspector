#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

#include <QObject>
#include <QImage>
#include <QByteArray>

class SerialComm;

class ImageUploader : public QObject
{
    Q_OBJECT

public:
    explicit ImageUploader(SerialComm *serial,
                           const QString &serverHost,
                           const QString &serverPort,
                           const QString &ssid,
                           const QString &password,
                           QObject *parent = nullptr);
    ~ImageUploader();

    /// 启动连接并上传图片
    void checkNetworkAndUpload(const QImage &image);

signals:
    /// 网络或上传出错
    void errorOccurred(const QString &msg);
    /// 识别完成后返回纯 JSON 字符串
    void recognitionResult(const QString &result);

private:
    bool ensureConnection();
    bool uploadImage(const QImage &image);
    void connectSignals();

    SerialComm *m_serial;
    QString      m_serverHost;
    QString      m_serverPort;
    QString      m_ssid;
    QString      m_password;
    QByteArray  *m_responseBuffer;
};

#endif // IMAGEUPLOADER_H

