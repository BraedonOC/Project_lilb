#ifndef OBJECT_H
#define OBJECT_H


struct Object {
    double x;
    double y;
    int type;

    //****** optional variables that can be used ******
    int colorOffsetR = 0;
    int colorOffsetG = 0;
    int colorOffsetB = 0;
    int shapeOffset = 0;
    int rotation = 0;
};


#endif
