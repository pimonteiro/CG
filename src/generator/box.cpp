#include <sstream>
#include "headers/box.h"
#include "headers/plane.h"
#include <regex>


std::string sumNPoints(const std::string&);

std::string
box(float xP, float yP, float zP, int div)
{
        double dz  {zP / (2 * div)};
        double zO  {-zP / 2 + dz};
        double dx  {xP / (2 * div)};
        double xO, auxO;
        std::ostringstream os;

        for (int j {0}; j < div; j++) {
                xO = -xP / 2 + dx;
                auxO = -zP / 2 + dz;

                for (int i {0}; i < div; i++) {
                        os << plane(xO, zP / 2, zO, 2 * dx, 2 * dz, 0, 1); // cima
                        os << plane(xO, -zP / 2, zO, 2 * dx, 2 * dz, 0, 0); // baixo
                        os << plane(xO, zO, zP / 2, 2 * dx, 2 * dz, 1, 1); // frente
                        os << plane(xO, zO, -zP / 2, 2 * dx, 2 * dz, 1, 0); // trás
                        os << plane(xP / 2, zO, auxO, 2 * dz, 2 * dz, 2, 1); // direita
                        os << plane(-xP / 2, zO, auxO, 2 * dz, 2 * dz, 2, 0); // esquerda
                        xO += 2 * dx;
                        auxO += 2 * dz;
                }

                zO += 2 * dz;
        }

        return sumNPoints(os.str());
}

std::string
sumNPoints(const std::string& s)
{
        std::istringstream s0(s);
        std::ostringstream os, r;
        int counter{0};
        std::string oneLine;
        std::regex p("[0-9]+(\\r\\n|\\r|\\n)?");

        while (getline(s0, oneLine)) {
                if (regex_match(oneLine, p))
                        counter += stoi(oneLine);

                else
                        os << oneLine << '\n';
        }

        r << counter << '\n' << os.str();
        return r.str();
}