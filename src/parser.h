#ifndef PARSER
#define PARSER
#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include "tree_builder.h"
namespace Parser {
   Tree parse(std::shared_ptr<std::string> input);
   
}
#endif
