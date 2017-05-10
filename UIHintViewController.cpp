#include"UIView.h"
#include"UIHintViewController.h"

/*enum UIViewborderStyle{
    NoneBorder,
    StarBorder,
    PoundBorder,
    EqualSignBorder,
    VerticalBarBorder,
    HorizonalBarBorder,
    AtSignBorder
};*/

UIHintViewController::UIHintViewController(const string ErrHint,UIView *rv):
    UIViewController(rv){
    CGRect windowFrame = CGRectMake(0,0,80,26);
    UIView *HintView = new UIView(windowFrame,HorizonalBarBorder);
    CGRect topicFrame = CGRectMake(4,6,71,6);
    UILabel *topic = new UILabel(topicFrame,ErrHint,StarBorder);

    HintView->addSubView(topic);
    rootView = HintView;
}
const string UIHintViewController::loadView(){
    if(rootView){
        rootView->drawRect();
    }
    cin.get();
    delete rootView;
    system("cls");
    return "";
}
