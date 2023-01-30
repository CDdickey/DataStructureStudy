#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define dataType int
#define dafaultSize 3

typedef enum{
    opretionSucess,
    initFail,
    outofIndex,
    noCap,
    resizeFail,
    reallocFail,


}errType;

typedef struct arraylist
{
    dataType *data;
    int lens;
    int cap;
}arraylist;

arraylist * arrayInit(){
    arraylist *list = NULL;
    list = malloc(sizeof(arraylist));
    if(list == NULL){
        return NULL;
    }
    list->lens = 0;
    list->cap = dafaultSize;
    list->data = malloc(dafaultSize);
    if(list->data == NULL){
        return NULL; 
    }else{
        return list;
    }
}

errType arrayDeInit(arraylist *list){
    free(list->data);
    free(list);
    return opretionSucess;
}

errType resize(arraylist *list,int new_cap){
    dataType* p=(dataType* )realloc(list->data,sizeof(dataType)* new_cap); //将arr中复制到p中
    if(p == NULL){
        return reallocFail;
    }else{
        list->data = p;
        list->cap = new_cap;
        return opretionSucess;
    }
}

errType checkCap(arraylist *list){
    if(list->lens < list->cap){
        if((list->lens)*2 < list->cap && list->lens != 0){
            if(opretionSucess == resize(list,list->cap/2)){
                return opretionSucess;
            }else{
                return resizeFail;
            }
        }
        return opretionSucess;
    }else{
        if(opretionSucess == resize(list,list->cap*2)){
            return opretionSucess;
        }else{
            return resizeFail;
        }
    }
}

//create
errType addLast(arraylist *list,dataType data){
    if(checkCap(list) != opretionSucess){
        return noCap;
    }
    list->data[list->lens] = data;
    list->lens++;
    return opretionSucess;

}

errType addData(arraylist *list,int index,dataType data){
    if(checkCap(list) != opretionSucess){
        return noCap;
    }
    if(index < list->lens){
        dataType *src = list->data+index;
        dataType *dst = src+1;
        memcpy(dst,src,(list->lens-index)*sizeof(dataType));
        list->data[index] = data;
        list->lens++;
        return opretionSucess;
    }
    if(index == list->lens){
        addLast(list,data);
        return opretionSucess;
    }
    return outofIndex;
}

//delete
errType deleteLast(arraylist *list){
    if(list->lens <= 0){
        return outofIndex;
    }
    list->data[list->lens]= '\0';
    list->lens--;
    if(checkCap(list) != opretionSucess){
        return noCap;
    }
    return opretionSucess;
}

errType deleteData(arraylist *list,int index){
    if(index < list->lens){
        dataType *src = list->data+index+1;
        dataType *dst = list->data+index;
        memcpy(dst,src,(list->lens-index)*sizeof(dataType));
        list->data[list->lens] = '\0';
        list->lens--;
        return opretionSucess;
    }
    if(index == list->lens){
        deleteLast(list);
        return opretionSucess;
    }
    return outofIndex;
}

//update
errType updateList(arraylist *list,int index,dataType data){
    if(index <= list->lens && index >= 0){
        list->data[index] = data;
        return opretionSucess;
    }
    return outofIndex;
}

//read
void showList(arraylist *list){
    for(int i=0;i<list->lens;i++){
        printf("%04d\t",list->data[i]);
    }
    printf("\n");
}

dataType readList(arraylist *list,int index){
    if(index <= list->lens && index >= 0){
        return list->data[index];
    }else{
        return 0;
    }
}