#include "headers/parser.h"
#include "headers/model.h"
#include "headers/group.h"
#include "headers/tinyxml2.h"
#include "headers/scale.h"
#include "headers/rotation.h"
#include "headers/translation.h"
#include "headers/catmull.h"
#include "headers/texture.h"
#include "headers/light.h"
#include "headers/directionalLight.h"
#include "headers/pointLight.h"
#include "headers/spotLight.h"
#include "../lib/headers/point.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>


using namespace tinyxml2;
using namespace std;


void parseDoc(Group *, XMLNode *);
Model *parseFile(const XMLElement *);
Translation *parseTranslate(XMLElement *);
Scale *parseScale(const XMLElement *);
Rotation *parseRotate(const XMLElement *);
Catmull *parseCatmul(XMLElement *);
Light *parseLight(XMLElement *);


float randomF() {
        std::random_device seeder;
        std::mt19937 engine(seeder());
        std::uniform_real_distribution<float> dist(0, 1);
        return dist(engine);
}

Parser::Parser() {
}

void Parser::ReadXML(Group *group, const char *xml) {
        XMLDocument xmlDoc;
        XMLError result {xmlDoc.LoadFile(xml)};

        if (result != XML_SUCCESS) {
                cerr << "Error:" << result << endl;
                exit(1);
        }

        XMLNode *pRoot {xmlDoc.FirstChild()};

        if (pRoot == nullptr) {
                cout << "Warning: Malformed XML file" << endl;
                exit(0);
        } else {
                XMLNode *pNode {pRoot->FirstChild()};

                if (pNode == nullptr) {
                        cout << "Warning: No models found" << endl;
                        exit(0);
                } else
                        parseDoc(group, pNode);
        }
}

void parseDoc(Group *group, XMLNode *pN) {
        XMLNode *pNode {pN->FirstChild()};

        if (pNode == nullptr)
                exit(0);

        for (; pNode; pNode = pNode->NextSibling()) {
                XMLElement *pElement {pNode->ToElement()};

                if (!strcmp(pElement->Name(), "light")) {
                        Light *l {parseLight(pElement)};
                        group->addLight(l);
                }

                if (!strcmp(pElement->Name(), "model")) {
                        if (pElement->Attribute("file")) {
                                Model *m {parseFile(pElement)};
                                m->prepare();
                                group->addModel(m);
                        }
                }

                if (!strcmp(pElement->Name(), "translate")) {
                        if (pElement->Attribute("time")) {
                                Catmull *c {parseCatmul(pElement)};
                                group->addTransformation(c);
                        } else {
                                Translation *t {parseTranslate(pElement)};
                                group->addTransformation(t);
                        }
                }

                if (!strcmp(pElement->Name(), "rotate")) {
                        Rotation *r {parseRotate(pElement)};
                        group->addTransformation(r);
                }

                if (!strcmp(pElement->Name(), "scale")) {
                        Scale *s {parseScale(pElement)};
                        group->addTransformation(s);
                }

                if (!strcmp(pElement->Name(), "group")) {
                        Group *g {new Group()};
                        parseDoc(g, pNode);
                        group->addGroup(g);
                }

                if (!strcmp(pElement->Name(), "models"))
                        parseDoc(group, pNode);

                if (!strcmp(pElement->Name(), "lights"))
                        parseDoc(group, pNode);
        }
}


