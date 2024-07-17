
#ifndef VALUE_H
#define VALUE_H

class RealValue;

class Value {
public:
    virtual int value()=0;
    virtual RealValue* base()=0;
    virtual ~Value(){};
};

class RealValue : public  Value {
private:
    int num =0;
public:
    RealValue(int num): num(num){}
    int value() override {return num;}
    int& getNum(){return  num;}
    RealValue* base()override {return this;};
};

class ValueDecorate :public  Value{
protected:
    Value* source;
public:
    ValueDecorate(Value* source):source(source){}
    RealValue* base()override{return source->base();};
    virtual ~ValueDecorate(){delete source;}
};

class TmpValue : public ValueDecorate{
private:
    int delt = 0;
public:
    TmpValue(Value* value, int delt): ValueDecorate(value), delt(delt){};
    int value() override{return source->value() + delt;}
};

#endif
