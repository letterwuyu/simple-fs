#ifndef _SESSION_H_
#define _SESSION_H_
class Session
{
public:
	Session(int session) : session_(session) {}
	virtual ~Session() {}
	Session(const Session& session)     : session_(session.GetSession()) {}
	Session(Session&& session) noexcept : Session_(Session.GetSession()) {}
	bool operator == (const Session& session)
	{
		return session_ == session.GetSession();
	}
	bool operator < (const Session& session)
	{
		return session_ < session.GetData();
	}
public:
	const GetSession() const
	{
		session_;
	}
private:
	int session_;
}
#endif /* _SESSION_H_ */
