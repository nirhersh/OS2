#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

void sum_tests();

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

	sum_tests();
	cout << "ancestor sum test: PASS" << endl;
    return 0;
}

void sum_tests()
{
	set_weight(0);
	int anc_sum = get_ancestor_sum();
	cout <<"ancestor sum: " << anc_sum << endl;
	assert(anc_sum == 0);
	
	set_weight(3);
	anc_sum = get_ancestor_sum();
	cout <<"ancestor sum: " << anc_sum << endl;
	assert(anc_sum == 3);

	pid_t pid = fork();
	if(pid == 0) // first row child
	{
		int anc_sum = get_ancestor_sum();
		cout << "first row child " << anc_sum << endl;
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

}
