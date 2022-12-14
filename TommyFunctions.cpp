#pragma once
using namespace TommyLogic;

/*
TRUTH TABLE

AND----OR----NAND----NOR----XNOR----XOR
00 0   00 0  00 1    00 1   00 1    00 0
01 0   01 1  01 1    01 0   01 0    01 1
10 0   10 1  10 1    10 0   10 0    10 1
11 1   11 1  11 0    11 0   11 1    11 0

*/

//1 YES, 2 NOT, 3 AND, 4 OR, 5 DELAY

void TommyLogic_Circular_Dependency_Test() {
	//TESTING RECURSIVE GATES
	LogicGate obj1("obj1"), obj2("obj2"), obj3("obj3"), obj4("obj4"), obj5("obj5"), obj6("obj6"), obj7("obj7"), obj8("obj8"), obj9("obj9");

	obj1.assignFunctions(1);//YES
	obj2.assignFunctions(1);//YES
	obj3.assignFunctions(2);//NOT
	obj4.assignFunctions(3);//AND
	obj5.assignFunctions(3);//AND
	obj6.assignFunctions(4);//OR
	obj7.assignFunctions(5);//DELAY
	obj8.assignFunctions(5);//DELAY
	obj9.assignFunctions(1);//YES

	obj3.input({ &obj1 });
	obj4.input({ &obj3,&obj7 });
	obj5.input({ &obj1,&obj2 });
	obj6.input({ &obj4,&obj5 });
	obj7.input({ &obj6 });
	obj8.input({ &obj7 });
	obj9.input({ &obj8 });

	UseGate gate(&obj9);
	gate.toggleDebugMode_Connected(5);

	SplitGate testgate(&obj9);
	testgate.printSpecialNodes();
	testgate.printSplits();

	obj9.call();

	gate.clear();

	gate.setTick(5);


	cout << endl << "=====TICK?=====" << endl;
	for (int i = 0; i < gate.CurrentObjArr.size(); i++) {
		cout << gate.CurrentObjArr[i]->Name << ": " << gate.CurrentObjArr[i]->Tick << endl;
	}

	obj1.inputarr({ {0,1},{1,0},{0,1} });
	obj2.inputarr({ {1,0},{0,1},{1,0} });
	gate.activate({ &obj1,&obj2 });

	gate.printAll();



	/* print whether other objs have received the Input Obj list
	for (int i = 0; i < gate.CurrentObjArr.size(); i++) {
		cout << gate.CurrentObjArr[i]->Name << ": ";
		for (int j = 0; j < gate.CurrentObjArr[i]->ObjInputList.size(); j++) {
			cout << gate.CurrentObjArr[i]->ObjInputList[j]->Name << " ";
		}cout << endl;
	}
	*/

	/* print whether other objs have received the CurrentObjArr list
	for (int i = 0; i < gate.CurrentObjArr.size(); i++) {
		cout << gate.CurrentObjArr[i]->Name << ": ";
		for (int j = 0; j < gate.CurrentObjArr[i]->AllObj.size(); j++) {
			cout << gate.CurrentObjArr[i]->AllObj[j]->Name << " ";
		}cout << endl;
	}
	*/

	/* print to check the FirstDelayNode conditions for all gates
	for (int i = 0; i < gate.CurrentObjArr.size(); i++) {
		cout << gate.CurrentObjArr[i]->Name << ": " << gate.CurrentObjArr[i]->FirstDelayNode;
		cout << endl;
	}
	*/
	
}

void TommyLogic_Legacy_Non_Circular_Depending_Test() {

	LogicGate obj1("obj1"), obj2("obj2"), obj3("obj3"), obj4("obj4"), obj5("obj5"), obj6("obj6"), obj7("obj7"), obj8("obj8"), obj9("obj9");

	obj1.assignFunctions(1);//YES
	obj2.assignFunctions(1);//YES
	obj3.assignFunctions(3);//AND
	obj4.assignFunctions(3);//AND
	obj5.assignFunctions(2);//NOT
	obj6.assignFunctions(2);//NOT
	obj7.assignFunctions(1);//YES
	obj8.assignFunctions(1);//YES
	obj9.assignFunctions(1);//YES

	obj3.input({ &obj1,&obj2 });
	obj4.input({ &obj2 });

	obj5.input({ &obj3 });
	obj6.input({ &obj4 });
	obj7.input({ &obj5 });
	obj8.input({ &obj6 });
	obj9.input({ &obj7, &obj8 });

	UseGate gate(&obj9);
	gate.toggleDebugMode_Connected(5);

	SplitGate testgate(&obj9);
	testgate.printSpecialNodes();
	testgate.printSplits();

	obj1.input(1);
	obj2.input(1);

	obj9.call();

	gate.printAll();
}

void TommyCounter_Test() {
	string test;
	getline(cin, test);
	TommyCounter CountingTest(test);
	cout << CountingTest.CountCommas() << endl;
	cout << CountingTest.getNumberOfEnters();
}

void FunctionalGate_Test() {

	FunctionalGate obj1("g1"), obj2("g2"), obj3("g3");

	obj1.input({ &obj2 });
	obj2.input({ &obj3 });
	obj3.input({ &obj1 });

	obj1.input(1,{1,2,3,4});
	obj2.input(1,{3,2,1});
	obj3.input(1,{0,0,0,0,0,999,1});

	obj1.setLoopLimit(0);
	obj1.initialize();

	obj1.setLoopLimit(5);
	obj1.run();

	for (int i = obj1.CachGates.size()-1; i >= 0 ; i--) {
		obj1.CachGates[i]->print_looped_results();
	}

}