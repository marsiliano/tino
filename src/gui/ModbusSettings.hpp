#pragma once

#include <QMainWindow>

class ModbusSettings : public QMainWindow
{
    Q_OBJECT

  public:
    explicit ModbusSettings(QMainWindow *parent = nullptr);
    ~ModbusSettings() = default;
};
