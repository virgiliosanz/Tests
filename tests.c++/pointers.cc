#include <iostream>
#include <memory>
#include <string>

class PagedData {
    public:
        PagedData() {s= "Hola"; v=4.5;}
        void show() {std::cout << s << " - " << v << std::endl;}
    private:
        std::string s;
        double v;
};

void testPointers()
{
    PagedData* a = new PagedData(); //raw pointer, ideally shouldn't be managed manually
    a->show();

    std::unique_ptr<PagedData> b = std::make_unique<PagedData>(); // only 1 unique owner can own at a time
    auto c = std::make_unique<PagedData>(); // same, but less verbose...

    c->show();
    // c.show(); // ERROR!! c is a pointer

    // auto f = c; // ERROR!! pointer cannot be shared
    auto f = std::move(c); // OK, just one can own the pointer

    std::shared_ptr<PagedData> d = std::make_shared<PagedData>(); // can be passed around liberally and have multiple owners
    auto e = std::make_shared<PagedData>(); // same, but less verbose...

    auto g = e; // OK: pointer can be shared

    // a will now leak as we forgot to call delete
    // yet b/c and d/e will be cleaned up for us
    // notice the lack of new and delete for b/c and d/e? modern c++ prefers the absence of new/delete calls;
    //
    //delete a;
}

int main()
{
    testPointers();
}
