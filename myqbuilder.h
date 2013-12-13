#ifndef MYQBUILDER_H
#define MYQBUILDER_H


enum TagType {hbox, vbox, list, form, field};

class MyQBuilder
{
public:
    MyQBuilder(){};

    virtual void add(QLayout*)=0;
    virtual void add(QWidget*)=0;

    virtual void addChildren(XMLElement*);


    static MyQBuilder* create(TagType tag, XMLElement* el, MyQBuilder* parent);
    static TagType getTagType(const char*);



};

#endif // MYQBUILDER_H
