//#define using_SA
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<map>
using namespace std;

class SuffixC{
public:
    struct suffix{
        int _index=0;
        char *_suff;
    };
    static int cmp(suffix A,suffix B){
        return strcmp(A._suff,B._suff) < 0 ? 1 : 0;
    }
    int* getSuffArray(const char *txt){
        int n = strlen(txt);
        suffix *suffixes = (suffix*)malloc(n*sizeof(suffix));
        for(int i=0;i<n;i++){
            suffixes[i]._index = i;
            suffixes[i]._suff = (char *)(txt + i);
        }
        sort(suffixes,suffixes+n,cmp);
        int *suffArray = new int[n];
        for(int i=0;i<n;i++){
            suffArray[i] = suffixes[i]._index;
        }
        return suffArray;
    }
};
void reciprocal(int N) {
    string result ="";
    if(N<0)
        result = "-";
    N = abs(N);
    int res = 1/N;
    result += to_string(res);
    int rem = (1%N)*10;
    if(rem == 0)
        cout<<result;
    map<int,int> characters;
    result += ".";
    int flag =0;
    while(rem != 0){
        cout<<endl<<rem;
        if(characters.count(rem)){
            int start = characters[rem];
            string normal = result.substr(0,start);
            int len;
            for(len=0; result[len]!='\0'; ++len);
            string recur = result.substr(start);
            result = normal + recur + " " + recur;
            flag =1;
            //cout<<result;
            break;
        }
        int l;
        for(l=0; result[l]!='\0'; ++l);
        characters[rem] = l;
        res = rem /N;
        result += to_string(res);
        rem = (rem%N)*10;
    }
    if(flag == 0)
        result = result + "0 0";
    cout<<endl<<result;
}
#ifdef using_SA
int main(){
    /*char input[] = "banana";
    SuffixC *s = new SuffixC();
    int *result = s->getSuffArray(input);
    for(auto i=0;i<strlen(input);i++)
        cout<<"   "<<result[i];*/
    reciprocal(7);
    return 0;
}
#endif
