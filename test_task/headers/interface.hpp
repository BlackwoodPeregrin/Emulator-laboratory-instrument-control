#pragma once

#include "emulator.hpp"

namespace Laboratory {
class MainWindow {
 public:
  auto Start() -> void;

 protected:
  auto Show_() -> void;

  auto ScanMainInput_(bool &exit) -> void;

  auto ShowInterfacePumpSets_() -> void;

  auto ShowInterfaceMeterSets_(int instrument) -> void;

  auto ScanPumpInput_(bool &button_back) -> void;

  auto ScanMeterInput_(bool &button_back, int instrument) -> void;

  auto ScanValue_(std::string const &message) -> double;

  auto PrintMessage_(std::string const &massege) -> void;

  auto PrintPauseMessege_(std::string const &massege) -> void;

  auto PrintCurrentInstrumentStatus_() -> void;

 private:
  Emulator m_emulator;
};
}  // namespace Laboratory
