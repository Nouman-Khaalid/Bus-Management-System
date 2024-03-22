#include<iostream>
#include <limits.h>
#include <string>
using namespace std;

#define INF 99999
#define V 7

int index = 0;
int path[V];
int main();
  
string city[V] = {"Islamabad", "Multan", "Faislabad", "Lahore", "Sadiq Abad", "Quetta", "Karachi"};

// Passenger record
struct record{
	string name;
	string phone_no;
	string cnic;
	string source;
	string destination;
	int seat_no;
	int charges;
	record* next = NULL;
};

void Deletion(string cnic);

void insert(string name, string phone_no, string cnic, 
string destination, string source, int seat_no, int charges, string bus_serial_number);

void display();


struct pri {
    string complain;
    pri* next;
};

void enter_Complain(string complain);

void delete_Complain();
void display_complains();




struct bus_tree{
	int serial_no;
	string bus_number;
	string driver_name;
	string cnic;
	string phone_no;
	int bus_fair;
	int height;
	
	bus_tree* left = NULL;
	bus_tree* right = NULL;
	bool seats[30];
	string names[30];
	
	record *record_start = NULL;
	record *record_end = NULL;
	
		pri *complains_front = NULL;
	pri *complains_rear = NULL;
};


bus_tree* root = NULL;


int getbf(bus_tree* p);
int gethight(bus_tree* p);
bus_tree* leftR(bus_tree* p);
bus_tree* rightR(bus_tree* p);
bus_tree* insert(bus_tree* r, string ser_no, string bus_no, string name, string cnic, string phone_no ,int fair);

bus_tree* creat(int key);

void pre_order(bus_tree* p);

void deletion(int x);

class Graph {
private:
    int G[V][V];  
    string city[V] = {"Islamabad", "Multan", "Faislabad", "Lahore", "Sadiq Abad", "Quetta", "Karachi"};


    int minDistance(int dist[], bool sptSet[]) {
        int min = INF, min_index;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

public:
    Graph() {
        // Initialize the graph matrix with the provided values
        int matrix[V][V] = {
            {0, 9, 0, 0, 2, 0, 1},
            {9, 0, 5, 1, 2, 4, 6},
            {7, 5, 0, 1, 2, 5, 0},
            {0, 1, 1, 0, 1, 3, 0},
            {2, 0, 2, 5, 0, 3, 6},
            {0, 4, 5, 3, 3, 0, 0},
            {1, 6, 0, 0, 6, 0, 0}
        };

        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                G[i][j] = matrix[i][j];
    }

    void displayGraph() {
        cout << "City Graph:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << city[i] << " - " << city[j] << " : ";
                if (G[i][j] != INF) {
                    cout << G[i][j] << " km";
                } else {
                    cout << "Not Connected";
                }
                cout << endl;
            }
        }
    }

    int findMaxDistance() {
        int maxDistance = INT_MIN;

        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (G[i][j] != INF)
                    maxDistance = max(maxDistance, G[i][j]);

        return maxDistance;
    }

    int findMinDistance() {
        int minDistance = INF;

        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (G[i][j] != INF)
                    minDistance = min(minDistance, G[i][j]);

        return minDistance;
    }
};

class BST{
	public:
	
