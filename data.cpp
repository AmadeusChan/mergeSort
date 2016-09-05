#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

int main(){
	cout<<"Length of Array:";
	int n;
	cin>>n;
	srand(time(NULL));
	freopen("input.txt","w",stdout);
	for (int i=0;i<n;++i) printf("%d %d\n",rand(),rand());
	fclose(stdout);
	return 0;
}
