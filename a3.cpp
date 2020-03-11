// a3.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Chirag Gupta
// St.# : 301391394
// Email: cga57@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// I used the cppreference online for syntax help and finding library functions 
//
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#include "cmpt_error.h"    // These are the only permitted includes!
#include "Chatbot.h"       //
#include <iostream>        // Don't include anything else.
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <cassert>

using namespace std;


// our helper function (Given in criteria)
// NOTE: HELPER FUNCTION NOT USED FOR TESTING
// INSTEAD THOROUGH TESTING OF EACH CHATBOT DONE
// THROUGH OTHER MEANS SUCH AS USING ASSERT
// AND OUTPUTTING TO SCREEN 
void converse(Chatbot* a, Chatbot* b, int max_turns = 50) {
  for(int turn = 1; turn <= max_turns; turn++) {
    string a_msg = a->get_reply();
    cout << "(" << turn << ") " << a->name() << ": " << a_msg << "\n";

    turn++;
    if (turn > max_turns) return;

    b->tell(a_msg);
    string b_msg = b->get_reply();

    cout << "(" << turn << ") " << b->name() << ": " << b_msg << "\n";
    a->tell(b_msg);
  } // for
}
// bot to copy users response
class Mirror_bot : public Chatbot {
private:
	string nm;
	string reply;
public:
	Mirror_bot(const string &name, const string &default1)
		: nm(name), reply(default1)
	{}
	string name() const {
		return nm;
	}

	void tell(const string& s){
		// sets private var reply to what it was told
		reply = s; 
	}
	string get_reply(){
		return reply;
	}
	~Mirror_bot(){}

}; // semicolon after classes

/// bot to give random replies
class Random_bot : public Chatbot {
private:
	string nm;
	string reply;
	vector<string> replies;
	// helper function to assist in randomizing reply
	// private since it not meant for to be used outside
	// of class
	void randomize_reply () {
		int size = replies.size();
		int random = -1;
		// Note: This is how rand function works below:
		// rand() % (max_number + 1 - minimum_number) + minimum_number

		// Max_number + 1 = size of vector
		// Min number = 0
		random = rand() % (size - 0) + 0;
		reply = replies[random];

	}
public:
	// constructor with string vector
	Random_bot(const string &name, const vector<string> &vector_replies1)
		: nm(name),reply("")
	{
		if(vector_replies1.size() == 0) {
			cmpt::error("Vector of replies is empty");
		}
		replies = vector_replies1;

	}
	Random_bot(const string &name, const string& file_name)
		: nm(name), reply("") // Sets reply empty for now
							  // will be randomized
							  // in the randomize_reply 
							  // helper function
	{
		// infile.open(); - NOT NEEDED
		ifstream infile;
		infile.open(file_name);

		// test to see if file can open
		if(infile.is_open() == false) {
			cmpt::error("File can't open");
		}

		// check to see if file is empty or not
		bool is_empty = true;
		string str;
		while(infile >> str){
			is_empty = false;
			break;
		}
		if(is_empty){
			cmpt::error("File can't be empty");
		}

		string line;
		while(getline(infile,line)){
			replies.push_back(line);
		}
		infile.close(); // closes file


	}
	string name() const {
		return nm;
	}
	// function doesent do anything, only exists to override
	// pure virual function in the chatbot superclass
	void tell(const string& s){
		// NOTE: This code DOES NOTHING
		// ONLY EXISTS to pass through make Compiler flag
		// Which does not allow unused function parameter
		string str = s; 
	}

	string get_reply(){
		randomize_reply();
		return reply;

	}
	~Random_bot(){
		
	}

};

class User_bot : public Chatbot {
private:
	string nm;
	string reply;

public:

  User_bot(const string &name)
  	: nm(name)
  {

  }
  string name() const {return nm;}

  // Give a string to this chatbot.
  void tell(const string& s){

  	// NOTE: This code DOES NOTHING
	// ONLY EXISTS to pass through make Compiler flag
	// Which does not allow unused function parameter
	string str = s; 

	// Actual code
  	cout << reply << endl; // prints the reply on the screen
  }

