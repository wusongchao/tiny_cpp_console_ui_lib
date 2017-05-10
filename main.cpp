#include"UIView.h"
#include"UIView.cpp"
#include"UIHintViewController.h"
#include"UIHintViewController.cpp"

int main(void){
    UIHintViewController *v1 = new UIHintViewController("Hello World!");
    v1->loadView();
    return 0;
}
