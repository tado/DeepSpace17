#include "ObjectController.h"

ObjectController::ObjectController() {
	ugenMax = 6;
}

void ObjectController::addObject(int id) {
	if (floorObjects.size() < ugenMax) {
		int type;
		int typeNum[3] = { 0, 0, 0 };
		//set ugen type
		for (int i = 0; i < floorObjects.size(); i++) {
			typeNum[floorObjects[i]->type]++;
		}
		if (typeNum[0] < typeNum[1]) {
			type = 0;
		}
		else if (typeNum[1] < typeNum[2]) {
			type = 1;
		}
		else {
			type = 2;
		}

		FloorObject *o = new FloorObject(id, type);
		floorObjects.push_back(o);
	}
	else {
		int type = (floorObjects.size() - 6) % 5 + 3;
		FloorObject *o = new FloorObject(id, type);
		floorObjects.push_back(o);
	}
}