		// Insertion

		
		bus_tree* insert(bus_tree* r, int ser_no, string bus_no, string name, string cnic, string phone_no ,int fair){
			//pre_order(r);
		
			if( r == NULL){
				return creat(ser_no, bus_no, name, cnic, phone_no, fair);
			}
			else if(ser_no < r->serial_no){
				r->left = insert(r->left, ser_no, bus_no, name, cnic, phone_no, fair);
			}
			else if(ser_no > r->serial_no){
				r->right = insert(r->right, ser_no, bus_no, name, cnic, phone_no, fair);
			}
			
			r->height = 1 + max(getheight(r->left), getheight(r->right));
			int bf = getbf(r);
			
			if(bf > 1 && ser_no < r->left->serial_no){
				return rightR(r);
			}
		
			if(bf < -1 && ser_no > r->right->serial_no){
				return leftR(r);         
			}
		
			if(bf > 1 && ser_no > r->left->serial_no){
				r->left = leftR(r->left);
				return rightR(r);
			}
		
			if(bf < -1 && ser_no < r->right->serial_no){
				r->right = rightR(r->right);
				return leftR(r);
			}
		
			return r;
		}
		
		
		//Traversal
		void pre_order(bus_tree* p){
		    if(p!=NULL){
		        cout<<"  Serial No:  "<<p->serial_no<< endl;
				cout<<"  Bus Number:  "<<p->bus_number<< endl;
			    cout<<"  Driver Name:  "<<p->driver_name<< endl;
			    cout<<"  CNIC:  "<<p->cnic<< endl;
		        cout<<"  Phone No:  "<<p->phone_no<< endl;
				cout<<"  Bus Fair:  "<<p->bus_fair << endl << endl;
		        pre_order(p->left);
		        pre_order(p->right);
		    }
		}
		
		void in_order(bus_tree* p){
		    if(p!=NULL){
		    	in_order(p->left);
		        cout<<p->serial_no<<"   ";
		        in_order(p->right);
		    }
		}
		
		
		int getheight(bus_tree* p){
		   int h = 0;
		   if (p != NULL) {
		      int l_height = getheight(p->left);
		      int r_height = getheight(p->right);
		      int max_height = max(l_height, r_height);
		      h = max_height + 1;
		   }
		   return h;
		}
		
		int getbf(bus_tree* p){
		   int l_height = getheight(p->left);
		   int r_height = getheight(p->right);
		   int b_factor = l_height - r_height;
		   return b_factor;
		}
		
		
		
		bus_tree* rightR(bus_tree* p){
			bus_tree* x = p->left;
			bus_tree* k = x->right;
			
			x->right = p;
			p->left = k;
			
			
			p->height = 1 + max(getheight(p->left), getheight(p->right));
			x->height = 1 + max(getheight(p->left), getheight(p->right));
			//pre_order(x);
			return x;
		}
		
		
		
		bus_tree* leftR(bus_tree* p){
			bus_tree* x = p->right;
			bus_tree* k = x->left;
			
			x->left = p;
			p->right = k;
			
			
			p->height = 1 + max(getheight(p->left), getheight(p->right));
			x->height = 1 + max(getheight(p->left), getheight(p->right));
			
			return x;
			
		}
		
		bus_tree* creat(int ser_no, string bus_no, string name, string cnic, string phone_no ,int fair){
			bus_tree* ptr = new bus_tree();
			ptr->serial_no = ser_no;
			ptr->bus_fair = fair;
			ptr->bus_number = bus_no;
			ptr->driver_name = name;
			ptr->phone_no = phone_no;
			ptr->cnic = cnic;
		
			
			ptr->left = NULL;
			ptr->right = NULL;
			ptr->height = 1;
			
			return ptr;
		}
		
//		Deletion
		void deletion(int x) {
		    bus_tree *p = root;
		    bus_tree *k;
		    while (p != NULL && p->serial_no != x) {
		        k = p;
		        if (x > p->serial_no) {
		            p = p->right;
		        } else p = p->left;
		    }
		    // Leaf Node
		    if (p->left == NULL && p->right == NULL) {
		        if (p == k->right) {
		            k->right = NULL;
		        } else k->left = NULL;
		        delete p;
		    } else if (p->right == NULL || p->left == NULL) { //Single Branches
		        if (p->right == NULL) {
		            if (p == k->left) {
		                k->left = p->left;
		            }else{  
		                k->right=p->left;
		            }delete p;
		        }
		        else
		        {
		            if(p==k->right){
		                k->right=p->right;
		            }else{
		                k->left=p->right;
		            }
		            delete p;
		        }
		    }
			else{
		    	 bus_tree* p2 = p->right;
		    	 bus_tree* p3 = p2;
				 while(p2->left != NULL){
				 	p3 = p2;
				 	p2 = p2->left;
				 }
				 if(p2->left == NULL && p2->right == NULL){
				 	
				 	p->serial_no = p2->serial_no;
				 	p->bus_number = p2->bus_number;
				 	p->driver_name = p2->driver_name;
				 	p->cnic = p2->cnic;
				 	p->phone_no = p2->phone_no;
				 	p->bus_fair = p2->bus_fair;
				 	
				 	if(p3 == p2)
				 		p->right = NULL;
				 	else p3->left = NULL;
				 }
				 else{
				 	p->serial_no = p2->serial_no;
				 	if(p2->right != NULL)
					 	p3->left = p2->right;                     
					 else
					 	p3->left = NULL;
				 }   
		    }
		    cout << "Record deleted" << endl;
		}
		
