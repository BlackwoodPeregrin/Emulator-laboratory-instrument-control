#include "../headers/emulator.hpp"

#include <random>

namespace Laboratory {

auto Emulator::Run() -> void {
  while (m_is_run) {
    //
    std::unique_lock<std::mutex> ul(m_mutex);
    m_cv.wait_for(ul, std::chrono::seconds(m_sleep_time),
                  [this] { return m_wake_thread; });
    if (!m_command.empty()) {
      auto command = m_command.front();
      if (command.first == Instrument::kPump) {
        // если скорость насоса !0, то запускаем с заданной скоростью
        if (command.second) {
          m_instrument.RunPump(command.second);
          // иначе выключаем насос
        } else {
          m_instrument.StopPump();
        }
      } else if (command.first == Instrument::kD1) {
        // если давление первого датчика !0, то устанавливаем давление
        if (command.second) {
          m_instrument.InstallPressureD1(command.second);
          // иначе сбрасываем давление
        } else {
          m_instrument.ResetPressureD1();
        }
      } else {
        // если давление второго датчика !0, то устанавливаем давление
        if (command.second) {
          m_instrument.InstallPressureD2(command.second);
          // иначе сбрасываем давление
        } else {
          m_instrument.ResetPressureD2();
        }
      }
      m_command.pop();
    } else {
      m_instrument_status.pump_status = m_instrument.GetStatusPump();
      m_instrument_status.pump_speed = m_instrument.GetValueSpeedPump();
      if (m_instrument_status.pump_speed != 0.0) {
        m_instrument_status.pump_speed += RandomNoise();
      }
      m_instrument_status.value_d1 =
          m_instrument.GetValuePressureD1() + RandomNoise();
      m_instrument_status.value_d2 =
          m_instrument.GetValuePressureD2() + RandomNoise();
      m_instrument_status.delta_values =
          m_instrument_status.value_d1 - m_instrument_status.value_d2;
    }
    if (m_wake_thread) {
      m_wake_thread = false;
    }
  }
}

auto Emulator::AddCommand(int instrument, double value) -> void {
  std::unique_lock<std::mutex> ul(m_mutex);
  m_command.push({instrument, value});
}

auto Emulator::ChangeSleepTime(unsigned sleep_time) -> void {
  m_sleep_time = sleep_time;
  m_wake_thread = true;
  m_cv.notify_one();
}

auto Emulator::GetInstrumentStatus() -> InstrumentStatus {
  std::unique_lock<std::mutex> ul(m_mutex);
  return m_instrument_status;
}

auto Emulator::Stop() -> void {
  m_is_run = false;
  m_wake_thread = true;
  m_cv.notify_one();
}

auto Emulator::WaitTime() -> unsigned { return m_sleep_time; }

auto Emulator::RandomNoise() -> double {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_real_distribution<double> random_noise(kMinRandomNoise,
                                                      kMaxRandomNoise);
  return random_noise(gen);
}

};  // namespace Laboratory
