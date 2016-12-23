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
    void add_tag(Tree::Tag tag, int pos, size_t size){
        if(i == 0){
            tag.begin = pos;
            root.root = tag;
            boost::get<Tree::Tag>(root.root).parent = nullptr;
            i++;
        }else {
            if(tag.name.at(0) != '/'){
                tag.begin = pos;
                tag.parent = now;
                boost::get<Tree::Tag>(now)->children.push_back(tag);
                now = &(boost::get<Tree::Tag>(now)->children.back());
            }else{
                if(boost::get<Tree::Tag>(now)->parent != nullptr){
                    boost::get<Tree::Tag>(now)->end = pos+size;
                    now = boost::get<Tree::Tag>(now)->parent;


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

