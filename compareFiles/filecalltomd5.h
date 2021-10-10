#ifndef FILECALLTOMD5_H
#define FILECALLTOMD5_H
#include <QObject>

class fileCallToMd5 : public QObject
{
    Q_OBJECT
public:
    explicit fileCallToMd5(QObject *parent = nullptr);

    QString openDirectory();
    QByteArray getFileData(const QString &path);
    QString getSigFileMd5(const QByteArray &fileData);
    QString getFileMd5(const QString &path);
    QStringList getFiles(const QString &path);
signals:
    void signalGetFileMd5();
};

#endif // FILECALLTOMD5_H
