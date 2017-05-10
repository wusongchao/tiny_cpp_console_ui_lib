# HOW TO USE IT
   
Please forgive my poor English.   

And that is how it looks:
![Alt text](https://github.com/wusongchao/tiny_cpp_console_ui_lib/raw/master/main.png)
   
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

In the constructor,you should addEventListener for the UIInputField(or UITableView),
the main logic is written in the loadView Function,when the user finish his/her input,
the UIInputField will notify its Listener,and the information can be gotten in the information map.

In this sample,StaffStore is a singleton,belongs to the `Model` layer.
I've made a UIHintViewController for you to display some simple information,
such as Error information.

## In the Main Loop

```cpp
    map<string,UIViewController*> viewControllers;
    ServiceTypeStore::sharedStore();
    ClientStore::sharedStore()->loadData();
    StaffStore::sharedStore()->loadData();
    FinanceStore::sharedStore()->loadMachineData();

    //create the LoginView,then add it to the map
    CGRect windowFrame = CGRectMake(0,0,80,26);
    UILoginView *loginView = new UILoginView(windowFrame,StarBorder);
    UILoginViewController *loginViewController = new UILoginViewController(loginView);
    viewControllers["UILoginView"] = loginViewController;
```
First, prepare a map to store UIViewControllers.

```cpp
 string nextView;
 string currentView = "UILoginView";

 //control the switch
while(1){
  nextView = viewControllers[currentView]->loadView();
  currentView = nextView;
  if(currentView=="UIAdminOptionView"&&viewControllers["UIAdminOptionView"]==NULL){
      UIAdminOptionView *adminOptionView = new UIAdminOptionView(windowFrame2,StarBorder);
      UIAdminOptionViewController *adminOptionViewController = new UIAdminOptionViewController(adminOptionView);
      viewControllers["UIAdminOptionView"] = adminOptionViewController;
  }else{
      if(currentView=="UICoachOptionView"&&viewControllers["UICoachOptionView"]==NULL){
          UICoachOptionView *coachOptionView = new UICoachOptionView(windowFrame2,StarBorder);
          UICoachOptionViewController *coachOptionViewController = new UICoachOptionViewController(coachOptionView);
          viewControllers["UICoachOptionView"] = coachOptionViewController;
      }
  }
  system("cls");
}
```
That's is how to switch between different ViewControllers.

By the way,their is a sample of how to use UIOptionView
```cpp
 vector<string> r1;
 r1.push_back("name");
 r1.push_back("password");
 r1.push_back("age");
 r1.push_back("phonenumber");
 r1.push_back("salary");
 r1.push_back("bonus");
 UIRegisterAdministratorViewController *registerAdminViewController = new UIRegisterAdministratorViewController(
                                                                     r1,"Administrator");
 viewControllers["UIRegisterAdministratorView"] = registerAdminViewController;
 ```
 UIRegisterAdministratorViewController has a UIOptionView,and it take the vector r1 as a parameter,
 Don't forget to addEventlistener for the UIOptionView!!!!
 
