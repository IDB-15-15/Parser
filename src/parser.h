#ifndef PARSER
#define PARSER
#include <iostream>
#include "networklib.h"
#include "NETWORK.h"
#include <networkres.h>
#include <boost/variant.hpp>
#include <vector>
#include <regex>
#include <map>
#include "tree_builder.h"
namespace Parser {
   Tree parse(Network::NetworkRes* res);
   
}
#endif
