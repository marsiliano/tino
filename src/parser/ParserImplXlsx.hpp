#pragma once

#include "IParserImplementation.hpp"

namespace QXlsx {
    class Document;
}

class ParserImplXlsx final: public IParserImplementation {

public:
    Configuration parse(const QString &filename) override;

private:
    friend class tst_ParserXlsx;

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
    Block readAnalogResource(const QXlsx::Document &doc, const QString &resource);
    int searchTag(const QXlsx::Document &doc, const QString &tag);
    bool isTag(const QString &item);
};
