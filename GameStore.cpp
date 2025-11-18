#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Game {
    string name;
    string genre;
    int price;
};

// Utility Functions
void resize(Game*& arr, int& capacity);
string toLowerCase(const string &s);
int getIntInputWithRange(int minVal, int maxVal);
int findGameIndex(Game g[], int size, const string &gameName);
string selectGenre();

// File Handling
int loadGamesFromTextFile(Game *&arr, int &capacity);
void saveGamesToTextFile(Game arr[], int size);
void saveOrderToHistory(Game cart[], int cartSize, int orderID, int total);

// Admin Functions
bool handleAdminLogin();
void addGame(Game *&arr, int &size, int &capacity);
void removeGame(Game arr[], int &size);
void updateGamePrice(Game arr[], int size);
void viewAllGames(Game arr[], int size);

// Customer Functions
void inputPriceRange(int &minP, int &maxP);
bool isPriceInRange(int price, int minP, int maxP);
void filterAllGames(Game arr[], int size, int minP, int maxP);
void filterByGenre(Game arr[], int size, const string &genre, int minP, int maxP);
void viewCart(Game cart[], int cartSize);
void addToCart(Game *&cart, int &cartSize, int &cartCap, Game &g);
void removeFromCart(Game cart[], int &cartSize);

// Checkout & Order Functions
int calculateTotal(Game cart[], int cartSize);
bool isOrderIDUnique(int orderID);
int generateOrderID();
void checkout(Game *&cart, int &cartSize, int &cartCap);

// Menu Functions
void showMainMenu();
void customerMenu(Game *&games, int &gameCount, int &gameCapacity);
void adminMenu(Game *&games, int &gameCount, int &gameCapacity);


void resize(Game*& arr, int& capacity) {
    int newCap = capacity * 2;
    Game* newArr = new Game[newCap];
    for (int i = 0; i < capacity; i++) newArr[i] = arr[i];
    delete[] arr;
    arr = newArr;
    capacity = newCap;
}

string toLowerCase(const string &s) {
    string out = s;
    for (int i = 0; i < out.size(); i++) {
        out[i] = tolower(out[i]);
    }
    return out;
}

int calculateTotal(Game cart[], int cartSize) {
    int sum = 0;
    for (int i = 0; i < cartSize; i++) {
        sum += cart[i].price;
    }
    return sum;
}

bool isOrderIDUnique(int orderID) {
    ifstream fin("history.txt");
    if (!fin) return true;
    string line;
    string searchID = "Order ID: " + to_string(orderID);
    while (getline(fin, line)) {
        if (line == searchID) {
            fin.close();
            return false;
        }
    }
    fin.close();
    return true;
}

int generateOrderID() {
    int orderID;
    do {
        srand(time(0));
        orderID = 10000 + (rand() % 90000);
    } while (!isOrderIDUnique(orderID));
    return orderID;
}

void saveOrderToHistory(Game cart[], int cartSize, int orderID, int total) {
    ofstream fout("history.txt", ios::app);
    if (!fout) {
        cout << "Error: Unable to save order history.\n";
        return;
    }
    fout << "========================================\n";
    fout << "Order ID: " << orderID << "\n";
    fout << "----------------------------------------\n";
    fout << "Items Purchased:\n";   
    for (int i = 0; i < cartSize; i++) {
        fout << (i+1) << ". " << cart[i].name << " - Rs." << cart[i].price << "\n";
    } 
    fout << "----------------------------------------\n";
    fout << "Total Amount: Rs." << total << "\n";
    fout << "========================================\n\n";
    fout.close();
}

void saveGamesToTextFile(Game arr[], int size) {
    ofstream fout("games.txt");
    for (int i = 0; i < size; i++) {
        fout << arr[i].name << "\n" << arr[i].genre << "\n" << arr[i].price << "\n";
    }
    fout.close();
}


int loadGamesFromTextFile(Game *&arr, int &capacity) {
    ifstream fin("games.txt");
    string name, genre;
    int price;
    int count = 0;
    while (getline(fin, name)) {
        getline(fin, genre);
        fin >> price;
        fin.ignore();
        Game g;
        g.name = name;
        g.genre = genre;
        g.price = price;
        if (count >= capacity) {
            resize(arr, capacity);
        }
        arr[count] = g;
        count++;
    }
    fin.close();
    return count;
}

