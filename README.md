================================================================================
                    GAME STORE MANAGEMENT SYSTEM
                          PROJECT DOCUMENTATION
================================================================================

                              PRESENTED BY:
                      BCSF24M017 - UMER FAROOQ AFRIDI
                      BCSF24M032 - AYESHA BINT E YOUNUS
                      BCSF24M046 - GULSHAN MUSHTAQ


================================================================================
                            PROJECT OVERVIEW
================================================================================

The Game Store Management System is a console-based program designed to 
simulate the operations of a digital game store (like Steam or EpicGames).

The system allows users (customers) to browse, search, and purchase video 
games from a pre-defined list stored in a text file. The user can also enter 
as Admin (password protected) and can manipulate the pre-defined list by 
adding, removing game or changing their price.

The focus of the project is on file handling, arrays, dynamic memory 
allocation, and modular programming through multiple functions.


================================================================================
                            PROJECT OBJECTIVES
================================================================================

✓ To demonstrate practical use of structured programming concepts
✓ To implement arrays, dynamic memory allocation, and text file handling
✓ To build a menu-driven system that interacts with data stored in external 
  files (games.txt contains the database of games and history.txt is created 
  when you purchase for the first time and keeps on getting updated)
✓ To design the project so it can easily be converted to OOP later


================================================================================
                            SYSTEM MODULES
================================================================================

MODULE 1: ADMIN
---------------

The admin prepares a text file named games.txt that contains all game 
information beforehand.

Example content format:
  Name, Genre, Price
  Batman: Arkham Knight
  Action
  Rs. ###

This file serves as the main database for the store.


MODULE 2: USER (CUSTOMER)
-------------------------

The customer interacts with the store through a menu-driven interface.

Available options:
  1. View all available games
  2. Filter games by genre (e.g. Action, Sports, Adventure)
  3. Filter games by price range
  4. Search a specific game by name (He can view the name from above facilities)
  5. Add a game to cart
  6. Remove a game from cart
  7. View items in the cart
  8. Checkout and generate bill
  9. Exit the program

When the user checks out, their purchase information is stored in a text file 
(history.txt) for record keeping.


================================================================================
                        FILE HANDLING STRUCTURE
================================================================================

File            Type        Purpose
-------------   ---------   ---------------------------------------------------
games.txt       Text        Stores all game information (predefined by admin 
                            and can be manipulated later by admin in interface)

history.txt     Text        Stores user purchase records and bill details


================================================================================
                    PROGRAMMING CONCEPTS COVERED
================================================================================

Concept                         Application
-----------------------------   ---------------------------------------------
Arrays                          To store and display game data

Dynamic Memory Allocation       To manage user's cart and number of games 
                                available

Text File Handling              To read data from games.txt and to save 
                                purchase history in history.txt

Functions                       To handle each menu operation separately


Total Global Functions: 27 (to ensure modularity)


================================================================================
                    FUTURE OOP CONVERSION PLAN
================================================================================

When the project is later converted to Object-Oriented Programming, the 
following upgrades will be added:

- Customer, Game, Cart, and Store will become classes (Classes may be added 
  or removed according to our further needs)

- Support for multiple customers with unique purchase histories

- Discount system for frequent buyers or large purchases

- Option to rate or review games





================================================================================
                    GAME STORE MANAGEMENT SYSTEM
                            PROGRAM FLOW
================================================================================

================================================================================
                        PROGRAM INITIALIZATION
================================================================================

MAIN FUNCTION STARTUP
---------------------
- Creates dynamic game array (capacity: 100)
- Loads games from "games.txt" using loadGamesFromTextFile()
- Enters main menu loop


loadGamesFromTextFile()
-----------------------
Purpose: Load game data from text file into memory

Process:
- Reads file line-by-line (name, genre, price format)
- Creates Game objects and stores in array
- Automatically resizes array if capacity exceeded
- Returns count of games loaded

File Format Example:
  GTA V
  Action
  2500
  Minecraft
  Sandbox
  1500


================================================================================
                        MAIN MENU SYSTEM
================================================================================

showMainMenu()
--------------
Displays three options: Admin, Customer, Exit


getIntInputWithRange(minVal, maxVal)
------------------------------------
Purpose: Validate integer input within specified range

