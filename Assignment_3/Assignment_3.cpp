#include <iostream>
#include <vector>
#include <algorithm>//sort

using namespace std;


enum Inventory_SortStandard // for inventory
{
    price, volume, name
};


// for now, 3 classes with same data members and member fucntions,  these will be handled by inventory class
class Potion
{
public:
    Potion(string name, int price, float volume)
    {
        this->name = name;
        this->price = price;
        this->volume = volume;
    }


private:
    string name;
    int price;
    float volume;//space that item requires.

public:
    string get_Name()
    {
        return this->name;
    }
    int get_Price()
    {
        return this->price;
    }
    float get_Volume()
    {
        return this->volume;
    }
};

class Weapon
{
public:
    Weapon(string name, int price, float volume, int level)
    {
        this->name = name;
        this->price = price;
        this->volume = volume;
        this->level = level;
    }


private:
    string name;
    int price;
    float volume;//space that item requires.
    int level;// only for weapon

public:
    string get_Name()
    {
        return this->name;
    }
    int get_Price()
    {
        return this->price;
    }
    float get_Volume()
    {
        return this->volume;
    }
    int get_Level()
    {
        return this->level;
    }
};

class Resource
{
public:
    Resource(string name, int price, float volume, string info)
    {
        this->name = name;
        this->price = price;
        this->volume = volume;
        this->info = info;
    }


private:
    string name;
    int price;
    float volume;//space that item requires.
    string info;// the information of the resource, only for this class

public:
    string get_Name()
    {
        return this->name;
    }
    int get_Price()
    {
        return this->price;
    }
    float get_Volume()
    {
        return this->volume;
    }
    string get_Info()
    {
        return this->info;
    }
};

/*
void PrintResult(vector<ItemSlot> Inventory)
{
    for (int i = 0; i < Inventory.size(); i++)
    {
        cout << "Name: " << Inventory[i].getName() << ", Price: " << Inventory[i].getPrice() << ", Count: " << Inventory[i].getCurrentCount() << endl;
    };
}
*/

/*(
template<typename Count>
Count template_function(Count c, string* name)
{
    Count A = c;
    *name = "askdasd";
    return A*A
}
*/


template<typename T>
class Inventory //------------------------------------** Inventory **
{
    //=== data members =====//
private:
    vector<T*> T_itemsPtr;
    int max_capacity;// max item limit
    float current_capacity;// current item space // itme volume is float, so, it is float now.
    string inventory_name;
  
    /*
    // miestake here.
    this data members are designed for classes with structures of item
    but if they does not have data members that shares same attributes, it will fail
    fuck
    */

    int item_count;//number of items in inventory // increment when item is added and decrement when it is removed 
    // ----> also used for item index( item index== item_count-1)

public:
    Inventory(int max_capacity, string inventory_name)
    {
        if (max_capacity <= 0)//minimum of 1
        {
            this->max_capacity = 1;
        }
        else
        {
            this->max_capacity = max_capacity;
        }
        this->current_capacity = 0;// when the inventory is newly constructed, no items would be in there.// default
        this->item_count = 0;// same here

        //this->T_itemsPtr.resize(max_capacity);//resize to capacity // resize will fill the vector with nullptrs. to only make change on vector length, use reserve;
        this->T_itemsPtr.reserve(max_capacity);

        this->inventory_name = inventory_name;

    }
    ~Inventory()// is this necessary for vector?
    {
        /*// this is vector. this wont work
        delete[] T_itemsPtr;
        T_itemsPtr=nullptr;
        */

        for (T* T_itemPtr : T_itemsPtr)// not so sure what to put where auto is in. fuck
        {
            delete T_itemPtr;// singular!!! not vector
        }// is this necessary?

        T_itemsPtr.clear();

    }
    //===== member functions =====//
public:

    string get_InventoryName()
    {
        return this->inventory_name;
    }



    void AddItem(T* itemPtr)// to do so, T must have volume to be used
    {
        if (current_capacity + itemPtr->get_Volume() < max_capacity)// if the capacity after adding item does not excede the max capacity
        {
            this->T_itemsPtr.push_back(itemPtr);// add item in vector
            //update attributes
            current_capacity += itemPtr->get_Volume();
            item_count += 1;//increment count
        }
        else
        {
            bool isloop = true;
            char input;

            while (isloop == true)// in case of invalid input is detected, so that it can try again
            {
                cout << this->inventory_name <<"의 인벤토리가 꽉 찼습니다. 인벤토리를 확장하시겠습니까? (Y/N): ";
                cin >> input;
                if (input == 'Y' || input == 'y')
                {
                    Resize_Capacity(max_capacity * 2);// double the capacity of inventory

                    // add item in vector
                    T_itemsPtr.push_back(itemPtr);
                    //update attributes
                    current_capacity += itemPtr->get_Volume();
                    item_count += 1;//increment count
                    isloop = false;// leave loop
                }
                else if (input == 'N' || input == 'n')
                {
                    cout << this->inventory_name << "의 인벤토리가 꽉찼습니다. 아이템을 넣을 수 없습니다." << endl;
                    isloop = false;// leave loop
                }
                else
                {
                    cout << "잘못된 입력입니다. 다시 진행해주십쇼." << endl;
                    // isloop = true;// stuck in loop // no need for reasigning value
                }
            }
        }
    }

