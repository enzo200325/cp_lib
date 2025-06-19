typedef vector<vector<int>> mat; 

const int mod = 1e9 + 7; 
mat I; 

void add(int& a, int b) {
    a += b; 
    if (a >= mod) a -= mod; 
    if (a < 0) a += mod; 
} 
int get_mult(int a, int b) {
    return 1ll * a * b % mod; 
} 

mat mult(mat a, mat b) {
    mat c; 
    c.assign(a.size(), vector<int>(b[0].size())); 
    assert(a[0].size() == b.size()); 

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < a[0].size(); k++) {
                add(c[i][j], get_mult(a[i][k], b[k][j])); 
            } 
        } 
    } 
    return c; 
} 

mat binexp(mat A, ll e) {
    mat ret; 
    ret.assign(A.size(), vector<int>(A[0].size(), 0)); 
    for (int i = 0; i < ret.size(); i++) ret[i][i] = 1; 

    while (e) {
        if (e&1) ret = mult(A, ret); 
        e >>= 1; 
        A = mult(A, A); 
    } 
    return ret; 
} 

