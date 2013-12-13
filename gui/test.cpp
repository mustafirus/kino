#include "tinyxml2.h"

#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QMdiArea>
using namespace std;
using namespace tinyxml2;

#include "myqbuilder.h"

#include <cstdint>

/*    auto s = tagrules[parent];
    if(s.find(tag)==s.end())
        return;
*/
void test(QMdiArea* mdi){
    MyQBuilder::build(mdi, "/home/golubev/qt/gui/window.xml");

    int a = 0;
    a=1;
}


#ifdef FUCK
enum TagType {hbox, vbox, list, form, field};
void addLayout(XMLElement* el, TagType tag, QLayout* parent_layout){
    switch (tag) {
    case vbox:
        //parent_layout->add
        break;
    default:
        break;
    }
}

void recurse(XMLElement* el, TagType parent_tag, QLayout* parent_layout){
    auto tag = vbox;//tagmap[el->Name()];

    cout << "creating " << el->Name() << endl;
    switch (tag) {
    case window:
       createWindow();
        break;
    default:
        break;
    }

    XMLElement* child = el->FirstChildElement();
    while(child){
        recurse(child, tag);
        child = child->NextSiblingElement();
    }
    return;
}


/*TagRules tagrules;


void addTagrule(TagRules& tagrules, TagType t, TagSet s){
    tagrules.emplace (tagrules.begin() + t, s);
}

void filltagrules(){
    addTagrule( tagrules, root, {window} );
    addTagrule( tagrules, window, {vbox, hbox, list, form} );
    addTagrule( tagrules, vbox, {hbox, list, form} );
    addTagrule( tagrules, hbox, {vbox, list, form} );
    addTagrule( tagrules, list, {field} );
    addTagrule( tagrules, form, {field} );
}
*/
void createWindow(){

}

void test(){
//    filltagrules();
    MyQObjectMaker::build("/home/golubev/qt/gui/window.xml");
}

class WidMaker{


    virtual add(QLayout* , XMLElement* el){}

    static void recurse(XMLElement* el, TagType parent){
        auto tag = tagmap[el->Name()];
        auto s = tagrules[parent];

        if(s.find(tag)==s.end())
            return;

        //printf("creating %s\n", el->Name());
        cout << "creating " << el->Name() << endl;
        switch (tag) {
        case window:
           createWindow();
            break;
        default:
            break;
        }

        XMLElement* child = el->FirstChildElement();
        while(child){
            recurse(child, tag);
            child = child->NextSiblingElement();
        }
        return;
    }
    static create(){}
};

class QWidgetM : public QWidget, public WidMaker {
    QWidgetM(){}
}


/*

cWid = new QWidget(centralWidget);
verticalLayout = new QVBoxLayout(cWid);
horizontalLayout_2 = new QHBoxLayout();

verticalLayout->addLayout(horizontalLayout_2);
horizontalLayout_3 = new QHBoxLayout();

tableView = new QTableView(cWid);

horizontalLayout_3->addWidget(tableView);
verticalLayout->addLayout(horizontalLayout_3);

horizontalLayout = new QHBoxLayout();

verticalLayout->addLayout(horizontalLayout);
*/
#endif //FUCK
