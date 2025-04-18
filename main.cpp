#include "../database/database.cpp"
#include "../database/shard.cpp"
#include "../storage/bucket.cpp"
#include "../storage/dashtable.cpp"
#include "../storage/hasher.cpp"
#include "../storage/segment.cpp"
#include "dashtable.hpp"
#include <iostream>

using namespace std;

void updateScore(Database* db, const string& player, int score) {
    try {
        cout << "[DEBUG] updateScore called for player: " << player << ", score: " << score << endl;

        string existingScoreStr;
        try {
            existingScoreStr = db->Get(player);
            cout << "[DEBUG] Existing score string: " << existingScoreStr << endl;
        } catch (const std::runtime_error& e) {
            cout << "[DEBUG] Player not found in DB (runtime_error): " << e.what() << endl;
            existingScoreStr = "";  // Treat as new player
        } catch (const std::exception& e) {
            cout << "[DEBUG] Some other std::exception: " << e.what() << endl;
            existingScoreStr = "";  // Fallback
        }

        if (!existingScoreStr.empty()) {
            int existingScore = stoi(existingScoreStr);
            if (score > existingScore) {
                db->Put(player, to_string(score));
                cout << "✅ Updated score: " << player << " -> " << score << endl;
            } else {
                cout << "⚠️  Score not updated (lower than current): " << player << " -> " << score << endl;
            }
        } else {
            db->Put(player, to_string(score));
            cout << "🆕 New player added: " << player << " -> " << score << endl;
        }
    } catch (const std::exception& e) {
        cout << "[ERROR] Uncaught exception in thread: " << e.what() << endl;
    } catch (...) {
        cout << "[ERROR] Unknown exception in thread." << endl;
    }
}



void menu(Database* db) {
    cout << "[DEBUG] Entered menu()" << endl;
    int choice;
    while (true) {
        cout << "\n===== Leaderboard Menu =====\n";
        cout << "1. Submit score\n";
        cout << "2. View player score\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "[ERROR] cin failed. Exiting...\n";
            break;
        }

        cout << "[DEBUG] Choice entered: " << choice << endl;

        if (choice == 1) {
            string name;
            int score;
            cout << "Enter player name: ";
            cin >> name;
            cout << "Enter score: ";
            cin >> score;

            cout << "[DEBUG] Submitting score for " << name << ": " << score << endl;

            thread t(updateScore, db, name, score);
            t.join();
        } else if (choice == 2) {
            string name;
            cout << "Enter player name to view score: ";
            cin >> name;
            string score = db->Get(name);
            if (!score.empty()) {
                cout << "🎯 " << name << "'s score: " << score << endl;
            } else {
                cout << "❌ Player not found." << endl;
            }
        } else if (choice == 3) {
            cout << "👋 Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    cout << "[DEBUG] Starting program...\n";
    Database* db = new Database(8);  // Or any number of shards you want
    cout << "[DEBUG] Database created.\n";
    menu(db);
    cout << "[DEBUG] Returned from menu(). Cleaning up...\n";
    delete db;
    return 0;
}


// int main(int argc, char** argv) {
// 	Database* db = new Database(4);
// 	db->Put("Atharva", "Desai");

// 	delete db;
// }
