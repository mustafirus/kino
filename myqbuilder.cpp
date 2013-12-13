#include <QLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableView>
#include <tinyxml2.h>
using namespace tinyxml2;
#include "myqbuilder.h"

void MyQBuilder::addChildren(XMLElement* el){

    XMLElement* ch = el->FirstChildElement();
    while(ch){
        MyQBuilder* mqb = create(getTagType(ch->Name()), ch, this);
        mqb->addChildren(ch);
        ch = ch->NextSiblingElement();
    }
}


class MyQVBoxLayout : public QVBoxLayout, public MyQBuilder{
public:
    MyQVBoxLayout(XMLElement* el){}
    void add(QLayout* ch){addLayout(ch);}
    void add(QWidget* ch){addWidget(ch);}
};

class MyQHBoxLayout : public QHBoxLayout, public MyQBuilder{
public:
    MyQHBoxLayout(XMLElement* el){}
    void add(QLayout* ch){addLayout(ch);}
    void add(QWidget* ch){addWidget(ch);}
};

class MyQFormLayout : public QFormLayout, public MyQBuilder{
public:
    MyQFormLayout(XMLElement* el){}
    void add(QLayout* ){}
    void add(QWidget* ){}
    void addChildren(XMLElement* el){

        XMLElement* ch = el->FirstChildElement();
        while(ch){
            if(field != getTagType(ch->Name()) )
                    continue;
            addRow(el->Attribute("label"), new QLineEdit());
            ch = ch->NextSiblingElement();
        }
    }
};

class MyQTableView : public QTableView, public MyQBuilder{
public:
    MyQTableView(XMLElement* el){}
    void add(QLayout* ){}
    void add(QWidget* ){}
    void addChildren(XMLElement* el){

        XMLElement* ch = el->FirstChildElement();
        while(ch){
            if(field != getTagType(ch->Name()) )
                    continue;
            //// column names
            ch = ch->NextSiblingElement();
        }
    }
};

MyQBuilder* MyQBuilder::create(TagType tag, XMLElement* el, MyQBuilder* parent){
    switch (tag) {
    case vbox:{
        MyQVBoxLayout* l=new MyQVBoxLayout(el);
        parent->add(l);
        return l;}
    case hbox:{
        MyQHBoxLayout* l=new MyQHBoxLayout(el);
        parent->add(l);
        return l;}
    case form:{
        MyQFormLayout* l=new MyQFormLayout(el);
        parent->add(l);
        return l;}
    case list:{
        MyQTableView* l=new MyQTableView(el);
        parent->add(l);
        return l;}
    default:
        break;
    }
    return nullptr;
}

TagType MyQBuilder::getTagType(const char*){
    return vbox;
}
