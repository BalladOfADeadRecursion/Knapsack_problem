#include <iostream>
#include <vector>
using namespace std;

struct Item {
    int weight;
    int volume;
};

int knapsackMaxValue(vector<Item>& items, vector<int>& counts, int capacity, int num_items) {
    vector<vector<vector<int>>> dp(num_items + 1, vector<vector<int>>(capacity + 1, vector<int>(capacity + 1, 0)));

    for (int i = 1; i <= num_items; ++i) {
        for (int j = 0; j <= counts[i - 1]; ++j) {
            for (int w = capacity; w >= items[i - 1].weight * j; --w) {
                for (int v = capacity; v >= items[i - 1].volume * j; --v) {
                    dp[i][w][v] = max(dp[i][w][v], dp[i - 1][w - items[i - 1].weight * j][v - items[i - 1].volume * j] + items[i - 1].weight * j);
                }
            }
        }
    }

    if (dp[num_items][capacity][capacity] == 0) {
        cout << "Решений нет" << endl;
        return 0;
    }

    int res_weight = dp[num_items][capacity][capacity];
    vector<int> chosen_counts(num_items, 0);

    for (int i = num_items; i > 0 && res_weight > 0; --i) {
        while (res_weight >= items[i - 1].weight && dp[i][res_weight][res_weight] == dp[i - 1][res_weight - items[i - 1].weight][res_weight - items[i - 1].volume] + items[i - 1].weight) {
            chosen_counts[i - 1]++;
            res_weight -= items[i - 1].weight;
        }
    }

    int x1 = chosen_counts[0];
    int x2 = chosen_counts[1];
    int x3 = chosen_counts[2];
    int x4 = chosen_counts[3];
    int x5 = chosen_counts[4];

    cout << "Количество предмета x1: " << x1 << endl;
    cout << "Количество предмета x2: " << x2 << endl;
    cout << "Количество предмета x3: " << x3 << endl;
    cout << "Количество предмета x4: " << x4 << endl;
    cout << "Количество предмета x5: " << x5 << endl;

    return dp[num_items][capacity][capacity];
}

int main() {
    setlocale(LC_ALL, "Rus");
    vector<Item> items;
    vector<int> counts;

    int num_items = 5; // Количество предметов (ограничено до 5)

    cout << "Введите количество каждого предмета (x1-x5): ";
    for (int i = 0; i < num_items; ++i) {
        int count;
        cout << "Количество предмета x" << (i + 1) << ": ";
        cin >> count;
        while (count < 0) {
            cout << "Количество предмета не может быть отрицательным. Введите положительное значение: ";
            cin >> count;
        }
        counts.push_back(count);
    }

    int capacity;
    cout << "Введите вместимость рюкзака по весу и объему: ";
    cin >> capacity;
    while (capacity < 0) {
        cout << "Вместимость рюкзака не может быть отрицательной. Введите положительное значение: ";
        cin >> capacity;
    }

    cout << "Введите вес и объем каждого предмета:\n";
    for (int i = 0; i < num_items; ++i) {
        int weight, volume;
        cout << "Вес предмета x" << (i + 1) << ": ";
        cin >> weight;
        while (weight < 0) {
            cout << "Вес предмета не может быть отрицательным. Введите положительное значение: ";
            cin >> weight;
        }

        cout << "Объем предмета x" << (i + 1) << ": ";
        cin >> volume;
        while (volume < 0) {
            cout << "Объем предмета не может быть отрицательным. Введите положительное значение: ";
            cin >> volume;
        }

        items.push_back({ weight, volume });
    }

    int max_weight = knapsackMaxValue(items, counts, capacity, num_items);
    cout << "Максимальный вес предметов в рюкзаке: " << max_weight << endl;

    return 0;
}