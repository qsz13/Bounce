/*
 * ScoreData.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#include "ScoreData.h"

int ScoreData::score;
int ScoreData::highScore;
bool ScoreData::gameIsOver = false;
ScoreData::ScoreData() {

}

ScoreData::~ScoreData() {
}

void ScoreData::setScoreTo0() {
	score = 0;
}
int ScoreData::getScore() {
	return score;
}
void ScoreData::winRound() {
	score += 50;
}
void ScoreData::itemScore() {
	score += 10;
}
void ScoreData::defendScore() {
	score += 5;
}
