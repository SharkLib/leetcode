using namespace std;
class Foo {
public:
    Foo() {
        
    }
    mutex mut;
    condition_variable cond;

    bool b1 = false;
    bool b2 = false;

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        unique_lock<std::mutex> lock(mut);
        printFirst();
    
        b1 = true;
        cond.notify_all();
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        unique_lock<std::mutex> lock(mut);
       while (!b1) cond.wait(lock);
        printSecond();
    
        b2 = true;
        cond.notify_all();
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        unique_lock<std::mutex> lock(mut);
        while (!b2) cond.wait(lock);
        printThird();
    }
};