Process:
- Reads integer input
- Loops until valid value entered
- Returns validated integer


================================================================================
                        ADMIN MODE
================================================================================

handleAdminLogin()
------------------
Purpose: Authenticate admin access

Process:
- Prompts for password (hardcoded: "112356")
- Compares input with password
- Returns true/false for access


adminMenu()
-----------
Purpose: Manage game inventory

Options:
1. Add Game
2. Remove Game
3. Update Price
4. View All Games
5. Save & Exit


----------------------------
ADMIN FUNCTIONS - DETAILED
----------------------------

addGame()
---------
Purpose: Add new game to inventory

Steps:
1. Get game name (validate not empty)
2. Check duplicate using findGameIndex()
3. Select genre from 17 predefined options via selectGenre()
4. Get price (validate >= 0)
5. Resize array if needed
6. Add game to array and increment count


removeGame()
------------
Purpose: Remove game from inventory

Steps:
1. Get game name
2. Find index using findGameIndex()
3. Shift all elements left to fill gap
4. Decrement size


updateGamePrice()
-----------------
Purpose: Modify existing game price

Steps:
1. Find game by name
2. Display current price
3. Get new price (validate 0-10000)
4. Update in array


viewAllGames()
--------------
Purpose: Display all games in formatted table

Output: Name | Genre | Price for each game


saveGamesToTextFile()
---------------------
Purpose: Persist game data to file

Process:
- Opens "games.txt" for writing
- Writes each game (name, genre, price on separate lines)
- Called automatically when exiting admin menu


----------------------------
ADMIN HELPER FUNCTIONS
----------------------------

findGameIndex()
---------------
Purpose: Search for game by name (case-insensitive)

Process:
- Converts search name to lowercase
- Compares with each game in array
- Returns index if found, -1 if not found


toLowerCase()
-------------
Purpose: Convert string to lowercase for comparison

Process: Loops through string and applies tolower() to each character


selectGenre()
-------------
Purpose: Let user choose from predefined genres

Process:
- Displays 17 genre options (Action, RPG, Sports, etc.)
- Returns selected genre string based on choice


resize()
--------
Purpose: Double array capacity when full

Process:
- Creates new array with double capacity
- Copies all elements from old to new
- Deletes old array
- Updates pointer and capacity


================================================================================
                        CUSTOMER MODE
================================================================================

customerMenu()
--------------
Purpose: Browse games and make purchases

Setup:
- Creates dynamic cart array (initial capacity: 5)
- Manages cart operations
- Handles checkout process

Options:
1. Search/Browse Games
2. Add to Cart
3. Remove from Cart
4. View Cart
5. Checkout
6. View Purchase History
7. Exit


----------------------------
CUSTOMER FUNCTIONS - DETAILED
----------------------------

OPTION 1: Search/Browse Games
------------------------------

inputPriceRange()
-----------------
Purpose: Optional price filter for search

Process:
- Asks if user wants price filter (Y/N)
- If yes: gets min/max price with validation
- If no: sets range to 0-10000 (all prices)


filterAllGames()
----------------
Purpose: Display all games within price range

Process:
- Loops through game array
- Checks each game's price using isPriceInRange()
- Displays matching games


filterByGenre()
---------------
Purpose: Display games matching genre AND price range

Process:
- Similar to filterAllGames()
- Additional check: genre must match exactly
- Displays games meeting both criteria


isPriceInRange()
----------------
Purpose: Check if price falls within min/max range

Returns: true if price >= minP AND price <= maxP


OPTION 2: Add to Cart
---------------------

addToCart()
-----------
Purpose: Add selected game to shopping cart

Steps:
1. Check if game already in cart (prevents duplicates)
2. Resize cart if capacity reached
3. Copy game to cart array
4. Increment cart size


OPTION 3: Remove from Cart
---------------------------

removeFromCart()
----------------
Purpose: Remove item from cart

Steps:
1. Display current cart
2. Get game name to remove
3. Find in cart (case-insensitive)
4. Shift elements left to fill gap
5. Decrement cart size


OPTION 4: View Cart
--------------------

viewCart()
----------
Purpose: Display all items in cart

Output: Numbered list showing name, genre, price, and total count


OPTION 5: Checkout
------------------

