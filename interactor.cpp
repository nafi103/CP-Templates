class Interactor{
    public:
    int sz;
    vector<int>v;
    public:
    Interactor(){
        int N = getRandomNumber(1,200000);
        sz = N;
        v.resize(sz);
        for(int i = 0; i < sz; i++){
            v[i] = getRandomNumber(0,1);
        }
    }
    int makeQuery(){
    }
    bool checkValidity(){
    }
};