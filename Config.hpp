#ifndef CONFIG_HPP
# define CONFIG_HPP

// NOTE Configuration 파일의 Server Block 밖 정보들을 저장한다. ServerManager 객체의 멤버 변수로 사용된다
class Config
{
public:
	Config(config_block, env);

	const std::string&	get_m_software_name(void) const;
	const std::string&	get_m_softwrae_version(void) const;
	const std::string&	get_m_http_version(void) const;
	const std::string&	get_m_cgi_version(void) const;
	const char**		get_m_base_env(void) const;

private:
	std::string			m_software_name;
	std::string			m_software_version;
	std::string			m_http_version;
	std::string			m_cgi_version;
	char**				m_base_env;
};

#endif