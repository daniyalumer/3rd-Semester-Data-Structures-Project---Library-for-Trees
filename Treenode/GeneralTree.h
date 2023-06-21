
#include <iostream>
#include <queue>
using namespace std;

class list;

class gnode
{
public:
    int data;
    list* children;
    gnode* sibling;
    friend class list;

};

class list
{
public:
    gnode* head;
    list()
    {
        head = new gnode;
        head->data = -1;
        head->sibling = NULL;
        head->children = NULL;
    }

    void insert(int a)
    {
        gnode* v = new gnode;
        v->data = a;
        v->sibling = head;
        v->children = NULL;
        head = v;
    }

    int size()
    {
        int size = 0;
        gnode* temp = head;
        while (temp->sibling != NULL)
        {
            size++;
            temp = temp->sibling;
        }
        return size;
    }

    bool empty()
    {
        return(size() == 0);
    }

    void print()
    {
        gnode* temp = head;
        while (temp->sibling != NULL)
        {
            cout << temp->data << ' ';
            temp = temp->sibling;
        }
        cout << "** ";
    }


    friend class gnode;
};



class tree
{
public:
    gnode* root;
    queue <gnode*> q;
    tree()
    {
        root = new gnode;
        root->data = -1;
        root->children = NULL;
        root->sibling = NULL;
        q.push(root);
    }

    bool haschildren(gnode* v)
    {
        return(v->children != NULL);
    }

    bool match(gnode* v, int k)
    {
        return(v->data == k);
    }

    void enqueue_children(gnode* v)
    {
        gnode* iter = v->children->head;
        while (iter->sibling != NULL)
        {
            q.push(iter);
            iter = iter->sibling;
        }
    }

    gnode* search(int k, gnode* temp)
    {

        if (!match(temp, k))
        {
            if (haschildren(temp))
            {
                q.pop();
                enqueue_children(temp);
                search(k, q.front());
            }
            else
            {
                q.pop();
                search(k, q.front());
            }
        }

        if (q.empty())
        {
            return NULL;
        }
        else
        {
            return(q.front());
        }
    }

    void insert(int parent, int child)
    {
        gnode* v = search(parent, root);
        if (v != NULL)
        {
            if (haschildren(v))
            {
                v->children->insert(child);
            }
            else
            {
                v->children = new list;
                v->children->insert(child);
            }
        }
        else
        {
            cout << parent << " not in tree" << endl;
        }
    }


    void print2d()
    {







    }

};





