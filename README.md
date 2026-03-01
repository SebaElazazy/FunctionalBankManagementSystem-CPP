# Bank Management System (C++) 🏦

A robust, console-based Bank Management System built with **C++**. This project demonstrates structured programming, file handling, and a custom security/permissions system.

## 🚀 Key Features
* **User Authentication:** Secure login system to verify user identity.
* **Permission-Based Access:** Managed using **Bitwise operations** to control access to specific menus (e.g., Read, Write, Delete, Manage Users).
* **Client Management (CRUD):** Complete system to Add, Find, Update, and Delete client records.
- **Transactions System:** Supports Deposits, Withdrawals, and real-time Balance tracking with validation.
- **Data Persistence:** All records are persistently stored and managed via text files (`Clients.txt` and `Users.txt`).

## 🛠️ Technical Concepts Applied
* **File Handling:** Using `fstream` for reading and writing data records.
* **Data Structures:** Utilizing `structs` and `vectors` for organized data management.
* **Security Logic:** Implementation of an "Access Denied" layer based on user permission levels.
* **Input Validation:** Ensuring account numbers exist and balances are sufficient before transactions.

## 📂 Project Structure
* `Bank System.cpp`: The main source code containing all logic and menus.
* `Clients.txt`: Database for client information.
* `Users.txt`: Database for system users and their permission bits.

---
*Developed as part of my C++ learning journey.*
This project helped me bridge the gap between theoretical concepts and practical implementation. My next goal is to refactor this system using **Object-Oriented Programming (OOP)**!
