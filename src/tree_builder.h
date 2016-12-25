#ifndef TREE_BUILDER
#define TREE_BUILDER
#include <iostream>
#include "tree.h"
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
    void add_tag(Tree::Tag tag, const char* begin,size_t pos, size_t end){
        if(i == 0){
            tag.begin = begin;
            root.root = tag;
            boost::get<Tree::Tag>(root.root).parent = nullptr;
            i++;
        }else {
            if(tag.name.at(0) != '/'){
				
					tag.begin = begin+pos;
					tag.pos = pos;
					tag.end = end;
					tag.parent = now;
					
					boost::get<Tree::Tag>(now)->children.push_back(tag);
					if(tag.name == "meta" || tag.name == "link" || tag.name =="img" || tag.name =="br" ){
					
					}else{
						now = &(boost::get<Tree::Tag>(now)->children.back());
					}

            }else{
				if(tag.name == "/meta" || tag.name == "/link" || tag.name =="/img" || tag.name =="/br"){
					tag.begin = begin+pos;
					tag.pos = pos;
					tag.end = end;
					tag.parent = now;
					boost::get<Tree::Tag>(now)->children.push_back(tag);
				}else{	

                if(boost::get<Tree::Tag>(now)->parent != nullptr){
                    boost::get<Tree::Tag>(now)->end = end;
                    now = boost::get<Tree::Tag>(now)->parent;
                }				

				}
            }
        }
    }

    void add_text(Tree::Text text){
        Tree::Tag* t = &(boost::get<Tree::Tag>(*now));
        text.parent = t;
		
        boost::get<Tree::Tag>(*now).children.push_back(text);
    }
};
}
#endif

