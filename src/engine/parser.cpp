#include "headers/parser.h"
#include "headers/model.h"
#include "headers/group.h"
#include "headers/tinyxml2.h"
#include "headers/scale.h"
#include "headers/rotation.h"
#include "headers/translation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>


using namespace tinyxml2;
using namespace std;


void parseDoc(Group*, XMLNode*);
Model* parseFile(const XMLElement*);
Translation* parseTranslate(XMLElement*);
Scale* parseScale(const XMLElement*);
Rotation* parseRotate(const XMLElement*);


float
randomF()
{
        std::random_device seeder;
        std::mt19937 engine(seeder());
        std::uniform_real_distribution<float> dist(0, 1);
        return dist(engine);
}

Parser::Parser()
{
}

void
Parser::ReadXML(Group* group, const char* xml)
{
        XMLDocument xmlDoc;
        XMLError result {xmlDoc.LoadFile(xml)};

        if (result != XML_SUCCESS) {
                cerr << "Error:" << result << endl;
                exit(1);
        }

        XMLNode* pRoot {xmlDoc.FirstChild()};

        if (pRoot == nullptr) {
                cout << "Warning: Malformed XML file" << endl;
                exit(0);
        } else {
                XMLNode* pNode {pRoot->FirstChild()};

                if (pNode == nullptr) {
                        cout << "Warning: No models found" << endl;
                        exit(0);
                } else
                        parseDoc(group, pNode);
        }
}

void
parseDoc(Group* group, XMLNode* pN)
{
        XMLNode * pNode {pN->FirstChild()};

        if (pNode == nullptr)
                exit(0);

        for (; pNode; pNode = pNode->NextSibling()) {
                XMLElement* pElement {pNode->ToElement()};

                if (!strcmp(pElement->Name(), "model")) {
                        if (pElement->Attribute("file")) {
                                Model* m {parseFile(pElement)};
                                group->addModel(m);
                        }
                }

                if (!strcmp(pElement->Name(), "translate")) {
                        Translation* t {parseTranslate(pElement)};
                        group->addTransformation(t);
                }

                if (!strcmp(pElement->Name(), "rotate")) {
                        Rotation* r {parseRotate(pElement)};
                        group->addTransformation(r);
                }

                if (!strcmp(pElement->Name(), "scale")) {
                        Scale* s {parseScale(pElement)};
                        group->addTransformation(s);
                }

                if (!strcmp(pElement->Name(), "group")) {
                        Group* g {new Group()};
                        parseDoc(g, pNode);
                        group->addGroup(g);
                }

                if (!strcmp(pElement->Name(), "models"))
                        parseDoc(group, pNode);
        }
}

Model*
parseFile(const XMLElement* pElement)
{
        float r {randomF()};
        float g {randomF()};
        float b {randomF()};

        if (pElement->Attribute("r"))
                r = stof(pElement->Attribute("r"));

        if (pElement->Attribute("g"))
                g = stof(pElement->Attribute("g"));

        if (pElement->Attribute("b"))
                b = stof(pElement->Attribute("b"));

        string s {pElement->Attribute("file")};
        ifstream infile(s);

        if (!infile) {
                cerr << "Cannot open input file.\n";
                exit(1);
        }

        string line;
        getline(infile, line);
        int nPoints {stoi(line)};
        Model* model {new Model(nPoints)};
        model->addColour(r, g, b);

        while (getline(infile, line)) {
                vector<string> v;
                istringstream buf(line);

                for (string word; buf >> word;)
                        v.push_back(word);

                for (auto i {v.begin()}; i != v.end(); ++i)
                        model->addElement(stof(*i));
        }

        return model;
}

Translation*
parseTranslate(XMLElement* pElement)
{
        Translation* t {new Translation()};

        if (pElement->Attribute("time"))
                t->addTime(fabs(stof(pElement->Attribute("time"))));

        XMLNode *pNode1 {pElement->FirstChild()};
        float x {0};
        float y {0};
        float z {0};

        for (; pNode1; pNode1 = pNode1->NextSibling()) {
                XMLElement* pElement1 = pNode1->ToElement();

                if (!strcmp(pElement1->Name(), "point")) {
                        if (pElement1->Attribute("x"))
                                x = stof(pElement1->Attribute("x"));

                        if (pElement1->Attribute("y"))
                                y = stof(pElement1->Attribute("y"));

                        if (pElement1->Attribute("z"))
                                z = stof(pElement1->Attribute("z"));

                        t->addPoint(new Point(x, y, z));
                }
        }

        return t;
}

Rotation*
parseRotate(const XMLElement* pElement)
{
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

Scale*
parseScale(const XMLElement* pElement)
{
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

