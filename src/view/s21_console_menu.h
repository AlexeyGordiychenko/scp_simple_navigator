#ifndef S21_A2_MENU_H_
#define S21_A2_MENU_H_

#include <functional>
#include <iostream>
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
  void FunctionWithOneUint(std::function<void(uint32_t)>,
                           const std::string& prompt);
  void FunctionWithTwoUints(std::function<void(uint32_t, uint32_t)>,
                            const std::string& prompt);
  void FunctionWithString(std::function<void(std::string&)> func,
                          const std::string& prompt);

  void PrintVector(const std::vector<uint32_t>& v);

 private:
  std::string invalid_choice_message_;
  std::string prompt_;
  std::vector<std::pair<std::string_view, std::function<void()>>> commands_;
  std::istream& in;
  std::ostream& out;
};
}  // namespace s21
#endif  // S21_A2_MENU_H_
