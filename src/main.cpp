#include <cctype>
#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

enum class Token_Type {
  _return,
  int_lit,
  semi,
};
struct Token {
  Token_Type type;
  std::optional<std::string> value;
};

std::vector<Token> tokens;

void tokenize(const std::string &str) {
  std::string buf{};
  for (int i = 0; i < str.size(); i++) {
    if (std::isalpha(str[i])) {
      buf.push_back(str[i]);
      i++;
      while (std::isalnum(str.at(i))) {
        buf.push_back(str.at(i));
        i++;
      }
      i--;
      if (buf == "return") {
        std::cout<<buf<<std::endl;
        tokens.push_back({.type = Token_Type::_return});
        buf.clear();
      }
    }
    else if (std::isspace(str[i])) {
      continue;
    }
    else if (std::isdigit(str[i])) {
      buf.push_back(str[i]);
      i++;
      while (std::isdigit(str[i])) {
         buf.push_back(str[i]);
         i++;   
      }
      i--;
      tokens.push_back({.type = Token_Type::int_lit,.value = buf});
      std::cout<<buf<<std::endl;
      buf.clear(); 
    }
  }
  std::cout << buf;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Incorrect Usages.." << std::endl;
    std::cerr << "hydro <input.batman>" << std::endl;
  }

  std::string contents;
  std::stringstream contents_stream;
  {
    std::fstream input(argv[1], std::ios::in);
    contents_stream << input.rdbuf();
    contents = contents_stream.str();
  }
  tokenize(contents);
  return EXIT_SUCCESS;
}
