#include "stdafx.h"
#include "Map.h"
#include "WallMap.h"

WallMap* WallMap::Create(string name)
{
	WallMap* temp = new WallMap();
	temp->type = ObType::Actor;
	return temp;
}

WallMap::WallMap() : Map()
{
	glitingBoardActiveTime = 0.5f;
	backUpGlitingBoardActiveTime = glitingBoardActiveTime;
}

WallMap::~WallMap()
{
	delete[] pillarUnderSpeed;
	delete[] upDownBoardSpeed;
	delete[] leftRightBoardSpeed;
	delete[] isPillarUnderUp;
	delete[] isUpDownBoardUp;
	delete[] isLeftRightBoardGo;
}

void WallMap::Update()
{
	for (int i = 0; i < pillarUnderList.size(); i++) {
		if (isPillarUnderUp[i]) {
			pillarUnderList[i]->MoveWorldPos(Vector3(0, 1, 0) * pillarUnderSpeed[i] * DELTA);
			if (pillarUnderList[i]->GetLocalPos().y > 7.0f) isPillarUnderUp[i] = false;
		}
		else {
			pillarUnderList[i]->MoveWorldPos(Vector3(0, -1, 0) * pillarUnderSpeed[i] * DELTA);
			if (pillarUnderList[i]->GetLocalPos().y < -7.0f) isPillarUnderUp[i] = true;
		}
	}
	for (int i = 0; i < upDownBoardList.size(); i++) {
		if (isUpDownBoardUp[i]) {
			upDownBoardList[i]->MoveWorldPos(Vector3(0, 1, 0) * upDownBoardSpeed[i] * DELTA);
			if (upDownBoardList[i]->GetLocalPos().y > 5.0f) isUpDownBoardUp[i] = false;
		}
		else {
			upDownBoardList[i]->MoveWorldPos(Vector3(0, -1, 0) * upDownBoardSpeed[i] * DELTA);
			if (upDownBoardList[i]->GetLocalPos().y < -5.0f) isUpDownBoardUp[i] = true;
		}
	}
	for (int i = 0; i < leftRightBoardList.size(); i++) {
		if (isLeftRightBoardGo[i]) {
			leftRightBoardList[i]->MoveWorldPos(Vector3(1, 0, 0) * leftRightBoardSpeed[i] * DELTA);
			if (leftRightBoardList[i]->GetLocalPos().x > 19.0f) isLeftRightBoardGo[i] = false;
		}
		else {
			leftRightBoardList[i]->MoveWorldPos(Vector3(-1, 0, 0) * leftRightBoardSpeed[i] * DELTA);
			if (leftRightBoardList[i]->GetLocalPos().x < -19.0f) isLeftRightBoardGo[i] = true;
		}
	}
	glitingBoardActiveTime -= DELTA;
	if (glitingBoardActiveTime < 0) {
		for (int i = 0; i < glitingBoardList.size(); i++) glitingBoardList[i]->visible = not glitingBoardList[i]->visible;
		glitingBoardActiveTime = backUpGlitingBoardActiveTime;
		isGlitingBoardChange = not isGlitingBoardChange;
	}

	Map::Update();
}

