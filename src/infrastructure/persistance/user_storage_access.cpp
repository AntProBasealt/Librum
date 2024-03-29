#include "user_storage_access.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include "endpoints.hpp"

namespace infrastructure::persistence
{

void UserStorageAccess::getUser(const QString& authToken)
{
    auto request = createRequest(data::userGetEndpoint, authToken);
    auto reply = m_networkAccessManager.get(request);

    connect(reply, &QNetworkReply::finished, this,
            &UserStorageAccess::proccessGetUserResult);
}

void UserStorageAccess::changeFirstName(const QString& authToken,
                                        const QString& newFirstName)
{
    auto request = createRequest(data::userPatchEndpoint, authToken);

    const QString quote = "\"";
    auto jsonData = R"([{ "op": "replace", "path": "firstName", "value": )" +
                    quote + newFirstName + quote + "}]";

    auto reply = m_networkAccessManager.sendCustomRequest(request, "PATCH",
                                                          jsonData.toUtf8());


    // Make sure to release the reply's memory
    connect(reply, &QNetworkReply::finished, this,
            [this]()
            {
                auto reply = qobject_cast<QNetworkReply*>(sender());
                validateNetworkReply(200, reply, "Changing firstname");

                reply->deleteLater();
            });
}

void UserStorageAccess::changeLastName(const QString& authToken,
                                       const QString& newLastName)
{
    auto request = createRequest(data::userPatchEndpoint, authToken);

    const QString quote = "\"";
    auto jsonData = R"([{ "op": "replace", "path": "lastName", "value": )" +
                    quote + newLastName + quote + "}]";

    auto reply = m_networkAccessManager.sendCustomRequest(request, "PATCH",
                                                          jsonData.toUtf8());


    // Make sure to release the reply's memory
    connect(reply, &QNetworkReply::finished, this,
            [this]()
            {
                auto reply = qobject_cast<QNetworkReply*>(sender());
                validateNetworkReply(200, reply, "Changing lastname");

                reply->deleteLater();
            });
}

void UserStorageAccess::changeEmail(const QString& authToken,
                                    const QString& newEmail)
{
    Q_UNUSED(authToken)
    Q_UNUSED(newEmail)
    // TODO: Implement
}

void UserStorageAccess::changeProfilePicture(const QString& authToken,
                                             const QImage& newProfilePicture)
{
    Q_UNUSED(authToken)
    Q_UNUSED(newProfilePicture)
    // TODO: Implement when filestorage server is up
}

void UserStorageAccess::deleteTag(const QString& authToken, const QString& uuid)
{
    QString endPoint = data::tagDeletionEndpoint + "/" + uuid;
    auto request = createRequest(endPoint, authToken);

    auto reply = m_networkAccessManager.sendCustomRequest(request, "DELETE");


    // Make sure to release the reply's memory
    connect(reply, &QNetworkReply::finished, this,
            [this]()
            {
                auto reply = qobject_cast<QNetworkReply*>(sender());
                validateNetworkReply(204, reply, "Deleting tag");

                reply->deleteLater();
            });
}

void UserStorageAccess::renameTag(const QString& authToken,
                                  const QJsonObject& bookForUpdate)
{
    QString endPoint = data::tagUpdateEndpoint;
    auto request = createRequest(endPoint, authToken);

    QJsonDocument jsonDoc(bookForUpdate);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);

    auto reply =
        m_networkAccessManager.sendCustomRequest(request, "PUT", jsonData);


    // Make sure to release the reply's memory
    connect(reply, &QNetworkReply::finished, this,
            [this]()
            {
                auto reply = qobject_cast<QNetworkReply*>(sender());
                validateNetworkReply(201, reply, "Renaming tag");

                reply->deleteLater();
            });
}

void UserStorageAccess::proccessGetUserResult()
{
    auto reply = qobject_cast<QNetworkReply*>(sender());
    auto status = validateNetworkReply(200, reply, "Getting User");
    if(!status.success)
    {
        emit gettingUserFailed();
        return;
    }

    auto jsonDoc = QJsonDocument::fromJson(reply->readAll());
    auto jsonObj = jsonDoc.object();

    auto firstName = jsonObj["firstName"].toString();
    auto lastName = jsonObj["lastName"].toString();
    auto usedBookStorage =
        static_cast<long>(jsonObj["usedBookStorage"].toDouble());
    auto bookStorageLimit =
        static_cast<long>(jsonObj["bookStorageLimit"].toDouble());
    auto email = jsonObj["email"].toString();
    auto tags = jsonObj["tags"].toArray();

    emit userReady(firstName, lastName, email, usedBookStorage,
                   bookStorageLimit, tags);

    // Make sure to release the reply's memory
    reply->deleteLater();
}

QNetworkRequest UserStorageAccess::createRequest(const QUrl& url,
                                                 const QString& authToken)
{
    QNetworkRequest result { url };
    result.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    result.setRawHeader("X-Version", "1.0");
    result.setRawHeader(QByteArray("Authorization"),
                        "Bearer " + authToken.toUtf8());

    QSslConfiguration sslConfiguration = result.sslConfiguration();
    sslConfiguration.setProtocol(QSsl::AnyProtocol);
    sslConfiguration.setPeerVerifyMode(QSslSocket::QueryPeer);
    result.setSslConfiguration(sslConfiguration);

    return result;
}

ServerReplyStatus UserStorageAccess::validateNetworkReply(
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

}  // namespace infrastructure::persistence