#include <array>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <exception>
#include <ios>
#include <iostream>
#include <fstream>
#include <QApplication>
#include "GameWindow.hpp"
#include "OperatorPanel.hpp"
#include "GEngine.hpp"
#include <boost/program_options.hpp>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "SoundPlayer.hpp"

//TODO:
//naprawić opcję skalowania interfejsu operatora
//include/exclude kategorii
//id pytania i odpowiedzi do pliku
//rozne opcje formatu pliku pytan (.que, .json) i skrypt pomiedzy nimi
//ukrywanie opcji 'gora' 'dół' w zależności od tego czy mogą być kilknięte
//lepsze ikony dla 'gora' 'dol' 'enter'
//refaktor:: polepszyć hermetyzacje
//refaktor:: ujenolicić nazewnictwo

namespace po = boost::program_options;
using std::string;
using std::vector;

int main(int argc, char* argv[]) {

    //po::options_description desc("Usage:\n" + string(argv[0]) + " -i <questions_file> [ -h ] [ -s scale ] [ -p panel_scale ] [-m]\nArguments");
    po::options_description desc("Usage:\n" + string(argv[0]) + 
                                          " -i <questions_file> [ -h ]" +
                                          " -o <question_output_file>" + 
                                          " [ -s scale ] [-m]" +
                                          " [ -t seconds ] [ -f x ]" +
                                          " [ -1 name color hcolor points ]" +
                                          " [ -2 name color hcolor points ]" +
                                          " [ -3 name color hcolor points ]" +
                                          " [ -e ] [ -P path ]" +
                                          "\nArguments");
    try {
        vector<string> blue = {"niebiescy","#19247C","#007FFF","5000"};
        vector<string> green = {"zieloni","#006633","#33CC66","5000"};
        vector<string> yellow = {"żółci","#C0A62C","#F9E04B","5000"};
        desc.add_options()
            ("help,h","displays this message")
            ("questions_file,i",po::value<string>()->value_name("questions_file")->required(),"path to file with questions")
            ("questions_output_file,o",po::value<string>()->value_name("output_file")->default_value("output.que"),"path to ouptut file.\nOutput file gets info if question was used in this session or not")
            ("scale,s",po::value<double>()->value_name("scale")->default_value(1.0),"scale of game window")
            //("panel_scale,p",po::value<double>()->value_name("scale")->default_value(1.0),"scale of operator window") wyłączony do naprawy
            ("mirror,m","mirrors team placement in game window")
            ("answer_time,t",po::value<uint>()->value_name("seconds")->default_value(60),"time for team to answer")
            ("tip_freq,f",po::value<uint>()->value_name("x")->default_value(10),"probability of drawing a tip instead of question.\nx - mean draws to happen, for x probability to draw tip equals 1/x")
            ("team1,1",po::value<vector<string>>()->multitoken()->value_name("name color hcolor points")->default_value(blue,"blue '#19247C' '#007FFF' 5000"),"options for team 1:\nname - name of team\ncolor - color for standby\nhcolor - color for highlight\npoints - starting points for team")
            ("team2,2",po::value<vector<string>>()->multitoken()->value_name("name color hcolor points")->default_value(green,"green '#006633' '#33CC66' 5000"),"options for team 2:\nsee --team1")
            ("team3,3",po::value<vector<string>>()->multitoken()->value_name("name color hcolor points")->default_value(yellow,"yellow '#C0A62C' '#F9E04B' 5000"),"options for team 3:\nsee --team1")
            ("exclude_musical,e","do not import musical question from question set")
            ("path_to_wavs,P",po::value<string>()->value_name("path")->default_value("sounds/"),"path do directory where .wav files for musical questions are")
        ;
        
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }
        po::notify(vm);

        if (vm["scale"].as<double>() <= 0.0) {
            throw std::runtime_error("scale number is negative!");
        }
        if (vm["tip_freq"].as<uint>() < 2) {
            throw std::runtime_error("tip_freq argument is lesser than 2, game cannot be launched!");
        }

        std::ifstream qf(vm["questions_file"].as<string>());
        if (!qf) {
            throw std::runtime_error(vm["questions_file"].as<string>()+" file does not exist!");
        }
        std::ofstream outf(vm["questions_output_file"].as<string>());        
        QApplication app(argc,argv);
        bool is_mirrored = vm.count("mirror");
        std::array<Team, 3> teams({
            Team(vm[is_mirrored ? "team3" : "team1"].as<vector<string>>()),
            Team(vm["team2"].as<vector<string>>()),
            Team(vm[is_mirrored ? "team1" : "team3"].as<vector<string>>())
            });
        SoundPlayer sp;
        GEngine gengine(&sp, qf,outf,teams,
                        vm["answer_time"].as<uint>(),
                        vm["tip_freq"].as<uint>(),
                        vm.count("exclude_musical"),
                        vm["path_to_wavs"].as<string>());

        GameWindow gwindow(gengine,vm["scale"].as<double>(),is_mirrored);
        gwindow.show();
        //OperatorPanel oppan(&gwindow,&gengine, vm["panel_scale"].as<double>());
        OperatorPanel oppan(&gwindow,&gengine);
        oppan.show();

        return app.exec();
    } catch(std::exception & e) {
        std::cout << desc << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cout << desc << std::endl;
        std::cout << "Unknown error!" << std::endl;
        return 2;
    }
}