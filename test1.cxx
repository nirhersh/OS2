#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

void sum_tests();
void heaviest_descendant_test();

/*..................................... README .........................................*/
/*
to run this test you need to run the test
if you think we are wrong pls be 100% sure before contacting us
roei.bloch@yourMOM.ac.techion.il
nice to meet you.
have a good one lol.

				composed by the half milion test composers - Nir & Roei
*/

using namespace std;

int main() {
    int x = get_weight();
	cout << "weight: " << x << endl;
	assert(x == 0);
    x = set_weight(5);
	cout << "set_weight returns: " << x << endl;
	assert(x == 0);
    x = get_weight();
	cout << "new weight: " << x << endl;
	assert(x == 5);
    cout << "set & get test: PASS" << endl;

	heaviest_descendant_test();
	cout << "heaviest descendant test: PASS" << endl;

	sum_tests();
	cout << "ancestor sum test: PASS" << endl;

	
    return 0;
}

void sum_tests()
{
	set_weight(0);
	int anc_sum = get_ancestor_sum();
	assert(anc_sum == 0);
	
	set_weight(3);
	anc_sum = get_ancestor_sum();
	assert(anc_sum == 3);

	pid_t pid = fork();
	if(pid == 0) // first row child
	{
		int anc_sum = get_ancestor_sum();
		assert(anc_sum == 6);
		set_weight(5);
		assert(get_ancestor_sum() == 8);
		pid_t pid1 = fork();
		if(pid1 == 0){ // second row child
			assert(get_ancestor_sum() == 13);
			set_weight(0);
			assert(get_ancestor_sum() == 8);
			while(1);
		}
		while(1);
	} else { // daddy
		assert(get_ancestor_sum() == 3);
		pid_t pid2 = fork();
		if(pid2 == 0){ // second child first row
			assert(get_ancestor_sum() == 6);
			set_weight(10);
			assert(get_ancestor_sum() == 13);
			while(1);
		}
	}
	sleep(5);
}

void heaviest_descendant_test()
{
	set_weight(0);
	int dec_hav = get_heaviest_descendant();
	assert(dec_hav == -ECHILD);	
	pid_t pid1 = fork();
	if(pid1 == 0)
	{
		sleep(7); //after the assert of the 1 father 2 sons happpens
		pid_t pid3 = fork();
		if(pid3 == 0) // second row first child
		{
			assert(get_heaviest_descendant() == -ECHILD);
			set_weight(10);
		} else {
			sleep(2);
			assert(get_heaviest_descendant() == pid3);
		}

		while(1);
	} else {
		assert(get_heaviest_descendant() == pid1);
		pid_t pid2 = fork();
		if(pid2 == 0) //first row second child
		{
			set_weight(4);
			while(1);
		} else {
			sleep(2);
			assert(get_heaviest_descendant() == pid2);\
			sleep(10); //it will take some time. 
			int last_test_haha;
			last_test_haha = get_heaviest_descendant();
			assert(last_test_haha != pid1 && last_test_haha != pid2 && last_test_haha != -ECHILD);
		}

	}

}