		bus_tree* search(int bus_serial_number){
			bus_tree *p = root;
		
			while (p->serial_no != bus_serial_number && p!=NULL){
				if (bus_serial_number > p->serial_no){
					p = p->right;
				}
				else{
					p = p->left;
				}
			}
			
			return p;
		}
				
		void bookseats(int seat, int bus_serial_number){
			try{
			
			
			bus_tree *bus = search(bus_serial_number);
		
			if(bus == NULL){
				cout<<"Bus with above mentioned serial number is not regestered"<<endl;
				return;
			}
			else{
				
				if(bus->seats[seat-1]){
					cout<<"  Invalid Seat booked"<<endl;
				}
				
				else if(seat<30){
					string name,source, destination;
					cout<<"Enter your name"<<endl;
					cin>>name;
					bus->seats[seat-1] = true;
					bus->names[seat-1] = name;
					
					for(int i = 0; i<V; i++){
						cout<<i+1<<"  "<<city[i]<<endl;
					}
					cout<<"From where you have started your journey??"<<endl;
					cin>>source;
					cout<<"Where you want to go??"<<endl;
					for(int i = 0; i<V; i++){
						cout<<i+1<<"  "<<city[i]<<endl;
					}
					cin>>destination;
			
				}
				
				else{
					cout<<"Seat not available"<<endl;
				}
			}
		}catch (const exception& e) {
        cerr << "Exception in bookseats function: " << e.what() << endl;
    	}
		}
		
		
		void cancel_booking(int seat, int bus_serial_number){
			try{
			bus_tree *bus = search(bus_serial_number);
			if(bus == NULL){
				cout<<"Bus with above mentioned serial number is not registered"<<endl;
			}
			else{
				cout<<"Enter your name"<<endl;
				string name;
				cin>>name;
				if(seat<30 && bus->seats[seat-1] == true && bus->names[seat-1]==name){
					bus->seats[seat-1] = false;
					bus->names[seat-1] = "";
				}
			
				if(bus->names[seat-1]!=name){
					cout<<"Seat is not booked on the entered name"<<endl;
				}
				if(seat>30){
					cout<<"Seat not available"<<endl;
				}
				if(!bus->seats[seat-1]){
					cout<<"Seat is not booked"<<endl;

	
				}
			}
			}catch (const exception& e) {
        	cerr << "Exception in cancel_booking function: " << e.what() << endl;
    		}
			
		}

	
		void show_booking(string password, int bus_serial_number){
			try{
			
			if(password == "1234"){
				bus_tree *bus = search(bus_serial_number);
				
				if(bus == NULL){
					cout<<"No bus of above mentioned serial number is registered"<<endl;
				}
				
				else{
					for(int i =0; i<30; i++){
						if(bus->seats[i]){
							cout<<"Seat no: "<<i+1<<"\nName: "<<bus->names[i]<<endl<<endl;
						}
					}                             
				}
				
			}
			else{
				cout << "Invalid password" << endl;
			}
		}catch (const exception& e) {
        cerr << "Exception in show_booking function: " << e.what() << endl;
    	}
			
		}
		
		
};


class Pri {
public:
    Pri() {
    }
    BST t;