void showMainMenu() {
    cout << "\n===== GAME STORE =====\n";
    cout << "1. Admin\n";
    cout << "2. Customer\n";
    cout << "3. Exit\n";
    cout << "Choose option: ";
}

int getIntInputWithRange(int minVal, int maxVal) {
    int x;
    cin >> x;
    while (x < minVal || x > maxVal) {
        cout << "Enter a number between " << minVal << " and " << maxVal << ": ";
        cin >> x;
    }
    return x;
}

void inputPriceRange(int &minP, int &maxP) {
    cout << "Do you want to filter by price range? (Y/N): ";
    char ch;
    cin >> ch;
    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n') {
        cout << "Invalid input! Enter Y or N: ";
        cin >> ch;
    }
    cin.ignore(); 
    if (ch == 'Y' || ch == 'y') {
        cout << "Enter minimum price (min 0): ";
        cin >> minP;
        while(minP < 0){
            cout << "Invalid, try again: ";
            cin >> minP;
        }
        cout << "Enter maximum price (max 10000): ";
        cin >> maxP;
        while (maxP < 0 || maxP > 10000){
            cout << "Invalid, try again: ";
            cin >> maxP;
        }
        cin.ignore(); 
        if (maxP < minP) swap(minP, maxP);
    } else {
        minP = 0;
        maxP = 10000;
    }
}

bool isPriceInRange(int price, int minP, int maxP) {
    if (price >= minP && price <= maxP) {
        return true;
    } else {
        return false;
    }
}

string selectGenre() {
    cout << "\n=== SELECT GENRE ===\n";
    cout << "1. Action\n";
    cout << "2. Adventure\n";
    cout << "3. RPG\n";
    cout << "4. Sports\n";
    cout << "5. Racing\n";
    cout << "6. Simulation\n";
    cout << "7. Strategy\n";
    cout << "8. Horror\n";
    cout << "9. Puzzle\n";
    cout << "10. Shooter\n";
    cout << "11. Open-World\n";
    cout << "12. Online\n";
    cout << "13. Roguelike\n";
    cout << "14. Metroidvania\n";
    cout << "15. Stealth\n";
    cout << "16. Survival\n";
    cout << "17. Sandbox\n";
    cout << "Choose genre (1-17): ";
    int choice = getIntInputWithRange(1, 17);
    if (choice == 1) return "Action";
    else if (choice == 2) return "Adventure";
    else if (choice == 3) return "RPG";
    else if (choice == 4) return "Sports";
    else if (choice == 5) return "Racing";
    else if (choice == 6) return "Simulation";
    else if (choice == 7) return "Strategy";
    else if (choice == 8) return "Horror";
    else if (choice == 9) return "Puzzle";
    else if (choice == 10) return "Shooter";
    else if (choice == 11) return "Open-World";
    else if (choice == 12) return "Online";
    else if (choice == 13) return "Roguelike";
    else if (choice == 14) return "Metroidvania";
    else if (choice == 15) return "Stealth";
    else if (choice == 16) return "Survival";
    else if (choice == 17) return "Sandbox";
}

bool handleAdminLogin() {
    cout << "Enter admin password: ";
    const string password = "112356";
    string attempt;
    getline(cin, attempt);
    if (attempt == password) {
        cout << "Access granted.\n";
        return true;
    } else {
        cout << "Access denied.\n";
        return false;
    }
}

int findGameIndex(Game g[], int size, const string &gameName) {
    string low = toLowerCase(gameName);
    for (int i = 0; i < size; ++i) {
        if (toLowerCase(g[i].name) == low) return i;
    }
    return -1;
}

void addGame(Game *&arr, int &size, int &capacity) {
    cout << "Enter new game details.\n";
    Game g;
    cout << "Name: ";
    getline(cin, g.name);
    if (g.name.size() == 0) {
        cout << "Name cannot be empty.\n";
        return;
    }
    if (findGameIndex(arr, size, g.name) != -1) {  
        cout << "This game already exists. \n";
        return;
    }
    g.genre = selectGenre();  
    cout << "Price: ";
    cin >> g.price;
    while(g.price < 0){
        cout << "Invalid, try again(must be greater than or equal to 0): ";
        cin >> g.price;
    }
    cin.ignore(); 
    if (size >= capacity) {
        resize(arr, capacity);
    }
    arr[size] = g;
    size++;
    cout << "Game added successfully.\n";
}

