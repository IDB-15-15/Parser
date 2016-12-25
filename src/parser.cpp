#include "parser.h"


namespace Parser{
int countMatchInRegex(std::shared_ptr<std::string> s, std::regex words_regex)
{
    auto words_begin = std::sregex_iterator(
                s->begin(), s->end(), words_regex);
    auto words_end = std::sregex_iterator();

    return std::distance(words_begin, words_end);
}

Tree parse(Network::NetworkRes* res)
{
    std::regex comments("<!--(.*?)-->");
	std::regex doc("<!DOCTYPE\s*(.*?)*\s*>");
    std::regex reg("<(/?[^\\>]+)>");
    std::regex attrs("([[:alnum:]-]*)\\s*=\\s*([\'\"]\\s*([\\S]*)\\s*[\'\"])");
	
   std::shared_ptr<std::string>  source = std::make_shared<std::string>(res->res_arr,res->size);
   std::shared_ptr<std::string> wodoc;
   std::shared_ptr<std::string> wocoms;
   
   bool docf = false;
   bool comf = false;
   if(countMatchInRegex(source, doc) != 0)
   {
	   wodoc = std::make_shared<std::string>("");
       std::regex_replace(std::back_inserter(*wodoc),
                     source->begin(), source->end(), doc, "");
					 docf = true;
   }else{
	   wodoc = source;
   }
   if(countMatchInRegex(wodoc,comments) != 0)
   {
	   wocoms = std::make_shared<std::string>("");
         std::regex_replace(std::back_inserter(*wocoms),
                     wodoc->begin(), wodoc->end(), comments, "");
					 comf = true;
   }else{
	  wocoms = wodoc; 
   }

	if(docf || comf){
		res->res_arr = wocoms->c_str();
		res->size = wocoms->size();
		res->res = wocoms;
	}


auto str_begin =
        std::sregex_iterator(wocoms->begin(), wocoms->end(), reg);
auto str_end = std::sregex_iterator();


auto i = str_begin;
std::shared_ptr<TreeBuilder> b = std::make_shared<TreeBuilder>();
int last_pos = 0;
for(;!(i==str_end);i++){
    std::smatch match = *i;
    std::string match_str = match.str();
    int pos = i->position();

    if(pos-last_pos!= 0){
		std::string str(wocoms->c_str()+last_pos,pos-last_pos);
		int spaces = 0;;
		for(auto it : str){
			if(isspace(it))
				spaces++;
		}
		if(spaces!=pos-last_pos){
        Tree::Text text(wocoms->c_str()+last_pos,pos-last_pos);
        b->add_text(text);
		}
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
        std::string value = match[3].str();
        attributes.insert( std::pair<std::string,std::string>(name,value) );

    }
    Tree::Tag tag(name_tag,attributes);
    b->add_tag(tag,wocoms->c_str(),pos,pos+match_str.size());
    last_pos = pos+match_str.size();
}

return b->root;
}

} 


