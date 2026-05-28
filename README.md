# 🎮 Game Store Management System

A console-based C++ application that simulates a digital game store — inspired by platforms like Steam and Epic Games. Built as a 3rd semester OOP course project using structured programming concepts.

---

## 👥 Presented By

| Roll Number | Name |
|---|---|
| BCSF24M017 | Umer Farooq Afridi |
| BCSF24M032 | Ayesha Bint e Younus |
| BCSF24M046 | Gulshan Mushtaq |

---

## 📌 Project Overview

The system allows **customers** to browse, search, filter, and purchase video games from a pre-defined inventory stored in a text file. An **Admin** (password-protected) can manage the inventory by adding, removing, or updating game prices.

---

## 🎯 Project Objectives

- Demonstrate practical use of structured programming concepts
- Implement arrays, dynamic memory allocation, and text file handling
- Build a menu-driven system that interacts with data stored in external files
  - `games.txt` — main game database (admin-managed)
  - `history.txt` — created on first purchase, updated on every checkout
- Design the project so it can easily be converted to OOP later

---

## 🗂️ System Modules

### Module 1 — Admin
The admin prepares and manages `games.txt` containing all game information.

**File format:**
```
Name, Genre, Price
Batman: Arkham Knight, Action, 6500
```

### Module 2 — Customer
The customer interacts with the store through a menu-driven interface with the following options:

1. View all available games
2. Filter games by genre (e.g. Action, Sports, Adventure)
3. Filter games by price range
4. Search a specific game by name
5. Add a game to cart
6. Remove a game from cart
7. View items in the cart
8. Checkout and generate bill
9. Exit the program

Upon checkout, purchase details are saved to `history.txt` for record keeping.

---

## 📁 File Structure

| File | Type | Purpose |
|---|---|---|
| `games.txt` | Text | Stores all game information (predefined and admin-editable) |
| `history.txt` | Text | Stores user purchase records and bill details |

---

## 🧠 Programming Concepts Covered

| Concept | Application |
|---|---|
| Arrays | Store and display game data |
| Dynamic Memory Allocation | Manage cart and number of available games |
| Text File Handling | Read from `games.txt`, write purchase history to `history.txt` |
| Functions | Handle each menu operation separately |

> **Total Global Functions: 27** — ensuring full modularity across the system

---

## ⚙️ Program Flow

```
PROGRAM START
│
├── loadGamesFromTextFile()     → Load games.txt into memory (dynamic array, cap: 100)
│
└── MAIN MENU LOOP
    ├── 1. Admin Mode
    │   ├── handleAdminLogin()  → Password check (hardcoded: 112356)
    │   └── adminMenu()
    │       ├── Add Game
    │       ├── Remove Game
    │       ├── Update Price
    │       ├── View All Games
    │       └── Save & Exit     → saveGamesToTextFile()
    │
    ├── 2. Customer Mode
    │   └── customerMenu()
    │       ├── Browse / Search / Filter Games
    │       ├── Add to Cart
    │       ├── Remove from Cart
    │       ├── View Cart
    │       ├── Checkout        → generateOrderID() → saveOrderToHistory()
    │       └── View Purchase History
    │
    └── 3. Exit
```

---

## 🔧 Function Reference

### Admin Functions

| Function | Purpose |
|---|---|
| `handleAdminLogin()` | Authenticates admin via hardcoded password |
| `adminMenu()` | Displays and routes admin options |
| `addGame()` | Adds new game after validating name, genre, and price |
| `removeGame()` | Removes game by name, shifts array elements left |
| `updateGamePrice()` | Finds game and updates its price (range: 0–10000) |
| `viewAllGames()` | Displays all games in formatted table |
| `saveGamesToTextFile()` | Persists current inventory to `games.txt` |
| `findGameIndex()` | Case-insensitive search — returns index or -1 |
| `toLowerCase()` | Converts string to lowercase for comparison |
| `selectGenre()` | Lets user choose from 17 predefined genres |
| `resize()` | Doubles array capacity when full (100→200→400...) |

### Customer Functions

| Function | Purpose |
|---|---|
| `customerMenu()` | Displays and routes customer options |
| `inputPriceRange()` | Optional price filter (Y/N), sets min/max range |
| `filterAllGames()` | Displays all games within price range |
| `filterByGenre()` | Displays games matching genre AND price range |
| `isPriceInRange()` | Returns true if price falls within min–max |
| `addToCart()` | Adds game to cart — prevents duplicates, auto-resizes |
| `removeFromCart()` | Removes game from cart, shifts elements left |
| `viewCart()` | Displays cart contents with total item count |
| `checkout()` | Processes purchase, generates order ID, clears cart |
| `calculateTotal()` | Sums all prices in current cart |
| `generateOrderID()` | Generates unique 5-digit random order ID |
| `isOrderIDUnique()` | Checks `history.txt` to confirm ID not already used |
| `saveOrderToHistory()` | Appends order details to `history.txt` |

---

## 💾 Memory Management

**Dynamic Arrays Used:**
- `games[]` — Main inventory (starts at 100, doubles as needed)
- `cart[]` — Shopping cart (starts at 5, doubles as needed)

**Resize Strategy:** Capacity doubles when full → old array deleted after copying → no memory leaks

**Cleanup:** Both arrays deleted at program end via `delete[]`

---

## ✨ Key Design Features

