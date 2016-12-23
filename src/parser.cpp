#include "parser.h"


namespace Parser{
int countMatchInRegex(std::shared_ptr<std::string> s, std::regex words_regex)
{
    auto words_begin = std::sregex_iterator(
                s->begin(), s->end(), words_regex);
    auto words_end = std::sregex_iterator();

    return std::distance(words_begin, words_end);
}

Tree parse(std::shared_ptr<std::string> inp)
{
    std::regex comments("<!--(.*?)-->");
	std::regex doc("<!DOCTYPE HTML>");
    std::regex reg("<(/?[^\\>]+)>");
    std::regex attrs("([[:alnum:]]*)=('([^']*)'|\"([^\"]*)\"|([[:alnum:]]*))");

   std::shared_ptr<std::string> inp1;
   std::shared_ptr<std::string> input;
   bool docf = false;
   if(countMatchInRegex(inp, doc) != 0)
   {
	   inp1 = std::make_shared<std::string>("");
       std::regex_replace(std::back_inserter(*inp1),
                     inp->begin(), inp->end(), doc, "");
					 docf = true;
   }
   else
   {
      inp1 = inp;
   }
   if(countMatchInRegex(inp1,comments) != 0)
   {
	  
       input = std::make_shared<std::string>("");
	   
	
         std::regex_replace(std::back_inserter(*input),
                     inp1->begin(), inp1->end(), comments, "");
   }
   else
   {
      input = inp1;
   }


auto str_begin =
        std::sregex_iterator(input->begin(), input->end(), reg);
auto str_end = std::sregex_iterator();


auto i = str_begin;
std::shared_ptr<TreeBuilder> b = std::make_shared<TreeBuilder>();
int last_pos = 0;
for(;!(i==str_end);i++){
    std::smatch match = *i;
    std::string match_str = match.str();
    int pos = i->position();

    if(pos-last_pos!= 0){
        std::string text_str = input->substr(last_pos,pos-last_pos);
        Tree::Text text(text_str);
        b->add_text(text);
    }
    std::string tag_str = match[1].str();
    auto tag_begin =
            std::sregex_iterator(tag_str.begin(), tag_str.end(), attrs);
    auto tag_end = std::sregex_iterator();
    std::sregex_iterator j = tag_begin;
    size_t space = tag_str.find_first_of(' ',0);
    std::string name_tag = tag_str.substr(0,space);

    std::map<std::string,std::string> attributes;
    for(;!(j==tag_end);j++){
        std::smatch match = *j;
        std::string name = match[1].str();
        std::string value = match[2].str();
        attributes.insert( std::pair<std::string,std::string>(name,value) );

    }
    Tree::Tag tag(name_tag,attributes);
    b->add_tag(tag);
    last_pos = pos+match_str.size();
}
return b->root;
}

} 


