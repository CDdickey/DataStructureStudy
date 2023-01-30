#include "stdio.h"
#include "arraylist.h"

arraylist *Test = NULL;


int main(){
    Test = arrayInit();
    if(Test == NULL){
        printf("Error!\n");
    }

    showList(Test);
    //create
    addLast(Test,100);
    addLast(Test,333);
    showList(Test);
    addData(Test,0,233);
    addLast(Test,444);
    addData(Test,2,6);
    showList(Test);
    updateList(Test,2,232);
    addLast(Test,212);
    showList(Test);
    deleteLast(Test);
    deleteData(Test,0);
    printf("ret:%d\n",readList(Test,3));
    showList(Test);
    arrayDeInit(Test);
}