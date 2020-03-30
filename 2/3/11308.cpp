/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 * 11239 - Open Source
 *
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <utility>
#include <set>
#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

namespace std {
template<typename T, typename... Args>
  unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }
}

struct recipe_t {
  private:
  ull                      _cost{ 0 };

  public:
  std::string                         name;
  std::vector<std::pair<string, ull>> ingredients;

  void calc_colst(const std::map<std::string, ull>& prices) {
    _cost = 0;
    for (const auto& ingredient : ingredients) {
      auto it = prices.find(ingredient.first);
      if (it != prices.end()) {
        const auto& price{ it->second };
        const auto& ammount{ ingredient.second };
        _cost += ammount * price;
      }
    }
  }

  ull cost() const {
    return _cost;
  }

  bool operator<(const recipe_t& other) const {
    ll diff { (ll)_cost - (ll)other._cost };
    return diff ? diff < 0ll : name < other.name;
  }
};

struct store_t {
  std::string                    name;
  ull                            budget{ 0ll };
  std::map<std::string, ull>     ingredients;
  std::vector<recipe_t>          recipes;
};

int main() {
  string output = "";
  ull binders;
  std::string store, ingredient_name, recipe_name;
  cin >> binders;
  cin.ignore();

  for (ull ii = 0; ii < binders; ii++) {
    store_t store;
    ull ingredients, recipes, cost, recipe_items, ammount;

    std::getline(cin, store.name);
    cin >> ingredients >> recipes >> store.budget;
    std::transform(store.name.begin(),
                   store.name.end(),
                   store.name.begin(),
                   [](char c) { return std::toupper(c); });

    for (ull jj = 0; jj < ingredients; jj++) {
      cin >> ingredient_name >> cost;
      store.ingredients[ingredient_name] = cost;
    }
    cin.ignore();

    for (ull jj = 0; jj < recipes; jj++) {
      recipe_t recipe;

      std::getline(cin, recipe.name);
      cin >> recipe_items;

      for (ull kk = 0; kk < recipe_items; kk++) {
        cin >> ingredient_name >> ammount;
        recipe.ingredients.push_back({ingredient_name, ammount});
      }

      recipe.calc_colst(store.ingredients);

      if (recipe.cost() <= store.budget) {
        store.recipes.emplace_back(std::move(recipe));
      }
      cin.ignore();
    }
    std::cout << store.name << "\n";

    if (store.recipes.size()) {
      std::sort(store.recipes.begin(), store.recipes.end());
      for (const auto& recipe : store.recipes) {
        std::cout << recipe.name << "\n";
      }
    }
    else {
      std::cout << "Too expensive!\n";
    }

    std::cout << "\n";
  }

  return(0);
}