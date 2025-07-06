const int K = 26;

struct Vertex {
    int next[K];
    bool output = false;

    Vertex() {
        fill(begin(next), end(next), -1);
    }
};

vector<Vertex> Trie(1);

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (Trie[v].next[c] == -1) {
            Trie[v].next[c] = Trie.size();
            Trie.emplace_back();
        }
        v = Trie[v].next[c];
    }
    Trie[v].output = true;
}

void delete_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (Trie[v].next[c] == -1) {
            return;
        }
        v = Trie[v].next[c];
    }
    Trie[v].output = false;
}