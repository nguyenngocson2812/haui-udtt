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
int Z_app(string P, string T){
	string s = P + "$" + T;
	int n = s.size(), cnt = 0;;
	vector<int> z(n, 0);
	z_algo(s, z);
	cout << endl;
	for(int i : z){
		if(i == P.size()){
			cnt++;
		}
	}
	return cnt;
}
//	qhd
void qhd(vector<Phone> d, int F[7][1001], int n, int m){
//	F[n][m];
	for(int i = 0; i <= m; i++) F[0][i] = 0;
	for(int i = 1;i <= n; i++){
		for(int j = 0; j <= m; j++){
			F[i][j] = F[i - 1][j];
			if(j >= d[i].kichThuoc){
				int tmp = d[i].giaBan + F[i - 1][j - d[i].kichThuoc];
				if(tmp > F[i][j]){
					F[i][j] = tmp;
				}
			}
		}
	}
}
void res1(vector<Phone> d, int F[7][1001], int n1, int m1, vector<Phone> &res){
//	F[n][m];
	int i = n1, j = m1;
	while(i != 0){
		if(F[i][j] != F[i - 1][j]){
			j -= d[i].kichThuoc;
			res.push_back(d[i]);
		}
		i--;
	}
}

//	de quy
int tong(vector<Phone> d, int index, int n){
	if(index == n - 1){
		return d[index].giaBan;
	}
	return d[index].giaBan + tong(d, index + 1, n);	
}

//	chia de tri
int chiadetri(vector<Phone> d, int left, int right){
	if(left == right){
		if(d[left].giaBan >= 4000000){
			return 1;
		}
		return 0;
	}
	int mid = (left + right) / 2;
	int cnt_left = chiadetri(d, left, mid);
	int cnt_right = chiadetri(d, mid + 1, right);
	return cnt_left + cnt_right;
}

//	boyer
int char_in_string(char x, string a){
	for(int i = a.size() - 1; i >= 0; i--){
		if(x == a[i]){
			return i;
		}
	}
	return -1;
}
int boyer(string P, string T){
	int v = P.size(), i = v - 1;
	while(i < T.size()){
		int k = v - 1;
		while(k > -1 && P[k] == T[i]){
			i--;
			k--;
		}
		if(k < 0){
			return i + 1;
		}
		else{
			int x = char_in_string(T[i], P);
			if(x < 0){
				i += v;
			}
			else{
				i += v - x - 1;
			}
		}
	}
	return -1;
}

//	tham lam
int tham_lam(vector<int> d, int max_value) {
	int i = 1;
	int sum = 0, cnt = 0;
	int tmp = max_value;
	while(i < d.size()) {
		if(tmp - d[i] >= 0) {
			cnt++;
			sum += d[i];
			tmp -= d[i];
		}
		i++;
	}
	if(max_value == sum) {
		return cnt;
	} else {
		return 0;
	}
}
int main(){
	vector<Phone> d;
	vector<Phone> res;
	int n = 6;
	d.push_back({ "", 0, 0});
	d.push_back({ "SSD Abc", 4, 5000000 });
	d.push_back({ "SSD", 5, 4500000 });
	d.push_back({ "vivo", 5, 4000000 });
	d.push_back({ "xiaomi", 3, 3500000 });
	d.push_back({ "bphone", 3, 3000000 });
	d.push_back({ "bphone2", 3, 3000000 });
	
	int dp[7][1001] = {0};
	cout << "--------------" << endl;
	cout << "--------------" << endl;
	int m = 13;
	qhd(d, dp, n, m);
	res1(d, dp, n, m, res);
	
	for(Phone i : res) {
		cout << i.nhanHieu << " - " << i.giaBan << endl;
	}
	cout << "Tong: " << tong(d, 0, d.size());
	cout << "chiadetri: " << chiadetri(d, 0, d.size() - 1);
		cout << "--------------" << endl;
		
	string T = "mothaibabonnamsau";
	string P = "namsau";
	
	
	cout << boyer(P, T);
	
	
	return 0;
}