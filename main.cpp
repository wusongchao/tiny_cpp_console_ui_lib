#include"UIView.h"
#include"UIView.cpp"
#include"UIHintViewController.h"
#include"UIHintViewController.cpp"
#include"tinyxml2.h"
#include"tinyxml2.cpp"
#include<iostream>

using namespace std;
using namespace tinyxml2;
int main(void){
//    UIHintViewController *v1 = new UIHintViewController("Hello World!");
//    v1->loadView();
    XMLDocument doc;
    doc.LoadFile("test.xml");
    const char* content = doc.FirstChildElement("Hello")->GetText();
    cout << content;
    return 0;
}
