class FooBar {
private:
    int n;
    mutex m;
    condition_variable cond;
    bool foo_flag = true;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(m);
            while(!foo_flag)
                cond.wait(lock);
                
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            foo_flag = false;
            cond.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(m);
            while(foo_flag)
                cond.wait(lock);
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            foo_flag = true;
            cond.notify_all();
        }
    }
};