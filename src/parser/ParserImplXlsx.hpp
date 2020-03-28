#pragma once

#include "IParserImplementation.hpp"

class Bitset;
class UWord;
class SWord;

namespace QXlsx {
    class Document;
}

class ParserImplXlsx final: public IParserImplementation {

public:
    Configuration parse(const QString &filename) override;

private:
    enum XlsxColumns {
        Resource = 1,
        DefaultValue,

        PlaceHolder
    };

    struct Tags
    {
        static constexpr auto digitalInputs = "DIGITAL INPUTS";
        static constexpr auto digitalOutputs = "DIGITAL OUTPUTS";
        static constexpr auto analogInputs = "ANALOGIC INPUTS";
        static constexpr auto analogOutputs = "ANALOGIC OUTPUTS";
        static constexpr auto encoders = "ENCODERS";
    };

    Block readDigitalResource(const QXlsx::Document &doc, const QString &resource);
    Block readInputs(const QXlsx::Document &doc);
    int searchTag(const QXlsx::Document &doc, const QString &tag);
    bool isTag(const QString &item);

    std::unique_ptr<Bitset> makeBitset(const QString &obj, const Block &b = Block()) const;
    std::unique_ptr<UWord> makeUWord(const QString &obj, const Block &b = Block()) const;
    std::unique_ptr<SWord> makeSWord(const QString &obj, const Block &b = Block()) const;
};