    void enter_Complain(int bus_serial_number) {
        bus_tree* bus = t.search(bus_serial_number);
        if (bus == NULL) {
            cout << "Bus not registered" << endl;
        } else {
            string complain;
            cout << "Enter complain: ";
            getline(cin >> ws, complain); 

            pri* newComplain = new pri;
            newComplain->complain = complain;
            newComplain->next = NULL;

            if (bus->complains_front == NULL) {
                bus->complains_front = bus->complains_rear = newComplain;
            } else {
                
                pri* node = bus->complains_front;
                pri* prev = NULL;

                while (node != NULL) {
                    prev = node;
                    node = node->next;
                }

                if (prev == NULL) {
                    
                    newComplain->next = bus->complains_front;
                    bus->complains_front = newComplain;
                } else {
                    
                    prev->next = newComplain;
                    bus->complains_rear = newComplain;
                }
            }
        }

        cout << "Complaint Submitted" << endl;
    }

    void delete_Complain(int bus_serial_number) {
        bus_tree* bus = t.search(bus_serial_number);
        if (bus == NULL) {
            cout << "Bus not registered" << endl;
        } else {
            pri* p = bus->complains_front;

            if (p == NULL) {
                cout << "No complaints registered" << endl;
            } else {
                bus->complains_front = bus->complains_front->next;
                cout << "Complaint: " << p->complain << endl;
                delete p;
            }
        }
    }

    void display_complains(int bus_serial_number) {
        bus_tree* bus = t.search(bus_serial_number);

        if (bus == NULL) {
            cout << "Bus not registered" << endl;
        } else {
            cout << "Complaints for Bus Serial Number " << bus_serial_number << ":" << endl;
            pri* p = bus->complains_front;

            if (p == NULL) {
                cout << "No complaints registered" << endl;
            } else {
                while (p != NULL) {
                    cout << "Complaint: " << p->complain << endl;
                    p = p->next;
                }
            }
        }
    }
};

class Record{
	
	public:
		BST t;
		void insert(string name, string phone_no, string cnic, string destination, string source, int seat_no, int charges, int bus_serial_number){
			try{
			
			bus_tree *bus = t.search(bus_serial_number);
			
			if (bus == NULL){
				cout<<"Bus not registered"<<endl;
			}
			
			else{
				record* p = new record();
				p->name = name;
				p->phone_no = phone_no;
				p->cnic = cnic;
				p->destination = destination;
				p->source = source;
				p->seat_no = seat_no;
				p->charges = charges;
			
				if(bus->record_start == NULL){
					bus->record_start = bus->record_end = p;
				}
				else{
					bus->record_end->next = p;
					bus->record_end = p;
				}
			}
			
			cout << "Record added" << endl;
		}catch (const exception& e) {
        cerr << "Exception in insert function: " << e.what() << endl;
    	}
		}
		
		
		void deletion(int bus_serial_number){
			bus_tree *bus = t.search(bus_serial_number);
			
			if(bus == NULL){
				cout<<"Bus not regestered"<<endl;
			}
			
			else{
				string cnic;
				cout<<"Enter your cnic"<<endl;
				cin>>cnic;
				record* p = bus->record_start;
				record* k;
			
				while(p != NULL && p->cnic != cnic){
					k = p;
					p = p->next;
				}
			
				if(p == NULL){
					cout << "Record not found" << endl;
				}
				else{
					if(p == bus->record_start){
						bus->record_start = bus->record_start->next;
					}
					else if(p == bus->record_end){
						bus->record_end = k;
					}
					else{
						k->next = p->next;
					}
				}
			}
			
			cout << "Record deleted" << endl;
		}
		
		
		void display(int bus_serial_number){
			bus_tree *bus = t.search(bus_serial_number);
			
			if(bus == NULL){
				cout<<"Bus not regestered"<<endl;
			}
			else{
				record* p = bus->record_start;
			
				while(p != NULL){
					cout << " Name: "<< p->name<< endl;
					cout << " Phone No: "<< p->phone_no<< endl;
					cout << " CNIC: "<< p->cnic<< endl;
					cout << " Source: "<< p->source<< endl;
					cout << " Destination: "<< p->destination<< endl;
					cout << " Seat No: "<< p->seat_no<< endl;
					cout << " Charges: " << p->charges<< endl<< endl;
				
					cout << endl;
				
					p = p->next;
					}
				}
			}
			
};



