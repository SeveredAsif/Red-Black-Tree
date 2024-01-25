#include "2105131.hpp"
using namespace std;

int main()
{
    RBT rbt;
    while (1)
    {
        string s;
        cin >> s;
        if (s == "I")
        {
            int key;
            string val;
            cin >> key >> val;
            Node *x = new Node(key, val);
            rbt.insert(x);
            string p = rbt.print(rbt.root);
            // cout<<rbt.root->val<<endl;
            cout << p << endl;
        }
        else if (s == "E")
        {
            int key;
            cin >> key;
            Node *x = rbt.find(key);
            if (x == nullptr)
                cout << key << " Not found" << endl;
            else
                rbt.Delete(x);
            string p = rbt.print(rbt.root);
            cout << p << endl;
        }
        else if (s == "P")
        {
            string p = rbt.print(rbt.root);
            cout << p << endl;
        }
        else if (s == "F")
        {
            int key;
            cin >> key;
            // string m;
            // cin >> m;
            Node *x = rbt.find(key);
            if (x == nullptr)
                cout << key << " Not found" << endl;
            else
                cout << key << " found" << endl;
        }
        else if (s == "Q")
        {
            break;
        }
    }
}