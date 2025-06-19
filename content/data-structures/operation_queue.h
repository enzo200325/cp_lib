template<typename T, auto op>
struct op_stack {
    vector<pair<T, T>> stc; 
    void push(T x) {
        stc.emplace_back(x, stc.size() ? op(stc.back().second, x) : x); 
    } 
    void pop() {
        stc.pop_back(); 
    } 
    T get() {
        return stc.back().second; 
    } 
    bool empty() {
        return (int)stc.size() == 0; 
    } 
};  

template<typename T, auto op> 
struct op_queue {
    op_stack<T, op> s_pop, s_push; 

    void push(T x) {
        s_push.push(x); 
    } 
    void pop() {
        if (s_pop.empty()) {
            while (!s_push.empty()) {
                s_pop.push(s_push.stc.back().first); 
                s_push.pop(); 
            } 
        } 
        s_pop.pop(); 
    } 
    T get() {
        if (s_pop.empty()) return s_push.get(); 
        else if (s_push.empty()) return s_pop.get(); 
        else return op(s_pop.get(), s_push.get()); 
    } 
};  

