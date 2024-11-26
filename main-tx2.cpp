#include <bits/stdc++.h>
using namespace std;

struct Phone {
	string nhanHieu;
	int kichThuoc; //donvi: mm
	int giaBan;
};
//	tham lam
//vector<phone> &res;
//int cnt = 0;
//while(){
//	if(){
//		tmp += d[i].giaBan;
//		cnt++;
//		res.push_back(d[i]);
//	}
//	i++;
//}
//if(m == tmp){
//	return res.size();
//}
//else {
//	return 0;
//}

void qhd(vector<Phone> d, int F[7][1001], int n, int m) {
//	F[n][m]; 0 -> 700: 701
//	n: 6; [1;6];
	for(int i = 0; i <= m; i++) F[0][i] = 0;
	for(int i = 1; i <= n; i++) {	
		for(int j = 0; j <= m; j++) {
			F[i][j] = F[i - 1][j];
			if(j >= d[i].kichThuoc) {
//				kich thuoc: w[]
//				value: v[]
				int tmp = d[i].giaBan + F[i - 1][j - d[i].kichThuoc];
				if(tmp > F[i][j]) {
					F[i][j] = tmp;
				}
			}
		}
	}
//	lay do vat khoi luong <= m co tong gia tri lon nhat
}
//	gai tri lon nhat, so luong can lay
int truyVet(vector<Phone> d, int F[7][1001], int n, int m, int &max_value, vector<Phone> &res) {
	//	F[n][m];
	max_value = F[n][m];
	cout <<"Max: " << max_value << endl;
//	0.5 -> 1 d
	int i = n, j = m;
	while(i !=  0) {
		if(F[i][j] != F[i - 1][j]) {
			cout << i << " ";
			j -= d[i].kichThuoc;
			res.push_back(d[i]);
		}
		i--;
	}
	cout << "size: " << res.size() << endl;
	for(Phone i : res){
		cout << i.nhanHieu << " - " << i.giaBan << endl;
	}
	
	return res.size();
}

int main() {
//	_test case boyer_
//	string P = "namsau";
//	string T = "mothaibabonnamsau";
//	string T1 = "0123456789";
//	int check = boyer(P, T);
//	if(check != -1)	cout << "YES" << endl;
//	cout << check << endl;
	vector<Phone> d;
	int n = 6;
//	n >= 6; tx1 tx2
	d.push_back({ "", 0, 0});
	d.push_back({ "Samsung", 4, 5000000 });
	d.push_back({ "apple", 5, 4500000 });
	d.push_back({ "vivo", 5, 4000000 });
	d.push_back({ "xiaomi", 3, 3500000 });
	d.push_back({ "bphone", 3, 3000000 });
	d.push_back({ "bphone2", 3, 3000000 });
	
//	15
	int s = 15;
	int dp[7][1001];
	qhd(d, dp, n, s);
	
	int max_value = 0;
	vector<Phone> res;
	truyVet(d, dp, n, s, max_value, res);
	
//	[0;1000];
//		0 	1 	2	3	4	5	6	7	8	... 	1000
//	0 	0 	0	0	0	0	0	0	0	
//	1
//	2
//	3
//	4
//	5
//	6
	
	return 0;
}