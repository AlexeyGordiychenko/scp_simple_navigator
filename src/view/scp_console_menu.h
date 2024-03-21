#ifndef SCP_A2_CONSOLE_MENU_H_
#define SCP_A2_CONSOLE_MENU_H_

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace scp {

class ConsoleMenu {
 public:
  ConsoleMenu(
      const std::string& message, const std::string& invalid_choice_message,
      const std::string& prompt,
      const std::vector<std::pair<std::string_view, std::function<void()>>>&
          commands,
      std::istream& in = std::cin, std::ostream& out = std::cout);
  ConsoleMenu(const ConsoleMenu&) = delete;
  ConsoleMenu& operator=(const ConsoleMenu&) = delete;
  ConsoleMenu(ConsoleMenu&&) = delete;
  ConsoleMenu& operator=(ConsoleMenu&&) = delete;
  ~ConsoleMenu() = default;

  void operator()() const;

  void SetCurrentFile(const std::string& filename);
  void PrintVector(const std::vector<uint32_t>& v, const std::string& desc);
  void PrintMatrix(const std::pair<std::vector<uint32_t>, uint32_t>& data,
                   const std::string& desc);
  void PrintValue(const uint32_t value, const std::string& desc);

  template <typename... Args, typename... Prompts, std::size_t... I>
  void CallMenuFunctionImpl(std::function<void(Args...)> func,
                            std::tuple<Prompts...> prompts,
                            std::index_sequence<I...>) {
    std::tuple<Args...> args_tuple;
    try {
      // Validate and store inputs in args_tuple
      std::apply(
          [&](auto&&... args) {
            (ValidateInput(args, std::get<I>(prompts)), ...);
          },
          args_tuple);

      // Call the function with the validated inputs
      std::apply([&func](auto&&... args) { func(args...); }, args_tuple);
    } catch (const std::exception& e) {
      out_ << kRed << kBold << e.what() << kResetColor << '\n';
    }
  }

  template <typename... Args, typename... Prompts>
  void CallMenuFunction(std::function<void(Args...)> func,
                        std::tuple<Prompts...> prompts) {
    CallMenuFunctionImpl(func, prompts,
                         std::make_index_sequence<sizeof...(Args)>{});
  }

  template <typename... Funcs>
  void MeasureFunctionsTime(uint32_t n, Funcs... funcs) {
    (MeasureSingleFunctionTime(n, funcs), ...);
  }

 private:
  std::string invalid_choice_message_;
  std::string prompt_;
  std::string current_file_info_;
  std::vector<std::pair<std::string_view, std::function<void()>>> commands_;
  std::istream& in_;
  std::ostream& out_;

  // Colors
  const std::string kRed = "\033[0;31m";
  const std::string kGreen = "\033[0;32m";
  const std::string kYellow = "\033[0;33m";
  const std::string kBold = "\033[1m";
  const std::string kResetColor = "\033[0m";

  template <typename T>
  void ValidateInput(T& arg, const std::string& prompt) {
    auto valid_input = false;
    while (!valid_input && out_ << prompt) {
      if constexpr (std::is_same_v<T, std::string>) {
        in_.clear();
        in_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        valid_input = (std::getline(in_, arg)) ? true : false;
      } else {
        valid_input = (in_ >> arg && in_.peek() == '\n');
      }

      if (!valid_input) {
        in_.clear();
        in_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        out_ << invalid_choice_message_;
      }
    }
  }

  template <typename Func>
  void MeasureSingleFunctionTime(
      uint32_t n, const std::pair<Func, std::string>& func_text_pair) {
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t i = 0; i < n; ++i) {
      func_text_pair.first();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    out_ << kGreen << kBold << "Execution time for " << func_text_pair.second
         << ": " << std::fixed << std::setprecision(3)
         << (duration.count() / 1000.0) << " seconds" << kResetColor
         << std::endl;
  }
};
}  // namespace scp
#endif  // SCP_A2_CONSOLE_MENU_H_