Light *parseLight(XMLElement *pElement1) {
        float pos[3];
        float amb[4];
        float spotDir[3];
        float color[4];
        int flaC = 0; // Has Color?
        int flaA = 0; // Has Ambient Color?
        int flaSD = 0; // Has Spot Direction?
        int flaP = 0; // Has Position?

        if (!strcmp(pElement1->Name(), "light")) {
                if (pElement1->Attribute("x")) {
                        pos[0] = stof(pElement1->Attribute("x"));
                        flaP = 1;
                }

                if (pElement1->Attribute("y")) {
                        pos[1] = stof(pElement1->Attribute("y"));
                        flaP = 1;
                }

                if (pElement1->Attribute("z")) {
                        pos[2] = stof(pElement1->Attribute("z"));
                        flaP = 1;
                }

                if (pElement1->Attribute("diffR")) {
                        flaC = 1;
                        color[0] = stof(pElement1->Attribute("diffR"));
                }

                if (pElement1->Attribute("diffG")) {
                        flaC = 1;
                        color[1] = stof(pElement1->Attribute("diffG"));
                }

                if (pElement1->Attribute("diffB")) {
                        flaC = 1;
                        color[2] = stof(pElement1->Attribute("diffB"));
                }

                if (pElement1->Attribute("diffA")) {
                        flaC = 1;
                        color[3] = stof(pElement1->Attribute("diffA"));
                }

                if (pElement1->Attribute("ambR")) {
                        flaA = 1;
                        amb[0] = stof(pElement1->Attribute("ambR"));
                }

                if (pElement1->Attribute("ambG")) {
                        flaA = 1;
                        amb[1] = stof(pElement1->Attribute("ambG"));
                }

                if (pElement1->Attribute("ambB")) {
                        flaA = 1;
                        amb[2] = stof(pElement1->Attribute("ambB"));
                }

                if (pElement1->Attribute("ambA")) {
                        flaA = 1;
                        amb[3] = stof(pElement1->Attribute("ambA"));
                }

                if (pElement1->Attribute("spotDirx"))
                        spotDir[0] = stof(pElement1->Attribute("spotDirx"));

                if (pElement1->Attribute("spotDiry"))
                        spotDir[1] = stof(pElement1->Attribute("spotDiry"));

                if (pElement1->Attribute("spotDirz"))
                        spotDir[2] = stof(pElement1->Attribute("spotDirz"));

                if (pElement1->Attribute("type")) {
                        string tt = pElement1->Attribute("type");

                        if (tt.compare("POINT") == 0) {
                                PointLight *l { new PointLight() };

                                if (flaA)
                                        l->setAmb(amb);

                                if (flaC)
                                        l->setColor(color);

                                if (flaP)
                                        l->setPos(pos);

                                return l;
                        } else if (tt.compare("DIRECTIONAL") == 0) {
                                DirectionalLight *l { new DirectionalLight()};

                                if (flaA)
                                        l->setAmb(amb);

                                if (flaC)
                                        l->setColor(color);

                                if (flaP)
                                        l->setPos(pos);

                                return l;
                        } else if (tt.compare("SPOT") == 0) {
                                SpotLight *l { new SpotLight()};

                                if (flaA)
                                        l->setAmb(amb);

                                if (flaC)
                                        l->setColor(color);

                                if (flaSD)
                                        l->setSpotDir(spotDir);

                                if (flaP)
                                        l->setPos(pos);

                                if (pElement1->Attribute("cutOff"))
                                        l->setCutOff(stof(pElement1->Attribute("cutOff")));

                                if (pElement1->Attribute("exp"))
                                        l->setExp(stof(pElement1->Attribute("exp")));

                                return l;
                        } else {
                                cerr << "Bad light format.\n";
                                exit(1);
                        }
                }
        }

        return nullptr;
}

