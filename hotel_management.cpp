#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#define MAX_ROOMS 100

using namespace std;

// Customer Class
class Customer {
public:
    string name;
    string address;
    string phone;
    string from_date;
    string to_date;
    float payment_advance;
    int booking_id;
};

// Room Class
class Room {
public:
    int roomNumber;
    char ac;
    char type;
    char stype;
    int rent;
    int status;
    Customer cust;

    Room() {
        roomNumber = 0;
        rent = 0;
        status = 0;
    }

    void addRoom();
    void searchRoom(int);
    void displayRoom();
};

// Global Room Array
Room rooms[MAX_ROOMS];
int count = 0;

// Function to add a new room
void Room::addRoom() {
    cout << "\nEnter Room Number: ";
    cin >> roomNumber;

    cout << "\nType AC/Non-AC (A/N): ";
    cin >> ac;

    cout << "\nType Comfort (S/N): ";
    cin >> type;

    cout << "\nType Size (B/S): ";
    cin >> stype;

    cout << "\nDaily Rent: ";
    cin >> rent;

    status = 0;
    cout << "\nRoom Added Successfully!\n";
}

// Function to search for a room
void Room::searchRoom(int rno) {
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == rno) {
            cout << "\nRoom Details\n";
            cout << "\nRoom is " << (rooms[i].status == 1 ? "Reserved" : "Available");
            rooms[i].displayRoom();
            return;
        }
    }
    cout << "\nRoom not found!\n";
}

// Function to display room details
void Room::displayRoom() {
    cout << "\nRoom Number: " << roomNumber;
    cout << "\nType AC/Non-AC: " << ac;
    cout << "\nType Comfort: " << type;
    cout << "\nType Size: " << stype;
    cout << "\nRent: " << rent << "\n";
}

// Hotel Management Class
class HotelMgnt {
public:
    void checkIn();
    void getAvailRoom();
    void searchCustomer(string);
    void checkOut(int);
    void guestSummaryReport();
};

// Function for customer check-in
void HotelMgnt::checkIn() {
    int rno, found = 0;
    cout << "\nEnter Room Number: ";
    cin >> rno;

    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == rno) {
            found = 1;
            if (rooms[i].status == 1) {
                cout << "\nRoom is already Booked!";
                return;
            }

            cout << "\nEnter Booking ID: ";
            cin >> rooms[i].cust.booking_id;

            cout << "\nEnter Customer Name: ";
            cin >> rooms[i].cust.name;

            cout << "\nEnter Address: ";
            cin >> rooms[i].cust.address;

            cout << "\nEnter Phone: ";
            cin >> rooms[i].cust.phone;

            cout << "\nEnter From Date: ";
            cin >> rooms[i].cust.from_date;

            cout << "\nEnter To Date: ";
            cin >> rooms[i].cust.to_date;

            cout << "\nEnter Advance Payment: ";
            cin >> rooms[i].cust.payment_advance;

            rooms[i].status = 1;
            cout << "\nCustomer Checked-in Successfully!\n";
            return;
        }
    }

    if (!found) {
        cout << "\nRoom not found!";
    }
}

// Function to display available rooms
void HotelMgnt::getAvailRoom() {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 0) {
            rooms[i].displayRoom();
            found = true;
        }
    }
    if (!found) {
        cout << "\nAll rooms are reserved!\n";
    }
}

// Function to search customer by name
void HotelMgnt::searchCustomer(string pname) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 1 && rooms[i].cust.name == pname) {
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].roomNumber << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "\nCustomer not found!";
    }
}

// Function for customer check-out
void HotelMgnt::checkOut(int roomNum) {
    int days;
    float billAmount;
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 1 && rooms[i].roomNumber == roomNum) {
            found = true;
            cout << "\nEnter Number of Days: ";
            cin >> days;

            billAmount = days * rooms[i].rent;
            cout << "\n######## CheckOut Details ########";
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].roomNumber;
            cout << "\nAddress: " << rooms[i].cust.address;
            cout << "\nPhone: " << rooms[i].cust.phone;
            cout << "\nTotal Amount Due: " << billAmount;
            cout << "\nAdvance Paid: " << rooms[i].cust.payment_advance;
            cout << "\nTotal Payable: " << billAmount - rooms[i].cust.payment_advance << "\n";

            rooms[i].status = 0;
            return;
        }
    }

    if (!found) {
        cout << "\nRoom not found!";
    }
}

// Function to display summary report
void HotelMgnt::guestSummaryReport() {
    if (count == 0) {
        cout << "\nNo Guests in the Hotel!";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 1) {
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].roomNumber;
            cout << "\nAddress: " << rooms[i].cust.address;
            cout << "\nPhone: " << rooms[i].cust.phone;
            cout << "\n---------------------------------------";
        }
    }
}

// Function to manage rooms
void manageRooms() {
    Room room;
    int option, rno;
    do {
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\nEnter Option: ";
        cin >> option;

        switch (option) {
            case 1:
                room.addRoom();
                rooms[count++] = room;
                break;
            case 2:
                cout << "\nEnter Room Number: ";
                cin >> rno;
                room.searchRoom(rno);
                break;
        }
    } while (option != 3);
}

// Main Function
int main() {
    HotelMgnt hm;
    int opt, rno;
    string pname;

    do {
        cout << "\n1. Manage Rooms\n2. Check-In\n3. Available Rooms\n4. Search Customer\n5. Check-Out\n6. Guest Summary Report\n7. Exit\n";
        cout << "Enter Option: ";
        cin >> opt;

        switch (opt) {
            case 1: manageRooms(); break;
            case 2: hm.checkIn(); break;
            case 3: hm.getAvailRoom(); break;
            case 4: cout << "Enter Customer Name: "; cin >> pname; hm.searchCustomer(pname); break;
            case 5: cout << "Enter Room Number: "; cin >> rno; hm.checkOut(rno); break;
            case 6: hm.guestSummaryReport(); break;
            case 7: cout << "\nTHANK YOU!"; break;
        }
    } while (opt != 7);

    return 0;
}
