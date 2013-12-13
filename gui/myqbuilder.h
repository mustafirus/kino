#ifndef MYQBUILDER_H
#define MYQBUILDER_H



class MyQBuilder
{
public:
    enum class TagType {null=0, hbox, vbox, list, form, field};
    typedef map<string,TagType> TagMap;

    MyQBuilder(){};

    virtual void add(QLayout*)=0;
    virtual void add(QWidget*)=0;

    virtual void addChildren(XMLElement*);


    static MyQBuilder* create(TagType tag, XMLElement* el, MyQBuilder* parent);
    static TagType getTagType(const char*);
    static void build(QMdiArea* mdi, const char* str);

};

#endif // MYQBUILDER_H
