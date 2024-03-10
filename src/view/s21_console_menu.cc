#include "s21_console_menu.h"

#include <limits>
#include <sstream>

s21::ConsoleMenu::ConsoleMenu(
    const std::string& message, const std::string& invalid_choice_message,
    const std::string& prompt,
    const std::vector<std::pair<std::string_view, std::function<void()>>>&
        commands,
    std::istream& in, std::ostream& out)
    : commands_{commands}, in_{in}, out_{out} {
  // Construct the invalid choice message
  invalid_choice_message_ = kRed + kBold + invalid_choice_message + kResetColor;
  // Construct the prompt message
  std::stringstream ss;
  ss << kBold << message;
  for (size_t i = 0; i < commands_.size(); ++i) {
    ss << kYellow << kBold << '[' << (i + 1) << "] " << kResetColor
       << commands_[i].first << '\n';
  }
  ss << kResetColor << prompt;
  prompt_ = ss.str();
}

void s21::ConsoleMenu::operator()() const {
  uint32_t userChoice;
  out_ << '\n';
  while (!(out_ << current_file_info_) || !(out_ << prompt_) ||
         !(in_ >> userChoice) || userChoice <= 0 ||
         userChoice > commands_.size() || in_.peek() != '\n') {
    in_.clear();  // Clear the error state
    in_.ignore(std::numeric_limits<std::streamsize>::max(),
               '\n');  // Ignore the rest of the line
    out_ << '\n' << invalid_choice_message_;
  }
  commands_[userChoice - 1].second();  // Execute the selected function
}

void s21::ConsoleMenu::SetCurrentFile(const std::string& filename) {
  current_file_info_ = filename.empty()
                           ? ""
                           : kBold + "Current file: " + kGreen + kBold +
                                 filename + kResetColor + '\n';
}

void s21::ConsoleMenu::PrintVector(const std::vector<uint32_t>& v,
                                   const std::string& desc) {
  out_ << kGreen << kBold << desc << kResetColor;
  for (auto i : v) {
    out_ << i << " ";
  }
  out_ << std::endl;
}

void s21::ConsoleMenu::PrintMatrix(
    const std::pair<std::vector<uint32_t>, uint32_t>& data,
    const std::string& desc) {
  out_ << kGreen << kBold << desc << kResetColor;
  for (uint32_t i = 0; i < data.second; ++i) {
    for (uint32_t j = 0; j < data.second; ++j) {
      out_ << data.first[i * data.second + j] << " ";
    }
    out_ << std::endl;
  }
}
