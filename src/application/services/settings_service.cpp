#include "settings_service.hpp"
#include <QDebug>
#include <QFile>
#include <QHash>
#include <QJsonDocument>
#include <QJsonObject>

namespace application::services
{

SettingsService::SettingsService(
    ISettingsStorageGateway* settingsStorageGateway) :
    m_settingsStorageGateway(settingsStorageGateway)
{
}

QString SettingsService::getSetting(const QString& settingName)
{
    auto defaultValue = QVariant::fromValue(QString(""));
    return m_settings->value(settingName.toLower(), defaultValue).toString();
}

void SettingsService::setSetting(const QString& settingName,
                                 const QString& value)
{
    auto dataToSet = QVariant::fromValue(value.toLower());

    m_settings->setValue(settingName.toLower(), dataToSet);
    m_settingsStorageGateway->updateSettings(m_authToken, getSettingsAsBytes());
}

void SettingsService::loadUserSettings(const QString& token,
                                       const QString& email)
{
    Q_UNUSED(token);
    m_userEmail = email;

    createSettings();
}

void SettingsService::clearUserData()
{
    m_userEmail.clear();
}

void SettingsService::createSettings()
{
    auto uniqueFileName = getUniqueUserHash();
    auto format = QSettings::NativeFormat;
    m_settings = std::make_unique<QSettings>(uniqueFileName, format);

    generateDefaultSettings();
}

QString SettingsService::getUniqueUserHash() const
{
    auto userHash = qHash(m_userEmail);

    return QString::number(userHash);
}

void SettingsService::generateDefaultSettings()
{
    QJsonObject defaultSettings = getDefaultSettings();
    for(const auto& settingKey : defaultSettings.keys())
    {
        if(m_settings->contains(settingKey))
            continue;

        auto settingValue = defaultSettings.value(settingKey).toString();
        setSetting(settingKey, settingValue);
    }
}

QJsonObject SettingsService::getDefaultSettings()
{
    QFile defaultSettingsFile(m_defaultSettingsFile);
    if(!defaultSettingsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open default settings file!";
    }

    QByteArray rawJson = defaultSettingsFile.readAll();
    auto jsonDoc = QJsonDocument::fromJson(rawJson);
    return jsonDoc.object();
}

QByteArray SettingsService::getSettingsAsBytes()
{
    QFile settingsFile(m_settings->fileName());
    if(!settingsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open settings file!";
    }

    return settingsFile.readAll();
}

}  // namespace application::services