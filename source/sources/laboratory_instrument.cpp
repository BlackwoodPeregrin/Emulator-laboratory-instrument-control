#include "../headers/laboratory_instrument.hpp"

namespace Laboratory {
LaboratoryInstrument::LaboratoryInstrument(LaboratoryInstrument const &other) {
  *this = other;
}

LaboratoryInstrument::LaboratoryInstrument(LaboratoryInstrument &&other) {
  *this = std::move(other);
}

LaboratoryInstrument &LaboratoryInstrument::operator=(
    LaboratoryInstrument const &other) {
  if (this != &other) {
    m_speed_pump = other.m_speed_pump;
    m_meter_d1 = other.m_meter_d1;
    m_meter_d2 = other.m_meter_d2;
  }
  return *this;
}

LaboratoryInstrument &LaboratoryInstrument::operator=(
    LaboratoryInstrument &&other) {
  if (this != &other) {
    std::swap(m_speed_pump, other.m_speed_pump);
    std::swap(m_meter_d1, other.m_meter_d1);
    std::swap(m_meter_d2, other.m_meter_d2);
  }
  return *this;
}

auto LaboratoryInstrument::RunPump(double speed) -> void {
  m_speed_pump = speed;
}

auto LaboratoryInstrument::StopPump() -> void { m_speed_pump = 0.0; }

auto LaboratoryInstrument::GetValueSpeedPump() -> double {
  return m_speed_pump;
}

auto LaboratoryInstrument::GetStatusPump() -> std::string {
  if (m_speed_pump) {
    return "Скорость";
  }
  return "Остановлен";
}
//
auto LaboratoryInstrument::InstallPressureD1(double value) -> void {
  m_meter_d1 = value;
}

auto LaboratoryInstrument::ResetPressureD1() -> void { m_meter_d1 = 0.0; }

auto LaboratoryInstrument::GetValuePressureD1() -> double { return m_meter_d1; }

auto LaboratoryInstrument::InstallPressureD2(double value) -> void {
  m_meter_d2 = value;
}

auto LaboratoryInstrument::ResetPressureD2() -> void { m_meter_d2 = 0.0; }

auto LaboratoryInstrument::GetValuePressureD2() -> double { return m_meter_d2; }

}  // namespace Laboratory
