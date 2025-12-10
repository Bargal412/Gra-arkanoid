#include "Score.hpp"
#include <fstream>
#include <vector>
#include <algorithm>

void saveScoreToFile(int score)
{
    std::ofstream file("scores.txt", std::ios::app);
    if (file)
        file << score << "\n";
}

std::vector<int> loadScoresFromFile()
{
    std::ifstream file("scores.txt");
    std::vector<int> scores;
    int s;

    while (file >> s)
        scores.push_back(s);

    std::sort(scores.rbegin(), scores.rend());
    return scores;
}