checkout()
----------
Purpose: Complete purchase and save order

Steps:
1. Display cart contents
2. Calculate total using calculateTotal()
3. Confirm purchase (Y/N)
4. If confirmed:
   - Generate unique 5-digit order ID
   - Save order to history file
   - Clear cart
   - Display order confirmation


calculateTotal()
----------------
Purpose: Sum all prices in cart

Process: Loops through cart and adds all prices


generateOrderID()
-----------------
Purpose: Create unique 5-digit order number

Process:
- Generates random number (10000-99999)
- Checks uniqueness using isOrderIDUnique()
- Repeats until unique ID found


isOrderIDUnique()
-----------------
Purpose: Verify order ID not already used

Process:
- Opens "history.txt"
- Searches for "Order ID: [number]"
- Returns true if not found (unique)


saveOrderToHistory()
--------------------
Purpose: Append order details to history file

Format:
  ========================================
  Order ID: [5-digit number]
  ----------------------------------------
  Items Purchased:
  1. [Game Name] - Rs.[Price]
  2. [Game Name] - Rs.[Price]
  ----------------------------------------
  Total Amount: Rs.[Total]
  ========================================


OPTION 6: View Purchase History
--------------------------------
Purpose: Display all previous orders

Process:
- Opens "history.txt"
- Reads and displays entire file content
- Shows error if file doesn't exist


================================================================================
                        MEMORY MANAGEMENT
================================================================================

Dynamic Arrays Used:
1. games[] - Main inventory (starts at 100, grows as needed)
2. cart[] - Shopping cart (starts at 5, grows as needed)

Resize Strategy:
- Capacity doubles when full (100→200→400...)
- Old array deleted after copying
- Prevents memory leaks

Cleanup:
- Both arrays deleted at program end using delete[]


================================================================================
                        KEY DESIGN FEATURES
================================================================================

1. Case-Insensitive Search
   - All name comparisons use toLowerCase()

2. Duplicate Prevention
   - Admin: Can't add game with existing name
   - Customer: Can't add same game to cart twice

3. Input Validation
   - Price ranges enforced (0-10000)
   - Menu choices validated
   - Invalid input loops until corrected

4. Data Persistence
   - Games saved to "games.txt" on admin exit
   - Orders appended to "history.txt" on checkout

5. Dynamic Memory
   - Arrays automatically resize when capacity reached
   - No fixed limits on games or cart items

6. Unique Order IDs
   - 5-digit random numbers
   - Checked against history to prevent duplicates
   - Used for order tracking


================================================================================
                        PROGRAM FLOW SUMMARY
================================================================================

Main Loop:
1. Display main menu
2. Route to Admin or Customer mode
3. Perform operations within chosen mode
4. Return to main menu
5. Repeat until Exit selected

Admin Flow:
Login → Manage Inventory → Save → Return

Customer Flow:
Browse → Add to Cart → Checkout → Generate Order → Save History → Return

Data Flow:
File (games.txt) → Memory (games array) → Operations → File (save)
Cart → Checkout → History (history.txt)



================================================================================
                    GAME STORE MANAGEMENT SYSTEM
                      COMPREHENSIVE TEST CASE 
================================================================================

SYSTEM OVERVIEW:
----------------
Total Games Loaded: 135
Admin Password: 112356
File Dependencies: games.txt, history.txt


================================================================================
TEST 1: ADMIN MODE - VIEW ALL GAMES (Verify File Loading)
================================================================================

Steps:
1. Run Program
2. Choose: 1 (Admin)
3. Enter Password: 112356
4. Admin Menu → Choose: 4 (View All Games)

Expected Output:
- Display all 135 games in format: Name | Genre | Price
- First game: Batman: Arkham Knight (Action, 6500)
- Last game: Borderlands 2 (Shooter, 3000)

5. Admin Menu → Choose: 5 (Back to Main Menu)


================================================================================
TEST 2: ADMIN MODE - ADD NEW GAME
================================================================================

Steps:
1. Main Menu → Choose: 1 (Admin)
2. Enter Password: 112356
3. Admin Menu → Choose: 1 (Add Game)

Input:
- Name: Assassin's Creed Mirage
- Genre: Choose 1 (Action)
- Price: 7000

