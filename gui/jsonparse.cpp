#include <QFile>
#include <QXmlStreamReader>
#include <yajl/yajl_parse.h>

class JsonParse{
    yajl_callbacks callbacks;
    yajl_handle hand;
protected:
    virtual int get_null() = 0;
    virtual int get_string(const unsigned char * stringVal, size_t stringLen) = 0;
    virtual int start_array() = 0;
    virtual int end_array() = 0;
    static int s_get_null(void * ctx){
        return ((JsonParse*)ctx)->get_null();
    }
    static int s_get_string(void * ctx, const unsigned char * stringVal, size_t stringLen){
        return ((JsonParse*)ctx)->get_string(stringVal, stringLen);
    }
    static int s_start_array(void * ctx){
        return ((JsonParse*)ctx)->start_array();
    }
    static int s_end_array(void * ctx){
        return ((JsonParse*)ctx)->end_array();
    }

    JsonParse(){
        callbacks = {
            s_get_null,
            NULL,
            NULL,
            NULL,
            NULL,
            s_get_string,
            NULL,
            NULL,
            NULL,
            s_start_array,
            s_end_array
        };
        hand = yajl_alloc(&callbacks, NULL, (void *) this);
    }
    ~JsonParse(){
        yajl_complete_parse(hand);
        yajl_free(hand);
    }
public:
    void parse(const unsigned char* data, size_t len){

        if (yajl_parse(hand, data, len) != yajl_status_ok) {
            return;
        }
    }
};

class JsonTableParse : public JsonParse{
    int arlevel=0;
    int row=-1;
    int col=-1;

    int get_null(){
        return true;
    }
    int get_string(const unsigned char * stringVal, size_t stringLen){

        setData(row,col, QString::fromUtf8(QByteArray( (const char* )stringVal, stringLen )));
        ++col;
        return true;
    }
    int start_array(){
        switch (++arlevel) {
        case 1:
            break;
        case 2:
            col=0;
            ++row;
            break;
        default:
            return false;
        }
        return true;
    }
    int end_array(){
        switch (arlevel--) {
        case 1:
        case 2:
            break;
        default:
            return false;
        }
        return true;
    }
protected:
    virtual void setData(int row, int col, QString val) = 0;
};
#include <QStandardItemModel>

class Json2TableModel : public JsonTableParse{
    QStandardItemModel *model;

    void setData(int row, int col, QString val){
        model->item(row, col)->setText(val);
    }

public:
    Json2TableModel(QStandardItemModel *m) : model(m){}

};

void filldata(QStandardItemModel *model){
    Json2TableModel jtm(model);
    const char* s = "[[ \"c11\", \"c11\",\"c11\",\"c11\" ],[ \"c11\", \"c11\",\"c11\",\"c11\" ],[ \"c11\", \"c11\",\"c11\",\"c11\" ]]";
    size_t l = strlen(s);
    jtm.parse((const unsigned char*)s,l);
//    XTFiller ff("/home/golubev/qt/gui/tabdata.xml");
//    ff.run();
//    QFile file("/home/golubev/qt/gui/tabdata.xml");
//    QXmlStreamReader xml(&file);
//    file.open(QIODevice::ReadOnly);
}

