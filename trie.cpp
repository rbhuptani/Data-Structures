#define using_trie
#include<iostream>
#include<stdlib.h>
#include<string.h>
#define TOTAL_SIZE 26
#define CHAR_TO_INDEX(C) ((int)C - (int)'a')

using namespace std;
int g_c = 0;
class trie_node{
public:
    trie_node(){
        g_c++;
        _data = 0;
        for(int i=0;i<TOTAL_SIZE;i++)
            _children[i] = nullptr;
    }
    int getData(){
        return _data;
    }
    void setData(int data){
        _data = data;
    }
    void setChildrenI(int index,trie_node *node){
        _children[index] = node;
    }
    trie_node* getChildrentI(int index){
        return _children[index];
    }

private:
    int _data=0;
    trie_node *_children[TOTAL_SIZE];
};

class trie{
public:
    trie(){
        _count = 0;
        _root = new trie_node();
    }
    int getCount(){
        return _count;
    }
    void setCount(int count){
        _count = count;
    }
    void incrCount(){
        _count++;
    }
    void decrCount(){
        _count++;
    }
    trie_node * getRoot(){
        return _root;
    }
    void insert(const char str[],int data){
        incrCount();
        int level,index,length;
        length = strlen(str);
        trie_node *pCrawl = getRoot();
        for(level = 0;level<length;level++){
            index = CHAR_TO_INDEX(str[level]);
            if(! pCrawl->getChildrentI(index))
                pCrawl->setChildrenI(index,new trie_node());
            pCrawl = pCrawl->getChildrentI(index);
        }
        pCrawl->setData(data);
    }
    int search(const char str[]){
        int level,index,length;
        length = strlen(str);
        trie_node *pCrawl = getRoot();
        for(level = 0;level<length;level++){
            index = CHAR_TO_INDEX(str[level]);
            if(! pCrawl->getChildrentI(index))
                return 0;
            pCrawl = pCrawl->getChildrentI(index);
        }
        if(pCrawl)
            return pCrawl->getData();
        return 0;
    }
    bool isNodeFree(trie_node *node){
        for(int i=0;i<TOTAL_SIZE;i++)
            if(node->getChildrentI(i))
                return false;
        return true;
    }
    bool deleteNode(trie_node *currNode,const char str[],int level,int len){
        if(currNode){
            if(level == len){
                if(currNode->getData()){
                    currNode->setData(0);
                    if(isNodeFree(currNode))
                        return true;
                    return false;
                }
            }
            else{
                int index = CHAR_TO_INDEX(str[level]);
                if(deleteNode(currNode->getChildrentI(index),str,level+1,len)){
                    currNode->setChildrenI(index,nullptr);
                    return (isNodeFree(currNode) &&  (currNode->getData() == 0));
                }
            }
        }
        return false;
    }

    void deleteStr(const char str[]){
        int len = strlen(str);
        if(len>0){
            decrCount();
            deleteNode(getRoot(),str,0,len);
        }

    }

private:
    trie_node *_root=nullptr;
    int _count=0;
};

#ifdef using_trie

int main(){
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    trie *newTrie = new trie();
    for(int i=0;i<8;i++)
        newTrie->insert(keys[i],strlen(keys[i]));
    cout<<endl<<"count :: "<<g_c<<" :: "<<sizeof(trie_node);
    cout<<endl<<newTrie->search("the");
    cout<<endl<<newTrie->search("answer");
    cout<<endl<<newTrie->search("there");
    cout<<endl<<newTrie->search("a");
    cout<<endl<<newTrie->search("their");
    cout<<endl<<newTrie->search("thesd");
    cout<<endl<<newTrie->search("thasfe");
    cout<<endl<<"Deletion:";
    newTrie->deleteStr("there");
    cout<<endl<<newTrie->search("the");
    cout<<endl<<newTrie->search("there");
    return 0;
}

#endif // using_trie
