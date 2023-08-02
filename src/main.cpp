#include <array>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/value_semantic.hpp>
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
//ukrywanie opcji 'gora' 'dół' w zależności od tego czy mogą być kilknięte
//lepsze ikony dla 'gora' 'dol' 'enter'
//blackbox
//user interface
//directed sequence; tip or blackbox on demand
//one-to-one
//dynamic display of teams (maybe more teams?)
//refaktor:: polepszyć hermetyzacje
//refaktor:: ujenolicić nazewnictwo

namespace po = boost::program_options;
using std::string;
using std::vector;

int main(int argc, char* argv[]) {

    //po::options_description desc("Usage:\n" + string(argv[0]) + " -i <questions_file> [ -h ] [ -s scale ] [ -p panel_scale ] [-m]\nArguments");
    po::options_description desc("Usage:\n" + string(argv[0]) + 
                                          " -i <questions_file> [ -h ]" +
                                          " [ -o <question_output_file> ]" + 
                                          " [ -s scale ] [ -p scale ] [-m]" +
                                          " [ -t seconds ] [ -f x ]" +
                                          " [ -1 name color hcolor points ]" +
                                          " [ -2 name color hcolor points ]" +
                                          " [ -3 name color hcolor points ]" +
                                          " [ -e ] [ -P path ]" +
                                          " [ -I list ] [ -E list ]" +
                                          " [ -d ] [ -q ] [ -l lang ]" +
                                          "\nArguments");
    try {
        vector<string> blue;
        vector<string> green;
        vector<string> yellow;
        vector<string> Inc;
        vector<string> Exc;
        desc.add_options()
            ("help,h","displays this message")
            ("questions_file,i",po::value<string>()->value_name("questions_file")->required(),"path to file with questions in .que format")
            ("questions_output_file,o",po::value<string>()->value_name("output_file")->default_value("output.que"),"path to ouptut file.\nOutput file gets info if question was used in this session or not")
            ("scale,s",po::value<double>()->value_name("scale")->default_value(1.0),"scale of game window")
            ("panel_scale,p",po::value<double>()->value_name("scale")->default_value(1.0),"scale of operator window")
            ("mirror,m","mirrors team placement in game window")
            ("answer_time,t",po::value<uint>()->value_name("seconds")->default_value(60),"time for team to answer")
            ("tip_freq,f",po::value<uint>()->value_name("x")->default_value(10),"probability of drawing a tip instead of question.\nx - mean draws to happen, for x probability to draw tip equals 1/x")
            ("team1,1",po::value<vector<string>>()->multitoken()->value_name("name color hcolor points")->default_value(blue,"blue '#19247C' '#007FFF' 5000"),"options for team 1:\nname - name of team\ncolor - color for standby\nhcolor - color for highlight\npoints - starting points for team")
            ("team2,2",po::value<vector<string>>()->multitoken()->value_name("name color hcolor points")->default_value(green,"green '#006633' '#33CC66' 5000"),"options for team 2:\nsee --team1")
            ("team3,3",po::value<vector<string>>()->multitoken()->value_name("name color hcolor points")->default_value(yellow,"yellow '#C0A62C' '#F9E04B' 5000"),"options for team 3:\nsee --team1")
            ("exclude_musical,e","do not import musical question from question set")
            ("path_to_wavs,P",po::value<string>()->value_name("path")->default_value("sounds/"),"path do directory where .wav files for musical questions are")
            ("include_categories,I",po::value<vector<string>>(&Inc)->multitoken()->value_name("list")->default_value({"All"},"All"),"list of questions categories that game will read from question file.\nAll - all categories.\nexample: -I All\nexample: -I Football \"Classical Music\"")
            ("exclude_categories,E",po::value<vector<string>>(&Exc)->multitoken()->value_name("list"),"list of questions categories that game will not read from question file.\nWorks only if option -I is not used or set to All\nexample: -E Football \"Classical Music\"\nexample: -I All -E Football \"Classical Music\"")
            ("dry_run,d","program will not be exacuted, but checking integrity of qeustions set and all filtering operations (-i, -o, -e, -P, -I, -E) will be performed. Also, program will check if all other program parameters are set correctly.")
            ("show_question_nr,q","show question number in game window")
            ("lang,l",po::value<string>()->value_name("lang")->default_value("PL"),"language, avalible: PL, EN")
        ;
        
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }
        po::notify(vm);
        
        blue = vm["team1"].as<vector<string>>();
        if (blue.size() != 4 && !blue.empty())
            throw std::runtime_error("wrong number of parameters in option -1");
        green = vm["team2"].as<vector<string>>();
        if (green.size() != 4 && !green.empty())
            throw std::runtime_error("wrong number of parameters in option -2");
        yellow = vm["team3"].as<vector<string>>();
        if (yellow.size() != 4 && !yellow.empty())
            throw std::runtime_error("wrong number of parameters in option -3");

        GEngineLocInterface * gengine_loc;
        GameWindowLocInterface * gwindow_loc;
        OperatorPanelLocInterface *oppan_loc;
        std::string lang = vm["lang"].as<string>();
        if (lang == "PL") {
            gengine_loc = new GEngineLocPL;
            gwindow_loc = new GameWindowLocPL;
            oppan_loc = new OperatorPanelLocPL;
            if (blue.empty())
                blue = {"niebiescy","#19247C","#007FFF","5000"};
            if (green.empty())
                green = {"zieloni","#006633","#33CC66","5000"};
            if (yellow.empty())
                yellow = {"żółci","#C0A62C","#F9E04B","5000"};
        } else if (lang == "EN") {
            gengine_loc = new GEngineLocEN;
            gwindow_loc = new GameWindowLocEN;
            oppan_loc = new OperatorPanelLocEN;
            if (blue.empty())
                blue = {"blue","#19247C","#007FFF","5000"};
            if (green.empty())
                green = {"green","#006633","#33CC66","5000"};
            if (yellow.empty())
                yellow = {"yellow","#C0A62C","#F9E04B","5000"};
        } else {
            throw std::runtime_error("language not recognised!");
        }

        std::ifstream qf(vm["questions_file"].as<string>());
        if (!qf) {
            throw std::runtime_error(vm["questions_file"].as<string>()+" file does not exist!");
        }
        std::ofstream outf(vm["questions_output_file"].as<string>());
        if (!outf) {
            throw std::runtime_error("problem with opening file "+vm["questions_output_file"].as<string>()+" !");
        }        

        double scale = vm["scale"].as<double>();
        double panel_scale = vm["panel_scale"].as<double>();
        if (scale <= 0.0) {
            throw std::runtime_error("scale number is negative!");
        }
        if (panel_scale <= 0.0) {
            throw std::runtime_error("panel_scale number is negative!");
        }
        if (vm["tip_freq"].as<uint>() < 2) {
            throw std::runtime_error("tip_freq argument is lesser than 2, game cannot be launched!");
        }

        if (Inc.empty() || std::find(Inc.begin(), Inc.end(), "All") != Inc.end())
            Inc.clear();
        if (!Inc.empty())
            Exc.clear();

        bool is_mirrored = vm.count("mirror");
        std::array<Team, 3> teams({
            Team(is_mirrored ? yellow : blue),
            Team(green),
            Team(is_mirrored ? blue : yellow)
            });

        QApplication app(argc,argv);
        SoundPlayer sp;
        GEngine gengine(gengine_loc, &sp, qf,outf,teams,Inc,Exc,
                        vm["answer_time"].as<uint>(),
                        vm["tip_freq"].as<uint>(),
                        vm.count("exclude_musical"),
                        vm["path_to_wavs"].as<string>());
        if (vm.count("dry_run")) {
            std::cout << "dry run is completed, check out " + vm["questions_output_file"].as<string>() << std::endl;
            return 0;
        }

        GameWindow gwindow(gwindow_loc,gengine,scale,is_mirrored,vm.count("show_question_nr"));
        gwindow.show();
        OperatorPanel oppan(oppan_loc,&gwindow,&gengine, panel_scale);
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