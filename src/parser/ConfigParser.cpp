#include "ConfigParser.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

core::Settings ConfigParser::parse(const QString &filename)
{
    QFile file{ filename };
    if (!file.exists()) {
        throw std::logic_error("file not exists");
    }

    if (!file.open(QIODevice::ReadOnly)) {
        throw std::logic_error("can't open file");
    }

    QJsonParseError error;
    const auto content = file.readAll();
    auto doc           = QJsonDocument::fromJson(content, &error);
    if (error.error != QJsonParseError::NoError) {
        throw std::logic_error("error parsing json " +
                               std::to_string(error.error));
    }

    core::Settings set;
    auto settings = doc.object().find("settings");
    //    if (!settings->isObject()) {
    //        return {};
    //    }
    return {};
}
