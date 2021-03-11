template<typename T, typename TT>

T myfilter(const T &v, TT prediction)
{
    T res;
    for(auto cur: v)
        if (prediction(cur))
            res.insert(res.end(), cur);
            
    return res;
}