| Feature | Implementation |
|---|---|
| Case-insensitive search | All comparisons use `toLowerCase()` |
| Duplicate prevention | Admin can't add existing game; customer can't add same game to cart twice |
| Input validation | Price ranges enforced (0–10000); invalid menu input loops until corrected |
| Data persistence | Games saved to `games.txt` on admin exit; orders appended to `history.txt` on checkout |
| Dynamic memory | Arrays auto-resize when capacity is reached |
| Unique Order IDs | 5-digit random numbers verified against history before assignment |

---

## 🧪 Test Cases

### Test 1 — Admin: View All Games
**Steps:** Run → Admin (pw: 112356) → View All Games  
**Expected:** All 135 games displayed. First: `Batman: Arkham Knight (Action, 6500)` | Last: `Borderlands 2 (Shooter, 3000)`

---

### Test 2 — Admin: Add New Game
**Input:** Name: `Assassin's Creed Mirage` | Genre: Action | Price: 7000  
**Expected:** "Game added successfully." | Total becomes 136

---

### Test 3 — Admin: Duplicate Prevention
**Input:** Try to add `GTA V`  
**Expected:** "This game already exists." — system rejects without prompting for genre/price

---

### Test 4 — Admin: Update Game Price
**Input:** Game: `Valorant` | New Price: 5000  
**Expected:** "Price updated." | Valorant displays Rs.5000 in view

---

### Test 5 — Admin: Remove Game
**Input:** Game: `Left 4 Dead 2`  
**Expected:** "Game removed." | Total becomes 135 | Saved to `games.txt` on exit

---

### Test 6 — Customer: Browse All Games (No Filter)
**Input:** Price filter: N | Mode: Show All  
**Expected:** All 135 games displayed

---

### Test 7 — Customer: Price Range Filter
**Input:** Price filter: Y | Min: 0 | Max: 2000  
**Expected sample output:**
```
Rocket League     | Sports       | Rs.0
Fortnite          | Online       | Rs.0
Cuphead           | Action       | Rs.1500
Hollow Knight     | Metroidvania | Rs.1500
Dead Cells        | Action       | Rs.2000
Rainbow Six Siege | Shooter      | Rs.2000
```

---

### Test 8 — Customer: Genre + Price Combined Filter
**Input:** Price: 5000–10000 | Genre: Action  
**Expected sample output:**
```
Batman: Arkham Knight          | Action | Rs.6500
Marvel's Spider-Man Remastered | Action | Rs.7500
Ghost of Tsushima              | Action | Rs.9000
God of War Ragnarok            | Action | Rs.10000
```
> All results must satisfy **both** conditions (Action genre AND price 5000–10000)

---

### Test 9 — Customer: Add Items to Cart
| Input | Expected |
|---|---|
| `Minecraft Java Edition` | "Minecraft Java Edition added to cart successfully!" |
| `The Witcher 3` | "The Witcher 3 added to cart successfully!" |
| `Hollow Knight` | "Hollow Knight added to cart successfully!" |

---

### Test 10 — Customer: Cart Duplicate Prevention
**Input:** Add `Minecraft Java Edition` again  
**Expected:** "Minecraft Java Edition is already in your cart!"

---

### Test 11 — Customer: View Cart
```
===== YOUR CART =====
Minecraft Java Edition  | Sandbox      | Rs.5000
The Witcher 3           | RPG          | Rs.5000
Hollow Knight           | Metroidvania | Rs.1500
Total items: 3
```

---

### Test 12 — Customer: Remove From Cart
**Input:** Remove `The Witcher 3`  
**Expected:** "The Witcher 3 removed from cart." | Cart now shows 2 items

---

### Test 13 — Customer: Checkout
**Expected flow:**
```
===== CHECKOUT =====
Total Amount: Rs.6500
Confirm purchase? (Y/N): Y

Purchase successful!
Your Order ID: 47382
Thank you for shopping with us!
```
> Cart cleared after successful checkout

---

### Test 14 — Customer: View Purchase History
```
--- Purchase History ---
Order ID: 47382
Items Purchased:
  Minecraft Java Edition - Rs.5000
  Hollow Knight          - Rs.1500
Total Amount: Rs.6500
```

---

### Test 15 — Customer: Unique Order ID Generation
**Steps:** Add `GTA V` + `Cyberpunk 2077` → Checkout  
**Expected:** New unique 5-digit order ID different from previous order | Both orders visible in history

---

### Test 16 — Data Persistence (Restart Verification)
**Steps:** Exit program → Restart → Admin → View All Games  
**Verification checklist:**
- [ ] Total games: 135
- [ ] `Assassin's Creed Mirage` still present (added in Test 2)
- [ ] `Left 4 Dead 2` still absent (removed in Test 5)
- [ ] `Valorant` price: Rs.5000 (updated in Test 4)
- [ ] Both purchase orders still in `history.txt`

---

## 🔮 Future OOP Conversion Plan

When converted to Object-Oriented Programming, the following upgrades are planned:

- `Customer`, `Game`, `Cart`, and `Store` will become classes
- Support for multiple customers with unique purchase histories
- Discount system for frequent buyers or large purchases
- Option to rate or review games

---

## 🚀 How to Run

```bash
# Compile
g++ main.cpp -o GameStore

# Run
./GameStore          # Linux/macOS
GameStore.exe        # Windows
```

> Make sure `games.txt` is in the same directory as the executable before running.

---

## 👤 Author

**Umer Farooq Afridi**
BS Computer Science — University of the Punjab, Lahore
🔗 [LinkedIn](https://www.linkedin.com/in/umerfarooqafridi/) &nbsp;|&nbsp; 🐙 [GitHub](https://github.com/code-runner006)


