#include "Mask.hpp"

#include <QtWidgets/QLabel>

class GroupWidget : public QWidget
{
    Q_OBJECT
  public:
    GroupWidget(core::Group val, QWidget *parent = nullptr);
    ~GroupWidget() {}
};