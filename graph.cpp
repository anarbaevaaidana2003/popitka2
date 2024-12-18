// graph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void makeSymmetric(vector<vector<int>>& graph) {
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != graph[j][i]) {
                graph[i][j] = graph[j][i] = max(graph[i][j], graph[j][i]);
            }
        }
    }
}

void dsaturColoring(const vector<vector<int>>& graph, const vector<string>& lectures) {
    int numLectures = lectures.size();
    vector<int> which_color(numLectures, -1);
    vector<int> saturation(numLectures, 0);
    vector<bool> usedColors(numLectures, false);

    vector<int> degree(numLectures, 0);
    for (int i = 0; i < numLectures; i++) {
        for (int j = 0; j < numLectures; j++) {
            if (graph[i][j] == 1) {
                degree[i]++;
            }
        }
    }

    for (int k = 0; k < numLectures; k++) {
        int maxSat = -1, maxDeg = -1, selected = -1;
        for (int i = 0; i < numLectures; i++) {
            if (which_color[i] == -1) {
                if (saturation[i] > maxSat || (saturation[i] == maxSat && degree[i] > maxDeg)) {
                    maxSat = saturation[i];
                    maxDeg = degree[i];
                    selected = i;
                }
            }
        }

        fill(usedColors.begin(), usedColors.end(), false);
        for (int j = 0; j < numLectures; j++) {
            if (graph[selected][j] == 1 && which_color[j] != -1) {
                usedColors[which_color[j]] = true;
            }
        }

        int color = 0;
        while (usedColors[color]) {
            color++;
        }
        which_color[selected] = color;

        for (int j = 0; j < numLectures; j++) {
            if (graph[selected][j] == 1 && which_color[j] == -1) {
                saturation[j]++;
            }
        }
    }

    vector<string> timeSlots = { "8:00", "9:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00" };
    vector<vector<string>> schedule(timeSlots.size());

    for (int i = 0; i < numLectures; i++) {
        int slot = which_color[i];
        if (slot < timeSlots.size()) {
            schedule[slot].push_back(lectures[i]);
        }
    }

    cout << "Lecture Schedule:\n";
    for (int i = 0; i < schedule.size(); i++) {
        if (!schedule[i].empty()) {
            cout << timeSlots[i] << " ";
            for (int j = 0; j < schedule[i].size(); j++) {
                cout << schedule[i][j];
                if (j < schedule[i].size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}

int main() {
    vector<string> lectures = { "BIL-303", "BIL-315", "BIL-317", "BIL-373", "BIL-381",
                               "BIL-377", "BIL-385", "BIL-407", "BIL-409",
                               "BIL-411", "MUH-403", "BIL-473", "BIL-475",
                               "BIL-483", "BIL-485", "BIL-489" };

    int numLectures = lectures.size();

    vector<vector<int>> graph = {
        {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0 ,0 ,0},
        {1 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,1 ,0},
        {1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,1 ,1 ,1 ,1 ,0 ,0 ,1,0 },
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1},
        {1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    };

    makeSymmetric(graph);

    dsaturColoring(graph, lectures);

    return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