    void Resize_Capacity(int new_max_capacity)// maybe with conditions?
    {
        if (new_max_capacity > this->max_capacity)// if expending
        {
            this->T_itemsPtr.reserve(new_max_capacity);// resize the inventory first// !!!!!!! this was causing the nullptr problem!!!!! needs to be reserve not resize!!!! it fills new space with nullptr!!!!! FUCK
            this->max_capacity = new_max_capacity;// set new capacity
        }
        else if (new_max_capacity == this->max_capacity)//no change
        {
            cout << this->inventory_name << "의 인벤토리 용량에 변화가 없습니다."; PrintOutStatus();
        }
        else// if new capacity is smaller than the current max capacity
        {
            bool isloop = true;
            char input;

            while (isloop == true)
            {
                cout << this->inventory_name << "의 인벤토리의 용량을 줄이면 아이템이 사라집니다. 진행하시겠습니까? (Y/N): ";
                cin >> input;
                if (input == 'Y' || input == 'y')// reduce max capacity and remove item from inventory till it can be held
                {
                    while (current_capacity <= new_max_capacity)// loop till the new capacity is bigger or equal to the current capacity
                    {
                        RemoveLastItem();
                    }
                    // removing item done

                    cout << this->inventory_name << "의 인벤토리가 줄어들었습니다."; PrintOutStatus();
                    isloop = false;// leave loop
                }
                else if (input == 'N' || input == 'n')
                {
                    cout << this->inventory_name << "의 인벤토리 용량에 변화가 없습니다."; PrintOutStatus();
                    isloop = false;// leave loop
                }
                else
                {
                    cout << "잘못된 입력입니다. 다시 진행해주십쇼." << endl;
                }
            }
        }
    }

    void PrintOutStatus()//현재 용량: print current_capacity/ max_capacity , 아이템 수: item_count
    {
        cout << " 현재 용량 : " << current_capacity << " / " << max_capacity << " 아이템 수 : " << item_count << endl;
    }

    void RemoveLastItem()
    {
        if (item_count > 0)// if there is item to remove
        {
            current_capacity -= T_itemsPtr[item_count - 1]->get_Volume();//update the capacity chagne first
            //remove item and update other changes
            T_itemsPtr.pop_back();//remove the last item
            item_count -= 1;//decrement item count

            cout << this->inventory_name << "의 아이템( " << T_itemsPtr[item_count - 1]->get_Name() << " )이 제거되었습니다." << endl;
        }
        else
        {
            cout << this->inventory_name << "의 인벤토리가 비어있습니다."; PrintOutStatus();
        }
    }


    //======= for sorting =======//

    static bool isBigger(T* A, T* B)
    {
        //  return A.getCurrentCount() > B.getCurrentCount(); //-----------> the sort comparator must be A<B, this order cannot be changed;
        return A->get_Volume() < B->get_Volume();// changed
    }

    static bool isMoreExpensive(T* A, T* B)
    {
        return A->get_Price() < B->get_Price();
    }

    static string Convert_to_Capital(string str)
    {
        string converted = str;

        for (int i = 0; i < converted.length(); i++)//convert alphabet into capital
        {
            if (converted[i] >= 'a' && converted[i] <= 'z')// if char is lower case
            {
                converted[i] = converted[i] + ('A' - 'a');// add the gap between upper case and lower case // -> make lower case upper case char
            }
        }
        return converted;
    }

    static bool isAlphabeticallyHigher(T* A, T* B)//???? not so sure how i can name this so... fuck it
    {
        // check the ascii number and compare, but conver all char into capital and then compare

        string C_str_A = Convert_to_Capital(A->get_Name());
        string C_str_B = Convert_to_Capital(B->get_Name());
        //Converted_string

        bool isA = false;// A<B need to be returned
        int looplength;// use shorter length as loop count

        if (C_str_A.length() >= C_str_B.length())
        {
            looplength = C_str_B.length();
        }
        else
        {
            looplength = C_str_A.length();
        }

        for (int i = 0; i < looplength; i++)
        {
            if (C_str_A[i] != C_str_B[i])
            {
                if (C_str_A[i] > C_str_B[i]) isA = false;
                else isA = true;
                break;
            }
            else// if char is same// compare the original to check upper or lower case(upper>lower)
            {
                if (A->get_Name()[i] != B->get_Name()[i])
                {
                    if (A->get_Name()[i] > B->get_Name()[i]) isA = false;
                    else isA = true;
                }
                break;
            }
        }
        return isA;// return the result
    }

