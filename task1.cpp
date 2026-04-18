#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;
struct new_order{
    uint64_t order_id;
    char side;
    int32_t price;
    uint32_t quantity;
};

struct change_order{
    uint64_t order_id;
    int32_t new_price;
    uint32_t new_quantity;


};

struct cancel_order{
    uint64_t order_id;

};

class OrderBook{
    public:
    void OnNewOrder(const new_order& order);
    void OnChangeOrder(const change_order& order);
    void OnCancelOrder(const cancel_order& order);

    void Print();
    private:
    struct Order{
        char side;
        int32_t price;
        uint32_t qty;

    };
    unordered_map<uint64_t,Order>orders;
    map<int32_t,uint64_t>buys;
    map<int32_t,uint64_t>sells;

    void addQty(char  side, int32_t price,uint32_t qty){
        if (side=='B'){
            buys[price]+=qty;
        }
        else if (side =='S'){
            sells[price]+=qty;
        }
    }

    void removeQty(char side , int32_t price,uint32_t qty){

        if(side='B'){
            auto it = buys.find(price);
            if(buys.find(price)==buys.end()){return;}
            if(buys.find(price)->second<=qty){
                buys.erase(it);
            }
            else{
                buys.find(price)->second-=qty;
            }
        }
        else{
            auto it=sells.find(price);
            if(it==sells.end()){return;}
            if(it->second<=qty){
                sells.erase(sells.find(price));

            }
            else{
                it->second-=qty;
            }
            
        }
    }


};
void OrderBook::OnNewOrder(const new_order &o){
    if(orders.count(o.order_id)){return;}
    if(o.side!='B'&&o.side!='S'){
        return;
    }
    orders[o.order_id]={o.side,o.price,o.quantity};
    addQty(o.side,o.price,o.quantity);


}
void OrderBook::OnChangeOrder(const change_order &c){
    auto it =orders.find(c.order_id);
    if(it == orders.end()){return;}
    auto &o=it->second;
    removeQty(o.side,o.price,o.qty);
    o.price=c.new_price;
    o.qty=c.new_quantity;
    addQty(o.side,o.price,o.qty);

}

void OrderBook::OnCancelOrder(const cancel_order &c){
    auto it=orders.find(c.order_id);
    if(it == orders.end())return;
    removeQty(it->second.side,it->second.price,it->second.qty);
    orders.erase(it);

}

void OrderBook::Print(){
    cout<<"Buys\n";
    cout<<"Quantity\n";
    for(auto it =buys.begin();it!=buys.end();it++){
        cout<<it->first<<'\t'<<it->second<<'\n';
    }
    cout<<"sells\n";
    cout<<"Quantity\n";
    for(auto it =sells.begin();it!=sells.end();it++){
        cout<<it->first<<'\t'<<it->second<<'\n';
    }
};


int main() {
    OrderBook ob;
 
    ob.OnNewOrder({1, 'B', 100, 6000});
    ob.OnNewOrder({2, 'B', 100, 4000});
    ob.OnNewOrder({3, 'B',  99, 2000});
    ob.OnNewOrder({4, 'B',  98, 1000});
 
    ob.OnNewOrder({5, 'S', 102, 3000});
    ob.OnNewOrder({6, 'S', 102, 4000});
    ob.OnNewOrder({7, 'S', 103, 2000});
    ob.OnNewOrder({8, 'S', 104, 9000});
 
    ob.Print();
 
    ob.OnChangeOrder({3, 99, 5000});
    ob.OnCancelOrder({7});
    ob.OnChangeOrder({6, 101, 4000});
 
    cout<<"After updates"<<endl;
    ob.Print();
    


    OrderBook ob2;
    cout<<"\nSecond order book\n"<<endl;
 
    ob2.OnNewOrder({10, 'B', 50, 100});   
    ob2.OnNewOrder({11, 'B', 50, 100});   
    ob2.OnNewOrder({11, 'B', 49,  999});  
    ob2.OnNewOrder({12, 'S', 60, 200});
    ob2.OnNewOrder({13, 'S', 60, 300});   
 
    
    ob2.Print();
  
    ob2.OnCancelOrder({10});             
    ob2.OnCancelOrder({11});              
    ob2.OnCancelOrder({999});             
    ob2.OnChangeOrder({888, 70, 1});      
 
    ob2.OnChangeOrder({12, 60, 50});      
    ob2.OnChangeOrder({13, 61, 300});     
 
    cout<<"After updates"<<endl;
    ob2.Print();


}

