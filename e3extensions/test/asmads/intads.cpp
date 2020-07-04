#include <iostream>
#include <random>

using namespace std;

// Driver program to test above functions
int main()
{
    unsigned no_ads = 1<<9;
    unsigned distance = rand();
    unsigned distance_squared = distance * distance;
    unsigned user [2] = { rand(), rand() };
    unsigned ad_N [no_ads];
    unsigned ad_E [no_ads];
    for ( size_t i=0; i<no_ads; i++ )
    {
        ad_N[i] = rand();
        ad_E[i] = rand();
    }
    unsigned show_ad [no_ads];
    asm("l.debug");
    for (int i = 0; i < no_ads; i++)
    {
        show_ad[i] = ((user[0] - ad_N[i]) * (user[0] - ad_N[i]) + (user[1] - ad_E[i]) * (user[1] - ad_E[i])) < (distance_squared);
    }
    asm("l.debug");
    // Print out which advertised events are within the distance from the user. //
    cout << "Advertisements relevant to the user's location:\n";
    for (int i = 0; i < no_ads; i++)
    {
        cout << show_ad[i] << " ";
    }
	cout << "\n";
}
