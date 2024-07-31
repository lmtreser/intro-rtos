// code for producer (j)

// producer j is ready
// to produce an item
flag[j] = true;

// but consumer (i) can consume an item
turn = i;

// if consumer is ready to consume an item
// and if its consumer's turn
while (flag[i] == true && turn == i)
	
{ /* then producer will wait*/ }

// otherwise producer will produce
// an item and put it into buffer (critical Section)

// Now, producer is out of critical section
flag[j] = false;
// end of code for producer

//--------------------------------------------------------
// code for consumer i

// consumer i is ready
// to consume an item
flag[i] = true;

// but producer (j) can produce an item
turn = j;

// if producer is ready to produce an item
// and if its producer's turn
while (flag[j] == true && turn == j)
	
{ /* then consumer will wait */ }

// otherwise consumer will consume
// an item from buffer (critical Section)

// Now, consumer is out of critical section
flag[i] = false;
// end of code for consumer
