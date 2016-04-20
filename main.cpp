//
//  main.cpp
//  search word_01312016
//
//  Created by apple on 1/31/16.
//  Copyright © 2016 apple. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include<sstream>
using namespace std;

class TextQuery{
public:
    typedef std::vector<std::string> ::size_type line_no;
    void read_file(std::ifstream&is)
    {
        store_file(is); build_map();
    }
    std::set<line_no> run_query(const std::string&) const;
    std::string text_line(line_no) const;
private:
    void store_file(std::ifstream&);
    void build_map();
    std::vector<std::string> lines_of_text;
    std::map<std::string, std::set<line_no> >word_map;
};

//open_file
    std::ifstream& open_file(std::ifstream &in, const std::string &file)
    {
        in.close();
        in.clear();
        in.open(file.c_str());
        return in;
    }
//make_plural

    std::string make_plural(size_t ctr, const std::string &word, const std::string &ending)
    {
        return (ctr==1)? word : word + ending;
    }

//print_file

void print_results(const std::set<TextQuery::line_no>&locs,
                   const std::string&sought,
                   const TextQuery&file){
    typedef std::set<TextQuery::line_no> line_nums;
    line_nums::size_type size=locs.size();
    std::cout<<"\n"<<sought<<"occurs"
    <<size<<""
    <<make_plural(size,"time","s")<<std::endl;
    line_nums::const_iterator it=locs.begin();
    for( ; it!=locs.end();++it)
    {
    std::cout<<"\t(line"
        <<(*it)+1<<")"
        <<file.text_line(*it)<<endl;
    }
    
}
//store file

void TextQuery::store_file(ifstream &is)
{
    string textline;
    while (getline(is, textline))
        lines_of_text.push_back(textline);
}


//build map
void TextQuery::build_map()
{
    for(line_no line_num=0; line_num!=lines_of_text.size(); ++line_num)
    {
       
            istringstream line(lines_of_text[line_num]);
        //istringstream line(lines_of_text[line_num]);
        string word;
        while (line>>word) {
            word_map[word].insert(line_num);
        }
    }
}
//support search run_query

set<TextQuery::line_no>
TextQuery::run_query(const string &query_word) const
{
    map<string,set<line_no> >::const_iterator loc=word_map.find(query_word);
    if(loc==word_map.end())
    {
        return set<line_no>();
    }
    else{
        return loc->second;
    }
}
string TextQuery::text_line(line_no line) const
{
    if (line<lines_of_text.size()) {
        return lines_of_text[line];
        
    }
    throw std::out_of_range("line number out of range");
}






//main
int main(int argc, const char * argv[]) {
    std::ifstream infile("a.txt");
    if(argc<2||!open_file(infile,argv[1]))
    {
        std::cerr<<"No input file!"<<std::endl;
        return EXIT_FAILURE;
    }
    TextQuery tq;
    tq.read_file(infile);
    while(true)
    {
    std::cout<<"enter word to look for, or q to quit:";
        std::string s;
        std::cin>>s;
        if(!std::cin||s=="q") break;
        std::set<TextQuery::line_no> locs=tq.run_query(s);
        print_results(locs,s,tq);
    }
    return 0;
}






























