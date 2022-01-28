#ifndef _ROBOCATMATH_H_
#define _ROBOCATMATH_H_
#pragma once


class RoboCat {
public:
	RoboCat() :mHealth(10), mMewCount(3) {
		mName[0] = '\0';
	}
	void Write(OutputMemoryStream& inStream)const {
		inStream.Write(mHealth);
		inStream.Write(mMewCount);
		inStream.Write(mName, strlen(mName));
		//inStream.Write(mMiceIndice);
	}
	void Read(InputMemoryStream& outStream) {
		outStream.Read(mHealth);
		cout << "\nmHealth: " << mHealth;
		outStream.Read(mMewCount);
		cout << "\nmMewCount: " << mMewCount;
		outStream.Read(mName, strlen(mName));
		//outStream.Read(mMiceIndices);
	}
private:
	int32_t mHealth;
	int32_t mMewCount;
	char mName[128];
	vector<int32_t> mMiceIndices;
};

#endif // !_ROBOCATMATH_H_


