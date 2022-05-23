#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>
#include<map>
#include<string>

using namespace std;


int find_number(char* els, int n, char x) {
	for (int i = 0; i < n; i++) {
		if (els[i] == x)
			return i;
	}
}

bool assoc(char** v, char* els, int n) {
	int checker = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (v[find_number(els, n, v[i][j])][k] != v[i][find_number(els, n, v[j][k])])
					return false;
			}
		}
	}
	return true;
}


set<set<char>> all_gen(char* els, int n, int x) {
	set<set<char>> res;
	while (x < n) {

		if (x == 1) {
			for (int i = 0; i < n; i++) {
				set<char> t1;
				t1.insert(els[i]);
				res.insert(t1);
			}
		}

		else {
			for (int i = 0; i < n; i++) {
				for (set<char> t1 : res) {
					set<char> t2 = t1;
					t2.insert(els[i]);
					res.insert(t2);
				}
			}
		}
		x++;
	}
	return res;
}


void alg_1(char** v, int n, char* els) {
	set<set<char>> all1 = all_gen(els, n, 1);
	set<set<char>> r_res;
	set<set<char>> l_res;
	set<set<char>> b_res;

	for (set<char> x : all1) {
		set<char> res1 = x;
		for (char el : x)
			for (int i = 0; i < n; i++)
				res1.insert(v[find_number(els, n, el)][i]);
		if (x.size() == res1.size())
			r_res.insert(x);


		set<char> res2 = x;
		for (char el : x)
			for (int i = 0; i < n; i++)
				res2.insert(v[i][find_number(els, n, el)]);
		if (x.size() == res2.size())
			l_res.insert(x);


		if (res1 == res2 && res1.size() == x.size())
			b_res.insert(x);
	}



	cout << "\nLeft   ";
	for (set<char> x : l_res) {
		cout << "{ ";
		for (char y : x) {
			cout << y << " ";
		}
		cout << "}  ";
	}

	cout << "\nRight   ";
	for (set<char> x : r_res) {
		cout << "{ ";
		for (char y : x) {
			cout << y << " ";
		}
		cout << "}  ";
	}

	cout << "\nBilateral   ";
	for (set<char> x : b_res) {
		cout << "{ ";
		for (char y : x) {
			cout << y << " ";
		}
		cout << "}  ";
	}
	cout << endl;
}


set<pair<char, char>> my_union(set<pair<char, char>> x, set<pair<char, char>> y) {
	set<pair<char, char>> res;
	for (pair<char, char> el1 : x)
		if (y.find(el1) != y.end())
			res.insert(el1);
	return res;
}


set<int> my_intersection(vector<int> x, vector<int> y) {
	set<int> res;
	for (int el1 : x)
		for (int el2 : y)
			if (el1 == el2)
				res.insert(el1);
	return res;
}


vector<int> my_intersection2(vector<int> x, vector<int> y) {
	vector<int> res;
	for (int el1 : x)
		for (int el2 : y)
			if (el1 == el2)
				res.push_back(el1);
	return res;
}


vector<vector<int>> eq(int** v2, int n, char* els) {

	vector<vector<int>> res;
	int* count = new int[n];
	for (int i = 0; i < n; i++) {
		count[i] = 1;
	}

	for (int i = 0; i < n; i++) {
		if (count[i]) {
			vector<int> srez;
			for (int j = i; j < n; j++) {
				if (v2[i][j] && count[j]) {
					count[j] = 0;
					srez.push_back(j);
				}
			}
			count[i] = 0;
			res.push_back(srez);
		}
	}

	cout << endl << "Фактор-множество: {";
	for (int i = 0; i < res.size(); i++) {
		cout << "{";
		for (int j = 0; j < res[i].size(); j++) {
			cout << els[res[i][j]];
			if (j != res[i].size() - 1)
				cout << ", ";
		}
		cout << "}";
		if (i != res.size() - 1)
			cout << ", ";
	}
	cout << "}" << endl;

	return res;

}


string print_inter(set<int> v, char* els) {
	string res = "";
	res += "{";
	for (int x : v) {
		res = res + els[x] + ", ";
	}
	res.pop_back();
	res.pop_back();
	res += "}";
	return res;
}

string print_inter_vec(vector<int> v, char* els) {
	string res = "";
	res += "{";
	for (int x : v) {
		res = res + els[x] + ", ";
	}
	res.pop_back();
	res.pop_back();
	res += "}";
	return res;
}



