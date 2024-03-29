#include "authentication_access.hpp"
#include "endpoints.hpp"


using namespace adapters::dtos;

namespace infrastructure::persistence
{

void AuthenticationAccess::authenticateUser(const LoginDto& loginDto)
{
    auto request = createRequest(data::authenticationEndpoint);

    QJsonObject jsonObject;
    jsonObject["email"] = loginDto.email;
    jsonObject["password"] = loginDto.password;

    QJsonDocument jsonDocument { jsonObject };
    QByteArray data = jsonDocument.toJson(QJsonDocument::Compact);


    auto reply = m_networkAccessManager.post(request, data);


    // Handle authentication result and release the reply's memory
    connect(reply, &QNetworkReply::finished, this,
            [this]()
            {
                auto reply = qobject_cast<QNetworkReply*>(sender());

                auto res = validateNetworkReply(200, reply, "Authentication");
                if(!res.success)
                {
                    emit authenticationFinished("");

                    reply->deleteLater();
                    return;
                }

                emit authenticationFinished(reply->readAll());
                reply->deleteLater();
            });
}

void AuthenticationAccess::registerUser(const RegisterDto& registerDto)
{
    auto request = createRequest(data::registrationEndpoint);

    QJsonObject jsonObject;
    jsonObject["firstName"] = registerDto.firstName;
    jsonObject["lastName"] = registerDto.lastName;
    jsonObject["email"] = registerDto.email;
    jsonObject["password"] = registerDto.password;

    QJsonDocument jsonDocument { jsonObject };
    QByteArray data = jsonDocument.toJson(QJsonDocument::Compact);


    auto reply = m_networkAccessManager.post(request, data);


    // Handle registration result and release the reply's memory
    connect(reply, &QNetworkReply::finished, this,
            [this]()
            {
                auto reply = qobject_cast<QNetworkReply*>(sender());

                auto res = validateNetworkReply(201, reply, "Registration");
                if(!res.success)
                {
                    emit registrationFinished(false, res.errorMessage);

                    reply->deleteLater();
                    return;
                }

                emit registrationFinished(true, "");
                reply->deleteLater();
            });
}

ServerReplyStatus AuthenticationAccess::validateNetworkReply(
    int expectedStatusCode, QNetworkReply* reply, const QString& name)
{
    auto statusCode =
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();


    if(reply->error() != QNetworkReply::NoError ||
       expectedStatusCode != statusCode)
    {
        auto content = reply->readAll();
        qWarning() << name + " failed: " + content;

        return ServerReplyStatus {
            .success = false,
            .errorMessage = content,
        };
    }

    return ServerReplyStatus { .success = true };
}

QNetworkRequest AuthenticationAccess::createRequest(QUrl url)
{
    QNetworkRequest result { url };
    result.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    result.setRawHeader("X-Version", "1.0");

    QSslConfiguration sslConfiguration = result.sslConfiguration();
    sslConfiguration.setProtocol(QSsl::AnyProtocol);
    sslConfiguration.setPeerVerifyMode(QSslSocket::QueryPeer);
    result.setSslConfiguration(sslConfiguration);

    return result;
}

}  // namespace infrastructure::persistence