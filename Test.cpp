#include "doctest.h"
#include "range.hpp"
#include "accumulate.hpp"
#include "compress.hpp"
#include "filterfalse.hpp"

#include <cmath>
#include <vector>
#include <string>
#include <iterator>

using namespace itertools;
using namespace std;

//20 tests for each
//accumulate : 20 tests for each part
//Checks if a number is a multiple of 3
struct multiple_3
{
    multiple_3() {}
    bool operator()(int y) const { return y % 3 == 0; }
};
//Checks if a number is a multiple of 3 and 2
struct multiple_3and2
{
    multiple_3and2() {}
    bool operator()(int x) const
    {
        return (x % 3 == 0) && (x % 2 == 0);
    }
};
//Checks if a number to the power of two is bigger than 15
struct powHigher
{
    powHigher() {}
    bool operator()(double x)
    {
        return (pow(x, 2) > 15);
    }
};
//lambda expression to check multiple3_2 AND powHigher
auto ftor = [](double x) { multiple_3and2 num;
        powHigher p;
        return num(x) && p(x); };

TEST_CASE("Range")
{
    CHECK_NOTHROW(range(5, 5));
    ///////////////////
    int count = 0;
    for (auto i : range(7, 30))
    {
        count++;
    }
    CHECK(count == 23);
    ///////////////////
    count = 0;
    for (auto i : range(15, 200))
    {
        count++;
    }
    CHECK(count == (200 - 15));
    ///////////////////
    CHECK_NOTHROW(range r(1, 1500000));

    count = 0;
    for (auto i : range(0, 20))
    {
        CHECK(i == count++);
    }
}

TEST_CASE("Accumulate")
{
    vector<int> vecInt = {1,2,3,4};
    vector<string> vecString = {"Hello", "Bye", "Adam"};
    vector<float> vecFloat = {-1, 0.3, 5.2, -8.3};
    
    
    //Part A
    CHECK_NOTHROW(accumulate(range(5, 5)));
    CHECK_NOTHROW(accumulate{vecInt});
    CHECK_NOTHROW(accumulate{vecString});
    CHECK_NOTHROW(accumulate{vecFloat});
    
     ///////////////////
    int count = 0;
    for (auto i : accumulate(range(1, 5)))
    {
        count++;
    }
    CHECK(count == 4);
    ///////////////////
         ///////////////////
    count = 0;
    for (auto i : accumulate(vecInt))
    {
        count++;
    }
    CHECK(count == 4);
    ///////////////////
    int arr[]={1,3,6,10};
    int j = 0;
         auto b = accumulate(vecInt).begin();

     for (int i = 0; i < (sizeof(arr)/sizeof(*arr)) ; i++)
     {
          CHECK(*b == arr[j]);
     }
     
     
     int arr2[]={1,3,6,10};
     j = 0;
     auto a = accumulate(vecInt).begin();
     for (int i = 0; i < (sizeof(arr2)/sizeof(*arr2)) ; i++)
     {
          CHECK(*a == arr2[j]);
     }
        for (auto i : accumulate(vecInt))
        {
            CHECK(i == arr2[j]);
            j++;
        }        
        
    string arr3[]={"Hello", "HelloBye", "HelloByeAdam"};
     j = 0;
     auto c = accumulate(vecString).begin();
     for (int i = 0; i < (sizeof(arr3)/sizeof(*arr3)) ; i++)
     {
         //next(c,1);
         // CHECK(arr3[j].compare(*c));
     }

    



    //Part B
        CHECK_NOTHROW(accumulate(range(5, 5), [](int x,int y){return x+y;}));
        
    ///////////////////
    count = 0;
    for (auto i : accumulate(vecInt,[](int x,int y){return x+y;}))
    {
        count++;
    }
    CHECK(count == 4);
    ///////////////////
    
        ///////////////////
    count = 0;
    for (auto i : accumulate(range(5, 5),[](int x,int y){return x+y;}))
    {
        count++;
    }
    CHECK(count == 4);
    ///////////////////

    
}

TEST_CASE("Filterfalse")
{

    multiple_3 f1;
    multiple_3and2 f2;
    powHigher f3;
    for (auto i : filterfalse(f1, range(4, 25)))
    {
        CHECK(f1(i) == false);
    }
    for (auto i : filterfalse(f2, range(25, 78)))
    {
        CHECK(f2(i) == false);
    }
    for (auto i : filterfalse(f3, range(1, 8)))
    {
        CHECK(f3(i) == false);
    }
    for (auto i : filterfalse(f2, std::vector{6,12,24,5,4,-1,-5,88,789,12,7,56,89})){
        CHECK(f2(i) == false);
    }
}

TEST_CASE("Compress")
{
    multiple_3and2 f2;
    std::vector<bool> vec;
    for (auto i : range(0,60)){
        vec.push_back(f2(i));
    }
    for (auto i: compress(range(0,60),vec)){
        CHECK(i % 6 == 0);
    }
    /////////////////
    std::string s1 = "ariel university";
    std::vector<bool> v1 = {true, true, true, true, true};
    for (auto i: range(5,11)){
        v1.push_back(false);
    }
    for (auto i : compress(s1, v1)){
        bool c = (i >=65 && i<=90) || (i >=97 && i<=122);
        CHECK(c);
    }

    std::string s2 = "Neque porro quisquam est qui dolorem ipsum";
    std::vector<bool> v2;
    for (int i = 0; i < s2.size() - 5; i++){
        v2.push_back(false);
    }
    
    for (auto i :compress(s2, v2)){
        bool c = (i >=65 && i<=90) || (i >=97 && i<=122);
        CHECK(c);
    }
}
