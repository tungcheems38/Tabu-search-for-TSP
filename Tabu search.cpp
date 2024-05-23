#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<random>
#include <list>
using namespace std;
int chiphi (const vector<int>& route, const vector<vector<int>> & distance)
{
    int total_distance = 0;
    for (int i = 0; i < route.size(); ++i) {
    int current_city = route[i];
    int next_city;
    if (current_city == route.size())
        {next_city = route[0];}
    else {
        next_city = route[i + 1];}
    total_distance += distance[current_city][next_city];
  }
    cout << "Hamso1thanhcong";
  return total_distance;
}
    vector<int> lotrinhngaunhien(vector<int>& route, const &n) {
  for (int i = 0; i < n; ++i) {
    route[i] = i;
  }
  random_device rd;
  mt19937 gen(rd());
  shuffle(route.begin(), route.end(), gen);
  cout << "Hamso2thanhcong";
  return route;
}
vector<int> generate_neighbor_route(const vector<int>& route, const vector<vector<int>>& distance) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(0, route.size() - 1);
  int city1 = dis(gen);
  int city2 = dis(gen);
  while (city1 == city2) {
    city2 = dis(gen);
  }

  vector<int> neighbor_route = route;
  swap(neighbor_route[city1], neighbor_route[city2]);
  int new_distance = chiphi(neighbor_route, distance);
  cout << "Hamso3thanhcong";
  if (new_distance < chiphi(route, distance)) {
    return neighbor_route;
  } else {
    return route;
  }
}
bool is_tabu(const vector<int>& route, list<vector<int>>& tabu_list, int tabu_size) {
  // Duyệt qua danh sách "tabu"
  for (const vector<int>& tabu_route : tabu_list) {
    // So sánh các lộ trình
    if (route == tabu_route) {
        cout << "Hamso4thanhcong1";
      return true;
    }
  }
  cout << "Hamso4thanhcong2";
  return false;
}

// Hàm thêm một lộ trình vào danh sách "tabu"
void add_to_tabu_list(const vector<int>& route, list<vector<int>>& tabu_list, int tabu_size) {
  // Thêm vào đầu danh sách
  tabu_list.push_front(route);
  // Giữ kích thước danh sách "tabu"
  while (tabu_list.size() > tabu_size) {
    tabu_list.pop_back();
  }
cout << "Hamso5thanhcong";
}
int main ()
{
    int n;
    cin >> n;
    vector<vector<int>> distance(n, vector<int>(n));
    vector<int> route(n);
    ifstream fin;
    ofstream fout;
    fin.open("D:\\C++\\Tabusearch.txt");
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            fin >> distance [i][j];
            cout << distance [i][j];
        }
    }
    fin.close();
  lotrinhngaunhien(route,n);
   int chiphihientai=chiphi (route, distance);
  // Khởi tạo danh sách "tabu"
  list<vector<int>> tabu_list;
  const int tabu_size = 5; // Kích thước danh sách "tabu"

  // Lặp lại để tạo và đánh giá các "lộ trình lân cận"
  int max_iterations = 100; // Số lần lặp tối đa
  while (max_iterations-- > 0) {
    // Tạo "lộ trình lân cận" mới
    vector<int> neighbor_route = generate_neighbor_route(route, distance);

    // Kiểm tra xem "lộ trình lân cận" có trong danh sách "tabu" hay không
    if (is_tabu(neighbor_route, tabu_list, tabu_size)==false) {
      // Chấp nhận "lộ trình lân cận" mới nếu nó tốt hơn
      int chiphimoi = chiphi(neighbor_route, distance);
      if (chiphimoi < chiphihientai) {
        route = neighbor_route;
        chiphihientai= chiphimoi;
        cout << "Ham if co chay";

        // Cập nhật danh sách "tabu"
        add_to_tabu_list(route, tabu_list, tabu_size);}}}

        // Hiển thị "lộ trình lân cận" mới
        cout << "Lộ trình lân cận tốt nhất: ";
        for (int city : route) {
          cout << city << " -> ";
        }
        cout << n - 1 << endl;
        cout << "Tổng chiều dài: " << chiphihientai << endl;

  return 0;
}


















