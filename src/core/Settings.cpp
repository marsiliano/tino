#include "Settings.hpp"

bool core::Settings::operator==(const Settings &other) const
{
    return baud_rate == other.baud_rate &&
           break_enabled == other.break_enabled &&
           data_bits == other.data_bits &&
           data_terminal_ready == other.data_terminal_ready &&
           stop_bits == other.stop_bits && flow_control == other.flow_control &&
           request_to_send == other.request_to_send;
}
