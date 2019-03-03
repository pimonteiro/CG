#include "parser.h"
#include "model.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace tinyxml2;
using namespace std;

Parser::Parser() {
}

void Parser::ReadXML(Scene* scene, char* xml) {
    XMLDocument xmlDoc;

    XMLError result = xmlDoc.LoadFile(xml);
    if(result != XML_SUCCESS) {
        cerr << "Error:" << result << endl;
        exit(1);
    }

    XMLNode* pRoot {xmlDoc.FirstChild()};
    if (pRoot == nullptr) {
        cout << "Warning: Malformed XML file" << endl;
        exit(0);
    } else {
        XMLElement* pElement {pRoot->FirstChildElement("model")};
        if (pElement == nullptr) {
            cout<< "Warning: No models found" << endl;
            exit(0);
        } else {
            string s;
            for(; pElement; pElement=pElement->NextSiblingElement()) {
                if(pElement->Attribute("file")) {
                    Model* model {new Model()};
                    s = pElement->Attribute("file");
                    ifstream infile(s);
                    if(!infile) {
                        cerr << "Cannot open input file.\n";
                    }
                    string line;
                    getline(infile, line);
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
                            if(it==0) x=stof(*i);
                            if(it==1) y=stof(*i);
                            if(it==2) z=stof(*i);
                            it++;
                        }
                        Point* p {new Point(x,y,z)};
                        model->addElement(p);
                    }
                    scene->addModel(model);
                }

            }
        }
    }
}