  // Get a string from this chatbot.
  string get_reply() { 
  	cout << "Enter a line of text: " << endl;
  	cin >> reply;
  	return reply;

  }
  // AN HELPER FUNCTION DECLARED FOR TESTING PURPOSES
  // Only returns the reply: Does not ask user for line 
  string get_just_reply(){
  	return reply;
  }

  // virtual destructor
  ~User_bot() { }

};

class Datetime_bot : public Chatbot {
private:
	string reply = ""; // member initialization
	string nm;
	vector<string> replies;
	// helper function to assist in randomizing reply
	// private since it not meant for to be used outside
	// of class
	void randomize_reply () {
		int size = replies.size();
		int random = -1;
		// Note: This is how rand function works below:
		// rand() % (max_number + 1 - minimum_number) + minimum_number

		// Max_number + 1 = size of vector
		// Min number = 0
		random = rand() % (size - 0) + 0;
		reply = replies[random];

	}

public:
	Datetime_bot(const string &name, const vector<string> &vector_replies1)
		:nm(name), replies(vector_replies1)
	{
		if(vector_replies1.size() == 0) {
			cmpt::error("Vector of replies is empty");
		}

	}

	string name() const{return nm;}

	// Give a string to this chatbot.
	void tell(const string& s){

		bool date_or_time = false;
			// int pos = -1;
			// pos = s.find("date")
			// int pos2 = -1;
			// pos2 = s.find("time")
		// put everything to lower case for s
		// which must be stored into a new variable
		// since argument must not be altered
		string s2;
		for(char c : s){
			c = tolower(c); // tolower converts every character into lower case
			s2 += c;
		}

		// Note: string::npos is the value that find returns if the substring
		// string is not found
		if (s2.find("date") != string::npos || s2.find("time") != string::npos) {
	    	// found 
	    	date_or_time = true;
	    }
		if(date_or_time){
			time_t now= time(0); // current time as time a time_t object
			reply = ctime(&now); // Converts to string with date+time	
		} else{
			randomize_reply(); // helper function
		}

	}


    // Get a string from this chatbot.
    string get_reply(){return reply;}

    // virtual destructor
    ~Datetime_bot() { }


};
class Personal_siri : public Chatbot {
private:
	string nm;
	string reply;
public:

  Personal_siri(const string&name)
  	: nm(name)
  {

  }
  
  string name() const {return nm;}

  void tell_celebrities(const string& s){
  	string s2;
	for(char c : s){
		c = tolower(c); // tolower converts every character into lower case
			s2 += c;
	}
	// female singers
	if(s2.find("ariana") != string::npos || s2.find("billie") != string::npos || s2.find("cardie") != string::npos || s2.find("beyonce") != string::npos || s2.find("jennifer") != string::npos || s2.find("shakira") != string::npos || s2.find("taylor") != string::npos || s2.find("camilla") != string::npos || s2.find("ellie") != string::npos || s2.find("becky") != string::npos || s2.find("rihanna") != string::npos || s2.find("neha") != string::npos){
		reply = "She is a good singer";
		return;
	}
	// male singers
	if(s2.find("ed sheeran") != string::npos || s2.find("justin") != string::npos || s2.find("drake") != string::npos || s2.find("arjit") != string::npos || s2.find("sonu") != string::npos || s2.find("maroon") != string::npos || s2.find("cent") != string::npos || s2.find("blake") != string::npos || s2.find("shelton") != string::npos || s2.find("jackson") != string::npos || s2.find("elvis") != string::npos || s2.find("bruno") != string::npos){
		reply = "He is a good singer";
		return;
	}
  }

