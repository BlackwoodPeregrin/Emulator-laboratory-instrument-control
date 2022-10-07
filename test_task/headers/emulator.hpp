#pragma once
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

#include "laboratory_instrument.hpp"

namespace Laboratory {

enum Instrument { kPump = 1, kD1, kD2 };

constexpr unsigned kDefaultSleepTimeSec = 5;
constexpr double kMinRandomNoise = 0.01;
constexpr double kMaxRandomNoise = 1.0;

class Emulator {
 public:
  Emulator() = default;
  ~Emulator() = default;

  auto Run() -> void;

  auto AddCommand(int instrument, double value = 0.0) -> void;

  auto ChangeSleepTime(unsigned sleep_time) -> void;

  auto GetInstrumentStatus() -> InstrumentStatus;

  auto Stop() -> void;

  auto WaitTime() -> unsigned;

  auto RandomNoise() -> double;

 private:
  //
  LaboratoryInstrument m_instrument;
  InstrumentStatus m_instrument_status;
  //
  std::queue<std::pair<int, double>> m_command;
  std::atomic<unsigned> m_sleep_time{kDefaultSleepTimeSec};
  bool m_is_run{true};
  bool m_wake_thread{true};
  std::mutex m_mutex;
  std::condition_variable m_cv;
};
}  // namespace Laboratory
