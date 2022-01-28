
#ifndef _MEMORYSTREAM_H_
#define _MEMORYSTREAM_H_
#pragma once
class OutputMemoryStream {
public:
	OutputMemoryStream() :mBuffer(nullptr), mHead(0), mCapacity(0) { ReallocBuffer(32); };
	~OutputMemoryStream() { free(mBuffer); };
	const char* GetBufferPtr() const { return mBuffer; };
	uint32_t GetLength()const { return mHead; };

	void Write(const void* inData, size_t inByteCount);
	template<typename T> void Write(const T& inData);

private:
	void ReallocBuffer(uint32_t inNewLength);
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};
void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength) {
	mBuffer = static_cast<char*>(realloc(mBuffer, inNewLength));
	mCapacity = inNewLength;
}
void OutputMemoryStream::Write(const void* inData, size_t inByteCount) {
	//공간 충분히 확보
	uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity)
		ReallocBuffer(max(mCapacity * 2, resultHead));
	memcpy(mBuffer + mHead, inData, inByteCount);
	mHead = resultHead;
}
template<typename T>void OutputMemoryStream::Write(const T& inData) {
	static_assert(is_arithmetic<T>::value || is_enum<T>::value, "Generic Write only supports primitive data types");
	Write(&inData, sizeof(inData));
}



class InputMemoryStream {
public:
	InputMemoryStream(char* inBuffer, uint32_t inByteCount) :
		mBuffer(inBuffer), mCapacity(inByteCount), mHead(0) {};
	~InputMemoryStream() { std::free(mBuffer); }
	const char* GetBufferPtr() const { return mBuffer; };
	uint32_t GetLength()const { return mHead; };
	void Read(void* outData, size_t inByteCount);
	template<typename T> void Read(T& outData);
private:
	void ReallocBuffer(uint32_t inNewLength);
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};
void InputMemoryStream::ReallocBuffer(uint32_t inNewLength) {
	mBuffer = static_cast<char*>(realloc(mBuffer, inNewLength));
	mCapacity = inNewLength;
}
void InputMemoryStream::Read(void* outData, size_t inByteCount) {
	uint32_t resultHead = mHead + inByteCount;
	if (resultHead > mCapacity)
	{
		//handle error, no data to read!
		//...
	}

	std::memcpy(outData, mBuffer + mHead, inByteCount);

	mHead = resultHead;
}
template<typename T> void InputMemoryStream::Read(T& outData) {
	static_assert(is_arithmetic<T>::value || is_enum<T>::value, "Generic Write only supports primitive data types");
	Read(&outData, sizeof(outData));
}
#endif // !_MEMORYSTREAM_H_
