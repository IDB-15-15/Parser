#ifndef TREE
#define TREE
#include <string>
#include <vector>
#include "boost/variant.hpp"

#include <map>
namespace Parser {
        struct Tree{
		class Tag;
        class Text
        {
        public:
            std::string value;
            Tag* parent = nullptr;
            Text();

            ~Text() = default;

            Text(std::string in_value){
                this->value = in_value;
            }
        };

        class Tag
        {
        public:
            std::string name;
            std::map <std::string,std::string> attributes;
            std::vector<boost::variant<Tag,Text>> children;
            boost::variant<Tag,Text>* parent = nullptr;

            Tag(){}


            Tag
            (std::string _name,std::map<std::string,std::string> _attributes)
            {
                name = _name;
                attributes = _attributes;
            }
			
            ~Tag() = default;
        };
        boost::variant<Tag,Text> root;
        };
    
}
#endif
