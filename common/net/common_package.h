#ifndef _COMMON_PACKAGE_H__
#define _COMMON_PACKAGE_H__
class CommonPackage {
public:
	CommonPackage(void* pevent = nullptr, void* pdata = nullptr);
	~CommonPackage();
public:
	void 		SetEvent(void* pevent);
	void*		GetEvent(void); 
	void 		SetData(void* pdata);
	void*     	GetData(void);
private:
	void* pevent_;
	void* pdata_;
};
#endif //_COMMON_PACKAGET_H__
