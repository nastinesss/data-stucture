#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Book {
    string title;
    string genre;
    double price;
    int popularity;
    string dateAdded;
    bool isSoldOut;
};

void printBook(const Book& b) {
    cout << "Title: " << setw(15) << left << b.title
         << "| Genre: " << setw(10) << b.genre
         << "| Price: " << setw(6) << b.price
         << "| Popularity: " << setw(3) << b.popularity
         << "| Date: " << b.dateAdded
         << "| Status: " << (b.isSoldOut ? "Sold out" : "Available") << endl;
}

void printAssortment(const vector<Book>& store) {
    cout << "\n--- Book store assortment ---\n";
    for (const auto& book : store) {
        printBook(book);
    }
    cout << "--------------------------------------\n";
}

int main() {
    vector<Book> store = {
        {"1984", "Dystopia", 250.50, 95, "2023-10-01", false},
        {"Dune", "Sci-Fi", 450.00, 88, "2023-11-15", true},
        {"Fahrenheit 451", "Dystopia", 200.00, 75, "2023-09-20", false},
        {"Hobbit", "Fantasy", 350.00, 99, "2024-01-10", false}
    };

    store.push_back({"Witcher", "Fantasy", 400.00, 92, "2024-03-05", false});

    store.erase(remove_if(store.begin(), store.end(), [](const Book& b) {
        return b.isSoldOut;
    }), store.end());

    cout << "\nAfter deleting sold books:";
    printAssortment(store);

    sort(store.begin(), store.end(), [](const Book& a, const Book& b) {
        return a.price < b.price;
    });
    cout << "\nSorting by price:";
    printAssortment(store);

    string targetGenre = "Dystopia";
    double minPrice = 100.0, maxPrice = 300.0;
    
    cout << "\nFiltration (Genre: " << targetGenre << ", Price: " << minPrice << "-" << maxPrice << "):\n";
    for (const auto& book : store) {
        if (book.genre == targetGenre && book.price >= minPrice && book.price <= maxPrice) {
            printBook(book);
        }
    }

    string searchTitle = "1984";
    auto it = find_if(store.begin(), store.end(), [&](const Book& b) {
        return b.title == searchTitle;
    });

    cout << "\nSearching book result '" << searchTitle << "':\n";
    if (it != store.end()) printBook(*it);
    else cout << "Book is not found.\n";

    return 0;
}