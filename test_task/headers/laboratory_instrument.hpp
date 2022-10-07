#pragma once

#include <iostream>

namespace Laboratory {

struct InstrumentStatus {
  std::string pump_status{};      // режим работы насоса
  double pump_speed{};            // скорость работы насоса
  double value_d1{}, value_d2{};  // давление датчиков Д1 Д2
  double delta_values{};  // Разность давления Д1 минус Д2.
};

class LaboratoryInstrument {
 public:
  LaboratoryInstrument() = default;
  LaboratoryInstrument(LaboratoryInstrument const &other);
  LaboratoryInstrument(LaboratoryInstrument &&other);
  LaboratoryInstrument &operator=(LaboratoryInstrument const &other);
  LaboratoryInstrument &operator=(LaboratoryInstrument &&other);
  ~LaboratoryInstrument() = default;

  auto RunPump(double speed) -> void;

  auto StopPump() -> void;

  auto GetValueSpeedPump() -> double;

  auto GetStatusPump() -> std::string;
  //
  auto InstallPressureD1(double value) -> void;

  auto ResetPressureD1() -> void;

  auto GetValuePressureD1() -> double;

  auto InstallPressureD2(double value) -> void;

  auto ResetPressureD2() -> void;

  auto GetValuePressureD2() -> double;

 private:
  // скорость насоса
  double m_speed_pump{};
  // датчики давления
  double m_meter_d1{}, m_meter_d2{};
};
}  // namespace Laboratory