void removeGame(Game arr[], int &size) {
    cout << "Enter name of game to remove: ";
    string name;
    getline(cin, name);
    int idx = findGameIndex(arr, size, name);
    if (idx == -1) {
        cout << "Game not found.\n";
        return;
    }
    for (int i = idx; i < size - 1; i++) arr[i] = arr[i + 1];
    size--;
    cout << "Game removed.\n";
}

void updateGamePrice(Game arr[], int size) {
    cout << "Enter name of game to update price: ";
    string name;
    getline(cin, name);
    int idx = findGameIndex(arr, size, name);
    if (idx == -1) {
        cout << "Game not found.\n";
        return;
    }
    cout << "Current price: " << arr[idx].price << "\n";
    cout << "Enter new price (0 - 10000): ";
    int p;
    cin >> p;
    while(p < 0 || p > 10000){
        cout << "Invalid, try again: ";
        cin >> p;
    }    
    arr[idx].price = p;
    cout << "Price updated.\n";
}

void viewAllGames(Game arr[], int size) {
    if (size == 0) { cout << "No games available.\n"; return; }
    cout << " | NAME | GENRE | PRICE |\n\n";
    for (int i = 0; i < size; i++) {
        cout <<" | " << arr[i].name << " | " << arr[i].genre
         << " | " << arr[i].price << " |\n";
    }
}

void adminMenu(Game *&games, int &gameCount, int &gameCapacity) {
    while (true) {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. Add Game\n";
        cout << "2. Remove Game\n";
        cout << "3. Update Game Price\n";
        cout << "4. View All Games\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choose: ";
        int ch = getIntInputWithRange(1, 6);
        cin.ignore();
        if (ch == 1) addGame(games, gameCount, gameCapacity);
        else if (ch == 2) removeGame(games, gameCount);
        else if (ch == 3) updateGamePrice(games, gameCount);
        else if (ch == 4) viewAllGames(games, gameCount);
        else if (ch == 5) { saveGamesToTextFile(games, gameCount);
             break; }
    }
}

void filterAllGames(Game arr[], int size, int minP, int maxP) {
    bool found = false;
    cout << "\nFiltered Games:\n";
    for (int i = 0; i < size; i++) {
        if (isPriceInRange(arr[i].price, minP, maxP)) {
            cout << " | " << arr[i].name << " | " << arr[i].genre << 
            " | Rs." << arr[i].price << " |\n";
            found = true;
        }
    }
    if (!found) cout << "No games match your filters.\n";
}

void filterByGenre(Game arr[], int size, const string &genre, int minP, int maxP) {
    bool found = false;
    cout << "\nFiltered Games :\n";
    for (int i = 0; i < size; i++) {
        if (isPriceInRange(arr[i].price, minP, maxP)
            && arr[i].genre == genre) {
            cout << " | " << arr[i].name << " | " << arr[i].genre << 
            " | Rs." << arr[i].price << " |\n";
            found = true;
        }
    }
    if (!found) cout << "No games match your filters.\n";
}

void viewCart(Game cart[], int cartSize) {
    if (cartSize == 0) { 
        cout << "Cart is empty.\n"; 
        return; 
    }
    cout << "\n===== YOUR CART =====\n";
    for (int i = 0; i < cartSize; i++) {
        cout << (i+1) << ". " << cart[i].name << " | " << cart[i].genre 
             << " | Rs." << cart[i].price << "\n";
    }
    cout << "Total items: " << cartSize << "\n";
}

void addToCart(Game *&cart, int &cartSize, int &cartCap, Game &g) {
    for (int i = 0; i < cartSize; i++) {
        if (toLowerCase(cart[i].name) == toLowerCase(g.name)) {
            cout << "" << g.name << " is already in your cart!\n";
            return;  
        }
    }
    if (cartSize >= cartCap) {
        resize(cart, cartCap);
    }
    cart[cartSize++] = g;
    
    cout << g.name << " added to cart successfully!\n";
}

