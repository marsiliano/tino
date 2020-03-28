#include "ParserImplXlsx.hpp"

#include "Configuration.hpp"
#include "../core/Bitset.hpp"
#include "../core/DoubleSWord.hpp"

#include <xlsx/xlsxdocument.h>

#include <QtDebug>

Configuration ParserImplXlsx::parse(const QString &filename)
{
    QXlsx::Document xlsx(filename);

    if (xlsx.dimension().lastRow() <= 0 ||
        xlsx.dimension().lastColumn() < ParserImplXlsx::DefaultValue) {
        qWarning() << "File not valid";
    }

    Protocol protocol;

    protocol.blocks.emplace_back(readDigitalResource(xlsx, Tags::digitalInputs));
    protocol.blocks.emplace_back(readDigitalResource(xlsx, Tags::digitalOutputs));
    protocol.blocks.emplace_back(readAnalogResource(xlsx, Tags::analogInputs));
    protocol.blocks.emplace_back(readAnalogResource(xlsx, Tags::analogOutputs));
    protocol.blocks.emplace_back(readAnalogResource(xlsx, Tags::encoders));

    return Configuration{{}, std::move(protocol)};
}

Block ParserImplXlsx::readDigitalResource(const QXlsx::Document &doc,
                                          const QString &resource)
{
    const auto rows = doc.dimension().lastRow();
    const auto firstRow = searchTag(doc, resource);

    if (firstRow == -1) {
        return {};
    }

    Block block;
    block.description = resource;

    Bitset bitset({},{}, 0);
    uint8_t bitsetCounter = 0;

    for (auto i = (firstRow + 1); i <= rows; i++, bitsetCounter++) {
        QString resource = doc.read(i, Resource).toString();
        if (resource.isEmpty() || isTag(resource)) {
            break;
        }

        if (bitsetCounter >= Bitset::size) {
            block.elements.emplace_back(std::make_shared<Bitset>(bitset));
            bitsetCounter = 0;
            bitset.clear();
        }

        QString value = doc.read(i, DefaultValue).toString();
        bitset.setAt(bitsetCounter, value.toInt() == 1, resource);
    }

    //Add last bitset
    if (!block.elements.empty()) {
        block.elements.emplace_back(std::make_shared<Bitset>(bitset));
    }

    return block;
}

Block ParserImplXlsx::readAnalogResource(const QXlsx::Document &doc,
                                         const QString &resource)
{
    const auto rows = doc.dimension().lastRow();
    const auto firstRow = searchTag(doc, resource);

    if (firstRow == -1) {
        return {};
    }

    Block block;
    block.description = resource;

    for (auto i = (firstRow + 1); i <= rows; i++) {
        QString resource = doc.read(i, Resource).toString();
        if (resource.isEmpty() || isTag(resource)) {
            break;
        }

        QString value = doc.read(i, DefaultValue).toString();
        DoubleSWord word(resource, {}, {}, value.toInt());
        block.elements.emplace_back(std::make_shared<DoubleSWord>(word));
    }

    return block;
}

int ParserImplXlsx::searchTag(const QXlsx::Document &doc, const QString &tag)
{
    const auto rows = doc.dimension().lastRow();

    for (auto i = 1; i <= rows; i++) {
        QString cell = doc.read(i, ParserImplXlsx::Resource).toString();
        if (cell.contains(tag)) {
            return i;
        }
    }

    return -1;
}

bool ParserImplXlsx::isTag(const QString &item)
{
    return (item.contains(Tags::digitalInputs) || item.contains(Tags::digitalOutputs) ||
            item.contains(Tags::analogInputs) || item.contains(Tags::analogOutputs) ||
            item.contains(Tags::encoders));
}
