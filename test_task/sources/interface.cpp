#include "../headers/interface.hpp"

namespace Laboratory {

auto MainWindow::Start() -> void {
  std::thread th1([this]() { m_emulator.Run(); });
  Show_();
  m_emulator.Stop();
  th1.join();
}

auto MainWindow::Show_() -> void {
  bool exit{false};
  while (!exit) {
    system("clear");
    PrintMessage_(
        "============ Laboratory ============\n"
        "1. Команды для насоса\n"
        "2. Команды для датчика давления Д1\n"
        "3. Команды для датчика давления Д2\n"
        "4. Изменить период ожидания обработчика (" +
        std::to_string(m_emulator.WaitTime()) +
        " сек.)\n"
        "5. Вывести текущее состояние прибора\n"
        "6. Закрыть программу");
    ScanMainInput_(exit);
  }
}

auto MainWindow::ScanMainInput_(bool &exit) -> void {
  std::string answer{};
  std::cin >> answer;

  if (answer == "1") {
    ShowInterfacePumpSets_();
  } else if (answer == "2") {
    ShowInterfaceMeterSets_(Instrument::kD1);
  } else if (answer == "3") {
    ShowInterfaceMeterSets_(Instrument::kD2);
  } else if (answer == "4") {
    int sleep_time = ScanValue_("Введите желаемый период ожидания(сек.)");
    if (sleep_time > 0) {
      m_emulator.ChangeSleepTime(sleep_time);
      PrintPauseMessege_("Установлено");
    } else {
      PrintPauseMessege_("Период ожидания должен быть больше нуля.");
    }
  } else if (answer == "5") {
    PrintCurrentInstrumentStatus_();
  } else if (answer == "6") {
    exit = true;
  } else {
    PrintPauseMessege_("Неккоректный ввод, попробуйте снова...");
  }
}

auto MainWindow::ShowInterfacePumpSets_() -> void {
  bool back_to_menu{false};
  while (!back_to_menu) {
    system("clear");
    PrintMessage_(
        "============ "
        "Команды для насоса ============\n"
        "1. Включить с заданной скоростью\n"
        "2. Остановить\n"
        "3. Выйти назад в меню");
    ScanPumpInput_(back_to_menu);
  }
}

auto MainWindow::ShowInterfaceMeterSets_(int instrument) -> void {
  std::string name_sensor{std::to_string(instrument - 1) + " "};
  bool back_to_menu{false};
  while (!back_to_menu) {
    system("clear");
    PrintMessage_("============ Команды для датчика Д" + name_sensor +
                  "============\n"
                  "1. Установить  давление\n"
                  "2. Сбросить давление в ноль\n"
                  "3. Выйти назад в меню");
    ScanMeterInput_(back_to_menu, instrument);
  }
}

auto MainWindow::ScanPumpInput_(bool &button_back) -> void {
  std::string answer{};
  std::cin >> answer;
  if (answer == "1") {
    double speed = ScanValue_("Введите скорость работы насоса");
    if (speed > 0) {
      // добавляем команду зпустить насос с заданной скоростью в очередь
      m_emulator.AddCommand(Instrument::kPump, speed);
      PrintPauseMessege_("Команда отправлена в очередь");
    } else {
      PrintPauseMessege_("Скорость работы насоса должна быть больше 0.");
    }
  } else if (answer == "2") {
    // добавляем команду остановить насос в очередь
    m_emulator.AddCommand(Instrument::kPump);
    PrintPauseMessege_("Команда отправлена в очередь");
  } else if (answer == "3") {
    // вернуться в главное меню
    button_back = true;
  } else {
    PrintPauseMessege_("Неккоректный ввод, попробуйте снова...");
  }
}

auto MainWindow::ScanMeterInput_(bool &button_back, int instrument) -> void {
  std::string answer{};
  std::cin >> answer;

  if (answer == "1") {
    double pressure = ScanValue_("Введите значение давления");
    if (pressure > 0) {
      // добавляем команду устанвоить значение давление в очередь
      m_emulator.AddCommand(instrument, pressure);
      PrintPauseMessege_("Команда отправлена в очередь");
    } else {
      PrintPauseMessege_("Значение даления должно быть больше 0.");
    }
  } else if (answer == "2") {
    // добавляем команду сбросить давление в очередь
    m_emulator.AddCommand(instrument);
    PrintPauseMessege_("Команда отправлена в очередь");
  } else if (answer == "3") {
    // вернуться в главное меню
    button_back = true;
  } else {
    PrintPauseMessege_("Неккоректный ввод, попробуйте снова...");
  }
}

auto MainWindow::ScanValue_(std::string const &message) -> double {
  PrintMessage_(message);
  double speed{};
  std::string value{};
  std::cin >> value;
  try {
    speed = std::stod(value);
  } catch (const std::exception &e) {
    speed = -1.0;
  }
  return speed;
}

auto MainWindow::PrintMessage_(std::string const &massege) -> void {
  std::cout << massege << '\n';
}

auto MainWindow::PrintPauseMessege_(std::string const &massege) -> void {
  std::cout << massege << '\n';
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

auto MainWindow::PrintCurrentInstrumentStatus_() -> void {
  auto instrument_status = m_emulator.GetInstrumentStatus();

  PrintMessage_("Насос\nТекущий режим работы:\t\t'" +
                instrument_status.pump_status + "'\n" +
                "Текущая скорость:\t\t" +
                std::to_string(instrument_status.pump_speed) + "\n" +
                "Текущее давление датчика Д1:\t" +
                std::to_string(instrument_status.value_d1) + "\n" +
                "Текущее давление датчика Д2:\t" +
                std::to_string(instrument_status.value_d2) + "\n" +
                "Разность давления Д1 минус Д2:\t" +
                std::to_string(instrument_status.delta_values));
  std::this_thread::sleep_for(std::chrono::seconds(2));
}

}  // namespace Laboratory
