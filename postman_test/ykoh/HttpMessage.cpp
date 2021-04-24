#include "HttpMessage.hpp"
#include <iostream>
#include <fstream>

// ANCHOR RequestLine class

RequestLine::RequestLine(void)
    : mMethod(UNDEFINED)
{
}

RequestLine::~RequestLine(void) {}

void	RequestLine::setMethod(char* str)
{
	// REVIEW if else if 보다 우아한 방법이 있을까..?
	if (strncmp(str, "GET", 4) == 0)
	{
		mMethod = GET;
	}
	else if (strncmp(str, "HEAD", 5) == 0)
	{
		mMethod = HEAD;
	}
	else if (strncmp(str, "POST", 5) == 0)
	{
		mMethod = POST;
	}
	else if (strncmp(str, "PUT", 4) == 0)
	{
		mMethod = PUT;
	}
	else if (strncmp(str, "DELETE", 7) == 0)
	{
		mMethod = DELETE;
	}
	else if (strncmp(str, "CONNECT", 8) == 0)
	{
		mMethod = CONNECT;
	}
	else if (strncmp(str, "OPTIONS", 8) == 0)
	{
		mMethod = OPTIONS;
	}
	else if (strncmp(str, "TRACE", 6) == 0)
	{
		mMethod = TRACE;
	}
	else
	{
		// FIXME 잘못된 메시지로 판단해야함 + exception class 만들기
		throw std::exception();
	}
}

void	RequestLine::setRequestTarget(char* str)
{
	mRequestTarget = str;
}

void	RequestLine::setHttpVersion(char* str)
{
	mHttpVersion = str;
}

void		RequestLine::setStatusCode(char* str) {}
void		RequestLine::setReasonPhrase(char* str) {}

// TODO StatusLine class

// StatusLine::StatusLine(void)
// 	: mStatusCode(0)
// {
// }

// StatusLine::~StatusLine(void) {}

// void	StatusLine::setHttpVersion(char* str)
// {
// 	mHttpVersion = str;
// }

// void	StatusLine::setStatusCode(char* str)
// {
// 	// 3digit
// 	// mStatusCode = str;
// }

// void	StatusLine::setReasonPhrase(char* str)
// {
// 	mReasonPhrase = str;
// }

// void	StatusLine::setMethod(char* str) {}
// void	StatusLine::setRequestTarget(char* str) {}




// ANCHOR HttpMessage class

HttpMessage::~HttpMessage(void)
{
}

// ANCHOR HttpMessageRequest class

HttpMessageRequest::HttpMessageRequest(char* buf)
{
    // REVIEW 메모리 할당 실패시 EXCEPTION이나 에러처리 필요해보임
    mStartLine = new RequestLine;
	messageParser(buf);
}

HttpMessageRequest::~HttpMessageRequest(void)
{
	delete mStartLine;
}

static void	eraseCR(char* token)
{
	if (token == NULL)
	{
		return ;
	}
	char*	cr = strrchr(token, '\r');
	if (cr)
	{
		*cr = '\0';
	}
}

// TODO meessageParser RFC7230에 맞춰서 디테일 파싱 진행해야함

void	HttpMessageRequest::messageParser(char* buf)
{
	// StartLine parsing
	char* token = strtok(buf, " ");
	std::cerr << "token 1 : " << token << "|" << std::endl;
	mStartLine->setMethod(token);
	token = strtok(NULL, " ");
	std::cerr << "token 2 : " << token << "|" << std::endl;
	mStartLine->setRequestTarget(token);
	token = strtok(NULL, "\n");
	eraseCR(token);
	std::cerr << "token 3 : " << token << "|" << std::endl;
	mStartLine->setHttpVersion(token);

	// HeaderField parsing
	std::cerr << std::string(10, '-') << "header field" << std::string(10, '-') << std::endl;

	while (true)
	{
		token = strtok(NULL, "\n");
		char*	colon = strchr(token, ':');
		if (colon)
		{
			*colon = '\0';
			std::string	name = token;
			colon++;
			eraseCR(colon);
			std::string	value = colon;

			// OWS trim (앞뒤 공백 자름)
			std::size_t foundFromFront = value.find_first_not_of(" ");
			if (foundFromFront == std::string::npos)
			{
				foundFromFront = 0;
			}
			std::size_t foundFromBack = value.find_last_not_of(" ");
			// REVIEW substr이 leak을 유발할수도 있으니 확인 필요 
			if (foundFromBack != value.length())
			{
				value = value.substr(foundFromFront, foundFromBack - foundFromFront + 1);
			}
			else
			{
				value = value.substr(foundFromFront, foundFromBack); // string is shorter as many as possible
			}

			mHeaderField[name] = value;
			std::cerr << name << ": " << "|" << mHeaderField[name] << "|" << std::endl;
		}
		else
		{
			break ;
		}
	}
	// TODO MessageBody parsing
	std::cerr << std::string(10, '-') << "messagebody field" << std::string(10, '-') << std::endl;
	// FIXME 버퍼 마지막을 판단할 수 있는 방법 강구해야함
	token += 2; // cr lf 넘어감
	
	// REVIEW 이 조건이 맞는지 잘 모르겠음
	if (*token)
	{
		// message body 있는 경우
		if (mHeaderField.find("content-length") != mHeaderField.end())
		{
			// content-length 가 있는 경우
			// token[std::atoi(mHeaderField["content-length"].c_str())] = '\0';
			mMessageBody.push_back(token);
		}
		else
		{
			// STUB message body가 있는데 content-length가 없는 경우가 있을까? 충분히 있을듯?
			std::cerr << "messege body : O coneent-length : X" << std::endl;
			throw std::exception();
		}
		
	}
	else
	{
		// STUB message body 없는 경우
	}
	if (mMessageBody.empty())
	{

	}
	else
	{
		std::cout << mMessageBody.at(0) << std::endl;
		std::ofstream	ofs("binarytest.png", std::ofstream::out | std::ofstream::app);

		ofs.write(mMessageBody.at(0), std::atoi(mHeaderField["content-length"].c_str()));

		ofs.close();
	}
	


}

// TODO HttpMessageResponse class

// HttpMessageResponse::HttpMessageResponse(char* buf)
// {
//     // EXCEPTION
//     mStartLine = new StatusLine;
// 	messageParser(buf);
// }

// HttpMessageResponse::~HttpMessageResponse(void)
// {
// 	delete mStartLine;
// }

// void	HttpMessageResponse::messageParser(char* buf)
// {
// 	// char* token = strtok(buf, " ");
// 	// std::cerr << "token 1 : " << token << "|" << std::endl;
// 	// mStartLine->setMethod(token);
// 	// token = strtok(NULL, " ");
// 	// std::cerr << "token 2 : " << token << "|" << std::endl;
// 	// mStartLine->setRequestTarget(token);
// 	// token = strtok(NULL, "\r\n");
// 	// std::cerr << "token 3 : " << token << "|" << std::endl;
// 	// mStartLine->setHttpVersion(token);
// }