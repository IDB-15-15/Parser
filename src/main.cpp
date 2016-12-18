#include <iostream>
#include "parser.h"
#include "boost/variant.hpp"

void walk(boost::variant<Parser::Tree::Tag,Parser::Tree::Text> root){
    if(root.which() == 0){
        Parser::Tree::Tag tag = boost::get<Parser::Tree::Tag>(root);
        if(tag.children.size() != NULL){
         std::cout<<tag.name<<"(";
       typedef std::map<std::string, std::string>::const_iterator MapIterator;
       for(MapIterator  iter = tag.attributes.begin(); iter != tag.attributes.end(); iter++){
           std::cout<<iter->first<<"="<<iter->second<<" ";
       }
       std::cout<<")"<<std::endl;
            for(int i = 0; i < tag.children.size(); i++){
                boost::variant<Parser::Tree::Tag,Parser::Tree::Text> next(boost::get<Parser::Tree::Tag>(root).children[i]);
                walk(next);
            }
        }
    }else{
        Parser::Tree::Text text = boost::get<Parser::Tree::Text>(root);
        std::cout<<text.value<<std::endl;
    }

}

int main(){
    std::shared_ptr<std::string> input = std::make_shared<std::string>("<html><head><title>KEKEKEKEEK</title></head><body text='aqua' font-size='5'><a href='ya.ru'>yandex</a></body></html>");
    Parser::Tree tree = Parser::parse(input);
    Parser::Tree::Tag root = boost::get<Parser::Tree::Tag>(tree.root);
	walk(tree.root);
    return 0;
}
