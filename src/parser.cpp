#include <iostream>
#include <vector>
#include <regex>
#include <Node.hpp>
#include "parser.hpp"
namespace Parser{
void parse(std::shared_ptr<std::string> input)
{
    std::regex reg("<(/?[^\>]+)>");
    std::regex attrs("([A-Za-z0-9]*)='([^']*)'");
    auto str_begin =
            std::sregex_iterator(input->begin(), input->end(), reg);
    auto str_end = std::sregex_iterator();
    std::sregex_iterator i = str_begin;
    Node* tree = new Node;
    int last_pos = 0;
    for(;!(i==str_end);i++){
        std::smatch match = *i;
        std::string match_str = match.str();
        int pos = match.position();
        if(pos-last_pos!= 0){
            std::string text_str = input->substr(last_pos,pos-last_pos);
            std::cout<<text_str<<std::endl;
            Node::Text text(text_str);
            Node::Base base(text);
            tree->add_text(base);
        }
        std::string tag_str = match[1].str();
        auto tag_begin =
                std::sregex_iterator(tag_str.begin(), tag_str.end(), attrs);
        auto tag_end = std::sregex_iterator();
        std::sregex_iterator j = tag_begin;
        size_t space = tag_str.find_first_of(' ',0);
        std::string name_tag = tag_str.substr(0,space);
        std::cout<<name_tag;
        std::cout<<"(";
        std::vector<Node::Attribute> attributes;
        for(;!(j==tag_end);j++){
            std::smatch match = *j;
            std::string name = match[1].str();
            std::string value = match[2].str();
            Node::Attribute attribute(name,value);
            attributes.push_back(attribute);
            std::string attr = name + "=" + value + ";";
            std::cout<<attr;
        }
        std::cout<<")"<<std::endl;
        Node::Tag tag(name_tag,attributes);
        Node::Base base(tag);


        tree->add_tag(base);
        last_pos = match.position()+match_str.size();

    }
}

} 

