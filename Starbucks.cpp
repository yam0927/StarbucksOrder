#include<iostream>
#include<vector>
#include<map>
using namespace std;

map<int, string> m_coffeeType;
map<int, string> m_cupSize;
map<int, string> m_tem;
map<int, string> m_sugur;
map<int, string> m_juice;

class Order;
class Decorator;
class Decorator1;
class Decorator2;
class Coffee;

class Coffee {
private:
    string coffeeType;
    string temperature;
    string cupSize;
public:
    Coffee(){}

    void setType(string coffeeTy){
        coffeeType = coffeeTy;
    }
    void setTem(string tem){
        temperature = tem;
    }
    void setSize(string _size){
        cupSize = _size;
    }
    
    double getPrice(){
        if(coffeeType == "coffee1" && cupSize == "small")
            return 10.0;
        if(coffeeType == "coffee1" && cupSize == "medium")
            return 12.0;
        if(coffeeType == "coffee1" && cupSize == "large")
            return 15.0;
        if(coffeeType == "coffee2" && cupSize == "small")
            return 20.0;
        if(coffeeType == "coffee2" && cupSize == "medium")
            return 25.0;
        if(coffeeType == "coffee2" && cupSize == "large");
            return 28.0;
    }

    void printInfo(){
        cout << "咖啡类型（美式咖啡, 抹茶星冰乐）:" << coffeeType << endl;
        cout << "咖啡温度（温热，去冰，加冰）:" << temperature << endl;
        cout << "咖啡杯型（小杯, 中杯, 大杯）: " << cupSize << endl;
    }
};

class Decorator{
public:
    double virtual getPrice(int amount) = 0;
    void virtual printDec() = 0;
};

class DecoratorA1 : public Decorator{ 
private:
    string decName;
    int decAmount;
public:
    DecoratorA1(string name, int amount):decName(name), decAmount(amount){}
    double getPrice(int amount) {
        return 3.0 * amount; //假设这类配料不打折，原价3元
    }
    void printDec() {
        cout << "添加配料1：" << decName << " 份数：" << decAmount << "份" << endl;
    }
};

class DecoratorA2 : public Decorator{ 
private:
    string decName;
    int decAmount;
public:
    DecoratorA2(string name, int amount):decName(name), decAmount(amount){}
    double getPrice(int amount) {
        return 5.0 * amount; //假设这类配料不打折，原价5元
    }
    void printDec() {
        cout << "添加配料2：" << decName << " 份数：" << decAmount << "份" << endl;
    }
};

class DecoratorB1 : public Decorator{
private:
    string decName;
    double decAmount;
public:
    DecoratorB1(string name, int amount):decName(name), decAmount(amount){}
    double getPrice(int amount) {
        return 2.0 * amount * 0.5; //假设这类配料打5折,原价2元
    }
    void printDec(){
        cout << "添加淋酱1：" << decName << endl;
    }
};

class DecoratorB2 : public Decorator{
private:
    string decName;
    double decAmount;
public:
    DecoratorB2(string name, int amount):decName(name), decAmount(amount){}
    double getPrice(int amount) {
        return 7.0 * amount * 0.6; //假设这类配料打6折,原价7元
    }
    void printDec(){
        cout << "添加淋酱2：" << decName << endl;
    }
};
class Order {
private:
    Coffee coffee;
    string tempature;
    string cupSize;
    map<Decorator*, int> details; //每种配料放多少份
    vector<Decorator*> items; //加配料的种类列表
public:
    Order(){}
    void setCoffeeInfo(string coffeeTy, string tem, string _size){
        coffee.setType(coffeeTy);
        coffee.setTem(tem);
        coffee.setSize(_size);
    }
    void addDecorator(Decorator *dec, int amount){
        items.push_back(dec);
        details[dec] = amount;
    }
    double getPrice(){
        double coffeePrice = coffee.getPrice();
        double decPrice = 0;
        double totalPrice = 0;
        for(int i = 0; i < items.size(); i++){
            decPrice += items[i]->getPrice(details[items[i]]);//将数量传入decorator的getPrice
        }
        totalPrice = coffeePrice + decPrice;
        return totalPrice;
    }
    void printOrder(){
        cout << "您的订单如下：" << endl;
        //打印咖啡基本情况
        coffee.printInfo();
        //打印配料
        for(int i = 0; i < items.size(); i++){
            items[i]->printDec();
        }
        //打印价格
        cout << "价格：" << getPrice() << "元" << endl;
    }
};

void initSystem(){
    m_coffeeType[1] = "美式咖啡";
    m_coffeeType[2] = "抹茶星冰乐";
    m_cupSize[1] = "小杯";
    m_cupSize[2] = "中杯";
    m_cupSize[3] = "大杯";
    m_tem[1] = "温热";
    m_tem[2] = "去冰";
    m_tem[3] = "加冰";
    m_sugur[1] = "枫叶糖浆";
    m_sugur[2] = "蓝莓糖浆";
    m_juice[1] = "蔓越莓酱";
}

int main(){
    initSystem();
    
    cout << "Welcome to StarBucks! 请开始定制您的饮品：" << endl;
    cout << "step1: 请选择咖啡类型（1:美式咖啡  2:抹茶星冰乐）(请输入1或2)" << endl;
    int coffeeTy;
    cin >> coffeeTy;
    cout << "step2: 请选择咖啡温度（1：温热 2：去冰 3：加冰）(请输入1或2或3)" << endl;
    int temperature;
    cin >> temperature;
    cout << "step3: 请选择咖啡杯型（1：小杯 2：中杯 3：大杯）(请输入1或2或3)" << endl;
    int cupSize;
    cin >> cupSize;
    cout << "请继续选择配料：（0：全部跳过 1：枫叶糖浆 2：蓝莓糖浆）(请输入0或1或2)" << endl;
    int sugerChoice1;
   
    Order order;
    order.setCoffeeInfo(m_coffeeType[coffeeTy], m_tem[temperature], m_cupSize[cupSize]);
    
    cin >> sugerChoice1;
    while(sugerChoice1 != 0){
        int amount1;
        cout << "请输入添加该配料的份数：" << endl;
        cin >> amount1;
        if(sugerChoice1 == 1){
            Decorator *pDec1 = new DecoratorA1(m_sugur[sugerChoice1], amount1);
            order.addDecorator(pDec1, amount1);
        }
        else if(sugerChoice1 == 2){
            Decorator *pDec1 = new DecoratorA2(m_sugur[sugerChoice1], amount1);
            order.addDecorator(pDec1, amount1);
        }
        else{
            ;
        }
        cout << "请继续选择配料：（0：全部跳过 1：枫叶糖浆 2：蓝莓糖浆）(请输入0或1或2)" << endl;
        cin >> sugerChoice1;
    }

    cout << "请继续选择淋酱（0：全部跳过 1：蔓越莓酱 2：巧克力酱）（请输入0或1或2）" << endl;
    int juiceChoice1;

    cin >> juiceChoice1;
    while(juiceChoice1 != 0){
        if(juiceChoice1 == 1){
            Decorator *pDec2 = new DecoratorB1(m_juice[juiceChoice1], 1);
            order.addDecorator(pDec2, 1);
        }
        else if(juiceChoice1 == 2){
            Decorator *pDec2 = new DecoratorB2(m_juice[juiceChoice1], 1);
            order.addDecorator(pDec2, 1);
        }
        else{
            ;
        }
        
        cout << "请继续选择淋酱（0：全部跳过 1：蔓越莓酱 2：巧克力酱）（请输入0或1或2）" << endl;
        cin >> juiceChoice1;
    }
    
    order.printOrder();

}