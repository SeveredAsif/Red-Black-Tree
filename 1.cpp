#include "2105131.hpp"
using namespace std;

int main()
{
    freopen("SampleIO/input.txt", "r", stdin);
    //  freopen("output.txt", "w", stdout);
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
            x->left = rbt.TNULL;
            x->right = rbt.TNULL;
            rbt.insert(x);
            rbt.print(rbt.root);
            cout << endl;
            // cout<<rbt.root->val<<endl;
            // cout << p << endl;
        }
        else if (s == "E")
        {
            int key;
            cin >> key;
            Node *x = rbt.find(key);
            if (x == nullptr)
                cout << key << " Not found" << endl;
            else
            {
                rbt.deleteNode(key);
                rbt.print(rbt.root);
            }
            // cout << p << endl;
        }
        else if (s == "Em")
        {
            if (rbt.root->left == nullptr && rbt.root->right == nullptr)
            {
                cout << "yes" << endl;
            }
            else
            {
                cout << "no" << endl;
            }
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
        else if (s == "S")
        {
            cout << rbt.sizee() << endl;
        }
        else if (s == "Itr")
        {
            rbt.inOrderHelper(rbt.root);
        }
        else if (s == "Clr")
        {
            int a = rbt.clear();
            if (a == 1)
            {
                cout << "successful" << endl;
                // cout<<rbt.sizee()<<endl;
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
    }
}