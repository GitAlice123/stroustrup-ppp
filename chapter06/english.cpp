/*
GRAMMAR
=======

Sentence:
    Noun Verb
    Article Noun Verb
    Sentence Conjunction Sentence

Conjunction:
    "and"
    "or"
    "but"

Noun:
    "birds"
    "fish"
    "C++"

Verb:
    "rules"
    "fly"
    "swim"

Article:
    "the"
*/
#include "../text_lib/std_lib_facilities.h"

//----------------------------------------------------------------------

class string_stream
{
public:
    string_stream();
    string get();
    void putback(string);

private:
    bool full;
    string buffer;
};

//---------------------------------------------------------------------

string_stream::string_stream()
    : full(false), buffer("")
{
}

//----------------------------------------------------------------------

void string_stream::putback(string s)
{
    if (full)
        error("putback() into a full buffer");
    buffer = s;  // copy s to buffer
    full = true; // buffer is now full
}

//---------------------------------------------------------------------

string string_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    string s;
    if(cin.peek()=='\n') return "error";
    cin >> s;
    return s;
}

//--------------------------------------------------------------------

string_stream ss;

//---------------------------------------------------------------------

bool Conjunction()
{
    string s = ss.get();
    if(s=="error") error("Missing conjunction");
    if (s == "and" || s == "or" || s == "but")
    {
        return true;
    }
    ss.putback(s);
    return false;
}

//---------------------------------------------------------------------

bool Noun()
{
    string s = ss.get();
    if(s=="error") error("Missing noun");   
    if (s == "birds" || s == "fish" || s == "C++")
    {
        return true;
    }
    ss.putback(s);
    return false;
}

//---------------------------------------------------------------------

bool Verb()
{
    string s = ss.get();
    if(s=="error") error("Missing verb");
    if (s == "rules" || s == "fly" || s == "swim")
    {
        return true;
    }
    ss.putback(s);
    return false;
}

//---------------------------------------------------------------------

// if there is a 'the', read in it, otherwise do nothing
void Article()
{
    string s = ss.get();
    if (s != "the")
        ss.putback(s);
}

//--------------------------------------------------------------------

bool Dot()
{
    string s = ss.get();
    if(s=="error") error("Missing dot");
    if (s == ".")
    {
        ss.putback(s);
        return true;
    }
    ss.putback(s);
    return false;
}

//---------------------------------------------------------------------

// read in a sentence and check whether it is right
bool sentence()
{
    /*
    Sentence:
    Noun Verb
    Article Noun Verb
    Sentence Conjunction Sentence
    */
    Article();
    if (!Noun())
        return false;
    if (!Verb())
        return false;
    if (Dot())
        return true;
    if (Conjunction() && sentence())
        return true;

    return false;
}

//----------------------------------------------------------------------

int main()
{
    try
    {
        while (cin)
        {
            string s = ss.get();
            if (s == "q")
                break;
            if (s == ".")
                cout << "OK\n";
            else
            {
                ss.putback(s);
                if (!sentence()||cin.peek() == '\n'){
                    cout << "not OK\n";
                    break;
                }
            }
        }
        keep_window_open();
    }
    catch (exception &e)
    {
        cerr << "error: " << e.what() << '\n';
        keep_window_open();
        return 1;
    }
    catch (...)
    {
        cerr << "Oops: unknown exception!\n";
        keep_window_open();
        return 2;
    }
}