#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <boost/algorithm/string/replace.hpp>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <boost/algorithm/string.hpp>

class Question {
    std::string category;
    std::string question;
    std::string answer;
    std::array<std::string,3> tips;
    std::string path_to_wav;
    bool _is_used;
    int id_number;
public:
    Question() = delete;
    Question(std::string _category, std::string _question, 
             std::string _answer, std::array<std::string,3> _tips,
             std::string _path_to_wav,
             bool is_used, 
             int _id_number) :
        category(_category), 
        question(_question), 
        answer(_answer), 
        tips(_tips),
        path_to_wav(_path_to_wav),
        _is_used(is_used), 
        id_number(_id_number) 
    {}
    std::string get_category() const {return category;};
    std::string get_question() const {return question;};
    std::string get_answer() const {return answer;};
    std::array<std::string,3> get_tips() const {return tips;};
    bool is_musical_q() const {return !path_to_wav.empty();}
    std::string get_path_to_wav() const {return path_to_wav;}
    bool is_used() const {return _is_used;}
    int get_id() const {return id_number;}
    void add_prefix_to_path(std::string prefix) {if(is_musical_q()) path_to_wav = prefix + path_to_wav + ".wav";}
    void remove_prefix_to_path(std::string prefix) {
        if(is_musical_q()) {
            boost::algorithm::replace_first(path_to_wav, prefix, "");
            boost::algorithm::replace_last(path_to_wav, ".wav", "");
        }
    }
    void set_as_used() {_is_used = true;}
};

#endif