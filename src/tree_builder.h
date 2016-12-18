#ifndef tree_builder
#define tree_builder
#include <iostream>
#include "tree_stuct.h"
#include "boost/variant.hpp"
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
namespace Parser {

class TreeBuilder{
public:

    Tree root;
    boost::variant<Tree::Tag,Tree::Text> *now = &root.root;
    int i = 0;
    void add_tag(Tree::Tag tag){
        if(i == 0){
            root.root = tag;
            boost::get<Tree::Tag>(root.root).parent = nullptr;
            i++;
        }else {

            if(tag.name.at(0) != '/'){
                tag.parent = now;
                boost::get<Tree::Tag>(now)->children.push_back(tag);
				//std::cout<<tag.name<<" -> "<<boost::get<Tree::Tag>(now)->name<<std::endl;
				now = &(boost::get<Tree::Tag>(now)->children.back());
            }else{
                                if(boost::get<Tree::Tag>(now)->parent != nullptr){
                                        now = boost::get<Tree::Tag>(now)->parent;
                }
            }
        }
    }

    void add_text(Tree::Text text){
        Tree::Tag* t = &(boost::get<Tree::Tag>(*now));
        text.parent = t;
        boost::get<Tree::Tag>(*now).children.push_back(text);
		//std::cout<<"\""<<text.value<<"\" -> "<<t->name<<std::endl;
       
    }
};
}
#endif

