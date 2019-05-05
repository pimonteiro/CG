#include "headers/parser.h"
#include "headers/model.h"
#include "headers/group.h"
#include "headers/tinyxml2.h"
#include "headers/material.h"
#include "headers/scale.h"
#include "headers/rotation.h"
#include "headers/translation.h"
#include "headers/catmull.h"
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
Catmull *parseCatmul(XMLElement *pElement);


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

                if (!strcmp(pElement->Name(), "model")) {
                        if (pElement->Attribute("file")) {
                                Model *m {parseFile(pElement)};
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
        }
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
        //model->addColour(r, g, b);
        int tt { 0 };
        int mode { 0 };

        while (getline(infile, line)) {
                vector<string> v;
                istringstream buf(line);

                for (string word; buf >> word;)
                        v.push_back(word);

                float point[3];
                int j { 0 };

                for (auto i {v.begin()}; i != v.end(); ++i, j++)
                        point[j] = stof(*i);

                if (mode == 0)
                        model->addVertexPoint(new Point(point[0], point[1], point[2]));
                else if (mode == 1)
                        model->addNormPoint(new Point(point[0], point[1], point[2]));

                tt++;

                if (tt == nPoints) {
                        mode++;
                        tt = 0;
                }
        }

        Material m = Material();

        if (pElement->Attribute("type")) {
                float r {0};
                float g {0};
                float b {0};

                if (pElement->Attribute("r"))
                        r = stof(pElement->Attribute("r"));

                if (pElement->Attribute("g"))
                        g = stof(pElement->Attribute("g"));

                if (pElement->Attribute("b"))
                        b = stof(pElement->Attribute("b"));

                m.addColor(r, g, b);
                string type = pElement->Attribute("type");

                if (type.compare("diffuse") == 0)
                        m.addType(DIFFUSE);

                if (type.compare("specular") == 0)
                        m.addType(SPECULAR);

                if (type.compare("emissive") == 0)
                        m.addType(EMISSIVE);

                if (type.compare("ambiente") == 0)
                        m.addType(AMBIENTE);
        }

        model->addMaterial(m);
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