Expected Output: "Game added successfully."

4. Admin Menu → Choose: 4 (View All Games)

Verification:
- Total games should now be 136
- "Assassin's Creed Mirage" should appear at the end of the list


================================================================================
TEST 3: ADMIN MODE - DUPLICATE PREVENTION
================================================================================

Steps:
1. Admin Menu → Choose: 1 (Add Game)
2. Enter Name: GTA V

Expected Output: "This game already exists."

Verification:
- System should reject immediately without prompting for genre/price
- Demonstrates duplicate prevention mechanism


================================================================================
TEST 4: ADMIN MODE - UPDATE GAME PRICE
================================================================================

Steps:
1. Admin Menu → Choose: 3 (Update Game Price)
2. Enter Name: Valorant

Expected Output:
- Current price: 0
- Prompt: Enter new price

3. Enter: 5000

Expected Output: "Price updated."

4. Admin Menu → Choose: 4 (View All Games)

Verification: Valorant should display Rs.5000


================================================================================
TEST 5: ADMIN MODE - REMOVE GAME
================================================================================

Steps:
1. Admin Menu → Choose: 2 (Remove Game)
2. Enter Name: Left 4 Dead 2

Expected Output: "Game removed."

3. Admin Menu → Choose: 4 (View All Games)

Verification:
- Left 4 Dead 2 should no longer appear in list
- Total games should be 135 (136 - 1)

4. Admin Menu → Choose: 5 (Back to Main Menu)

Note: Exiting admin menu automatically saves changes to games.txt


================================================================================
TEST 6: CUSTOMER MODE - BROWSE ALL GAMES (No Filters)
================================================================================

Steps:
1. Main Menu → Choose: 2 (Customer)
2. Customer Menu → Choose: 1 (Search/Browse)

Input:
- Filter by price range? N
- Search mode: 1 (Show All games)

Expected Output: Display all 135 games without filtering


================================================================================
TEST 7: CUSTOMER MODE - PRICE RANGE FILTER
================================================================================

Steps:
1. Customer Menu → Choose: 1 (Search/Browse)

Input:
- Filter by price range? Y
- Minimum price: 0
- Maximum price: 2000
- Search mode: 1 (Show All)

Expected Output (Sample Games):
- Rocket League (Sports, 0)
- Fortnite (Online, 0)
- Dota 2 (Online, 0)
- PUBG: Battlegrounds (Online, 0)
- Limbo (Adventure, 900)
- GTA III (Open-World, 1000)
- Cuphead (Action, 1500)
- Hollow Knight (Metroidvania, 1500)
- Terraria (Sandbox, 1500)
- Dead Cells (Action, 2000)
- Rainbow Six Siege (Shooter, 2000)
- Dishonored (Stealth, 2000)
- Little Nightmares (Horror, 2000)


================================================================================
TEST 8: CUSTOMER MODE - GENRE + PRICE COMBINED FILTER
================================================================================

Steps:
1. Customer Menu → Choose: 1 (Search/Browse)

Input:
- Filter by price range? Y
- Minimum price: 5000
- Maximum price: 10000
- Search mode: 2 (By Genre)
- Choose genre: 1 (Action)

Expected Output (Sample Games):
- Batman: Arkham Knight (Action, 6500)
- Marvel's Spider-Man Remastered (Action, 7500)
- Ghost of Tsushima (Action, 9000)
- Days Gone (Action, 5200)
- The Last of Us Part I (Action, 9000)
- God of War (2018) (Action, 7500)
- Sekiro: Shadows Die Twice (Action, 7800)
- God of War Ragnarok (Action, 10000)
- Marvel's Spider-Man: Miles Morales (Action, 6500)
- Marvel's Spider-Man 2 (Action, 9000)

Verification: All displayed games must satisfy BOTH conditions (Action genre AND price 5000-10000)


================================================================================
TEST 9: CUSTOMER MODE - ADD ITEMS TO CART
================================================================================

Steps:
1. Customer Menu → Choose: 2 (Add to Cart)
2. Enter: Minecraft Java Edition
   Expected: "Minecraft Java Edition added to cart successfully!"

3. Customer Menu → Choose: 2 (Add to Cart)
4. Enter: The Witcher 3
   Expected: "The Witcher 3 added to cart successfully!"

