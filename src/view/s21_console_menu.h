#ifndef S21_A2_MENU_H_
#define S21_A2_MENU_H_

#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace s21 {

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

  void PrintVector(const std::vector<uint32_t>& v);
  void PrintMatrix(const std::pair<std::vector<uint32_t>, uint32_t>& data);

  template <typename... Args, typename... Prompts, std::size_t... I>
  void FunctionWithArgsImpl(std::function<void(Args...)> func,
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
      out << e.what() << '\n';
    }
  }

  template <typename... Args, typename... Prompts>
  void FunctionWithArgs(std::function<void(Args...)> func,
                        std::tuple<Prompts...> prompts) {
    FunctionWithArgsImpl(func, prompts,
                         std::make_index_sequence<sizeof...(Args)>{});
  }

 private:
  std::string invalid_choice_message_;
  std::string prompt_;
  std::vector<std::pair<std::string_view, std::function<void()>>> commands_;
  std::istream& in;
  std::ostream& out;
  template <typename T>
  void ValidateInput(T& arg, const std::string& prompt) {
    auto valid_input = false;
    while (!valid_input && out << prompt) {
      if constexpr (std::is_same_v<T, std::string>) {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        valid_input = (std::getline(in, arg)) ? true : false;
      } else {
        valid_input = (in >> arg && in.peek() == '\n');
      }

      if (!valid_input) {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        out << invalid_choice_message_;
      }
    }
  }
};
}  // namespace s21
#endif  // S21_A2_MENU_H_
