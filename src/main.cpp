#include <iostream>
#include <fstream>
#include <QApplication>
#include "GameWindow.hpp"
#include "OperatorPanel.hpp"
#include "GEngine.hpp"

//TODO:
//ładny interfejs operatora z info z o punktacji
//id pytania i odpowiedzi do pliku
//ukrywanie opcji 'gora' 'dół' w zależności od tego czy mogą być kilknięte
//więcej opcji wywołania (mirror/czas_odp/punktacja) - getopts + script + .json
//lepsze ikony dla 'gora' 'dol' 'enter'
//refaktor:: polepszyć hermetyzacje
//refaktor:: ujenolicić nazewnictwo

int main(int argc, char* argv[]) {
    if (argc < 2)
        std::cout << "nie podano bazy pytań!" << std::endl;
    QApplication app(argc,argv);

    std::ifstream qf(argv[1]);
    GEngine gengine(qf);

    GameWindow gwindow(gengine);
    gwindow.show();
    OperatorPanel oppan(&gwindow,&gengine);
    oppan.show();

    return app.exec();

}