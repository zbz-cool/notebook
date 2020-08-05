# Modern C++

## if/switch 初始化语句

```C++
//before
auto*tmp = parseExpression();
if(tmp!=nullptr){
    work();
}

//after
 if (auto* tmp = parseExpression(); tmp != nullptr) {
    work();
}
```

## 结构化绑定

```C++
std::tuple<int,string> nextToken(){
    return {4,"fallthrough"};
}

//before
int main() {
    auto token = nextToken();
    std::cout<<std::get<int>(token)<<","<<std::get<std::string>(token);
    return 0;
}
//after
int main() {
    auto[tokenType,lexeme] = nextToken();
    std::cout<<tokenType<<","<<lexeme;
    return 0;
}
```

## std::string_view

```C++
2. //before
void isKeyword(const std::string & lit){
    work();
}
//after
void isKeyword(std::string_view lit){
    work();
}
```

## 内联变量

// A.h
inline int k = 10; //不需要为一个简单的变量分一个.cpp写定义了
5. 折叠表达式和泛型lambda//before
if(x=='x'||x=='X'||x=='e'||x=='E'||x=='.'){
    work();
}

//after
static auto anyone = [](auto&& k, auto&&... args) ->bool { return ((args == k) || ...); };
if(anyone(x,'x','X','e','E','.')){
    work();
}6. 继承构造函数struct Base{
    Base(int a,char b,double c, std::string d,float f)
    :a(a),b(b),c(c),d(std::move(d)),f(f){}

    int a;
    char b;
    double c;
    std::string d;
    float f;
};

//before
struct Derive : public Base{
    Derive(int a,char b,double c, std::string d,float f):Base(a,b,c,d,f){}
};

//after
struct Derive : public Base{
    using Base::Base;
};
7.  +lambda转换对lambda使用一元+表达式可以将它转换为普通函数指针// before 
int8_t (*CreateLonglink)(const std::string& name, const std::string& host,
 const std::vector<uint16_t> ports, const std::string& debugip)
 = +[](const std::string& name,
                         const std::string& host,
                         const std::vector<uint16_t> ports,
                         const std::string& debugip)->int8_t{
   
    ...
    return 0;
};
// after
auto CreateLonglink= +[](const std::string& name,
                         const std::string& host,
                         const std::vector<uint16_t> ports,
                         const std::string& debugip)->int8_t{
   
    ...
    return 0;
};