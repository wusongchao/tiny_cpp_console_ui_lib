// UIView.cpp: implementation of the UIView class.
//
//////////////////////////////////////////////////////////////////////

#include "UIView.h"

#include<map>
#include<iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGRect CGRectMake(int x,int y,int w,int h){
    CGRect res = {x,y,w,h};
    return res;
}

size_t stringToOptionNum(const string forTrans){
    size_t stringLen = forTrans.size();
    size_t res = 0;
    for(size_t i=0;i<stringLen;i++){
        if(!isdigit(forTrans[i])){
            if(isspace(forTrans[i])){
                continue;
            }else{
                throw runtime_error("incorrect input!");
            }
        }else{
            res = res*10+forTrans[i]-'0';
        }
    }
    return res;
}


UIView::UIView(CGRect f,UIViewborderStyle ub,UIViewController* li):frame(f),parentView(NULL),listener(li){
    switch(ub){
        case NoneBorder:borderStyle = ' ';break;
        case StarBorder:borderStyle = '*';break;
        case PoundBorder:borderStyle = '#';break;
        case EqualSignBorder:borderStyle = '=';break;
        case VerticalBarBorder:borderStyle = '|';break;
        case HorizonalBarBorder:borderStyle = '-';break;
        case AtSignBorder:borderStyle = '@';break;
    }
}

void UIView::drawBorder(){
    //calculate this view's real position(in the console window's coordinate system)
    if(parentView){
        frame.x+=parentView->frame.x;
        frame.y+=parentView->frame.y;
    }

    //get the handle of console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD newpos;
    newpos.X = frame.x;
    newpos.Y = frame.y;

    int w = frame.width;
    int h = frame.height;

    for(int i=1;i<=h;i++){
        newpos.Y = frame.y+i-1;
        SetConsoleCursorPosition(hOut,newpos);

        if(i==1||i==h){
            for(int j=1;j<=w;j++){
                cout << borderStyle;
            }
        }else{
            cout << borderStyle;
            for(int j=2;j<w;j++){
                cout << " ";
            }
            cout << borderStyle;
        }
    }
}

void UIView::drawRect(){
    drawBorder();

    size_t subViewsSize = subViews.size();
    for(size_t i=0;i!=subViewsSize;++i){
        subViews[i]->drawRect();
    }
}

void UIView::addEventListener(UIViewController *li){
    listener = li;
}

void UIView::addSubView(UIView *view){
    subViews.push_back(view);
}

void UIView::setParentView(UIView *pv){
    parentView = pv;
}

UIView::~UIView(){
    size_t subViewsSize = subViews.size();

    for(size_t i=0;i!=subViewsSize;++i){
        delete subViews[i];
    }
}

UILabel::UILabel(CGRect f,const string t,UIViewborderStyle b):UIView(f,b),text(t),hasBorder(0){
    if(b!=NoneBorder){
        hasBorder = 1;
    }
}

void UILabel::drawRect(){
    if(hasBorder){
        // use parent's drawRect function to build the border.
        drawBorder();
        // In the function drawBorder(),the frame is set.
        //frame.x++;
        //frame.y++;
    }else{
        if(parentView){
            frame.x+=parentView->frame.x;
            frame.y+=parentView->frame.y;
        }
    }

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newpos;

    newpos.X = frame.x;
    newpos.Y = frame.y;

    if(hasBorder){
        newpos.X++;
        newpos.Y++;
    }

    SetConsoleCursorPosition(hOut,newpos);

    size_t nowCharPos = 0;
    std::string::size_type lenOfText = text.size();

    int w = frame.width;
    int h = frame.height;

    while(nowCharPos<lenOfText){
        while(nowCharPos<lenOfText&&(nowCharPos+1)%w){
            cout << text[nowCharPos++];
        }

        if(nowCharPos<lenOfText){
            cout << text[nowCharPos++];
        }

        newpos.Y++;
        SetConsoleCursorPosition(hOut,newpos);
    }
}


UIOptionList::UIOptionList(CGRect f,vector<string>& li,UIViewborderStyle b):UIView(f,b),itemLists(li),hasBorder(0){
    if(b!=NoneBorder){
        hasBorder = 1;
    }
}

void UIOptionList::drawRect(){
    if(hasBorder){
        // use parent's drawRect function to build the border.
        drawBorder();
        // In the function drawBorder(),the frame is set.
        //frame.x++;
        //frame.y++;
    }else{
        if(parentView){
            frame.x+=parentView->frame.x;
            frame.y+=parentView->frame.y;
        }
    }

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newpos;

    newpos.X = frame.x;
    newpos.Y = frame.y;
    if(hasBorder){
        newpos.X++;
        newpos.Y++;
    }

    SetConsoleCursorPosition(hOut,newpos);

    size_t itemListsSize = itemLists.size();
    for(size_t i=0;i<itemListsSize;i++){
        cout << i+1 << "." << itemLists[i];
        newpos.Y++;
        SetConsoleCursorPosition(hOut,newpos);
    }
    notify();
}

//load the items list
void UIOptionList::notify(){
    if(listener){
        size_t itemsLen = itemLists.size();

        for(size_t i=0;i<itemsLen;i++){
            listener->loadOptions(i+1,itemLists[i]);
        }
    }
}

UIInputField::UIInputField(CGRect f,const string nt,UIInputFieldStyle s,UIViewborderStyle b):
    UIView(f,b),notifyType(nt),style(s),hasBorder(0){
    if(b!=NoneBorder){
        hasBorder = 1;
    }
}

void UIInputField::drawRect(){
    if(hasBorder){
        // use parent's drawRect function to build the border.
        drawBorder();
        // In the function drawBorder(),the frame is set.
        //frame.x++;
        //frame.y++;
    }else{
        if(parentView){
            frame.x+=parentView->frame.x;
            frame.y+=parentView->frame.y;
        }
    }

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newpos;

    newpos.X = frame.x;
    newpos.Y = frame.y;

    if(hasBorder){
        newpos.X++;
        newpos.Y++;
    }
    SetConsoleCursorPosition(hOut,newpos);

    if(style==Password){
        WORD wOldColorAttrs;
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        GetConsoleScreenBufferInfo(hOut,&csbiInfo);
        wOldColorAttrs = csbiInfo.wAttributes;

        // set the font-color to black
        SetConsoleTextAttribute(hOut,0);
        getline(cin,text);
        SetConsoleTextAttribute(hOut,wOldColorAttrs);
        notify(notifyType,text);
    }else if(style==Text){
        getline(cin,text);
        notify(notifyType,text);
    }else{
        getline(cin,text);
        notify(notifyType,text);
    }

}

void UIInputField::notify(string fieldType,string &info){
    if(listener){
        listener->update(fieldType,info);
    }
}


/*
class UILoginViewController:UIViewController{

};

class UIOptionViewController:*/

UIViewController::UIViewController(UIView *rv):rootView(rv){
}
const string UIViewController::loadView(){
    return "";
}

void UIViewController::loadOptions(size_t No,string &option){
    options[No] = option;
}

void UIViewController::update(string fieldType,string &info){
    informations[fieldType] = info;
}


