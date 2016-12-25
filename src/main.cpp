#include "networklib.h"
#include "network.h"
#include <networkres.h>
#include <boost/variant.hpp>
#include <iostream>
#include "parser.h"


void walk(boost::variant<Parser::Tree::Tag,Parser::Tree::Text> root){
    if(root.which() == 0){
        Parser::Tree::Tag tag = boost::get<Parser::Tree::Tag>(root);
		if(tag.name == "li"){
			Parser::Tree::Text t = tag.to_text();
			std::cout<<std::endl;
			std::cout.write(t.value,t.size);
			std::cout<<std::endl;
			std::cout<<std::endl;
		}
		std::cout<<"Tag : "<<tag.name<<"(";		
		typedef std::map<std::string, std::string>::const_iterator MapIterator;
            for(MapIterator  iter = tag.attributes.begin(); iter != tag.attributes.end(); iter++){
                std::cout<<iter->first<<"="<<iter->second<<" ";
            }
			std::cout<<")"<<std::endl;
			
			
        if(tag.children.size() != 0){        
            
            for(int i = 0; i < tag.children.size(); i++){
                boost::variant<Parser::Tree::Tag,Parser::Tree::Text> next(boost::get<Parser::Tree::Tag>(root).children[i]);
                walk(next);
            }

        }

    }else{
        Parser::Tree::Text text = boost::get<Parser::Tree::Text>(root);
		std::cout<<text.str<<std::endl;
    }

}

int main(){
	setlocale (LC_ALL,"");
	Network::NetworkRes res;
	res = Network::give_result("file://C:/index.html");
    Parser::Tree treer = Parser::parse(&res);
    Parser::Tree::Tag root = boost::get<Parser::Tree::Tag>(treer.root);
	std::cout<<std::endl;
	std::cout<<"this is walk"<<std::endl;
    walk(treer.root);

	return 0;
}