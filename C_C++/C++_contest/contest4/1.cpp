template<typename T, template <typename> class Container>

T process(const Container<T> &v)
{
    auto sum = T();
    if (!v.size()) return sum;
    auto cur = v.end();
    cur--;
    for (int i = 0; i < 3; i++){
        sum += *cur;
        if (cur == v.begin())
            break;
        cur--; 
        if (cur == v.begin())
            break;
        cur--;
    }
    return sum;
}
