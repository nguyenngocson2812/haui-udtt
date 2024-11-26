#include <bits/stdc++.h>
using namespace std;

struct Phone {
	string nhanHieu;
	int kichThuoc; //donvi: mm
	int giaBan;
};
// - de quy / chia de tri
// - tham lam
// 1 trong 2 sau:
// - qhd
// - boyer / z 
// số lượng && danh sách


int char_in_string(char x, string a) {
	for(int i = a.size() - 1; i >= 0; i--) {
		if(x == a[i]) {
			return i;
		}
	}
	return -1;
}
int boyer(string P, string T) {
	int v = P.size(), i = v - 1;
	while(i < T.size()) {
		int k = v - 1;
		while(k > -1 && P[k] == T[i]) {
			i--;
			k--;
		}
		if(k < 0) {
			return i + 1;
		} else {
			int x = char_in_string(T[i], P);
			if(x < 0) {
				i += v;
			} else {
				i += v - x - 1;
			}
		}
	}
	return -1;
}

void qhd(vector<Phone> d, int F[7][1001], int n, int m) {
	for(int i = 0; i <= m; i++) F[0][i] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			F[i][j] = F[i - 1][j];
			if(j >= d[i].kichThuoc) {
				int tmp = d[i].giaBan + F[i - 1][j - d[i].kichThuoc];
				if(tmp > F[i][j]) {
					F[i][j] = tmp;
				}
			}
		}
	}
}

void truy(vector<Phone> d, int F[7][1001], int n, int m, vector<Phone> &res) {
	int i = n, j = m;
	while(i != 0) {
		if(F[i][j] != F[i - 1][j]) {
			res.push_back(d[i]);
			j -= d[i].kichThuoc;
		}
		i--;
	}
}
void z_algo(string s, vector<int> &z){
	int left = 0, right = 0, n = s.size();
	for(int i = 1; i < n; i++){
		if(i > right){
			left = i;
			right = i;
			while(right < n && s[right - left] == s[right]){
				right++;
			}
			z[i] = right - left;
			right--;
		}
		else if(z[i - left] < right - i + 1){
			z[i] = z[i - left];
		}
		else{
			left = i;
			while(right < n && s[right - left] == s[right]){
				right++;
			}
			z[i] = right - left;
			right--;
		}
	}
}
int z_app(string P, string T){
	string s = P + "$" + T;
	int n = s.size(), cnt = 0;
	vector<int> z(n, 0);
	z_algo(s, z);
	for(int i : z){
		if(P.size() == i){
			cnt++;
		}
	}
	return cnt;
}

void A5(vector<Phone> d, vector<Phone> &res) {
	for(Phone i : d) {
		if(z_app("SSD", i.nhanHieu)){
			res.push_back(i);
		}
	}
}

//	tim kiem nhi phan
int A2(vector<Phone> d, int left , int right){
	if(left == right){
		if(d[left].giaBan >= 4000000){
			return 1;
		}
		return 0;
	}
	int mid = (left + right) / 2;
	int cnt_left = A2(d, left, mid);
	int cnt_right = A2(d, mid + 1, right);
	return cnt_left + cnt_right;
}
int A3(vector<Phone> d, int index, int n){
	if(index == n - 1){
		return d[index].giaBan;
	}
	return d[index].giaBan + A3(d, index + 1, n);
}

int main() {
	int n = 6;
	int s = 15;
//qhd
	vector<Phone> d;
	vector<Phone> res;
	d.push_back({ "", 0, 0});
	d.push_back({ "SSD Abc", 4, 5000000 });
	d.push_back({ "SSD", 5, 4500000 });
	d.push_back({ "vivo", 5, 4000000 });
	d.push_back({ "xiaomi", 3, 3500000 });
	d.push_back({ "bphone", 3, 3000000 });
	d.push_back({ "bphone2", 3, 3000000 });
	

	int dp[7][1001];
	qhd(d, dp, n, s);
	truy(d, dp, n, s, res);

	for(Phone i : res) {
		cout << i.nhanHieu << " - " << i.giaBan << endl;
	}
//z - boyer: danh sach + so luong
	cout << "-----------------" << endl;
	vector<Phone> res2;
	A5(d, res2);

	for(Phone i : res2) {
		cout << i.nhanHieu << " - " << i.giaBan << endl;
	}
//	chia de tri: >= 4000000 => 3
	cout << "-----------------" << endl;
	cout << A2(d, 0, d.size() - 1);
	cout << "-----------------" << endl;
//	de quy : tong gia = 23tr
	cout << A3(d, 0, d.size());
	
	return 0;
}