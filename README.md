# HOW TO USE IT
   
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

UIViewborderStyle is enum type,you can find its definition in `UIView.h`
