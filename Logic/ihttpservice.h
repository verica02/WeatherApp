#ifndef IHTTPSERVICE_H
#define IHTTPSERVICE_H

#include <QStringList>
#include <QObject>

/** @brief Http service interface */
struct IHTTPService : public QObject
{
    Q_OBJECT
public:
    explicit IHTTPService(QObject *parent=nullptr) : QObject(parent){}
    virtual ~IHTTPService(){}
    enum class ErrorCode {
        OK,
        NOT_OK
    };

    virtual void setQueryString(QStringList) = 0;
    virtual void setBaseUrl(QString) = 0;

public slots:
    virtual void get() = 0;

signals:
    void finished(QString replyBody,  ErrorCode errCode);
};

#endif // IHTTPSERVICE_H
