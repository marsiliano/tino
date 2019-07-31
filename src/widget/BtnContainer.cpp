#include "BtnContainer.hpp"

QString widget::BtnContainer::clrOn  = "background-color:#ff0000;";
QString widget::BtnContainer::clrOff = "background-color:#0000ff;";

widget::BtnContainer::BtnContainer(core::Byte *val1, int off)
{
    this->offset = off;
    this->val    = val1;

    for (int i = 0; i < 4; ++i) {
        b.emplace_back(std::make_pair(
            std::unique_ptr<QPushButton>(new QPushButton()), [i, this]() {
                val->set(i + offset);
                setClr(i);
            }));
        setClr(i);
    }
}

void widget::BtnContainer::setClr(int i)
{
    b[i].first->setStyleSheet((*val)[i + offset] ? clrOn : clrOff);
}
