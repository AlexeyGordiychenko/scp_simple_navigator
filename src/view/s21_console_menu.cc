#include "s21_console_menu.h"

#include <limits>
#include <sstream>

s21::ConsoleMenu::ConsoleMenu(
    const std::string& message, const std::string& invalid_choice_message,
    const std::string& prompt,
    const std::vector<std::pair<std::string_view, std::function<void()>>>&
        commands,
    std::istream& in, std::ostream& out)
    : invalid_choice_message_{invalid_choice_message},
      commands_{commands},
      in{in},
      out{out} {
  // Construct the prompt message
  std::stringstream ss;
  ss << message;
  for (size_t i = 0; i < commands_.size(); ++i) {
    ss << '[' << (i + 1) << "] " << commands_[i].first << '\n';
  }
  ss << prompt;
  prompt_ = ss.str();
}

void s21::ConsoleMenu::operator()() const {
  uint32_t userChoice;
  out << '\n';
  while (!(out << prompt_) || !(in >> userChoice) || userChoice <= 0 ||
         userChoice > commands_.size() || in.peek() != '\n') {
    in.clear();  // Clear the error state
    in.ignore(std::numeric_limits<std::streamsize>::max(),
              '\n');  // Ignore the rest of the line
    out << '\n' << invalid_choice_message_;
  }
  commands_[userChoice - 1].second();  // Execute the selected function
}

void s21::ConsoleMenu::FunctionWithOneUint(std::function<void(u_int32_t)> func,
                                           const std::string& prompt) {
  uint32_t a;
  while (!(out << prompt) || !(in >> a) || in.peek() != '\n') {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    out << '\n' << invalid_choice_message_;
  }
  func(a);
}

void s21::ConsoleMenu::FunctionWithTwoUints(
    std::function<void(u_int32_t, u_int32_t)> func, const std::string& prompt) {
  uint32_t a, b;
  while (!(out << prompt) || !(in >> a) || !(in >> b) || in.peek() != '\n') {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    out << '\n' << invalid_choice_message_;
  }
  func(a, b);
}

void s21::ConsoleMenu::FunctionWithString(
    std::function<void(std::string&)> func, const std::string& prompt) {
  std::string s;
  in.clear();
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (!(out << prompt) || !(std::getline(in, s))) {
    out << '\n' << invalid_choice_message_;
  }
  func(s);
}

void s21::ConsoleMenu::PrintVector(const std::vector<uint32_t>& v) {
  for (auto i : v) {
    out << i << " ";
  }
  out << std::endl;
}
