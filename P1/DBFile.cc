#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include <iostream>
#include <stdlib.h>



// stub file .. replace it with your own DBFile.cc

DBFile::DBFile () {

}

int DBFile::Create (const char *f_path, fType f_type, void *startup) {
}

void DBFile::Load (Schema &f_schema, const char *loadpath) {
}

int DBFile::Open (const char *f_path) {
	myFile.Open(0,(char *) f_path);
	pageBuffer = new Page();
}

void DBFile::MoveFirst () {
	//recPointer = (*pageBuffer).FirstRecordPointer();

	off_t numOfPages = myFile.GetLength();
	Record rec;
	if (numOfPages == 0) {
		myFile.AddPage(pageBuffer, 0);
		pageBuffer->EmptyItOut();
	}
		Page p;
		myFile.GetPage(&p, 0);
		readPagePointer = &p;
		p.GetFirst(&rec);
		recPointer = &rec;
		pageIndex = 0;
	
		

}

int DBFile::Close () {
	//myFile.AddPage(pageBuffer,0);
	cout << myFile.GetLength();
	//Page p1;
	//Record t2;
	Schema mySchema("catalog", "lineitem");
	//myFile.GetPage(&p1, 0);
	//while (p1.GetFirst(&t2)) {
	//	//t2.Print(&mySchema);
	//	//cout << endl;
	//}

	/*Page p2;
	Record t3;
	myFile.GetPage(&p2, 0);*/
	//myFile.AddPage(&p2, 1);

	cout << "Start" << endl;
	Page page1;
	Record rec1;
	myFile.GetPage(&page1, -22);
	while (page1.GetFirst(&rec1)) {
		rec1.Print(&mySchema);
		cout << endl;
	}
	/*cout << "mid" << endl;
	Page page2;
	Record rec2;*/
	/*myFile.GetPage(&page2, 1);
	while (page2.GetFirst(&rec2)) {
		rec2.Print(&mySchema);
		cout << endl;
	}*/
	cout << "done" << endl;

	cout << myFile.GetLength();
}

void DBFile::Add (Record &rec) {
	Record *temp = &rec;
	//cout << "1";
	off_t numOfPages = myFile.GetLength();

	numOfPages = (numOfPages == 0) ? 0 : numOfPages - 1;
	//cout << numOfPages << endl;
	//cout << "2";
	int status = (pageBuffer)->Append(&rec);
	//cout << status<<endl;
	if(status==1){
		return;
	}
	else  //When there is no space to store the current record in the buffer page
	{
		//Copy buffer to file
		myFile.AddPage(pageBuffer, numOfPages);
		//empty the buffer
		pageBuffer->EmptyItOut();
		//Now append record to the buffer
		(*pageBuffer).Append(temp);	//What if record size is greater than page size
	}
}

int DBFile::GetNext (Record &fetchme) {
	off_t numOfPages = myFile.GetLength();
	   	 
	if (numOfPages == 0) {
		
		MoveFirst();
		Record temp;
		temp = *recPointer;
		fetchme = temp;

		Record rec;
		int status = readPagePointer->GetFirst(&rec);
		if (status==0) {
			return 0;
		}
		else {
			recPointer = &rec;
			return 1;
		}
	}
	else if () {
		Record temp;
		temp = *recPointer;
		fetchme = temp;

		Record rec;
		int status = readPagePointer->GetFirst(&rec);
		if (status == 0) {
			myFile.GetLength();
			pageIndex = //todo
		}
		else {
			recPointer = &rec;
			return 1;
		}
	}
}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {
}
