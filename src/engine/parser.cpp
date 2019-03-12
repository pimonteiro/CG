#include "headers/parser.h"
#include "headers/model.h"
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


Parser::Parser() {
}

void parseFile(Scene* scene, const XMLElement* pElement) {
    Model* model {new Model()};
    string s {pElement->Attribute("file")};
    ifstream infile(s);
    if(!infile) {
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
        for(string word; buf >> word;) {
            v.push_back(word);
        }
        int it {0};
        float x;
        float y;
        float z;
        for(vector<string>::const_iterator i {v.begin()}; i != v.end(); ++i) {
            switch(it) {
                case 0 : x=stof(*i);
                         break;
                case 1 : y=stof(*i);
                         break;
                case 2 : z=stof(*i);
                         break;
                default : break;
            }
            it++;
        }
        switch(endTriangle) {
            case 0 : triangle->addX(new Point(x,y,z));
                     break;
            case 1 : triangle->addY(new Point(x,y,z));
                     break;
            case 2 : triangle->addZ(new Point(x,y,z));
                     model->addElement(triangle);
                     triangle = new Triangle();
                     break;
            default : break;
        }
        endTriangle != 2 ? endTriangle++ : endTriangle = 0;
    }
    scene->addModel(model);
}

void parseDoc(Scene* scene, XMLNode* pNode) {
    string s;
    for(; pNode; pNode=pNode->NextSibling()) {
        XMLElement* pElement {pNode->ToElement()};
        if(!strcmp(pElement->Name(),"model")) {
            if(pElement->Attribute("file")) {
                parseFile(scene, pElement);
            }
        }
        if (!strcmp(pElement->Name(),"translate")) {
            float x = 0;
            float y = 0;
            float z = 0;

            if(pElement->Attribute("X")) {
                x = stof(pElement->Attribute("X"));
            }
            if(pElement->Attribute("Y")) {
                y = stof(pElement->Attribute("Y"));
            }
            if(pElement->Attribute("Z")){
                z = stof(pElement->Attribute("Z"));
            }

            Translation* t = new Translation(Point(x,y,z));

        }
        if (!strcmp(pElement->Name(),"rotate")) {
            float angle {0};
            float axisx {0};
            float axisy {0};
            float axisz {0};

            if(pElement->Attribute("angle")) {
                angle = stof(pElement->Attribute("angle"));
            }
            if(pElement->Attribute("axisX")) {
                axisx = stof(pElement->Attribute("axisX"));
            }
            if(pElement->Attribute("axisY")) {
                axisy = stof(pElement->Attribute("axisY"));
            }
            if(pElement->Attribute("axisZ")){
                axisz = stof(pElement->Attribute("axisZ"));
            }

            Rotation* r = new Rotation(Point(axisx, axisy, axisz), angle);
        }
        if (!strcmp(pElement->Name(),"scale")) {
            float x = 0;
            float y = 0;
            float z = 0;

            if(pElement->Attribute("X")) {
                x = stof(pElement->Attribute("X"));
            }
            if(pElement->Attribute("Y")) {
                y = stof(pElement->Attribute("Y"));
            }
            if(pElement->Attribute("Z")){
                z = stof(pElement->Attribute("Z"));
            }

            Scale* s = new Scale(Point(x,y,z));

        }
        if (!strcmp(pElement->Name(),"group")) {
            // TODO
        }
    }
}

void Parser::ReadXML(Scene* scene, const char* xml) {
    XMLDocument xmlDoc;

    XMLError result {xmlDoc.LoadFile(xml)};
    if(result != XML_SUCCESS) {
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
            cout<< "Warning: No models found" << endl;
            exit(0);
        } else {
            parseDoc(scene, pNode);
        }
    }
}
