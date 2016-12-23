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
            const char* value;
			size_t size;
            Tag* parent = nullptr;
            Text(){};

            ~Text() = default;

            Text(const char* value_, size_t size_){
                this->value = value_;
				this->size = size_;
            }
        };

        class Tag
        {
        public:
            std::string name;
            std::map <std::string,std::string> attributes;
            std::vector<boost::variant<Tag,Text>> children;
            boost::variant<Tag,Text>* parent = nullptr;
            const char* begin;
			size_t pos;
			size_t end;
            Tag(){}

            Text to_text(){
                Text result;
				result.value = begin;
                result.size = end-pos;
                return result;
            }

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
