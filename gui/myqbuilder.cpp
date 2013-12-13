#include <QLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableView>
#include <QMdiArea>

#include "tinyxml2.h"
using namespace tinyxml2;

#include <map>
using namespace std;

#include "utils.h"

#include "myqbuilder.h"

void MyQBuilder::addChildren(XMLElement* el){

    XMLElement* ch = el->FirstChildElement();
    while(ch){
        MyQBuilder* mqb = create(getTagType(ch->Name()), ch, this);
        mqb->addChildren(ch);
        ch = ch->NextSiblingElement();
    }
}

class MyQWidget : public QWidget, public MyQBuilder{
public:
    MyQWidget(){}
    void add(QLayout* ch){setLayout(ch);}
    void add(QWidget* ){}
};

class MyQVBoxLayout : public QVBoxLayout, public MyQBuilder{
public:
    MyQVBoxLayout(XMLElement* ){}
    void add(QLayout* ch){addLayout(ch);}
    void add(QWidget* ch){addWidget(ch);}
};

class MyQHBoxLayout : public QHBoxLayout, public MyQBuilder{
public:
    MyQHBoxLayout(XMLElement* ){}
    void add(QLayout* ch){addLayout(ch);}
    void add(QWidget* ch){addWidget(ch);}
};

class MyQFormLayout : public QFormLayout, public MyQBuilder{
public:
    MyQFormLayout(XMLElement* ){}
    void add(QLayout* ){}
    void add(QWidget* ){}
    void addChildren(XMLElement* el){

        XMLElement* ch = el->FirstChildElement();
        while(ch){
            if(TagType::field != getTagType(ch->Name()) )
                    continue;
            const char* l1 = ch->Attribute("label");
            addRow(l1, new QLineEdit());
            ch = ch->NextSiblingElement();
        }
    }
};

class MyQTableView : public QTableView, public MyQBuilder{
public:
    MyQTableView(XMLElement* ){}
    void add(QLayout* ){}
    void add(QWidget* ){}
    void addChildren(XMLElement* el){

        XMLElement* ch = el->FirstChildElement();
        while(ch){
            if(TagType::field != getTagType(ch->Name()) )
                    continue;
            //// column names
            ch = ch->NextSiblingElement();
        }
    }
};

MyQBuilder* MyQBuilder::create(TagType tag, XMLElement* el, MyQBuilder* parent){
    switch (tag) {
    case TagType::vbox:{
        MyQVBoxLayout* l=new MyQVBoxLayout(el);
        parent->add(l);
        return l;}
    case TagType::hbox:{
        MyQHBoxLayout* l=new MyQHBoxLayout(el);
        parent->add(l);
        return l;}
    case TagType::form:{
        MyQFormLayout* l=new MyQFormLayout(el);
        parent->add(l);
        return l;}
    case TagType::list:{
        MyQTableView* l=new MyQTableView(el);
        parent->add(l);
        return l;}
    default:
        break;
    }
    return nullptr;
}

void MyQBuilder::build(QMdiArea* mdi, const char* str){

    string xml = get_file_contents(str);
    XMLDocument doc;
    doc.Parse( xml.c_str() );
    XMLElement* el = doc.RootElement();

    MyQWidget* wid = new MyQWidget();

    mdi->addSubWindow(wid);
    wid->addChildren(el);
}

//typedef set<TagType> TagSet;
//typedef vector<TagSet> TagRules;
#define MAPLINE(X) { #X, TagType::X }
//typedef MyQBuilder::TagMap TagMap;

MyQBuilder::TagType MyQBuilder::getTagType(const char* s1){
    static TagMap tagmap = {
        MAPLINE(vbox),
        MAPLINE(hbox),
        MAPLINE(list),
        MAPLINE(form),
        MAPLINE(field),
    };
    return tagmap[s1];
}
