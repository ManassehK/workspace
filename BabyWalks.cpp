#include <iostream>
#include <list>
#include <string>

using namespace std;

enum MenuOptions
{
  InsertContactListEntry = 0,
  SortOnName = 1,
  SortOnNumber = 2,
  DisplayEntries = 3,
  EraseEntry = 4,
  QuitContactList =5
};

struct ContactListItem
{
  string strContactsName;
  string strPhoneNumber;

  //constructor and destructor
  ContactListItem (const string& strName, const string& strNumber)
    {
      strContactsName = strName;
      strPhoneNumber = strNumber;
    }

    bool operator == (const ContactListItem& itemToCompare)const
    {
      return (itemToCompare.strContactsName == this->strContactsName);
    }

    bool operator < (const ContactListItem& itemToCompare)const
    {
      return (this->strContactsName < itemToCompare.strContactsName);
    }
};


int ShowMenu();
ContactListItem GetContactInfo();
void DisplayContactList (const list <ContactListItem>& listContacts);
void EraseEntryFromList (list <ContactListItem>& listContacts);
bool Predicate_CheckItemsOnNumber(const ContactListItem& item1, const ContactListItem& item2);

int main()
{
  list <ContactListItem> listContacts;

  int nUserSelection = 0;

  while ((nUserSelection = ShowMenu()) != (int)QuitContactList)
  {
    switch (nUserSelection)
    {
    case InsertContactListEntry:
        listContacts.push_back (GetContactInfo());
        cout << "Contacts list updated!"<<endl<<endl;
      break;

    case SortOnName:
          listContacts.sort();
          DisplayContactList(listContacts);
          break;

    case SortOnNumber:
        listContacts.sort(Predicate_CheckItemsOnNumber);
        DisplayContactList(listContacts);
        break;

    case DisplayEntries:
        DisplayContactList(listContacts);
        break;

    case EraseEntry:
          EraseEntryFromList(listContacts);
          DisplayContactList(listContacts);
          break;

    case QuitContactList:
        cout << "Ending application, bye! "<< endl;
        break;

    default:
    cout << "Invalid input' "<<nUserSelection<<".'";
    cout << "Choose an option between 0 and 4"<<endl<<endl;
      break;
    }
  }
  
  cout <<"Quiting! Bye!"<<endl;
    return 0;
}

int ShowMenu()
{
  cout << "*** What would you like to do next? ***" << endl << endl;
  cout << "Enter 0 to feed a name and phone number "<< endl;
  cout << "Enter 1 to sort the list by name "<< endl;
  cout << "Enter 2 to sort the list by number "<< endl;
  cout << "Enter 3 to display all entries "<< endl;
  cout << "Enter 4 to erase an entry "<< endl;
  cout << "Enter 5 to quite this application "<< endl <<endl;
  cout<< ">";

  int nOptionSelected = 0;

  //Accept user input
  cin >> nOptionSelected;

  cout << endl;
  return nOptionSelected;
}

bool Predicate_CheckItemsOnNumber (const ContactListItem& item1, const ContactListItem& item2)

{
  return (item1.strPhoneNumber < item2.strPhoneNumber);
}

ContactListItem GetContactInfo()
{
  cout << "*** Feed contact information ***" << endl;
  string strName;
  cout << "Please enter the person's name " << endl;
  cout <<">";
  cin >> strName;

  string strPhoneNumber;
  cout << "Please enter "<<strName<<"'s phone number "<<endl;
  cout << ">";
  cin >> strPhoneNumber;

  return ContactListItem (strName, strPhoneNumber);
}

void DisplayContactList(const list<ContactListItem>& listContacts)
{
  cout <<"*** Displaying contact information ***"<< endl;
  cout <<" There are "<<listContacts.size();
  cout <<" entries in the contact-list "<<endl;

  list <ContactListItem>::const_iterator iContact;
  for( iContact = listContacts.begin()
      ;iContact != listContacts.end()
      ;++ iContact)
      {
        cout <<"Name: '" << iContact->strContactsName;
        cout <<"'Number: '" <<iContact->strPhoneNumber <<"'"<<endl;
      }
      cout<<endl;
}

void EraseEntryFromList(list <ContactListItem>& listContacts)
{
  cout << "*** Erase an entry ***"<<endl;
  cout <<" Enter the name of the contact you wish to delete "<<endl;
  cout <<">";
  string strNameToErase;
  cin>>strNameToErase;
  listContacts.remove(ContactListItem(strNameToErase, ""));
}








