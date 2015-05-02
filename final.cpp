
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<bits/stdc++.h>
#include<exception>
using namespace std;
#define ll long long

class PRIME_GEN{
	public:
	PRIME_GEN(){
		srand(time(0));
	}
	ll modulo(ll base, ll exponent, ll mod);
	bool miller(ll prime_no,int iteration);
	ll prime_generator();
	ll random_number();
};


ll PRIME_GEN::modulo(ll base, ll exponent, ll mod){
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

bool PRIME_GEN::miller(ll prime_no,int iteration){
    ll s=0;
    ll d = prime_no - 1;
    while (d % 2 == 0)
    {
    	s++;
        d /= 2;
    }
 
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (prime_no - 3) + 2, temp = d;
        ll x = modulo(a, temp, prime_no);
        if(x!=1&&x!=prime_no-1){
        	   bool cool =true;
        	for(int j=0;j<s-1;j++){
        		x=modulo(x,2,prime_no);
        		if(x==1)
        		return true;
        		if(x==prime_no-1){
        		cool =false;
				j=s;}
			}
			if(cool){
			return true;
			}
		}
    }
    return false;
}

ll PRIME_GEN::random_number(){
	return rand() % 10000 + 10000;
}

ll PRIME_GEN::prime_generator(){
	ll temp=random_number();
	while(miller(temp,3)){
		temp=random_number();
	}
	return temp;
}

class MyException : public exception
{	

	public : 
		void exc()
		{
			cout<<"please enter a proper data  type\n";
		}	
};

class key_gen:public PRIME_GEN{
	ll prime_p,prime_q,private_key;
	public:
		ll n,public_key,phi_n;
	
	ll gcd(ll a,ll b)
	{
    	if(b==0)
        	return a;
    	else
       		gcd(b,a%b);
	}	
	
	ll mul_inv(ll a, ll b)
	{
		ll b0 = b, t, q;
		ll x0 = 0, x1 = 1;
		if (b == 1) return 1;
		while (a > 1) {
			q = a / b;
			t = b, b = a % b, a = t;
			t = x0, x0 = x1 - q * x0, x1 = t;
		}
		if (x1 < 0) x1 += b0;
			return x1;
	}
	
	void set_primes(){
		prime_p = prime_generator();
		prime_q = prime_generator(); 
	}
	
	void set_keys(){
		n=prime_p*prime_q;
		phi_n = (prime_p-1)*(prime_q-1);
		bool condition=true;
		while(condition){
			public_key=random_number()%phi_n+5;
			if(gcd(public_key,phi_n)!=1)
				continue;
			else
				condition = false;	
		}
		private_key=mul_inv(public_key,phi_n);
	}
	ll get_n(){
		return n;
	}
	ll get_publickey(){
		return public_key; }
		
	ll get_privatekey(){
		return private_key;}
		ll addmod( ll x, ll y, ll m )
{
  x %= m;
  y %= m;
  ll sum = x-m+y; // -m <= sum < m-1
  return sum < 0 ? sum + m : sum;
}

	ll timesmod( ll x, ll y, ll m )
{
  x %= m;
  y %= m;
  ll a = x < y ? x : y; // min
  ll b = x < y ? y : x; // max
  ll product = 0;
  for (; a != 0; a >>= 1, b = addmod(b,b,m) )
    if (a&1) product = addmod(product,b,m);
  return product;
}
			
};
class crypto:public key_gen{
	public:
	ll message,decrypted_msg,encrypted_msg;
	public:
	crypto(){
		set_primes();
		set_keys();
	}	
	ll encrypt_msg(ll message,ll publickey,ll ni){
		return modulo(message,publickey,ni) ;
		} 
	
