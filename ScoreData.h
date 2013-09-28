/*
 * ScoreData.h
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#ifndef SCOREDATA_H_
#define SCOREDATA_H_

class ScoreData {
public:
	ScoreData();
	virtual ~ScoreData();

	static void setScoreTo0();
	static int getScore();
	static void winRound();
	static void itemScore();
	static void defendScore();
	static int highScore;
	static bool gameIsOver;
private:
	static int score;


};

#endif /* SCOREDATA_H_ */
