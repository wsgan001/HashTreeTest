#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <ctime>
#include <string>
#include <sstream>
#include <functional>
//#include <boost/timer.hpp>
#include "propersubsets.hpp"
class Hash{
public:
    constexpr unsigned operator()(const unsigned long& d){
        return d % 10;
    }
};

typedef std::vector<unsigned long> Data1;
int main(){
    std::ifstream dset("117_FC.res");
    std::ifstream FGset("117.res");
    std::vector<std::pair<Data1, unsigned long> > Fg;
    std::vector<Data1> data;
    char tmp[500];
    dset.getline(tmp,500);
    while (dset.good()){
        std::stringstream ss(tmp);
        std::vector<unsigned long> a;
        char ch;
        ss >> ch;
        while(ss.good()){
            unsigned long tt;
            ss >> tt;
            a.push_back(tt);
            char ch;
            ss >> ch;
            if(ch != ')'){
                ss.putback(ch);
            }else{
                break;
            }
        }
        data.push_back(a);
        dset.getline(tmp,500);
    }
    FGset.getline(tmp,500);
    while(FGset.good()){
        std::stringstream ss(tmp);
        std::pair<Data1,unsigned long> a;
        char ch;
        ss >> ch;
        while(true){
            unsigned long tt;
            ss >> tt;
            a.first.push_back(tt);
            char ch;
            ss >> ch;
            if(ch != ')'){
                ss.putback(ch);
            }else{
                break;
            }
        }
        ss >> a.second;
        Fg.push_back(a);
        FGset.getline(tmp,500);
    }

    std::list<std::list<std::pair<std::vector<unsigned long>,unsigned long> > > results;
    ProperSubsets<unsigned long, Hash> p(Fg);
    unsigned int num = data.size();
    std::ofstream res("res.dat");
    /*for(auto it = data.cbegin(); data.cend() - it > 4; it+=4){
        auto a = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *it);
        auto b = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+1));
        auto c = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+2));
        auto d = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+3));

        results.push_back(a.get());
        results.push_back(b.get());
        results.push_back(c.get());
        results.push_back(d.get());

        if( results.size() > 10000){
            for(auto& x : results){
                for(auto& y : x){
                    res << "(";
                    for(auto& z : y.first){
                        res << z;
                        if(z != *(y.first.end() - 1)) res << ' ';
                    }
                    res << ") " << y.second << std::endl;
                }
                res << std::endl;
            }
            results.clear();
        }

        unsigned nn = (it - data.cbegin());
        std::cout.precision(2);
        if( nn / (num / 200) % 5 == 0 )
        std::cout << static_cast<unsigned>(ceil(nn * 100. / num)) << '%' << std::flush << '\r' ;
    }*/
    std::cout << std::endl;

    return 0;

}

//        auto e = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+4));
//        auto f = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+5));
//        auto g = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+6));
//        auto h = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+7));
//        auto i = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+8));
//        auto j = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+9));
//        auto k = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+10));
//        auto l = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+11));
//        auto m = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+12));
//        auto n = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+13));
//        auto o = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+14));
//        auto q = std::async(std::launch::async, &ProperSubsets<unsigned long, Hash>::operator(), &p, *(it+15));

//        results.push_back(e.get());
//        results.push_back(f.get());
//        results.push_back(g.get());
//        results.push_back(h.get());
//        results.push_back(i.get());
//        results.push_back(j.get());
//        results.push_back(k.get());
//        results.push_back(l.get());
//        results.push_back(m.get());
//        results.push_back(n.get());
//        results.push_back(o.get());
//        results.push_back(q.get());