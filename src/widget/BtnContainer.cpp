#include "BtnContainer.hpp"

BtnContainer::BtnContainer()
{
    b.reserve(8);
}

void BtnContainer::set(const int i)
{
    val.set(i);
    setClr(i);
}

void BtnContainer::setClr(const int i)
{
    if (val[i])
        b[i]->setStyleSheet("background-color:#ff0000;");
    else
        b[i]->setStyleSheet("background-color:#0000ff;");
}
