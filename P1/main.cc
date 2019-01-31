
#include <iostream>
#include "Record.h"
#include "DBFile.h"
#include <stdlib.h>
using namespace std;

extern "C" {
	int yyparse(void);   // defined in y.tab.c
}

extern struct AndList *final;

int main() {

	// try to parse the CNF
	cout << "Enter in your CNF: ";
	if (yyparse() != 0) {
		cout << "Can't parse your CNF.\n";
		exit(1);
	}

	// suck up the schema from the file
	Schema lineitem("catalog", "lineitem");

	// grow the CNF expression from the parse tree 
	CNF myComparison;
	Record literal;
	myComparison.GrowFromParseTree(final, &lineitem, literal);

	// print out the comparison to the screen
	myComparison.Print();

	// now open up the text file and start procesing it
	FILE *tableFile = fopen("lineitem.tbl", "r");

	Record temp;
	Schema mySchema("catalog", "lineitem");
	//char *bits = literal.GetBits ();
	//cout << " numbytes in rec " << ((int *) bits)[0] << endl;
	//literal.Print (&supplier);

		// read in all of the records from the text file and see if they match
	// the CNF expression that was typed in
	int counter = 0;
	ComparisonEngine comp;
	Record testRecord, t1, t2;
	Page testPage, testPage2;
	File testFile;

	/*while (temp.SuckNextRecord(&mySchema, tableFile) == 1) {
		counter++;
		if (counter % 10000 == 0) {
			cerr << counter << "\n";
		}
		if (comp.Compare(&temp, &literal, &myComparison))
			//temp.Print (&mySchema);
			//testPage.Append(&temp);

	}

	char name = 'i';
	Page testPage3;

	/*testFile.Open(0, &name);
	testFile.AddPage(&testPage, 0);
	testFile.GetPage(&testPage2,0);
	while (testPage2.GetFirst(&t1)) {
		t1.Print(&mySchema);
	}

	cout << "Done printing first set" << "\n" << endl;
		testFile.GetPage(&testPage3, 0);
		while (testPage3.GetFirst(&t2)) {
			t2.Print(&mySchema);
		}*/
	char name = 'i';
	DBFile db1;
	db1.Open(&name);
	while (temp.SuckNextRecord(&mySchema, tableFile) == 1) {
		if (comp.Compare(&temp, &literal, &myComparison)){
			db1.Add(temp);
			//temp.Print(&mySchema);
		}
		
	}
	db1.Close();

	//db1.MoveFirst();
	
/*	File f1;
	char name2 = 'j';
	Page testPage4;
	Page testPage5;
	f1.Open(0,&name2);

	
	while (temp.SuckNextRecord(&mySchema, tableFile) == 1) {

		counter++;
		if (counter % 10000 == 0) {
			cerr << counter << "\n";
		}
		if (comp.Compare(&temp, &literal, &myComparison)) {
			temp.Print(&mySchema);
			testPage4.Append(&temp);
			testPage5.Append(&temp);
		}
	}
	f1.AddPage(&testPage4, 0);

	f1.AddPage(&testPage5, 1);

	Page pg1, pg2;
	f1.GetPage(&pg1, 0);
	f1.GetPage(&pg2, 1);
	Record t5,t3;

	while (pg1.GetFirst(&t5)) {
		t5.Print(&mySchema);
		cout << endl;
	}

	cout <<endl<<"*******************************" <<endl;

	while (pg2.GetFirst(&t3)) {
		t3.Print(&mySchema);
		cout << endl;
	}

	*/

}