5. Customer Menu → Choose: 2 (Add to Cart)
6. Enter: Hollow Knight
   Expected: "Hollow Knight added to cart successfully!"


================================================================================
TEST 10: CUSTOMER MODE - CART DUPLICATE PREVENTION
================================================================================

Steps:
1. Customer Menu → Choose: 2 (Add to Cart)
2. Enter: Minecraft Java Edition

Expected Output: "Minecraft Java Edition is already in your cart!"

Verification: System prevents adding the same game twice


================================================================================
TEST 11: CUSTOMER MODE - VIEW CART
================================================================================

Steps:
1. Customer Menu → Choose: 4 (View Cart)

Expected Output:
===== YOUR CART =====
1. Minecraft Java Edition | Sandbox | Rs.5000
2. The Witcher 3 | RPG | Rs.5000
3. Hollow Knight | Metroidvania | Rs.1500
Total items: 3


================================================================================
TEST 12: CUSTOMER MODE - REMOVE FROM CART
================================================================================

Steps:
1. Customer Menu → Choose: 3 (Remove from Cart)
   (System automatically displays current cart)

2. Enter: The Witcher 3

Expected Output: "The Witcher 3 removed from cart."

3. Customer Menu → Choose: 4 (View Cart)

Expected Output:
===== YOUR CART =====
1. Minecraft Java Edition | Sandbox | Rs.5000
2. Hollow Knight | Metroidvania | Rs.1500
Total items: 2


================================================================================
TEST 13: CUSTOMER MODE - CHECKOUT PROCESS
================================================================================

Steps:
1. Customer Menu → Choose: 5 (Checkout)

Expected Output:
===== CHECKOUT =====
(Displays cart contents)
----------------------------------------
Total Amount: Rs.6500
----------------------------------------
Confirm purchase? (Y/N):

2. Enter: Y

Expected Output:
- "Purchase successful!"
- "Your Order ID: [5-digit number]" (e.g., 47382)
- "Thank you for shopping with us!"

3. Customer Menu → Choose: 4 (View Cart)

Expected Output: "Cart is empty."

Verification: Cart cleared after successful checkout


================================================================================
TEST 14: CUSTOMER MODE - VIEW PURCHASE HISTORY
================================================================================

Steps:
1. Customer Menu → Choose: 6 (View Purchase History)

Expected Output:
--- Purchase History ---
========================================
Order ID: [5-digit number]
----------------------------------------
Items Purchased:
1. Minecraft Java Edition - Rs.5000
2. Hollow Knight - Rs.1500
----------------------------------------
Total Amount: Rs.6500
========================================


================================================================================
TEST 15: CUSTOMER MODE - UNIQUE ORDER ID GENERATION
================================================================================

Steps:
1. Add new games to cart:
   - Customer Menu → Choose: 2 (Add to Cart)
   - Enter: GTA V

2. Customer Menu → Choose: 2 (Add to Cart)
   - Enter: Cyberpunk 2077

3. Customer Menu → Choose: 5 (Checkout)
4. Confirm: Y

Expected Output: New Order ID (different from previous order)

5. Customer Menu → Choose: 6 (View Purchase History)

Verification:
- Both orders should be displayed
- Each order has unique 5-digit ID
- History shows chronological order


================================================================================
TEST 16: DATA PERSISTENCE (Restart Verification)
================================================================================

Steps:
1. Customer Menu → Choose: 7 (Back to Main)
2. Main Menu → Choose: 3 (Exit)
   Expected: "Exiting..."

3. RESTART PROGRAM

4. Main Menu → Choose: 1 (Admin)
5. Enter Password: 112356
6. Admin Menu → Choose: 4 (View All Games)

Verification:
- Total games: 135
- "Assassin's Creed Mirage" still present (added in TEST 2)
- "Left 4 Dead 2" still absent (removed in TEST 5)
- "Valorant" price: 5000 (updated in TEST 4)

7. Admin Menu → Choose: 5 (Back to Main)
8. Main Menu → Choose: 2 (Customer)
9. Customer Menu → Choose: 6 (View Purchase History)

Verification: Both previous orders still stored in history.txt


================================================================================
                        END OF DOCUMENTATION
================================================================================

