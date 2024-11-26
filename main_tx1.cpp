#include <bits/stdc++.h>
using namespace std;

struct CONGVIEC{
	string maCV;
	float tdbd;
	float tdkt;
};
void title(){
	cout << setw(8) << "macv";
	cout << setw(8) << "tdbd";
	cout << setw(8) << "tdkt";
	cout << endl;
}
void data(CONGVIEC cv){
	cout << setw(8) << cv.maCV;
	cout << setw(8) << cv.tdbd;
	cout << setw(8) << cv.tdkt;
	cout << endl;
}

//De quy
void A1(CONGVIEC c[], int n, int index){
	if(index == n - 1){
		data(c[index]);
		return;
	}
	data(c[index]);
	A1(c, n, index + 1);
}


//chia de tri
float A2(CONGVIEC c[], int left, int right, int t){
	if(left == right){
		return (c[left].tdkt < t ? (c[left].tdkt - c[left].tdbd) : 0);
	}
	int mid = (left + right) / 2;
	float timeLeft = A2(c, left, mid, t);
	float timeRight = A2(c, mid + 1, right, t);
	return timeLeft + timeRight;
}
int x[100], dd[100];

//back-tracking
/**
* b1 : duyet cac gia tri
* b2: check
* b3: Out
*/
//[back-tracking] - hoán vị
void Try1(int k, int n) {
	for(int i = 1; i <= n; i++) {
		if(dd[i] == 0) {
			x[k] = i;
			if(n == k) {
				for(int j = 1; j <= k; j++) {
					cout << x[j] << " ";
				}
				cout << endl;
			} else {
				dd[i] = 1;
				Try1(k + 1, n);
				dd[i] = 0;
			}
		}
	}
}

//back-tracking - mCn
void Try(int k, int k1, int n, CONGVIEC cv[]){
	int last_element = (k == 1 ? 0 : x[k - 1]);
	for(int i = 1 + last_element; i <= n; i++){
		if(dd[i] == 0){
			x[k] = i;
			if(k1 == k){
				for(int j = 1; j <= k; j++){
					cout << "{ " << x[j] << " - " <<  cv[x[j] - 1].maCV<< ", ";
				}
				cout << endl;
			}
			else{
				dd[i] = 1;
				Try(k + 1, k1, n, cv);
				dd[i] = 0;
			}
		}
	}
}
int main(){
	int n = 6;
	CONGVIEC c[n] = {
		{ "cv001", 1, 4.5 },
		{ "cv002", 1, 2.5 },
		{ "cv003", 1, 2 },
		{ "cv004", 1, 2 },
		{ "cv005", 1, 2 },
		{ "cv006", 1, 2 },
	};
	
//	title();
//	A1(c, n, 0);
//	
	float t = 4.5;
//	
	cout << "Time: " <<A2(c, 0, n - 1, t) << endl;
	int k = 5;
	Try(1, k, n , c);
	
	
	return 0;	
}