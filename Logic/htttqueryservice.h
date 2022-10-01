#ifndef HTTTQUERYSERVICE_H
#define HTTTQUERYSERVICE_H
#include "ihttpservice.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class HttpQueryService : public IHTTPService
{
public:
    explicit HttpQueryService(QObject *parent = nullptr);

    void setQueryString(QStringList) override;
    void setBaseUrl(QString) override;

public slots:
    void get() override;

private slots:
    void onNetworkReply(QNetworkReply *);

private:
    QNetworkAccessManager networkAccessManager;
    QNetworkRequest networkRequest;
    QString baseUrl;
    QStringList query;
};

#endif // HTTTQUERYSERVICE_H
