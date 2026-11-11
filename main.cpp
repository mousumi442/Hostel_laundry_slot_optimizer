#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    string name;
    int room;

    void input()
    {
        cout << "Enter student name: ";
        cin >> name;
        cout << "Enter room number: ";
        cin >> room;
    }
};

class LaundryRequest
{
public:
    Student student;
    int slot;
    int machine;
    bool active;

    LaundryRequest()
    {
        active = false;
    }

    void book(int s, int m)
    {
        student.input();
        slot = s;
        machine = m;
        active = true;
    }

    void display()
    {
        if(active)
        {
            cout << "Name: " << student.name << endl;
            cout << "Room: " << student.room << endl;
            cout << "Machine: " << machine << endl;
            cout << "Slot: " << slot << endl;
        }
    }
};

class LaundryManager
{
    LaundryRequest requests[20];
    bool machines[10][2];

public:

    LaundryManager()
    {
        for(int i = 0; i < 10; i++)
        {
            machines[i][0] = false;
            machines[i][1] = false;
        }
    }

    void bookSlot()
    {
        int slot;
        cout << "\nAvailable Slots:\n";

        for(int i = 0; i < 10; i++)
        {
            cout << i + 1 << ". ";

            if(!machines[i][0] || !machines[i][1])
                cout << "Available\n";
            else
                cout << "Full\n";
        }

        cout << "Enter slot number: ";
        cin >> slot;

        if(slot < 1 || slot > 10)
        {
            cout << "Invalid slot!\n";
            return;
        }

        int machine;

        if(!machines[slot - 1][0])
            machine = 1;
        else if(!machines[slot - 1][1])
            machine = 2;
        else
        {
            cout << "Slot is full!\n";
            return;
        }

        for(int i = 0; i < 20; i++)
        {
            if(!requests[i].active)
            {
                requests[i].book(slot, machine);
                machines[slot - 1][machine - 1] = true;

                cout << "\nSlot booked successfully!\n";
                cout << "Machine: " << machine << endl;
                cout << "Slot: " << slot << endl;
                return;
            }
        }

        cout << "Booking limit reached!\n";
    }

    void viewBookings()
    {
        cout << "\n===== LAUNDRY SCHEDULE =====\n";

        bool found = false;

        for(int i = 0; i < 20; i++)
        {
            if(requests[i].active)
            {
                cout << "\nBooking " << i + 1 << endl;
                requests[i].display();
                found = true;
            }
        }

        if(!found)
            cout << "No bookings available.\n";
    }

    void cancelBooking()
    {
        string name;
        cout << "Enter student name: ";
        cin >> name;

        for(int i = 0; i < 20; i++)
        {
            if(requests[i].active && requests[i].student.name == name)
            {
                int slot = requests[i].slot;
                int machine = requests[i].machine;

                machines[slot - 1][machine - 1] = false;
                requests[i].active = false;

                cout << "Booking cancelled successfully.\n";
                return;
            }
        }

        cout << "Booking not found.\n";
    }

    void machineStatus()
    {
        cout << "\n===== MACHINE STATUS =====\n";

        for(int i = 0; i < 2; i++)
        {
            bool busy = false;

            for(int j = 0; j < 10; j++)
            {
                if(machines[j][i])
                    busy = true;
            }

            cout << "Machine " << i + 1 << ": ";

            if(busy)
                cout << "Occupied\n";
            else
                cout << "Available\n";
        }
    }
};

int main()
{
    LaundryManager laundry;
    int choice;

    do
    {
        cout << "\n===== HOSTEL LAUNDRY SLOT OPTIMIZER =====\n";
        cout << "1. Book Laundry Slot\n";
        cout << "2. View Bookings\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Check Machine Status\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                laundry.bookSlot();
                break;

            case 2:
                laundry.viewBookings();
                break;

            case 3:
                laundry.cancelBooking();
                break;

            case 4:
                laundry.machineStatus();
                break;

            case 5:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } 
    while(choice != 5);
    return 0;
}
