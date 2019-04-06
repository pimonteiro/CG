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

using namespace tinyxml2;
using namespace std;


void parseDoc(Group*, XMLNode*);
Model* parseFile(const XMLElement*);
Translation* parseTranslate(const XMLElement*);
Scale* parseScale(const XMLElement*);
Rotation* parseRotate(const XMLElement*);


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
        Model* model {new Model()};
        float r {0};
        float g {0};
        float b {0};

        if (pElement->Attribute("r"))
                r = stof(pElement->Attribute("r"));

        if (pElement->Attribute("g"))
                g = stof(pElement->Attribute("g"));

        if (pElement->Attribute("b"))
                b = stof(pElement->Attribute("b"));

        model->addColour(r, g, b);
        string s {pElement->Attribute("file")};
        ifstream infile(s);

        if (!infile) {
                cerr << "Cannot open input file.\n";
                exit(1);
        }

        string line;
        // Number of points
        getline(infile, line);
        Triangle* triangle {new Triangle};
        int endTriangle {0};

        while (getline(infile, line)) {
                vector<string> v;
                istringstream buf(line);

                for (string word; buf >> word;)
                        v.push_back(word);

                int it {0};
                float x;
                float y;
                float z;

                for (vector<string>::const_iterator i {v.begin()}; i != v.end(); ++i) {
                        switch (it) {
                        case 0 :
                                x = stof(*i);
                                break;

                        case 1 :
                                y = stof(*i);
                                break;

                        case 2 :
                                z = stof(*i);
                                break;

                        default :
                                break;
                        }

                        it++;
                }

                switch (endTriangle) {
                case 0 :
                        triangle->addX(new Point(x, y, z));
                        break;

                case 1 :
                        triangle->addY(new Point(x, y, z));
                        break;

                case 2 :
                        triangle->addZ(new Point(x, y, z));
                        model->addElement(triangle);
                        triangle = new Triangle();
                        break;

                default :
                        break;
                }

                endTriangle = (endTriangle + 1) % 3;
        }

        return model;
}

Translation*
parseTranslate(const XMLElement* pElement)
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

        return new Translation(Point(x, y, z));
}

Rotation*
parseRotate(const XMLElement* pElement)
{
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

        return new Rotation(Point(axisx, axisy, axisz), angle);
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