void alg_2(char** v, int n, char* els) {
	set<pair<char, char>> R;
	set<pair<char, char>> L;
	set<pair<char, char>> J;
	set<pair<char, char>> H;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			set<char> R1;
			R1.insert(els[i]);
			set<char> R2;
			R2.insert(els[j]);
			set<char> L1;
			L1.insert(els[i]);
			set<char> L2;
			L2.insert(els[j]);
			for (int k = 0; k < n; k++) {
				R1.insert(v[i][k]);
				R2.insert(v[j][k]);
				L1.insert(v[k][i]);
				L2.insert(v[k][j]);
			}
			if (R1 == R2)
				R.insert(make_pair(els[i], els[j]));
			if (L1 == L2)
				L.insert(make_pair(els[i], els[j]));


			set<char> J1;
			J1.insert(els[i]);
			set<char> J2;
			J2.insert(els[j]);
			for (int k = 0; k < n; k++) {
				J1.insert(v[k][i]);
				J2.insert(v[k][j]);
			}
			for (char el : J1) {
				for (int k = 0; k < n; k++) {
					J1.insert(v[find_number(els, n, el)][k]);
				}
			}
			for (char el : J2) {
				for (int k = 0; k < n; k++) {
					J2.insert(v[find_number(els, n, el)][k]);
				}
			}

			if (J1 == J2)
				J.insert(make_pair(els[i], els[j]));
		}
	}

	cout << "\nL   { ";
	for (pair<char, char> x : L) {
		cout << "(" << x.first << ", " << x.second << ") ";
	}

	cout << "}\nR   { ";
	for (pair<char, char> x : R) {
		cout << "(" << x.first << ", " << x.second << ") ";
	}

	cout << "}\nJ   { ";
	for (pair<char, char> x : J) {
		cout << "(" << x.first << ", " << x.second << ") ";
	}

	//Полугруппа конечна, поэтому D = J
	cout << "}\nD   { ";
	for (pair<char, char> x : J) {
		cout << "(" << x.first << ", " << x.second << ") ";
	}

	H = my_union(L, R);
	cout << "}\nH   { ";
	for (pair<char, char> x : H) {
		cout << "(" << x.first << ", " << x.second << ") ";
	}
	cout << "}\n\n";

	int** v1;
	v1 = new int* [n];
	for (int i = 0; i < n; i++) {
		v1[i] = new int[n];
		for (int j = 0; j < n; j++) {
			v1[i][j] = 0;
		}
	}
	for (pair<char, char> x : L) {
		v1[find_number(els, n, x.first)][find_number(els, n, x.second)] = 1;
	}
	cout << "L \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << v1[i][j] << " ";
		}
		cout << endl;
	}
	vector<vector<int>> l_eq = eq(v1, n, els);
	cout << "\n\n\n";



	int** v2;
	v2 = new int* [n];
	for (int i = 0; i < n; i++) {
		v2[i] = new int[n];
		for (int j = 0; j < n; j++) {
			v2[i][j] = 0;
		}
	}
	for (pair<char, char> x : R) {
		v2[find_number(els, n, x.first)][find_number(els, n, x.second)] = 1;
	}
	cout << "R \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << v2[i][j] << " ";
		}
		cout << endl;
	}

	vector<vector<int>> r_eq = eq(v2, n, els);
	cout << "\n\n\n";



	int** v3;
	v3 = new int* [n];
	for (int i = 0; i < n; i++) {
		v3[i] = new int[n];
		for (int j = 0; j < n; j++) {
			v3[i][j] = 0;
		}
	}
	for (pair<char, char> x : J) {
		v3[find_number(els, n, x.first)][find_number(els, n, x.second)] = 1;
	}
	cout << "D \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << v3[i][j] << " ";
		}
		cout << endl;
	}
	vector<vector<int>> d_eq = eq(v3, n, els);
	cout << "\n\n\n";



	for (vector<int> cl : d_eq) {
		vector<vector<int>> res_l;
		vector<vector<int>> res_r;
		for (vector<int> el : l_eq) {
			if (my_intersection2(cl, el) == el)
				res_l.push_back(el);
		}
		for (vector<int> el : r_eq)
			if (my_intersection2(cl, el) == el)
				res_r.push_back(el);

		cout << setw(15) << "";
		for (vector<int> ans : res_l) {
			string str1 = print_inter_vec(ans, els);
			cout << setw(15) << str1;
		}
		cout << endl;
		for (vector<int> ans : res_r) {
			string str1 = print_inter_vec(ans, els);
			cout << setw(15) << str1 << setw(15);
			for (vector<int> ans2 : res_l) {
				string str2 = print_inter(my_intersection(ans, ans2), els);
				cout << str2 << setw(15);
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}
}



int main() {
	setlocale(LC_ALL, "Russian");
	int w = 999;
	while (w > 0) {
		cout << "1 - алгоритмы построения идеалов полугруппы по таблице Кэли" << endl;
		cout << "2 - алгоритмы вычисления отношений Грина и построения «egg-box»-картины конечной полугруппы" << endl;
		cout << "0 - выход" << endl;
		cin >> w;
		if (w == 1) {
			int n;
			cout << "Введите количество элементов полугруппы. n = ";
			cin >> n;
			char* els = new char[n];
			cout << "Введите элементы: ";
			for (int i = 0; i < n; i++)
				cin >> els[i];

			char** v1;
			v1 = new char* [n];
			cout << endl;
			cout << "Введите таблицу Кэли:" << endl;
			for (int i = 0; i < n; i++) {
				v1[i] = new char[n];
				for (int j = 0; j < n; j++) {
					cin >> v1[i][j];
				}
			}
			if (assoc(v1, els, n))
				alg_1(v1, n, els);
			else
				cout << "Операция не ассоциативна" << endl;
		}


		if (w == 2) {
			int n;
			cout << "Введите количество элементов полугруппы. n = ";
			cin >> n;
			char* els = new char[n];
			cout << "Введите элементы: ";
			for (int i = 0; i < n; i++)
				cin >> els[i];

			char** v1;
			v1 = new char* [n];
			cout << endl;
			cout << "Введите таблицу Кэли:" << endl;
			for (int i = 0; i < n; i++) {
				v1[i] = new char[n];
				for (int j = 0; j < n; j++) {
					cin >> v1[i][j];
				}
			}

			if (assoc(v1, els, n))
				alg_2(v1, n, els);
			else
				cout << "Операция не ассоциативна" << endl;

		}
		cout << endl;
	}
	return 0;
}