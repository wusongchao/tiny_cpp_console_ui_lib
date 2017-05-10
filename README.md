# HOW TO USE IT
   
Please forgive my poor English.   
   
   
First,define a class inherit from `UIView`,like this:
```cpp
#ifndef UILOGINVIEW_H_INCLUDED
#define UILOGINVIEW_H_INCLUDED

#include"UIView.h"

class UILoginView:public UIView{
public:
    UILoginView(CGRect f,UIViewborderStyle ub);
};

#endif // UILOGINVIEW_H_INCLUDED
```
CGRect can be create by function `CGRectMake(int x,int y,int width,int height)`,
x and y mean the position(relate to the console window,both should be positive number)

UIViewborderStyle is an enum type,you can find its definition in `UIView.h`.

In the implement of `UILoginView`:
```cpp
#include"UIView.h"
#include"UILoginView.h"

using namespace std;
UILoginView::UILoginView(CGRect f,UIViewborderStyle ub):
    UIView(f,ub){
    CGRect topicFrame = CGRectMake(14,3,52,7);
    UILabel *topic = new UILabel(topicFrame,"         Welcome To The Management System",EqualSignBorder);
    CGRect subTitleFrame = CGRectMake(24,6,40,1);
    UILabel *subTitle = new UILabel(subTitleFrame,"Please input your ID and Password");
    CGRect hintFrame = CGRectMake(15,8,55,1);
    UILabel *hintLabel = new UILabel(hintFrame,"Because of VC's bug,please press the [Enter] twice");

    CGRect userIDLabelFrame = CGRectMake(21,14,4,1);
    UILabel *userIDLabel = new UILabel(userIDLabelFrame,"ID:");
    CGRect passWordLabelFrame = CGRectMake(21,15,9,1);
    UILabel *passWordLabel = new UILabel(passWordLabelFrame,"password:");
    CGRect idInputFieldFrame = CGRectMake(25,14,15,1);
    UIInputField *idInputField = new UIInputField(idInputFieldFrame,"text",Text);
    CGRect passwordInputFieldFrame = CGRectMake(31,15,17,1);
    UIInputField *passwordInputField = new UIInputField(passwordInputFieldFrame,"password",Password);
    addSubView(topic);
    addSubView(subTitle);
    addSubView(hintLabel);
    addSubView(userIDLabel);
    addSubView(passWordLabel);
    addSubView(idInputField);//5
    addSubView(passwordInputField);//6
}
```

Now we have three kinds of UIElement:UILabel,UIInputField,UIOptionView,
you can addEventListener for UIInputField or UIOptionView.

Let's see UIInputField's Contructor:
`UIInputField(CGRect f,const string nt,UIInputFieldStyle s=Text,UIViewborderStyle b=NoneBorder);`
nt represent the notifyType,used as the key in its Listener's map.
UIInputFieldStyle is also an enum type,if you choose the Password type,the Input area will be hidden,
like linux.

Each view will draw its subviews.

Then,define a class inherit from UIViewController.
```cpp
#ifndef UILOGINVIEWCONTROLLER_H_INCLUDED
#define UILOGINVIEWCONTROLLER_H_INCLUDED

#include"UIView.h"
#include"UILoginView.h"

class UILoginViewController:public UIViewController{
public:
    UILoginViewController(UIView *rv=NULL);
    const string loadView();
};
```
Implement:
```cpp
UILoginViewController::UILoginViewController(UIView *rv):
    UIViewController(rv){
    rootView->subViews[5]->addEventListener(this);
    rootView->subViews[6]->addEventListener(this);
}
const string UILoginViewController::loadView(){
    if(rootView){
        rootView->drawRect();
    }
    Administrator *forAdminCheck = StaffStore::sharedStore()->getAdministratorByID(
        stringToOptionNum(informations["text"]));
    if(forAdminCheck){
        if(forAdminCheck->getPassword()==informations["password"]){
            globalUserID = stringToOptionNum(informations["text"]);
            globalUserName = StaffStore::sharedStore()->getAdministratorByID(globalUserID)->getName();
            return "UIAdminOptionView";
        }else{
            UIHintViewController hintView("Wrong Password,please press [Enter] to go back to the LoginView");
            hintView.loadView();
            return loadView();
        }
    }else{
        Coach* forCoachCheck = StaffStore::sharedStore()->getCoachByID(
            stringToOptionNum(informations["text"]));
        if(forCoachCheck){
            if(forCoachCheck->getPassword()==informations["password"]){
                globalUserID = stringToOptionNum(informations["text"]);
                globalUserName = StaffStore::sharedStore()->getCoachByID(globalUserID)->getName();
                return "UICoachOptionView";
            }else{
                UIHintViewController hintView("Wrong Password,please press [Enter] to go back to the LoginView");
                hintView.loadView();
                return loadView();
            }
        }else{
            UIHintViewController hintView("can't find this ID,please press [Enter] to go back to the LoginView");
            hintView.loadView();
            return loadView();
        }
    }
    return "";
}
```
imple your 
