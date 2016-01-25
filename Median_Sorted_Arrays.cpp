//#define using_msa
#include<iostream>

using namespace std;

int min(int a,int b){
    return a<b ? a:b;
}
int max(int a,int b){
    return a>b ? a:b;
}
int median(int a[],int N){
    if(N & 1)
        return a[N/2];
    return (a[N/2] + a[N/2 - 1])/2;
}
float getMedian(int A[],int B[],int N){
    if(N == 0)   //empty arrays
        return -1;
    if(N==1)
        return (A[0]+B[0])/2;
    if(N==2)
        return (max(A[0],B[0]) + min(A[1],B[1]))/2.0;

    int medA = median(A,N);
    int medB = median(B,N);
    if(medA == medB)
        return medA;
    if(medA < medB){
        if(N & 1)
            return getMedian(A+N/2,B,N-N/2); //N is odd
        return getMedian(A+N/2-1,B,N-N/2+1);
    }
    else{
        if(N&1)
            return getMedian(A,B+N/2-1,N-N/2+1);
        return getMedian(A,B+N/2,N-N/2);
    }
}

#ifdef using_msa
int main(){
    int A[] = {1,2,3,5,5};
    int B[] = {6,6,8,9,10};
    cout<<getMedian(A,B,5);
    return 0;
}
#endif // using_msa