void WallMap::LoadFile(string _file)
{
	Map::LoadFile(_file);
	{
		int pillarUnderCount = 0;
		while (this->root->Find("Pillar1_under" + to_string(pillarUnderCount))) {
			pillarUnderList.push_back(this->root->Find("Pillar1_under" + to_string(pillarUnderCount)));
			pillarUnderList.back()->scale.y = 7;
			pillarUnderCount++;
		}
		pillarUnderCount = 0;
		while (this->root->Find("Pillar2_under" + to_string(pillarUnderCount))) {
			pillarUnderList.push_back(this->root->Find("Pillar2_under" + to_string(pillarUnderCount)));
			pillarUnderList.back()->scale.y = 7;
			pillarUnderCount++;
		}
		pillarUnderCount = 0;
		while (this->root->Find("Pillar3_under" + to_string(pillarUnderCount))) {
			pillarUnderList.push_back(this->root->Find("Pillar3_under" + to_string(pillarUnderCount)));
			pillarUnderList.back()->scale.y = 7;
			pillarUnderCount++;
		}
		pillarUnderCount = 0;
		while (this->root->Find("Pillar4_under" + to_string(pillarUnderCount))) {
			pillarUnderList.push_back(this->root->Find("Pillar4_under" + to_string(pillarUnderCount)));
			pillarUnderList.back()->scale.y = 7;
			pillarUnderCount++;
		}
		int pillarCount = 0;
		while (this->root->Find("Pillar1_" + to_string(pillarCount))) {
			pillarList.push_back(this->root->Find("Pillar1_" + to_string(pillarCount)));
			pillarList.back()->scale.y = 10;
			pillarCount++;
		}
		pillarCount = 0;
		while (this->root->Find("Pillar2_" + to_string(pillarCount))) {
			pillarList.push_back(this->root->Find("Pillar2_" + to_string(pillarCount)));
			pillarList.back()->scale.y = 10;
			pillarCount++;
		}
		pillarCount = 0;
		while (this->root->Find("Pillar3_" + to_string(pillarCount))) {
			pillarList.push_back(this->root->Find("Pillar3_" + to_string(pillarCount)));
			pillarList.back()->scale.y = 10;
			pillarCount++;
		}
		pillarCount = 0;
		while (this->root->Find("Pillar4_" + to_string(pillarCount))) {
			pillarList.push_back(this->root->Find("Pillar4_" + to_string(pillarCount)));
			pillarList.back()->scale.y = 10;
			pillarCount++;
		}
	}
	{
		int boardCount = 0;
		while (this->root->Find("GlitingBoard_" + to_string(boardCount))) {
			glitingBoardList.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
			if (boardCount < 5) {
				glitingBoardList1.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = false;
			}
			else if (boardCount < 10) {
				glitingBoardList2.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = true;
			}
			else if (boardCount < 15) {
				glitingBoardList1.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = false;
			}
			else if (boardCount < 20) {
				glitingBoardList2.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = true;
			}
			else if (boardCount < 25) {
				glitingBoardList1.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = false;
			}
			else if (boardCount < 30) {
				glitingBoardList2.push_back(this->root->Find("GlitingBoard_" + to_string(boardCount)));
				this->root->Find("GlitingBoard_" + to_string(boardCount))->visible = true;
			}
			boardCount++;
		}
	}

	int upDownBoardCount = 0;
	while (this->root->Find("UpDownBoard_" + to_string(upDownBoardCount))) {
		upDownBoardList.push_back(this->root->Find("UpDownBoard_" + to_string(upDownBoardCount)));
		upDownBoardCount++;
	}
	int leftRightBoardCount = 0;
	while (this->root->Find("LeftRightBoard_" + to_string(leftRightBoardCount))) {
		leftRightBoardList.push_back(this->root->Find("LeftRightBoard_" + to_string(leftRightBoardCount)));
		leftRightBoardCount++;
	}
	pillarUnderSpeed = new float[pillarUnderList.size()];
	upDownBoardSpeed = new float[upDownBoardList.size()];
	leftRightBoardSpeed = new float[leftRightBoardList.size()];
	isPillarUnderUp = new bool[pillarUnderList.size()];
	isUpDownBoardUp = new bool[upDownBoardList.size()];
	isLeftRightBoardGo = new bool[leftRightBoardList.size()];
	for (int i = 0; i < pillarUnderList.size(); i++) {
		pillarUnderSpeed[i] = RANDOM->Float(20, 50);
		isPillarUnderUp[i] = false;
	}
	for (int i = 0; i < upDownBoardList.size(); i++) {
		upDownBoardSpeed[i] = RANDOM->Float(10, 20);
		isUpDownBoardUp[i] = RANDOM->Int(0, 1);
	}
	for (int i = 0; i < leftRightBoardList.size(); i++) {
		leftRightBoardSpeed[i] = RANDOM->Float(70, 100);
		isLeftRightBoardGo[i] = RANDOM->Int(0, 1);
	}
}


void WallMap::LateUpdate()
{
}