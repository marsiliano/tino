#include "ConfigParser.hpp"

#include "ParserImplJson.hpp"
#include "ParserImplXlsx.hpp"

#include <QtDebug>

static const QString jsonExt(".json");
static const QString xlsxExt(".xlsx");

ConfigParser::ConfigParser(const QString &filename)
{
    if (filename.contains(jsonExt)) {
        m_impl = std::make_unique<ParserImplJson>();
        m_filename = filename;
    }

    if (filename.contains(xlsxExt)) {
        m_impl = std::make_unique<ParserImplXlsx>();
        m_filename = filename;
    }

    if (m_impl == nullptr) {
        qWarning() << "No implementation selected";
    }
}

Configuration ConfigParser::parse()
{
    if (m_impl == nullptr) {
        throw std::logic_error("Implementation not allocated");
    }

    return m_impl->parse(m_filename);
}