void removeFromCart(Game cart[], int &cartSize) {
    if (cartSize == 0) { 
        cout << "Cart is empty. Nothing to remove.\n"; 
        return; 
    }
    viewCart(cart, cartSize);
    cout << "\nEnter name of game to remove: ";
    string name; 
    getline(cin, name);
    for (int i = 0; i < cartSize; i++) {
        if (toLowerCase(cart[i].name) == toLowerCase(name)) {
            for (int j = i; j < cartSize - 1; j++) {
                cart[j] = cart[j + 1];
            }
            cartSize--;
            cout << name << " removed from cart.\n";
            return;
        }
    }
    cout << "Game not found in cart.\n";
}    

void checkout(Game *&cart, int &cartSize, int &cartCap) {
    if (cartSize == 0) { 
        cout << "Cart is empty. Nothing to checkout.\n"; 
        return; 
    }
    cout << "\n===== CHECKOUT =====\n";
    viewCart(cart, cartSize);
    int total = calculateTotal(cart, cartSize);
    cout << "\n----------------------------------------\n";
    cout << "Total Amount: Rs." << total << "\n";
    cout << "----------------------------------------\n";
    cout << "Confirm purchase? (Y/N): ";
    char confirm;
    cin >> confirm;
    while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n') {
        cout << "Invalid input! Enter Y or N: ";
        cin >> confirm;
    }
    cin.ignore();  
    if (confirm == 'Y' || confirm == 'y') {
        int orderID = generateOrderID();  
        saveOrderToHistory(cart, cartSize, orderID, total); 
        cout << "\nPurchase successful!\n";
        cout << "Your Order ID: " << orderID << "\n";
        cout << "Thank you for shopping with us!\n";
        cartSize = 0;  
    } else {
        cout << "Purchase cancelled.\n";
    }
}  

void customerMenu(Game *&games, int &gameCount, int &gameCapacity) {
    int cartCap = 5;
    Game *cart = new Game[cartCap];
    int cartSize = 0;
    while (true) {
        cout << "\n--- CUSTOMER MENU ---\n";
        cout << "1. Search / Browse Games\n";
        cout << "2. Add to Cart\n";
        cout << "3. Remove from Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Checkout\n";
        cout << "6. View Purchase History\n";
        cout << "7. Back to Main\n";
        cout << "Choose: ";
        int ch = getIntInputWithRange(1, 7);
        cin.ignore();
        if (ch == 1) {
            int minP, maxP;
            inputPriceRange(minP, maxP);
            cout << "Search mode:\n1) Show All games\n2) By Genre\nChoose: ";
            int mode = getIntInputWithRange(1, 2);
            cin.ignore();
            if (mode == 1) filterAllGames(games, gameCount, minP, maxP);
            else {
                string genre = selectGenre();  
                filterByGenre(games, gameCount, genre, minP, maxP);
            }
        }
        else if (ch == 2) {
            cout << "Enter Game name to add to cart: ";
            string name;
            getline(cin,name);
            int idx = findGameIndex(games, gameCount, name);
            if (idx == -1) { cout << "Game not found.\n"; }
            else {
                addToCart(cart, cartSize, cartCap, games[idx]);
            }
        }
        else if (ch == 3) {
            removeFromCart(cart, cartSize);
        }
        else if (ch == 4) {
            viewCart(cart, cartSize);
        }
        else if (ch == 5) {
            checkout(cart, cartSize, cartCap);
        }
        else if (ch == 6) {
            ifstream fin("history.txt");
            if(!fin){cout << "No purchase history available\n";}
            else {
            string line;
            cout << "\n--- Purchase History ---\n";
            while (getline(fin, line)) cout << line << "\n";
            fin.close();}
            }
        else if (ch == 7) break;
    }
    delete[] cart;
}


int main() {
    int gameCapacity = 100;
    Game *games = new Game[gameCapacity];
    int gameCount = 0;
    gameCount = loadGamesFromTextFile(games, gameCapacity);
    while(true) {
        showMainMenu();
        int choice = getIntInputWithRange(1, 3);
        cin.ignore();
        if (choice == 1) {
            if (handleAdminLogin()) {
                adminMenu(games, gameCount, gameCapacity);
            }
        } else if (choice == 2) {
            customerMenu(games, gameCount, gameCapacity);
        } else if (choice == 3) {
            cout << "Exiting... \n";
            break;
        }        
    }
    delete[] games;
    return 0;
}