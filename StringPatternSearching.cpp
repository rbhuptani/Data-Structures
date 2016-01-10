#define using_SPS
#include<iostream>
#include<string>
#define NOC 256
using namespace std;
/* Pattern searching in string using Boyer Moore Algorithm : Bad character Heuristic*/
int max(int a,int b){
    return a>b?a:b;
}

void BCH(const char *pat,const int len,int *badChar){
    for(int i=0;i<NOC;i++)
        badChar[i] = -1;
    for(int i=0;i<len;i++)
        badChar[(int)pat[i]] = i;
}

void BMsearch(const char*pattern,const char *str){
    cout<<endl<<"Pattern Search in String : Using Boyer Moore Algo";
    cout<<endl<<"======================================="<<endl;
    size_t pLen = string(pattern).length();
    size_t sLen = string(str).length();
    int badChar[NOC];
    BCH(pattern,pLen,badChar);
    int s =0;
    while(s < sLen-pLen){
        int j = pLen-1;
        while(j>=0 && pattern[j] == str[s+j])
            j--;
        if(j<0){
            cout<<endl<<string(pattern)<< " found at index "<<s;
            if(s+pLen < sLen)
                s += pLen - badChar[str[s+pLen]];
            else
                break;
        }
        else
            s += max(1,j -badChar[str[s+j]]);
    }
}

/*Pattern searching in string using KMPP algorithm */
void computeLPS(const char *pattern,int pLen,int *LPS){
    int len =0;
    int i=1;
    LPS[0] = 0;
    while(i<pLen){
        if(pattern[i] == pattern[len]){
            len++;
            LPS[i]= len;
            i++;
        }
        else{
            if(len != 0)
                len = LPS[i-1];
            else{
                LPS[i] =0;
                i++;
            }
        }
    }
}

void KMPSearch(const char *pattern,const char * str){
    cout<<endl<<"Pattern Search in String : Using KMP Algo";
    cout<<endl<<"=======================================";
    size_t pLen = string(pattern).length();//strlen(pattern);
    size_t sLen = string(str).length();
    int i,j;
    i=j=0;
    int *LPS = (int *)malloc(pLen*sizeof(int));
    computeLPS(pattern,pLen,LPS);
    while(i < sLen){
        if(pattern[j] == str[i]){
            i++;j++;
        }
        if(j == pLen){
            cout<<endl<<string(pattern)<< " found at index "<<(i-j);
            j = LPS[j-1];
        }
        else if(i<sLen && pattern[j] != str[i]){
            if(j!=0)
                j = LPS[j-1];
            else
                i++;
        }
    }
    cout<<endl;
}


/*pattern searching using naive searching method*/
void NaiveSearch(const char*pattern, const char* str){
    cout<<endl<<"Pattern Search in String : Naive Method";
    cout<<endl<<"=======================================";
    size_t pLen = string(pattern).length();//strlen(pattern);
    size_t sLen = string(str).length();
    for(int i=0;i<=sLen-pLen;i++){
        int j;
        for(j=0;j<pLen;j++)
            if(str[i+j] != pattern[j])
                break;
        if(j == pLen)
            cout<<endl<<string(pattern)<< " found at index "<<i;
    }
    cout<<endl;
}

#ifdef using_SPS
int main(){
    char str[] = "ABAAABCD";
    char pat[] = "ABC";
    NaiveSearch(pat,str);
    KMPSearch(pat,str);
    BMsearch(pat,str);
    return 0;
}
#endif // using_SPS
