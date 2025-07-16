const int K = 26;

struct Vertex {
    vector<int>next_char, go;
    bool output = false;
    int link = -1;

    Vertex(){
        next_char.assign(K,-1);
        go.assign(K,-1);
    }
};

vector<Vertex> Trie(1);

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (Trie[v].next_char[c] == -1) {
            Trie[v].next_char[c] = Trie.size();
            Trie.emplace_back();
        }
        v = Trie[v].next_char[c];
    }
    Trie[v].output = true;
}

void add_links() {
    queue<int> q;
    Trie[0].link = 0;
    for (int c = 0; c < K; c++) {
        int u = Trie[0].next_char[c];
        if (u != -1) {
            Trie[u].link = 0;
            q.push(u);
            Trie[0].go[c] = u;
        } else {
            Trie[0].go[c] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        for (int c = 0; c < K; c++) {
            int v = Trie[u].next_char[c], suffix_link = Trie[u].link;
            if (v != -1) {

                while (suffix_link != 0 && Trie[suffix_link].next_char[c] == -1){
                    suffix_link = Trie[suffix_link].link;
                }

                if (Trie[suffix_link].next_char[c] != -1)
                    Trie[v].link = Trie[suffix_link].next_char[c];
                else
                    Trie[v].link = 0;

                q.push(v);
            }
            Trie[u].go[c] = (v != -1) ? v : Trie[suffix_link].go[c];
        }
    }
}