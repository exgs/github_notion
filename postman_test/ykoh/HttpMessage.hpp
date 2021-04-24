#include <map>
#include <string>
#include <stack>

enum    eMethod
{
    UNDEFINED,
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE
};

//

class IStartLine
{
public:
    virtual ~IStartLine(void) {};

	virtual void	setMethod(char* str) = 0;
	virtual void	setRequestTarget(char* str) = 0;
	virtual void	setHttpVersion(char* str) = 0;
	virtual void	setStatusCode(char* str) = 0;
	virtual void	setReasonPhrase(char* str) = 0;
};

//

class RequestLine : public IStartLine
{
public:
    RequestLine(void);
    virtual ~RequestLine(void);
	void		setMethod(char* str); // 추 후에 함수포인터로 바뀔수도 있을 것같다. 메소드 별로 역할이 다르니..
	void		setRequestTarget(char* str);
	void		setHttpVersion(char* str);

private:
	void		setStatusCode(char* str);
	void		setReasonPhrase(char* str);

    eMethod     mMethod;
    std::string mRequestTarget;
    std::string mHttpVersion;
};

// class StatusLine : public IStartLine
// {
// public:
//     StatusLine(void);
//     virtual ~StatusLine(void);
// 	void		setHttpVersion(char* str);
// 	void		setStatusCode(char* str);
// 	void		setReasonPhrase(char* str);


// private:
// 	void		setMethod(char* str);
// 	void		setRequestTarget(char* str);

// 	std::string	mHttpVersion;
// 	int			mStatusCode;
//     std::string mReasonPhrase;
// };

///////////////////////////////////////////////////////////////////////
//Http Message class//
///////////////////////////////////////////////////////////////////////

class HttpMessage
{
public:
    virtual ~HttpMessage(void);

protected:
	virtual	void messageParser(char* buf) = 0;

    IStartLine*							mStartLine;
    std::map<std::string, std::string>	mHeaderField;
	// std::deque<uint8_t*>					mMessageBody; 	// NOTE messagebody 바꾸어야 할수도 있음 binary받기 위한 deque	
	std::deque<char*>					mMessageBody; 	// NOTE messagebody 바꾸어야 할수도 있음 binary받기 위한 deque	
	// std::string				mMessageBody; 	// NOTE messagebody 바꾸어야 할수도 있음 binary받기 위한 deque	
};

class HttpMessageRequest : public HttpMessage
{
public:
    HttpMessageRequest(char* buf); // 메모리 할당 후 startline에 넣어줌
    virtual ~HttpMessageRequest(void);

	void	messageParser(char* buf);
};

// class HttpMessageResponse : public HttpMessage
// {
// public:
//     HttpMessageResponse(char* buf); // 메모리 할당 후 startline에 넣어줌
//     virtual ~HttpMessageResponse(void);

// 	void	messageParser(char* buf);

// };