	ll decrypt_msg(ll enmsg,ll privatekey,ll ni){
			return modulo(enmsg,privatekey,ni);
		}
};
class input_output
{
	public:
		virtual void readFile() = 0;
		virtual void writeFile(string name,ll enc_message) = 0;
};
class Cryptography:public input_output
{
	public:
	//	string fileName = "Database";
		void readFile();
		void readFile(string name);
		void writeFile(string name,ll enc_message);
		void register_user(string name);
		void show_messages(string name);
		void send_message();
};
void Cryptography::readFile()
{
	  string line;
	  ifstream myfile ("Database.txt");
	  if (myfile.is_open())
	  {
	  	long long int counter = 1;
	    while ( getline (myfile,line) )
	    {
	      cout <<counter<<") "<< line << '\n';
	      counter++;
	    }
	    myfile.close();
	  }
	
	  else cout << "Unable to open file"; 

}
void Cryptography::readFile(string name)
{
	  string line;
	  string file = name+".txt";
	  fstream myfile ("");
	  myfile.open(file.c_str());
	  if (myfile.is_open())
	  {
	  	ll private_key,n;
	  	cout<<"Enter your private key : ";
	  	cin>>private_key;
	  	cout<<"Enter value of n : ";
	  	cin>>n;
	  	long long int counter = 1;
	    while ( getline (myfile,line) )
	    {
	      // Decryption
	      ll k = atoll(line.c_str());
	      crypto * temp= new crypto();
	      cout<<counter<<") "<<temp->decrypt_msg(k,private_key,n)<<"\n";
	      counter++;
	    }
	    myfile.close();
	  }
	
	  else cout << "Unable to open file\n"; 

}
void Cryptography::writeFile(string name,ll enc_message)
{
	string file = name+".txt";
	ofstream myfile("");
	myfile.open(file.c_str(),std::ios_base::app);
	if(myfile.is_open())
	{
		myfile<<enc_message<<"\n";
		myfile.close();
	}
	else cout<<"Unable to open file\n";
}
void Cryptography::register_user(string name)
{
	string filename = name+".txt";
	ofstream create("");
	create.open(filename.c_str());
	if(create.is_open())
	{
		create.close();
	}
	else cout<<"Could not create file\n\n";
	//generate keys
	
	crypto * temp = new crypto();
	
	ll public_key = temp->get_publickey();
	ll private_key = temp->get_privatekey();
	ll n = temp->get_n();
	
	ofstream myfile("");
	myfile.open("Database.txt",std::ios_base::app);
	if(myfile.is_open())
	{
		myfile<<name<<"\t"<<public_key<<"\t"<<n<<"\n";
		cout<<"Your private key is : "<<private_key<<"\n";
		myfile.close();
	}
	else cout<<"Unable to open file\n";
}
void Cryptography::show_messages(string name)
{
	readFile(name);
}
void Cryptography::send_message()
{
	MyException myex;
	readFile();
	string name;
	ll public_key,n,msg;
	cout<<"Enter name of recepient : ";
	cin>>name;
	cout<<"Enter public key : ";
	cin>>public_key;
	cout<<"Enter n : ";
	cin>>n;
	cout<<"Enter message : ";
	try{
	
		cin>>msg;
		if(cin.fail())
		{
			throw myex;
			
		}
	
	}
	catch (MyException& e){
		e.exc();
		
	}
	//encrypt message
	
	crypto * test = new crypto();
	ll enc_message=test->encrypt_msg(msg,public_key,n);
	
	writeFile(name,enc_message);
}

class UI:public Cryptography 
{
	private:
		int choice;
	public:
		void displayChoices();
		void takeAction();
};
void UI::displayChoices()
{
	cout<<"Hello User ;-)!!!\n\n";
	cout<<"\t1) Register as a User\n";
	cout<<"\t2) Read your messages\n";
	cout<<"\t3) Send a message\n\n";
	cout<<"Enter 1, 2 or 3 :-*\n\n";
	cin>>choice;
}
void UI::takeAction()
{
	if(choice==1)
	{
		string name;
		cout<<"Enter your name\n\n";
		cin>>name;
		Cryptography x;
		x.register_user(name);
	}
	else if(choice==2)
	{
		string name;
		cout<<"Enter your name\n";
		cin>>name;
		Cryptography x;
		x.show_messages(name);
	}
	else if(choice==3)
	{
		Cryptography x;
		x.send_message();
	}
	else cout<<"\nPlease enter a valid choice whenever u visit again\n";
}

int main()
{
	bool exit = false;
	while(!exit)
	{
		UI object;
		object.displayChoices();
		object.takeAction();
		int x;
		cout<<"Enter 0 to exit, 1 to continue operation.\n";
		cin>>x;
		if(x==0) exit = true;
	}
	
}