  // politics - mainly american
  void tell_politics(const string& s){
  	string s2;
	for(char c : s){
		c = tolower(c); // tolower converts every character into lower case
			s2 += c;
	}
	if(s2.find("win") != string::npos || s2.find("election") != string::npos || s2.find("2020") != string::npos || s2.find("america") != string::npos || s2.find("trump") != string::npos){
		reply = "Trump has the best chance of winning the 2020 election at about 70%.";
		return;
	}
	if(s2.find("healthcare") != string::npos || s2.find("insurance") != string::npos || s2.find("trudeau") != string::npos || s2.find("canada") != string::npos || s2.find("topics") != string::npos){
		reply = "Canadian healthcare trumps American healthcare by a mile (oops...I mean a kilometre )";
		return;
	}
	if(s2.find("abortion") != string::npos || s2.find("fetus") != string::npos || s2.find("babies") != string::npos || s2.find("pro-life") != string::npos || s2.find("baby") != string::npos){
		reply = "Abortion is an controversial topic. Are u pro-life or pro abortion?";
		return;
	}
	if(s2.find("patriot") != string::npos || s2.find("nation") != string::npos || s2.find("patriotism") != string::npos || s2.find("right") != string::npos || s2.find("christianity") != string::npos || s2.find("values") != string::npos || s2.find("family") != string::npos || s2.find("republican") != string::npos || s2.find("military") != string::npos || s2.find("war") != string::npos){
		reply = "You must be a republican or consevative.";
		return;
	}
	if(s2.find("democrat") != string::npos || s2.find("left") != string::npos || s2.find("ism") != string::npos || s2.find("race") != string::npos || s2.find("african") != string::npos || s2.find("hispanic") != string::npos || s2.find("lationo") != string::npos || s2.find("rights") != string::npos){
		reply = "You must be a democrat or liberal.";
		return;
	}
	if(s2.find("gun") != string::npos || s2.find("ammendment") != string::npos){
		reply = "Stand by the 2nd ammend";
		return;
	}


  }
  // keywords related to coronavirus
  void tell_coronavirus_edition(const string& s){
  	string s2;
	for(char c : s){
		c = tolower(c); // tolower converts every character into lower case
			s2 += c;
	}
	if(s2.find("death") != string::npos){
		reply = "Around 3,500 ppl have died.";
		return;
	}
	if(s2.find("prevention") != string::npos){
		reply = "Wash your hands for 20 seconds, use alcohol based sanitizer";
		return;
	}
	if(s2.find("china") != string::npos){
		reply = "Coronavirus originated in China. Its origins remain unknown";
		return;
	}
	if(s2.find("news") != string::npos || s2.find("news") != string::npos){
		reply = "Coronavirus is all over the news";
		return;
	}
	if(s2.find("economic") != string::npos || s2.find("economy") != string::npos || s2.find("gdp") != string::npos || s2.find("stocks") != string::npos || s2.find("money") != string::npos || s2.find("growth") != string::npos){
		reply = "Coronavirus has destroyed the economy worldwide. ALl countries are affected";
		return;
	}
	if(s2.find("afraid") != string::npos || s2.find("scared") != string::npos || s2.find("panic") != string::npos || s2.find("closure") != string::npos || s2.find("help") != string::npos || s2.find("fear") != string::npos){
		reply = "Coronavirus has caused worldwide panic and fears. Stay calm and prepared.";
		return;
	}
  }

  // french support - CASUAL EDITION ONLY
  void tell_french_edition(const string&s){
  	string s2;
	for(char c : s){
		c = tolower(c); // tolower converts every character into lower case
			s2 += c;
	}

	// Note: string::npos is the value that find returns if the substring
    // string is not found
	if (s2.find("comment") != string::npos && s2.find("sont") != string::npos && s2.find("tu") != string::npos) {
	    // found 
	    reply = "Bien et toi?";
	    return;


    } 
    // works like the date time bot - it returns everything
    if (s2.find("temps") != string::npos || s2.find("date") != string::npos){
    	time_t now= time(0); // current time as time a time_t object
		reply = ctime(&now);
		return;
	} 
	// Generic how statement (NOT INCLUDING HOW ARE YOU)
	if(s2.find("comment") != string::npos){
		reply = "Découvrez comment utiliser Google.";
		return;
	}
	// Generic what statement 
	if(s2.find("quoi") != string::npos){
		reply = "Qu'est ce que je sais.";
		return;
	}
	
	if(s2.find("quand") != string::npos){
		reply = "Cet événement a eu lieu à tout moment au cours des 3,2 derniers milliards d'années";
		return;
	}
	if(s2.find("pourquoi") != string::npos){
		reply = "Je n'ai aucune idée mec";
		return;
	}
	if(s2.find("qui") != string::npos){
		reply = "Je ne connais pas tout le monde mais je suis sûr que Donald Trump était impliqué";
		return;
	}
	if(s2.find("bonjour") != string::npos){
		reply = "Aucune idée de ce que tu me dis.";
		return;
	}
  }

