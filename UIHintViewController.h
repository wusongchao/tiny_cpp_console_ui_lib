#ifndef UIHINTVIEWCONTROLLER_H_INCLUDED
#define UIHINTVIEWCONTROLLER_H_INCLUDED

#include"UIView.h"

class UIHintViewController:public UIViewController{
public:
    UIHintViewController(const string ErrHint,UIView *rv=NULL);
    const string loadView();
};

#endif // UIHINTVIEWCONTROLLER_H_INCLUDED
