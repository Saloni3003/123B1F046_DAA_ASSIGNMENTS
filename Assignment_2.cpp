// ============================================================================
// Program: Movie Recommendation System Optimization using QuickSort
// Author: Saloni Khandelwal
// Roll No: 123B1F046
// ============================================================================

#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;

// ------------------- Structure Definition -------------------
struct Movie {
    string title;
    double rating;
    int year;
    long watchTime; // popularity measure (in thousands of views)
};

// ------------------- Partition Function -------------------
int partition(vector<Movie>& movies, int low, int high, const string& key) {
    Movie pivot = movies[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool condition = false;

        if (key == "rating")
            condition = movies[j].rating < pivot.rating; // ascending order
        else if (key == "year")
            condition = movies[j].year < pivot.year;
        else if (key == "watch")
            condition = movies[j].watchTime < pivot.watchTime;

        if (condition) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return (i + 1);
}

// ------------------- QuickSort Implementation -------------------
void quickSort(vector<Movie>& movies, int low, int high, const string& key) {
    if (low < high) {
        int pi = partition(movies, low, high, key);
        quickSort(movies, low, pi - 1, key);
        quickSort(movies, pi + 1, high, key);
    }
}

// ------------------- Display Function -------------------
void displayMovies(const vector<Movie>& movies, const string& key, double timeTaken) {
    cout << "\n============================================================\n";
    cout << "Movies Sorted by " << key << " (Ascending Order)\n";
    cout << "============================================================\n";
    cout << left << setw(15) << "Title" 
         << setw(10) << "Rating" 
         << setw(10) << "Year" 
         << setw(10) << "Watch" << "\n";
    cout << "------------------------------------------------------------\n";

    for (const auto& m : movies) {
        cout << left << setw(15) << m.title
             << setw(10) << fixed << setprecision(1) << m.rating
             << setw(10) << m.year
             << setw(10) << m.watchTime << "\n";
    }

    cout << "------------------------------------------------------------\n";
    cout << "Time taken by QuickSort: " << fixed << setprecision(3) << timeTaken << " ms\n";
    cout << "============================================================\n";
}

// ------------------- Main Function -------------------
int main() {
    vector<Movie> movies = {
        {"Titanic", 7.8, 1997, 12000},
        {"Matrix", 8.7, 1999, 9800},
        {"Gladiator", 8.5, 2000, 6600},
        {"Avatar", 7.9, 2009, 15000},
        {"Up", 8.2, 2009, 5400},
        {"Inception", 8.8, 2010, 8700},
        {"Avengers", 8.5, 2012, 9500},
        {"Interstellar", 8.6, 2014, 7300},
        {"Coco", 8.4, 2017, 4700},
        {"Joker", 8.4, 2019, 8200}
    };

    vector<string> keys = {"year", "rating", "watch"};

    for (const auto& key : keys) {
        vector<Movie> temp = movies; // copy for each sort
        auto start = high_resolution_clock::now();
        quickSort(temp, 0, temp.size() - 1, key);
        auto end = high_resolution_clock::now();
        double timeTaken = duration_cast<nanoseconds>(end - start).count() / 1e6; // in ms
        displayMovies(temp, key, timeTaken);
    }

    return 0;
}
