/*
 * ScoreData.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#include "ScoreData.h"

ScoreData::ScoreData() {
	// TODO Auto-generated constructor stub

}

ScoreData::~ScoreData() {
	// TODO Auto-generated destructor stub
}

void ScoreData::setScoreTo0(){
	score = 0;
}
int ScoreData::getScore(){
	return score;
}
void ScoreData::winRound(){
	score += 50;
}
void ScoreData::itemScore(){
	score += 10;
}
void ScoreData::defendScore(){
	score += 5;
}
