#include <iostream>
#include <string>
using std::string;

int get_line_sum(const string& line) {
  int sum = 0;

  // Loop through the string and get every character
  for (string::size_type i = 0; i != line.length(); i++) {
    char number = line[i];
    sum = sum + (number - '0');  // Convert char to int and add them
  }

  return sum;
}

char get_next_state(const string& neighborhood, const string& rules) {
  string::size_type index;

  // Find if the neighborhood is in the rules
  index = rules.find(neighborhood);
  if (index == string::npos)
    return '0';  // If it isn't, return 0
  else
    return rules[index + 7];  // If found return it's number
}

void update_line(string& cell_line, const string& rules) {
  string new_line = "";
  string neighborhood = "";
  char number;

  // Initialize the indexes for the neighborhood characters
  string::size_type index1 = cell_line.length() - 1;
  string::size_type index2 = 0;
  string::size_type index3 = 1;
  int loop_count = 0;

  // Loop until the first index is at the end of the line for the second time
  while ((index1 != cell_line.length() - 1) || (loop_count != 1)) {
    // Reset indexes back to 0 once they reach the length of the string
    if (index1 == cell_line.length()) {
      index1 -= cell_line.length();
      loop_count += 1;  // Indicate the index has wrapped around once
    }

    if (index2 == cell_line.length()) {
      index2 -= cell_line.length();
    }

    if (index3 == cell_line.length()) {
      index3 -= cell_line.length();
    }

    // Create neighborhood from the 3 indexes
    neighborhood += cell_line[index1];
    neighborhood += cell_line[index2];
    neighborhood += cell_line[index3];

    // Get number corresponding to the neighborhood and add it to the new line
    number = get_next_state(neighborhood, rules);
    new_line += number;

    // Update variables for a new loop
    index1 += 1;
    index2 += 1;
    index3 += 1;
    neighborhood = "";
  }

  cell_line = new_line;  // Update cell_line to be the new line
}

string run_cellular_automata(const string& rules, const int& number_lines,
                             string& starting_line) {
  string output_string = "";
  string line_string;
  int line_sum;
  string line_sum_str;

  for (int i = 0; i != number_lines; i++) {
    // Get the line sum and convert it to a string
    line_sum = get_line_sum(starting_line);
    line_sum_str = std::to_string(line_sum);

    // Create line of output and add it to the output string
    line_string = starting_line + " sum = " + line_sum_str + '\n';
    output_string += line_string;

    // Update the line used for a new loop
    update_line(starting_line, rules);
    line_string = "";
  }

  return output_string;
}

int main() {
  string rules;
  int number_lines;
  string starting_line;
  string display_string;
  string input_line;
  string input_string = "";

  // Create a mega-string of all the inputted lines
  while (getline(std::cin, input_line)) {
    input_string += (input_line + '\n');
  }

  // Get the indexes of useful places in the mega-string
  string::size_type period_index = input_string.find('.');
  string::size_type line_index = input_string.find('\n', period_index + 2);
  string::size_type end_index = input_string.find_last_of('\n');

  // Obtain the rules, the number of lines, and the starting line from the
  // mega-string
  rules = input_string.substr(0, period_index - 1);
  // Idea for std::stoi() from:
  // https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
  number_lines = std::stoi(
      input_string.substr(period_index + 2, line_index - (period_index + 1)));
  starting_line =
      input_string.substr(line_index + 1, (end_index - line_index) - 1);

  // Run the cellular automata
  display_string = run_cellular_automata(rules, number_lines, starting_line);
  std::cout << display_string;

  return 0;
}