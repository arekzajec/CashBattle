#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>
#include <array>
#include <vector>
#include <memory>

class Question {
    std::string category;
    std::string question;
    std::string answer;
    std::array<std::string,3> tips;
    int id_number;
public:
    Question() = delete;
    Question(std::string _category, std::string _question, 
             std::string _answer, std::array<std::string,3> _tips, 
             int _id_number) :
        category(_category), 
        question(_question), 
        answer(_answer), 
        tips(_tips), 
        id_number(_id_number) 
    {}
    std::string get_category() const {return category;};
    std::string get_question() const {return question;};
    std::string get_answer() const {return answer;};
    std::array<std::string,3> get_tips() const {return tips;};
    int get_id() const {return id_number;}    
};

#endif