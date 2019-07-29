#include "BtnContainer.hpp"

widget::BtnContainer::BtnContainer(core::Byte *val1)
{
    this->val = val1;
    for (int i = 0; i < 8; ++i) {
        b.emplace_back(std::make_pair(
            std::unique_ptr<QPushButton>(new QPushButton()), [i, this]() {
                val->set(i);
                setClr(i);
            }));
    }
    //    ci vorrebbe un modo per mettere in un Btncontainer i button da 0 a 3 e
    //    nell'altro dal 4 al 7, altrimenti entrambi contengono anche i valori
    //    dell'altro
}

void widget::BtnContainer::setClr(const int i)
{
    b[i].first->setStyleSheet((*val)[i] ? "background-color:#ff0000;"
                                        : "background-color:#0000ff;");
}
