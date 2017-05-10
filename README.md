# HOW TO USE IT
   
please for give my poor English   
   
   
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

UIViewborderStyle is enum type,you can find its definition in `UIView.h`.

In the implement of `UILoginView`:
```cpp
#include"UIView.h"
#include"UILoginView.h"

#include<map>
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

now we have three kinds of UIElement:UILabel,UIInputField,UIOptionView,
