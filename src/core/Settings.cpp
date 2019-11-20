#include "Settings.hpp"

bool Settings::operator==(const Settings &other) const
{
    return port_name == other.port_name && baud_rate == other.baud_rate &&
           break_enabled == other.break_enabled &&
           data_bits == other.data_bits &&
           data_terminal_ready == other.data_terminal_ready &&
           stop_bits == other.stop_bits && flow_control == other.flow_control &&
           request_to_send == other.request_to_send;
}
