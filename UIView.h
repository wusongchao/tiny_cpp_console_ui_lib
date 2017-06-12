// UIView.h: interface for the UIView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIVIEW_H__6EA40005_438B_4C64_BFCC_17B8A56DA57F__INCLUDED_)
#define AFX_UIVIEW_H__6EA40005_438B_4C64_BFCC_17B8A56DA57F__INCLUDED_

#pragma warning (disable: 4786)

#ifdef _MSC_VER
    #pragma warning(disable: 4786)
    #if _MSC_VER > 1000
        #pragma once
    #endif // _MSC_VER > 1000
#endif

#include<iostream>
#include<vector>
#include<string>
#include<windows.h>
#include<map>
#include<cctype>
#include<stdexcept>
#define TABLECELL_MAXWIDTH 25

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::map;
using std::runtime_error;
using namespace std;

extern unsigned int globalUserID;
extern string globalUserName;

enum UIViewborderStyle{
    NoneBorder,
    StarBorder,
    PoundBorder,
    EqualSignBorder,
    VerticalBarBorder,
    HorizonalBarBorder,
    AtSignBorder
};

enum UIInputFieldStyle{
    Text,
    Password,
    Option
};

typedef struct {
    int x;
    int y;
    int width;
    int height;
} CGRect;


CGRect CGRectMake(int x,int y,int w,int h);
// for the compatibility with c_style string,use string instead of string&
size_t stringToOptionNum(const string forTrans);

class UIViewController;

class UIView{
protected:
    char borderStyle;
    UIView *parentView;
    UIViewController *listener;

public:
    vector<UIView *> subViews;
    CGRect frame;

    UIView(CGRect f,UIViewborderStyle ub,UIViewController *li=NULL);

    void drawBorder();
    virtual void drawRect();

    void addEventListener(UIViewController *li);

    void addSubView(UIView *view);

    void setParentView(UIView *pv);

    virtual ~UIView();
};

class UILabel:public UIView{
protected:
    string text;
    bool hasBorder;

public:
    UILabel(CGRect f,const string t="",UIViewborderStyle b=NoneBorder);

    void drawRect();
};


class UIViewController{
protected:
    UIView *rootView;

    //
public:
    map<size_t,string> options;
    map<string,string> informations;

    UIViewController(UIView *rv=NULL);

    virtual const string loadView();

    void loadOptions(size_t No,string &option);

    void update(string fieldType,string &info);

};
/*
class UILoginViewController:UIViewController{

};

class UIOptionViewController:*/


class UIOptionList:public UIView{
protected:
    bool hasBorder;
    vector<string> itemLists;

public:
    UIOptionList(CGRect f,vector<string>& li,UIViewborderStyle b=NoneBorder);

    void drawRect();

    //load the items list
    void notify();

};

class UIInputField:public UIView{
protected:
    string notifyType;
    UIInputFieldStyle style;
    string text;
    bool hasBorder;

public:
    UIInputField(CGRect f,const string nt,UIInputFieldStyle s=Text,UIViewborderStyle b=NoneBorder);
    void drawRect();

    void notify(string fieldType,string &info);
};


class UITableView:UIView{
protected:
    void* dataSource;

public:
    UITableView();
};



#endif // !defined(AFX_UIVIEW_H__6EA40005_438B_4C64_BFCC_17B8A56DA57F__INCLUDED_)
