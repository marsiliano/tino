#include "GuiElement.hpp"

#include "Led.hpp"
#include "ValueWidget.hpp"

void GuiElement::resetToDefault()
{
    for (auto &w : widgets) {
        if (auto led = dynamic_cast<Led *>(w)) {
            led->resetToDefault();
        }

        if (auto valueWidget = dynamic_cast<ValueWidget *>(w)) {
            valueWidget->resetToDefault();
        }
    }
}
