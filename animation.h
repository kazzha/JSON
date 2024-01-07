#pragma once
#include <string>
#include <vector>

struct Frame
{
	std::string mName;
	double mDuration;
};

class Animation
{
private:
	std::string mName;
	bool mLoop;
	std::vector<Frame> mFrames;

public:
	void SetName(const std::string& name) { mName = name; }
	void SetLoop(bool Bool) { mLoop = Bool; }
	void AddFrame(const Frame& frame) { mFrames.push_back(frame); }

	std::string GetName() const { return mName; }
	bool GetLoop() { return mLoop; }
	std::vector<Frame>& GetFrames() { return mFrames; }

};