Model *parseFile(const XMLElement *pElement) {
        string s {pElement->Attribute("file")};
        ifstream infile(s);

        if (!infile) {
                cerr << "Cannot open input file.\n";
                exit(1);
        }

        string line;
        getline(infile, line);
        int nPoints {stoi(line)};
        Model *model {new Model(nPoints)};
        int mode {0}; // 3 modes (vertex, normal, texture points)
        int w {0};

        while (getline(infile, line)) {
                if (w == nPoints) {
                        w = 0;
                        mode++;
                }

                vector<string> v;
                istringstream buf(line);

                for (string word; buf >> word;)
                        v.push_back(word);

                float point[3];
                int j {0};

                for (auto i {v.begin()}; i != v.end(); ++i, j++)
                        point[j] = stof(*i);

                if (mode == 0)
                        model->addVertexPoint(new Point(point[0], point[1], point[2]));
                else if (mode == 1)
                        model->addNormPoint(new Point(point[0], point[1], point[2]));
                else
                        model->addTextPoint(new Point(point[0], point[1], point[2]));

                w++;
        }

        Material *m {new Material()};
        Texture *t {new Texture()};

        if (pElement->Attribute("texture")) {
                string filename { pElement->Attribute("texture")};
                t->addFile(filename);
        }

        if (pElement->Attribute("type")) {
                float r {0};
                float g {0};
                float b {0};
                int flC {0};

                if (pElement->Attribute("r")) {
                        r = stof(pElement->Attribute("r"));
                        flC = 1;
                }

                if (pElement->Attribute("g")) {
                        g = stof(pElement->Attribute("g"));
                        flC = 1;
                }

                if (pElement->Attribute("b")) {
                        b = stof(pElement->Attribute("b"));
                        flC = 1;
                }

                if (flC)
                        m->addColor(r, g, b);

                string type { pElement->Attribute("type")};

                if (type.compare("diffuse") == 0)
                        m->addType(DIFFUSE);

                if (type.compare("specular") == 0)
                        m->addType(SPECULAR);

                if (type.compare("emissive") == 0)
                        m->addType(EMISSIVE);

                if (type.compare("ambiente") == 0)
                        m->addType(AMBIENTE);
        }

        t->addMaterial(m);
        model->addTexture(t);
        return model;
}

Catmull *parseCatmul(XMLElement *pElement) {
        Catmull *t { new Catmull() };

        if (pElement->Attribute("time")) {
                float time {fabs(stof(pElement->Attribute("time")))};
                int flag {stoi(pElement->Attribute("selfRotate"))};
                t->addFlag(flag);
                t->addTime(time);
        }

        XMLNode *pNode1 {pElement->FirstChild()};
        float x {0};
        float y {0};
        float z {0};

        for (; pNode1; pNode1 = pNode1->NextSibling()) {
                XMLElement *pElement1 = pNode1->ToElement();

                if (!strcmp(pElement1->Name(), "point")) {
                        if (pElement1->Attribute("x"))
                                x = stof(pElement1->Attribute("x"));

                        if (pElement1->Attribute("y"))
                                y = stof(pElement1->Attribute("y"));

                        if (pElement1->Attribute("z"))
                                z = stof(pElement1->Attribute("z"));

                        Point *p {new Point(x, y, z)};
                        t->addPoint(p);
                }
        }

        return t;
}
Translation *parseTranslate(XMLElement *pElement) {
        float x {0};
        float y {0};
        float z {0};

        if (pElement->Attribute("x"))
                x = stof(pElement->Attribute("x"));

        if (pElement->Attribute("y"))
                y = stof(pElement->Attribute("y"));

        if (pElement->Attribute("z"))
                z = stof(pElement->Attribute("z"));

        Translation *t {new Translation(Point(x, y, z))};
        return t;
}

Rotation *parseRotate(const XMLElement *pElement) {
        float time {0};
        float angle {0};
        float axisx {0};
        float axisy {0};
        float axisz {0};

        if (pElement->Attribute("angle"))
                angle = stof(pElement->Attribute("angle"));

        if (pElement->Attribute("axisX"))
                axisx = stof(pElement->Attribute("axisX"));

        if (pElement->Attribute("axisY"))
                axisy = stof(pElement->Attribute("axisY"));

        if (pElement->Attribute("axisZ"))
                axisz = stof(pElement->Attribute("axisZ"));

        if (pElement->Attribute("time"))
                time = fabs(stof(pElement->Attribute("time")));

        return new Rotation(Point(axisx, axisy, axisz), angle, time);
}

Scale *parseScale(const XMLElement *pElement) {
        float x {0};
        float y {0};
        float z {0};

        if (pElement->Attribute("x"))
                x = stof(pElement->Attribute("x"));

        if (pElement->Attribute("y"))
                y = stof(pElement->Attribute("y"));

        if (pElement->Attribute("z"))
                z = stof(pElement->Attribute("z"));

        return new Scale(Point(x, y, z));
}