int main(){
	try{
	
	system("COLOR B");
	Pri p;
	BST t;
	Record r;
	int choice, choice1;
	
	while(choice != 0){
		cout<<"\t\t\t ....................   BUS RESERVATION SYSTEM   .................... \t\t\t"<<endl;
		cout<<"\nEnter 1 for bus reservation \nEnter 2 booking seat  \nEnter 3 for passenger record  \nEnter 4 for complains \nEnter 5 for distance \nEnter 0 to exit"<<endl;
		cin>> choice;
		
		switch(choice){
			case 1:
				cout<<"..........................\nEnter 1 for bus reservation \nEnter 2 to delete the record of reserved bus \nEnter 3 to search bus \nEnter 4 to display records of all buses"<<endl;
				cin>>choice1;
				
				if (choice1 == 1){
						int s_no, fair;
						string bus_no, name, cnic, phone_no;
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
						cout<<"Enter fair of the bus "<<endl;
						cin>>fair;
						cout<<"Enter bus number "<<endl;
						cin>>bus_no;
						cout<<"Enter driver name "<<endl;
						cin>>name;
						cout<<"Enter driver cnic "<<endl;
						cin>>cnic;
						cout<<"Enter drivers phone number"<<endl;
						cin>>phone_no;
						root = t.insert(root, s_no,bus_no,name,cnic,phone_no,fair);
				}
				
				else if (choice1 == 2){
						if (root == NULL){
							cout<<"No bus regesterd yet"<<endl;
						}else{
							int num;
							cout<<"..........................BUS SERIAL NUMBERS...................." << endl;
							t.in_order(root);
							cout << "Enter Serial number you want to delete" << endl;
							cin >> num;
							t.deletion(num);
						}
						
				}
				else if(choice1 == 3){
						
						if (root == NULL){
							cout<<"No bus regestered yet"<<endl;
						}else{
							int serial_number;
							cout<<"..........................BUS SERIAL NUMBERS...................." << endl;
							t.in_order(root);
							cout << "Enter serial number of the bus" << endl;
							cin >> serial_number;
							bus_tree* result = t.search(serial_number);
							if(result == NULL){
							cout << "Element not found" << endl;
							}
							else{
							cout << "Element found - Bus Number: " << result->bus_number << endl;
							}	
						}	                     
				}
				
				else if(choice1 == 4){
					if (root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						cout<<"...............     Records of all buses     ..............."<<endl;
						t.pre_order(root);
						cout << endl;
					}
				}
				
				else{
					cout<<"INVALID INPUT"<<endl;
				}
				break;
				
			case 2:
				cout<<"..........................\nEnter 1 to book seat \nEnter 2 to cancel booking \nEnter 3 to display all bookings"<<endl;
				cin>>choice1;
				
				if(choice1 == 1){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						int s_no, seat;
						cout<<"..........................BUS SERIAL NUMBERS...................." << endl;
						t.in_order(root);
						cout << endl;
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
						cout<<"Enter seat number"<<endl;
						cin>>seat;
						t.bookseats(seat, s_no);
					}
				}
				
				else if(choice1 == 2){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						int s_no, seat;
						cout<<"..........................BUS SERIAL NUMBERS...................."<<endl;
						t.in_order(root);
						cout << endl;
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
						cout<<"Enter seat number"<<endl;
						cin>>seat;
						t.cancel_booking(seat,s_no);
					}
				}
				
				else if(choice1 == 3){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						int s_no;
						string password;
						cout<<"..........................BUS SERIAL NUMBERS...................."<<endl;
						t.in_order(root);
						cout << endl;
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
						cout<<"Enter password"<<endl;
						cin>>password;
						t.show_booking(password, s_no);
					}
				}
				else{
					cout<<"INVALID INPUT"<<endl;
				}
				break;		
			
			
			
			case 3:
				cout<<"..........................\nEnter 1 to insert passenger information  \nEnter 2 to delete the record of a passenger \nEnter 3 to view all records of a passenger"<<endl;
				cin>>choice1;
				
				if(choice1 == 1){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						string name, phone_no, source, destination, cnic;
						int seat_no, charges, s_no;
						cout<<"Enter your name"<<endl;
						cin>>name;
						cout<<"Enter your cnic"<<endl;
						cin>>cnic;
						cout<<"Enter phone number"<<endl;
						cin>>phone_no;
						cout<<"Enter source"<<endl;
						cin>>source;
						cout<<"Enter destination"<<endl;
						cin>>destination;
						cout<<"Enter your seat number"<<endl;
						cin>>seat_no;
						cout<<"Enter charges"<<endl;
						cin>>charges;
						cout<<"..........................BUS SERIAL NUMBERS...................."<<endl;
						t.in_order(root);
						cout<<"Enter bus serial number"<<endl;
						cin>>s_no; 
						r.insert(name,phone_no,cnic,destination,source,seat_no,charges,s_no);
					}
				}
				else if(choice1 == 2){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						int s_no;
						cout<<"..........................BUS SERIAL NUMBERS...................."<<endl;
						t.in_order(root);
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
						r.deletion(s_no);
					}
				}
				
				else if(choice1 == 3){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						int s_no;
						cout<<"..........................BUS SERIAL NUMBERS...................."<<endl;
						t.in_order(root);
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
						r.display(s_no);
					}
				}
				
				else{
					cout<<"INVALID INPUT"<<endl;
				}
				break;
				
							
			case 4:
				cout<<"..........................\nEnter 1 to regester complain \nEnter 2 to delete 1st complain \nEnter 3 to view all regestered complains "<<endl;
				cin>>choice1;
				
				if(choice1 == 1){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						int s_no, age; 
						cout<<"..........................BUS SERIAL NUMBERS...................."<<endl;
						t.in_order(root);
						cout << endl;
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
//						cout<<"Enter your age"<<endl;
//						cin>>age;
						p.enter_Complain(s_no);
					}
				}
				
				else if(choice1 == 2){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						int s_no;
						cout<<"..........................BUS SERIAL NUMBERS...................." << endl;
						t.in_order(root);
						cout << endl;
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
						cout<<"COMPLAIN:\n..................."<<endl;
						p.delete_Complain(s_no);
					}
				}
				
				else if(choice1 == 3){
					if(root == NULL){
						cout<<"No bus regestered yet"<<endl;
					}else{
						int s_no;
						cout<<"..........................BUS SERIAL NUMBERS...................."<<endl;
						t.in_order(root);
						cout << endl;
						cout<<"Enter serial number of the bus"<<endl;
						cin>>s_no;
						cout<<"COMPLAINS\n..................."<<endl;
						p.display_complains(s_no);
					}
				}
				
				else{
					cout<<"INVALID INPUT"<<endl;
				}
				
				break;
				case 5:
				{
					cout<<"..........................\nEnter 1 to display all distances \nEnter 2 to display max distance \nEnter 3 to display min distance "<<endl;
					cin>>choice1;
   				    Graph graph;
					
					if(choice1==1){
					
				    
				    graph.displayGraph();
					}	
					else if(choice1==2){
					
				    
				    int maxDistance = graph.findMaxDistance();
				    cout << "Maximum Distance in the Graph: " << maxDistance << " km" << endl;
					}	
					
					else if(choice1==3){
					
				    
				    int minDistance = graph.findMinDistance();
				    cout << "Minimum Distance in the Graph: " << minDistance << " km" << endl;
					}
					else{
					cout<<"INVALID INPUT"<<endl;
					}
				}
				break;
				
			default:
				break;	
		}
	}
	}catch (const exception& e) {
        cerr << "Exception in main function: " << e.what() << endl;
    }
	return 0;
}