    void SortInventory(bool isAscending, Inventory_SortStandard standard)
    {
        switch (standard)
        {
        case(price)://------------------------------- price
            {
            if (isAscending == true)
            {
                sort(T_itemsPtr.begin(), T_itemsPtr.end(), isMoreExpensive);
            }
            else
            {
                sort(T_itemsPtr.begin(), T_itemsPtr.end(),

                    [](T* a, T* b) {return isMoreExpensive(b, a); });
            }
            break;
        }
              
        case(volume)://------------------------------- volume
        {
            if (isAscending == true)
            {
                sort(T_itemsPtr.begin(), T_itemsPtr.end(), isBigger);
            }
            else
            {
                sort(T_itemsPtr.begin(), T_itemsPtr.end(),

                    [](T* a, T* b) {return isBigger(b, a); });
            }
            break;
        }
        case(name)://---------------------------------- name
            {
            if (isAscending == true)
            {
                sort(T_itemsPtr.begin(), T_itemsPtr.end(), isAlphabeticallyHigher);
            }
            else
            {
                sort(T_itemsPtr.begin(), T_itemsPtr.end(),

                    [](T* a, T* b) {return isAlphabeticallyHigher(b, a); });
            }
            break;
               
            }
        }
    }

    void PrintAll()
    {
        if (item_count <= 0)
        {
            cout << this->inventory_name << "의 인벤토리가 비어 있습니다." << endl;
        }
        else
        {
            cout << "//====== "<< this->inventory_name<<" ======//" << endl;
            for (int i = 0; i < item_count; i++)
            {
                cout << "(" << i + 1 << ") " << "이름: " << this->T_itemsPtr[i]->get_Name() << " / 가격: " << this->T_itemsPtr[i]->get_Price() << " / 부피: " << T_itemsPtr[i]->get_Volume() << endl;
            }
            printf("\n");
            cout << "//--------------------//" << endl;
        }
    }

};


int main()
{
    // Create inventories with different classes
    Inventory<Potion> itemInventory(5,"포션 인벤");
    Inventory<Weapon> weaponInventory(3,"무기 인벤");
    Inventory<Resource> resourceInventory(4,"재료 인벤");

    // Add Items on Item inventory
    itemInventory.AddItem(new Potion("빨강 포션", 50, 1.0f));
    itemInventory.AddItem(new Potion("파랑 포션", 200, 2.0f));
    itemInventory.AddItem(new Potion("노랑 포션", 150, 1.5f));

    // Add Weapons on Weapon intentory
    weaponInventory.AddItem(new Weapon("철검", 500, 5.0f, 5));
    weaponInventory.AddItem(new Weapon("도끼", 400, 6.0f, 2));

    // Add Resources on resource inventory
    resourceInventory.AddItem(new Resource("철", 100, 3, "단단한 철입니다"));
    resourceInventory.AddItem(new Resource("구리", 50, 2, "구리구리한 구리"));

    // Print initial status
    cout << "//----- 인벤 -----//" << endl;
    cout << "포션: "; itemInventory.PrintOutStatus();
    cout << "무기: "; weaponInventory.PrintOutStatus();
    cout << "재료: "; resourceInventory.PrintOutStatus();

    printf("\n\n");

    Inventory_SortStandard howtosort;
    char input;
    bool isAscending;
    bool isrunning = true;

    while (isrunning == true)
    {
        cout << "분류기준을 선택하십쇼 (1) 가격, (2) 부피, (3) 알파벳 순 :";
        cin >> input;
        printf("\n");

        switch (input)
        {
        case('1'):
            howtosort = price;
            isrunning = false;
            break;
        case('2'):
            howtosort = volume;
            isrunning = false;
            break;
        case('3'):
            howtosort = name;
            isrunning = false;
            break;
        default:
            cout << "입력키가 보기에 없습니다. 다시 시도해주십쇼." << endl;
            break;
        }


    }

    isrunning = true;// reset for order typein

    while (isrunning == true)
    {
        cout << "순서를 선택하십쇼.  오름차순(1), 내림차순(2) : ";
        cin >> input;

        if (input == '1')
        {
            isAscending = true;
            isrunning = false;
        }
        else if (input == '2')
        {
            isAscending = false;
            isrunning = false;
        }
        else
        {
            cout << "입력키가 보기에 없습니다. 다시 시도해주십쇼." << endl;
            break;
        }
    }
    // left loop, sorting option chosen

    // sort by chosen standards

    itemInventory.SortInventory(isAscending, howtosort);
    weaponInventory.SortInventory(isAscending, howtosort);
    resourceInventory.SortInventory(isAscending, howtosort);

    //------ sorting done ------//
    
    // printout the result
    cout << "//----- 분류후 인벤 나열 -----//" << endl;

    itemInventory.PrintAll();
    weaponInventory.PrintAll();
    resourceInventory.PrintAll();

    return 0;
}