  // default tell (ENGLISH) - used for casual conversattion
  void tell_casual(const string& s) {
  	
  	// making everything 
  	string s2;
	for(char c : s){
		c = tolower(c); // tolower converts every character into lower case
			s2 += c;
	}

	// Note: string::npos is the value that find returns if the substring
    // string is not found
	if (s2.find("how") != string::npos && s2.find("are") != string::npos && s2.find("you") != string::npos) {
	    // found 
	    reply = "Good, how about you?";
	    return;


    } 
    // works like the date time bot - it returns everything
    if (s2.find("time") != string::npos || s2.find("date") != string::npos){
    	time_t now= time(0); // current time as time a time_t object
		reply = ctime(&now);
		return;
	} 
	// Generic how statement (NOT INCLUDING HOW ARE YOU)
	if(s2.find("how") != string::npos){
		reply = "Find out how using google.";
		return;
	}
	// Generic what statement 
	if(s2.find("what") != string::npos){
		reply = "What do I know. Google it mate";
		return;
	}
	if(s2.find("where") != string::npos){
		reply = "It is on earth somewhere.";
		return;
	}
	if(s2.find("when") != string::npos){
		reply = "This event took place anytime in the last 3.2 billion years";
		return;
	}
	if(s2.find("why") != string::npos){
		reply = "I have no idea man.";
		return;
	}
	if(s2.find("who") != string::npos){
		reply = "I dont know everyone but I am sure Donald Trump was involved";
		return;
	}
	if(s2.find("hello") != string::npos){
		reply = "Nice to meet you";
		return;
	}
	// default reply
	reply = "No idea what you are telling me.";
  }

  // Get a string from this chatbot.
  string get_reply() {
  	cout << reply << endl << endl;;
  	return reply;
  }

  void tell(const string& s){
  	cout << "User told: " << s << endl; // prints out user tell statement/question
  	// NOTE: This bot first goes over casual words
  	// Then overwrites the replie of casual with more specified replies
  	// If found in the user string
  	tell_casual(s);
  	tell_french_edition(s);
  	tell_coronavirus_edition(s);
  	tell_politics(s);
  	tell_celebrities(s);
  	get_reply();


  }

  // virtual destructor
  ~Personal_siri() { }

};


void test_mirror_bot(){
	Mirror_bot mbot("repeato", "repeato is ready to go!");
	// testing constructor
	assert(mbot.name() == "repeato");
	assert(mbot.get_reply() == "repeato is ready to go!");
	// testing tell method (member functions of the class)
	// This is the essence of the mirror bot
	// assures that reply will be the mirror of what it was told
	mbot.tell("pikachu");
	assert(mbot.get_reply() == "pikachu");

	cout << "All tests in Mirror bot passed " << endl;

}
void test_random_bot(){

	Random_bot cat{"Mittens", {"meow", "prr", "meeeeow"}};
	string s1 = cat.get_reply();
	cout << "The reply is: " << s1 << endl;
	assert(s1 == "meow" || s1 == "prr"
 || s1 == "meeeeow");

	// Note: This must be comment out as dog_sounds.txt
	// will not necessarily exist in marker's file system
	// HOWEVER, I have tested it on my program by creating
	// a dog_sounds file and the TEST HAS PASSED.
	// NOTE: FEEL FREE TO UNCOMMENT THE BELOW CODE
	// IF U HAVE THE dog_sounds.txt file with the same contents
	// AS SHOWN IN THE ASSIGNMENT EXAMPLE

	// Random_bot dog("Fido", "dog_sounds.txt");
	// string s2 = dog.get_reply();
	// cout << "The reply is: " << s2 << endl;
	// assert(s2 == "woof" || s2 == "ruff"
 // || s2 == "yap yap yap" || s2 == "bow wow");

 cout << "All tests for random bot passed" << endl;

}

void test_user_bot(){
	User_bot user{"stan"};

	string s = user.get_reply();

	// Should equal the line of text inputted
	// HAVE MANUALLY TESTESTED DIFFERENT VALUES
	// ALL TESTS PASSED
	user.tell("something random"); 

	cout << "The last line should print out what you inputted before" << endl;
	cout << "All tests for user bot passed" << endl;
}
void test_date_bot(){
	Datetime_bot dt_bot{"deetee", {"Ask me about the date or time!",
                               "I know the date and time!"}};
    dt_bot.tell("Wahoooo");

    assert(dt_bot.get_reply() == "Ask me about the date or time!" 
    || dt_bot.get_reply() == "I know the date and time!");
    dt_bot.tell("What is the daTe");
    cout << dt_bot.get_reply() << endl; // should print out date and time
    cout << "All tests for date bot passed" << endl;
    cout << endl << endl;
}
// My Personal siri:
// Covers English and French(limited support)
// Topics Include: Politics, celebrities, casual, french causal
// AND a special CORONAVIRUS ediiton (wide variety of facts 
// and snarky comments)
// MASSIVE KEYWORD POOL - TO AVOID HITTING DEFAULT REPLY
// KEYWORDS TAKE PRECEDENCE THROUGH THE ORDER OF CALLING
// In the regular tell function

void test_personal_siri(){
	cout << endl << endl;
	cout << "WELCOME TO MY PERSONAL CIRI CREATION" << endl;
	cout << "This bot covers different areas through searcing" << endl;
	cout << "From a wide array of key words often googled" << endl;
	cout << "LANUAGES INCLUDE: ENGLISH and French(limited topics)" << endl << endl;
	Personal_siri siri1("The Better Siri");

	// MASSIVE TESTING - note it will print out output automatically
	// just by calling the tell function

	// casual
	siri1.tell("How are you");
	siri1.tell("Where is California?");
	siri1.tell("Why do people like rap music even though its horrible");
	siri1.tell("Hello, my name is Bob");
	siri1.tell("When is the next solar eclipse");
	siri1.tell("Why is it raining?");
	siri1.tell("How to make pasta?");
	siri1.tell("Is pizaa better than pasta?");
	siri1.tell("What is the date");
	siri1.tell("Tell me the time please");
	
	// french-casual
	siri1.tell("Comment ca va bien");
	siri1.tell("Bonjour");
	siri1.tell("Qui est le pola");
	siri1.tell("Pourquoi est le ciel bleu");
	siri1.tell("Comment tapple tu");
	siri1.tell("Comment sont tu");
	siri1.tell("Quelle est temps");

	// coronavirus
	siri1.tell("How to avoid the coronavirus?");
	siri1.tell("I am scared");
	siri1.tell("Fear from the coronavirus");
	siri1.tell("death rate of coronavirus");
	siri1.tell("Coronavirus prevention guide");
	siri1.tell("Economic impact of cornavirus?");
	siri1.tell("symtoms of cornavirus");
	siri1.tell("media report of coronavirus");
	siri1.tell("death toll");
	siri1.tell("Should I buy some stocks");
	siri1.tell("Panic in the media");
	siri1.tell("Breaking news about coronavirus");
	siri1.tell("Preventing coronavirus");
	

	// politics
	siri1.tell("Is Donald trump going to win?");
	siri1.tell("Should I get an abortion");
	siri1.tell("Who will win 2020 election?");
	siri1.tell("How to improve the healthcare system?");
	siri1.tell("2nd ammendment is outdated");
	siri1.tell("How to protect your guns");
	siri1.tell("racism is the worst");
	siri1.tell("family values are most important");
	siri1.tell("Nationalism is good for the country");
	siri1.tell("We are all patriots");
	siri1.tell("I am a democrat");
	siri1.tell("I am republican");
	siri1.tell("Should I have a baby");
	siri1.tell("Fetuses are living beings");



	// celebrities - singers
	siri1.tell("ariana latest songs");
	siri1.tell("taylor vs demi");
	siri1.tell("Is Ed Sheeran the best make singer");
	siri1.tell("Is Drake a good singer");
	siri1.tell("I love Beyonce");
	siri1.tell("RIP Michael Jackson");
}


int main() {
  srand(time(NULL)); // assures random seed - makes things truly random
  // unit testing for each of the bots
  // EACH BOT HAS BEEN THOROUGHLY TESTED WITH A
  // MIX OF AUTOMATED TESTING (Assert) and Manual Testing (Using cout)
  test_mirror_bot();
  test_random_bot();
  test_user_bot();
  test_date_bot();

  // testing for personal bot - all printed out on screen
  // HEAVILY TESTED USING 100's of keywords
  test_personal_siri();


}